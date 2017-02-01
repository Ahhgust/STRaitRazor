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
#include <string.h>
#include <math.h>
#include <algorithm>
#include <climits>

#include "constants.h"
#include "lookup.h"
#include "str8.h"

using namespace std;

/* 
   Note to readers:
   These routines encode kmers (up to 32-bases in length) as 64-bit integers
   I do this so that you can compare kmers with (as little as) a single instruction
   However, the data we are using 32-base kmers from the FASTQ files, and we search for matches on kmers (from the config file)
   that are at most 32 bits.
   eg, for two kmers to match at the first 20 bases, 24 bits must be masked (ignored).
   I'm storing the (variable length) kmers from the config file in a sorted array.
   This means that the strings from the config file (and thus both files) must be encoded right to left, and the left-most n bits 
   (ie, the n least-signficant bits) must be masked in searches for equality. IE, it's 
   
   EG: the string "C" -> 01 00 00 (.....)
   and the string "CT" is 11 01 00 00 00 (...)
   This is because I want suffixes of the kmers, 

*/



/*
  Takes in an arbitrary word
  and a letter in the DNA alphabet
  and a position in the (original, GATC-form) dnaword (0-based)
  and it changes the letter in the binary form at the specified position to the specified word 
*/

binaryword
setLetter(binaryword w, char letter, unsigned pos) {


  pos = MAXWORD - 2 - (pos + pos);
  

  if (letter == 'A') { // clear two bits
    w &= ~( ((binaryword)3) << pos);
  } else if (letter == 'C') { // C is 01 in this schema
    w |= ((binaryword)1) << (pos); // set 1 bit to 1
    w &= ~( ((binaryword)1) << (pos+1)); // set the next bit to 0
  } else if (letter == 'G') {
    w |= ((binaryword)1) << (pos+1); //  and vice versa
    w &= ~( ((binaryword)1) << (pos)); //
  } else { // setting two bits
    w |= ((binaryword)3) << (pos);
  }

  return w;
}

/*
  Takes in an arbitrary word
  and a letter in the DNA alphabet
  and a position in the (original, GATC-form) dnaword (0-based)
  and it returns the letter in the binary form at the specified position to the specified word 
*/

char
getLetter(binaryword w, unsigned pos) {

  pos = MAXWORD - 2 - (pos + pos);  

  binaryword twobit = (w >> pos) & ((binaryword)3);
  if (twobit==0) {
    return 'A';
  } else if (twobit == 1) {
    return 'C';
  } else if (twobit == 2) {
    return 'G';
  }
  return 'T';
}



// converts a DNA string over {GATC} into a 64-bit number.
// assumes numChars <= 32 (duh!)
// AND that the DNA string is encoded right to left:
// EG: the string GAAC gets treated as CAAG -> 01(C) 00(A) 00(A) 10(G) 

binaryword
gatcToLong(char *s, unsigned numChars) {

  unsigned i;
  binaryword num=0;


  for (i=0; i < numChars; ++i, ++s) {
    num = setLetter(num, *s, i);
  }

  return num;
}

void
longToGatc(binaryword num, unsigned numChars, char *buffer) {
  unsigned i;

  memset(buffer, 'A', numChars); // initialize to 'A' (ie, 0)
  
  for (i=0; i < numChars; ++i, ++buffer) {
    *buffer = getLetter(num, i);
  }

}


void
printBinaryWord(FILE *f, binaryword w, unsigned numChars) {

  unsigned i;
  for (i=0; i < numChars; ++i)
    fprintf(f, "%c", getLetter(w, i));

}

void
reverseComplement(binaryword *in, binaryword *out, unsigned numBases) {

  unsigned j, i = numBases-1;
  unsigned inIndex, inBase, outIndex, outBase, prevOutIndex=UINT_MAX;

  char c;
  for (j=0 ; j < numBases; --i, ++j) {
    inIndex = i/(MAXWORD/2);
    inBase = i % (MAXWORD/2);
    c = getLetter(in[inIndex], inBase);
    if (c == 'A') {
      c = 'T';
    } else if (c == 'T') {
      c = 'A';
    } else if (c == 'G') {
      c = 'C';
    } else if (c == 'C') {
      c = 'G';
    } else {
      fprintf(stderr, "Cannot happen! Got letter: %c\n", c);
      exit(EXIT_FAILURE);
    }


    outIndex = j / (MAXWORD/2);
    outBase = j %  (MAXWORD/2);

    if (outIndex != prevOutIndex)
      out[outIndex] = 0;

    out[outIndex] = setLetter(out[outIndex], c, outBase);
    prevOutIndex = outIndex;
  }


}


