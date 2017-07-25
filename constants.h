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


#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <stdint.h>
#include <vector>
#include <string>
#include <cstring>


// This is where the max anchor size of 32 is set.
// this code uses 64-bit representations of DNA strings. this lets a 32-base Kmer be encoded as a single word
// and lets a test for an exact match of that 32-base string occur w/ a single ==
// setting this smaller (32 bits) may cause this application to run marginally faster
// setting it larger (128 bits; uint128_t ; only on 64-bit systems)
// will accommodate larger anchors, but cause the code to slow down (who knows how much?)



#define MAXWORD 64
#define binaryword uint64_t
#define MAXBINARYWORD ((binaryword)(0xffffffffffffffff))

#ifndef DEBUG
#define DEBUG 0
#endif

using namespace std;


// this is the internal representation of the config file
typedef struct {
  string locusName;
  string markerType;
  string forwardFlank;
  string reverseFlank;
  string strMotif;
  uint32_t forwardLength;
  uint32_t reverseLength;
  uint32_t motifLength;
  unsigned short motifPeriod;
  unsigned short motifOffset;
  unsigned short forwardCount;
  unsigned short reverseCount;
} Config;


// this is how the kmers in the config file are represented
struct Kmer {
  binaryword w; // 2-bit representation of a (up-to) 32-base DNA kmer
  unsigned char len; // how long the kmer actually is
  unsigned char type; // what type of kmer this is (forward or reverse anchor? complemented?)
  unsigned id; // the index in the Config associated with this str

  // used to sort kmers  
  bool operator < (const Kmer& i) const {
    if (i.w==w) {
      return len < i.len; // within a type, if tied lexicographically, then by length (yes this can happen.)
    }
    return w < i.w; // lexicographically
  }
};

// defined to sum to 3 for a valid pair
// note: made to sum to 3 for a proper pair
#define FORWARDFLANK 0
#define FORWARDFLANK_RC 1
#define REVERSEFLANK 3
#define REVERSEFLANK_RC 2

#define MOTIF 4
#define MOTIF_RC 5

#endif
