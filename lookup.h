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

#ifndef LOOKUP_H_
#define LOOKUP_H_

#include <utility>
#include <stdint.h>
#include <vector>
#include <stdio.h>

#include "constants.h"
#include "str8.h"

// reverse complements an array of binarywords with numBases in total
// and writes the output to stdout
// out must not equal in
void reverseComplement(binaryword *in, binaryword *out, unsigned numBases);

//  prints the (2*numChars) most significant bits in the word w to stream f
void printBinaryWord(FILE *f, binaryword w, unsigned numChars);

// converts a DNA string into it's representation as a 64-bit integer.
binaryword gatcToLong(char *s, unsigned numChars);

// this converts an integer to a DNA word (string composed of GATC)
void longToGatc(binaryword num, unsigned numChars, char *buffer);

// Below are routines that set the bits in a binaryword
// that correspond to single-base changes

// takes in a binaryword, and it gets the DNA base at the substring position (in the DNA word) pos
char getLetter(binaryword w, unsigned pos);

// this sets the letter a the substring position in the DNA word
binaryword setLetter(binaryword w, char letter, unsigned pos);

// this is for sliding over long dna strings; it appends letter to w (adding letter and removing the oldest letter in the string)
// note that in this encoding letter occupies the two most signficant bits in w (and the two least-significant bits are lost)
binaryword binaryAppend(binaryword w, char letter);

// this permutes all of the markers (all possible substitutions)
// and places them in a vector
std::vector< Kmer > *  
getConfigKmers(Config *c, unsigned numStrs);


#endif
