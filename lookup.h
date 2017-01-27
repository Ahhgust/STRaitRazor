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
