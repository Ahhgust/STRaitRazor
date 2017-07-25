/*
MIT License

Copyright (c) [2017] [August E. Woerner]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
  This is a mixture of C/C++ that parses a config file...
  Written by August Woerner
  Sept. 20th, 2016
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <algorithm>

using namespace std;

#include "trie.h"  
#include "str8.h"
#include "lookup.h"

// comments in the config file
#define COMMENT '#'
// and the seperator
#define SEP '\t'


bool
validDNAWithAmbiguities(const char* c) {

    while (*c) {
      if (*c != 'A' && *c != 'C' && *c != 'T' && *c != 'G' && 
	  *c != 'R' && *c != 'Y' && *c != 'S' && *c != 'W' && *c != 'K' && *c != 'M')
	return false;
      ++c;
    }
    return true;
}

bool
validDNA(const char* c) {

    while (*c) {
      if (*c != 'A' && *c != 'C' && *c != 'T' && *c != 'G')
	return false;
      ++c;
    }
    return true;
}


// reads in a config filename *char*)
// and returns a vector of locus configurations
vector<Config>*
parseConfig(char *file, unsigned *numStrs, char *filt) {


  if (file==NULL) {
    cerr << "Empty filename for the config file detected..." << endl;
    exit(EXIT_FAILURE);
  }


  ifstream myfile(file);
  
  if (! myfile.is_open() ) {
    cerr << "Failed to open " << file << " for reading" << endl;
    exit(EXIT_FAILURE);
  }
  
  vector<Config> *c = new vector<Config>;

  string line;
  *numStrs=0;
  
  while (getline(myfile, line)) {
    if (line[0] == COMMENT)
      continue;

    Config conf;
    conf.forwardCount=1; // defaults
    conf.reverseCount=1;

    stringstream ss(line);

    getline(ss, conf.locusName, SEP);
    getline(ss, conf.markerType, SEP);
    getline(ss, conf.forwardFlank, SEP);
    getline(ss, conf.reverseFlank, SEP);
    getline(ss, conf.strMotif, SEP);

    if (filt != NULL) {
      const char *type = conf.markerType.c_str();
      const char *f = filt;
      while (*f && *type) {
	if (*f != *type)
	  break;

	++f;
	++type;
      }
      if (*f && *type)
	continue; // grab the next record from the configuration file
    }

    // quantifier is tacked to the end
    // assume it's, EG:
    // GGATTTCCCCC,2   
    char lastChar = conf.forwardFlank[ conf.forwardFlank.length() -1];
    if (lastChar >= '0' && lastChar <= '9') {
      conf.forwardCount = lastChar - '0';
      conf.forwardFlank.resize( conf.forwardFlank.length() - 2);
    }

    lastChar = conf.reverseFlank[ conf.reverseFlank.length() -1];

    if (lastChar >= '0' && lastChar <= '9') {
      conf.reverseCount = lastChar - '0';
      conf.reverseFlank.resize( conf.reverseFlank.length() - 2);
    }

    conf.motifLength = conf.strMotif.length();
    conf.forwardLength = conf.forwardFlank.length();
    conf.reverseLength = conf.reverseFlank.length();

    if (conf.motifLength < 1 || conf.forwardLength < 1 || conf.reverseLength < 1) {
      cerr << "Problem with the lengths for locus:" << endl <<
	conf.locusName << endl;
    }
    
    if (! validDNAWithAmbiguities( conf.forwardFlank.c_str() ) ) {
	cerr << "Locus " << conf.locusName << " has illegal characters in " <<
	  conf.forwardFlank << endl;
	exit(EXIT_FAILURE);
    }


    if (! validDNAWithAmbiguities( conf.reverseFlank.c_str() ) ) {
	cerr << "Locus " << conf.locusName << " has illegal characters in " <<
	  conf.reverseFlank << endl;
	exit(EXIT_FAILURE);
    }
      
    if (! validDNA( conf.strMotif.c_str() ) ) {
	cerr << "Locus " << conf.locusName << " has illegal characters in motif " <<
	  conf.strMotif << endl;
	exit(EXIT_FAILURE);
    }

    // parsing integers (period and offset)
    string s;
    getline(ss, s, SEP);
    istringstream(s)  >>   conf.motifPeriod;

    getline(ss, s, SEP);
    istringstream(s)  >>   conf.motifOffset;

    if (conf.motifPeriod < 1 || conf.motifOffset < 1) {
      cerr << "Locus " << conf.locusName << " has illegal spacing characteristics " <<
	conf.motifPeriod << "\t" << conf.motifOffset  << endl;
	exit(EXIT_FAILURE);
    }

    c->push_back(conf);

    ++(*numStrs);
  }

  
  return c;
}


#if 0
int
main(int argc, char **argv) {

  unsigned howmany=0;
  vector<Config> *c = parseConfig(argv[1], &howmany);


  Trie trie;
  trie.makeTrieFromConfig(c, howmany);
  for (unsigned i=0; i < howmany; ++i) {
    if (! trie.existsPrefixMatch( c->at(i).strMotif.c_str(), c->at(i).motifLength, i, MOTIF)) {
      cerr <<"Un problemA\n";

    }

    string rev = c->at(i).strMotif;
    reverse( rev.begin(), rev.end() );
    for (unsigned j=0; j < c->at(i).motifLength; ++j) {
      if (rev[j] == 'A') {
	rev[j] = 'T';
      } else if (rev[j] == 'T') {
	rev[j] = 'A';
      }else if (rev[j] == 'G') {
	rev[j] = 'C';
      } else if (rev[j] == 'C') {
	rev[j] = 'G';
      }
    }
    if (! trie.existsPrefixMatch( rev.c_str(), c->at(i).motifLength, i, MOTIF_RC)) {
      cerr <<"Un backwards problemA\n";
    }

  }
  
  delete c;
  return 0;
}
#endif

