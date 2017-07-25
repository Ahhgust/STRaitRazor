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


#include <iostream>
#include <stdlib.h>

#include "constants.h"
#include "trie.h"
#include "lookup.h"


using namespace std;

/*
  Takes in a binaryword w of length wordLen
  and it returns the number of prefixes (anchors) that match;
  ie, if the anchor added in addWord is a prefix of w
  The IDs of these matches are added to *out, ordered by the length of the prefix match (length is not recorded)
 */

Trie::Trie() {
  root=NULL;
  numNodes=0;
}


unsigned
Trie::findPrefixMatch(const char *w, unsigned wordLen, unsigned *outId, unsigned char *outType) {
  unsigned i, numHits=0;
  
  char c;
  TrieNode *parent, *child;
  parent = root;
  
  // traverse the tree, 
  for (i=0; i < wordLen && *w; ++i, ++w) {

    if (parent->id != NULL) {
      int size = parent->id->size();
      for ( int i = 0; i < size; ++i) {
	++numHits;
	*outType++ = parent->type->at(i);
	*outId++ = parent->id->at(i);
      }
    }


    c = *w;
    if (c == 'A') {
      if (parent->a == NULL) {
	return numHits;
      }
      child = parent->a;
    } else if (c == 'C') {
      if (parent->c == NULL) {
	return numHits;
      }
      child = parent->c;
    } else if (c == 'G') {
      if (parent->g == NULL) {
	return numHits;
      }
      child = parent->g;
    } else {
      if (parent->t == NULL) {
	return numHits;
      }
      child = parent->t;
    }
    
    parent = child;
  }

  // this is a corner case....
  // the entire binaryword matches the entire anchor sequence

  if (parent->id != NULL) {
    int size = parent->id->size();
    for ( int i = 0; i < size; ++i) {
      ++numHits;
      *outType++ = parent->type->at(i);
      *outId++ = parent->id->at(i);
    }
  }

  return numHits;
}




bool
Trie::existsPrefixMatch(const char *w, unsigned wordLen, unsigned outId, unsigned char outType) {

  unsigned i;
  char c;
  TrieNode *parent, *child;
  parent = root;
  
  // traverse the tree, 
  for (i=0; i < wordLen && *w; ++i, ++w) {

    if (parent->id != NULL) {
      int size = parent->id->size();
      for ( int i = 0; i < size; ++i) {
	if ( parent->type->at(i) == outType &&
	     parent->id->at(i) == outId)
	  return true;
      }
    }


    c = *w;
    if (c == 'A') {
      if (parent->a == NULL) {
	return false;
      }
      child = parent->a;
    } else if (c == 'C') {
      if (parent->c == NULL) {
	return false;
      }
      child = parent->c;
    } else if (c == 'G') {
      if (parent->g == NULL) {
	return false;
      }
      child = parent->g;
    } else {
      if (parent->t == NULL) {
	return false;
      }
      child = parent->t;
    }
    
    parent = child;
  }

  // this is a corner case....
  // the entire binaryword matches the entire anchor sequence

  if (parent->id != NULL) {
    int size = parent->id->size();
    for ( int i = 0; i < size; ++i) {
	if ( parent->type->at(i) == outType &&
	     parent->id->at(i) == outId)
	  return true;
    }
  }

  return false;
}


// this allocates the memory for the trie
// AND it initializes the nodes to NULL
void
Trie::initMem(unsigned num_nodes) {
  
  unsigned i;
  mem = new TrieNode[num_nodes];
  TrieNode *head = mem;
  for (i=0; i < num_nodes; ++i, ++head) {
    (*head).a =     (*head).c =    (*head).g =     (*head).t = NULL;
    (*head).id = NULL;
    (*head).type = NULL;
  }

  numNodes = num_nodes;
  root = mem;
  
}



// nonrecursive implementation;
// it takes in a word of length wordLen
// and a unique identifier (index in the config)
// as well as the current root of the suffix trie, as well as a memory pool
// and it adds w to the suffix trie.
// note that w *must* be unique!!

void
Trie::addWord(const char *w, unsigned wordLen, unsigned id, unsigned char type) {
  
  unsigned i;
  char c;
  TrieNode *parent, *child;
  parent = root;

  //  cout << w << "\t" << mem - root << "\t";

  // traverse the tree, allocing as needed
  for (i=0; i < wordLen && *w; ++i, ++w) {
    c = *w;
    if (c == 'A') {
      if (parent->a == NULL) {
	parent->a = ++mem;
      }
      child = parent->a;
    } else if (c == 'C') {
      if (parent->c == NULL) {
	parent->c = ++mem;
      }
      child = parent->c;
    } else if (c == 'G') {
      if (parent->g == NULL) {
	parent->g = ++mem;
      }
      child = parent->g;
    } else {
      if (parent->t == NULL) {
	parent->t = ++mem;
      }
      child = parent->t;
    }
    
    parent = child;
  }

  if (parent->id == NULL) {
    parent->id = new vector<unsigned>;
    parent->type = new vector<unsigned char>;
    parent->id->push_back(id);
    parent->type->push_back(type);
  } else {
    // ensure that each type/id pair is only added once    
    for (i=0; i < parent->id->size(); ++i) {
      if (parent->id->at(i) == id &&
	  parent->type->at(i) == type)
	return;
    }

    parent->id->push_back(id);
    parent->type->push_back(type);    



  }


  
}

// this adds the reverse complement of a word to the trie

void
Trie::addWordRC(const char *w, unsigned wordLen, unsigned id, unsigned char type) {
  
  unsigned i;
  char c;
  TrieNode *parent, *child;
  parent = root;

  //  cout << w << "\t" << mem - root << "\t";

  // traverse the tree, allocing as needed
  for (i=wordLen; i > 0; --i) {
    c = w[i-1];

    if (c == 'A') {
      if (parent->t == NULL) {
	parent->t = ++mem;
      }
      child = parent->t;

    } else if (c == 'C') {
      if (parent->g == NULL) {
	parent->g = ++mem;
      }
      child = parent->g;
    } else if (c == 'G') {
      if (parent->c == NULL) {
	parent->c = ++mem;
      }
      child = parent->c;
    } else {
      if (parent->a == NULL) {
	parent->a = ++mem;
      }
      child = parent->a;
    }
    
    parent = child;
  }

  if (parent->id == NULL) {
    parent->id = new vector<unsigned>;
    parent->type = new vector<unsigned char>;
    parent->id->push_back(id);
    parent->type->push_back(type);
  } else {
    // ensure that each type/id pair is only added once    
    for (i=0; i < parent->id->size(); ++i) {
      if (parent->id->at(i) == id &&
	  parent->type->at(i) == type)
	return;
    }

    parent->id->push_back(id);
    parent->type->push_back(type);    

  }


  
}


Trie::~Trie() {
  unsigned i;
  TrieNode *n = root;
  for (i=0; i < numNodes; ++i, ++n) {
    if ((*n).id != NULL) {
      delete((*n).id);
      delete((*n).type);
    }
  }

  delete [] root;
}


/*
This takes in a DNA word 
and it permutes every possible 1-base substitution (no indels)
and adds each permutation to the vector
*/
 
void
Trie::addPermutations(string w, unsigned wordLen, unsigned id, unsigned char type1, unsigned char type2, unsigned char distance) {


  unsigned i, j;
  char letter, l1, l2;

  addWord(w.c_str(), wordLen, id, type1);
  addWordRC(w.c_str(), wordLen, id, type2);


  if (distance > 0) {
  // this does all of the (3*kmer.len) single-base substitution permutations
  // and adds them to the vector
    for (i=0; i < wordLen; ++i) {
      
      letter = w[i];
      
      if (letter != 'A') {
	w[i] = 'A';
	addWord(w.c_str(), wordLen, id, type1);
	addWordRC(w.c_str(), wordLen, id, type2);
      }
      if (letter != 'C') {
	w[i] = 'C';
	addWord(w.c_str(), wordLen, id, type1);
	addWordRC(w.c_str(), wordLen, id, type2);
      }
      if (letter != 'G') {
	w[i] = 'G';
	addWord(w.c_str(), wordLen, id, type1);
	addWordRC(w.c_str(), wordLen, id, type2);
      }
      if (letter != 'T') {
	w[i] = 'T';
	addWord(w.c_str(), wordLen, id, type1);
	addWordRC(w.c_str(), wordLen, id, type2);
      }
      // undo the substitution at base position i
      w[i] = letter;
    }
  } 

  if (distance > 1) { // all of the two-base substitutions as well

    char LETTERS[4] = {'A','C','G','T'};
    
    // every single pair of positions
    for (i=0; i < wordLen; ++i) {
      l1 = w[i];
      for (j=i+1; j < wordLen; ++j) {
	l2 = w[j];

	// every single pair of base pair changes
	unsigned char a, b;
	for (a=0; a < 4; ++a) {
	  for (b=0; b < 4; ++b) {
	    if (LETTERS[a] != l1 && LETTERS[b] != l2) { // make sure what we're adding is unique
	      w[i] = LETTERS[a];
	      w[j] = LETTERS[b];

	      addWord(w.c_str(), wordLen, id, type1);
	      addWordRC(w.c_str(), wordLen, id, type2);
	      w[i] = l1;
	      w[j] = l2;
	    }
	  }
	}
      }
    }


  }

}


unsigned 
Trie::nodesUsed() {
  return mem - root;
}




void
Trie::makeTrieFromConfig(vector<Config> *c, unsigned numStrs, unsigned char distance, unsigned char motifDistance) {
  unsigned i, nf, nr, memNeeded=0;

  if (distance >2) {
    cerr << "Sorry, the max anchor distance supported with trie-search is 2; " << distance   << " is too big!" << endl;
    exit(EXIT_FAILURE);
  } else if (motifDistance > 1) {
    cerr << "Sorry, the max motif distance supported with trie-search is 1; " << motifDistance   << " is too big!" << endl;
    exit(EXIT_FAILURE);
  }

  // make a table of IUPAC codes
  char IUPAC[255][2];
  memset(IUPAC, 0, 255+255);
  IUPAC[ (int)'R'][0] = 'A';
  IUPAC[ (int)'R'][1] = 'G';

  IUPAC[ (int)'Y'][0] = 'C';
  IUPAC[ (int)'Y'][1] = 'T';

  IUPAC[ (int)'S'][0] = 'G';
  IUPAC[ (int)'S'][1] = 'C';

  IUPAC[ (int)'W'][0] = 'A';
  IUPAC[ (int)'W'][1] = 'T';

  IUPAC[ (int)'K'][0] = 'G';
  IUPAC[ (int)'K'][1] = 'T';

  IUPAC[ (int)'M'][0] = 'A';
  IUPAC[ (int)'M'][1] = 'C';

  // compute an (upper-bound) on the number of nodes in the trie
  for (i=0; i < numStrs; ++i) {
    // math for the memory needed for a hamming distance of 1:
    // N = length of string + 1 (ie, including \0)
    // entering that string requires at most N nodes.
    // entering all the 1-base substitutions on that string requires
    // 3*N for all the substitutions on the 0th positoin
    // 3*(N-1) for all of the substutitions on the 1st position (previous position 0 is already in the trie)
    // 3*(N-2) for all of the subs on the second position (previous 2 positions are in the trie) 
    // ...
    // 3 
    // which is equal to:
    // N + 3N + (3(N)(N-1))/2
    //memNeeded += (2*c[i].forwardLength + 2) + (3* (c[i].reverseLength+2)* (c[i].reverseLength+3))/2;
    //memNeeded += (2*c[i].reverseLength + 2) + (3* (c[i].forwardLength+2)* (c[i].forwardLength+3))/2;

    // we have the forwardFlank twice (8N) (+ and - strand)
    // and again for the reverse flank
    nf = (8*((*c)[i].forwardLength+1)) + 3* ((*c)[i].forwardLength)*((*c)[i].forwardLength-1);
    nr = (8*((*c)[i].reverseLength+1)) + 3* ((*c)[i].reverseLength)*((*c)[i].reverseLength-1);


    const char *s = (*c)[i].forwardFlank.c_str();
    unsigned nfAmbig=0;
    for (unsigned j = 0; j < (*c)[i].forwardLength; ++j, ++s) { // adjust the memory for IUPAC codes (double the memory for each IUPAC code)
      if ( IUPAC[(int)*s][0] != 0) {
	nf = nf + nf;
	++nfAmbig;
      }
    }

    if (nfAmbig > 1) {
      cerr << endl << "At most 1 ambiguity code is supported per anchor." << endl 
	   << "Problem with locus: " << (*c)[i].locusName << " Anchor " << (*c)[i].forwardFlank << endl << endl;
      exit(EXIT_FAILURE);
    }

    s = (*c)[i].reverseFlank.c_str();
    unsigned nrAmbig=0;
    for (unsigned j = 0; j < (*c)[i].reverseLength; ++j, ++s) { // adjust the memory for IUPAC codes (double the memory for each IUPAC code)
      if ( IUPAC[(int)*s][0] != 0) {
	nr = nr + nr;
	++nrAmbig;
      }
    }



    if (nrAmbig > 1) {
      cerr << endl << "At most 1 ambiguity code is supported per anchor." << endl <<
	"Problem with locus: " << (*c)[i].locusName << " Anchor " << (*c)[i].reverseFlank << endl << endl;
      exit(EXIT_FAILURE);
    }
    
    if (distance == 0) {
      memNeeded += ((*c)[i].forwardLength+1)*(2*(nfAmbig+1)) + ((*c)[i].reverseLength+1)*(2*(nrAmbig+1));
    } else if (distance == 1) {
      memNeeded += nf + nr;
    } else if (distance == 2) {
      // got lazy with this one; wolfram alpha was used to simplify the sum:
      // sum i=1 to N (i)(i-1)
      // which is the (worst-case) memory needed to add a word of length N and all 2-permutations of it
      memNeeded += (nfAmbig*nfAmbig)*6*((*c)[i].forwardLength)*((*c)[i].forwardLength+1)*((*c)[i].forwardLength+2);
      memNeeded += (nrAmbig*nrAmbig)*6*((*c)[i].reverseLength)*((*c)[i].reverseLength+1)*((*c)[i].reverseLength-1);
    }

    memNeeded += ((*c)[i].motifLength+1) *2; // the motifs are also added
    if (motifDistance == 1) {
      memNeeded += (8*((*c)[i].motifLength+1)) + 3* ((*c)[i].motifLength)*((*c)[i].motifLength-1);
    }
  }

  initMem(memNeeded);

  for (i=0; i < numStrs; ++i) {
    // add all permutations for the forward flank (and its RC)

    int numAmbig=0;
    string s =  (*c)[i].forwardFlank;
    for (unsigned j= 0; j < (*c)[i].forwardLength; ++j) {
      if ( IUPAC[(int)s.at(j)][0] != 0) {

	int iupac = (int)s.at(j);

	s[j] = IUPAC[ iupac ][0]; // overwrite the ambiguity code with the first form, then add to trie
	addPermutations(s, (*c)[i].forwardLength, i, (unsigned char) FORWARDFLANK,
		    (unsigned char) FORWARDFLANK_RC, distance);


	s[j] = IUPAC[ iupac ][1]; // overwrite the ambiguity code with the second form, then add to trie
	addPermutations(s, (*c)[i].forwardLength, i, (unsigned char) FORWARDFLANK,
		    (unsigned char) FORWARDFLANK_RC, distance);

	++numAmbig;
	break;
      }
    }

    if (numAmbig==0)
      addPermutations((*c)[i].forwardFlank, (*c)[i].forwardLength, i, (unsigned char) FORWARDFLANK,
		      (unsigned char) FORWARDFLANK_RC, distance);

    numAmbig=0;
    s =  (*c)[i].reverseFlank;
    for (unsigned j= 0; j < (*c)[i].reverseLength; ++j) {
      if ( IUPAC[(int)s.at(j)][0] != 0) {

	int iupac = (int)s.at(j);

	s[j] = IUPAC[ iupac ][0]; // overwrite the ambiguity code with the first form, then add to trie
	addPermutations(s, (*c)[i].reverseLength, i, (unsigned char) REVERSEFLANK, 
		      (unsigned char) REVERSEFLANK_RC, distance);

	s[j] = IUPAC[ iupac ][1]; // overwrite the ambiguity code with the second form, then add to trie
	addPermutations(s, (*c)[i].reverseLength, i, (unsigned char) REVERSEFLANK, 
		      (unsigned char) REVERSEFLANK_RC, distance);
	
	++numAmbig;
	break;
      }
    }


    // and the reverse flank (and its RC)
    if (numAmbig==0)
      addPermutations((*c)[i].reverseFlank, (*c)[i].reverseLength, i, (unsigned char) REVERSEFLANK, 
		      (unsigned char) REVERSEFLANK_RC, distance);

    if (motifDistance==0) {
    // add the motif (no degeneracy in this)
      addWord((*c)[i].strMotif.c_str(), (*c)[i].motifLength, i, MOTIF);
      addWordRC((*c)[i].strMotif.c_str(), (*c)[i].motifLength, i, MOTIF_RC);
    } else {
      addPermutations((*c)[i].strMotif, (*c)[i].motifLength, i, (unsigned char) MOTIF, (unsigned char) MOTIF_RC, motifDistance);
    }
  } 
  
  //  cerr << memNeeded << " bytes asked for ; Mem unused: " << memNeeded - (mem-root) << endl;

  if (mem-root > (int) memNeeded) {
    cerr << "Error with the maths. Email the author (August) to fix this!" << endl;
    exit(1);
  }
  
}



#if 0

int
main(int argc, char**argv) {


  char word[] = "AAAAAA";
  char word2[] = "AATTT";
  unsigned len = 5;
  unsigned foundId[len+1];
  unsigned char foundType[len+1];

  Trie trie;
  trie.initMem(100);
  
  trie.addWord(word, 6, 0, 0);
  cout << trie.nodesUsed() << endl;

  trie.addPermutations(word, 6, 0, 0);
  cout << trie.nodesUsed() << endl;


  for (unsigned i=3; i <= len; ++i)
    trie.addWord(word, i, i, 0);

  for (unsigned i=3; i <= len; ++i)
    trie.addWord(word2, i, i, 0);

  unsigned numFound = trie.findPrefixMatch(word, len, foundId, foundType);
  cout << numFound << " matches found\n";

  numFound = trie.findPrefixMatch(word2, len, foundId, foundType);
  cout << numFound << " OTHER matches found\n";
  

  unsigned numStrs=0;
  Config *markers = parseConfig(argv[1], &numStrs);
  Trie trie;
  trie.makeTrieFromConfig(markers, numStrs);
  for (unsigned i=0; i < numStrs; ++i) {
    cout << i << "\t" << trie.existsPrefixMatch(markers[i].forwardFlank, markers[i].forwardLength,
						i, FORWARDFLANK) << endl ;

  }


  return 1;

}

#endif



