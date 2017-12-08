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

#ifndef STR8_H_
#define STR8_H_


#include <stdint.h>
#include <vector>
#include <string>

#include "constants.h"

// this prints the internal representation of the STR configuration file
void printConf(Config *conf);
//this frees the memory associated with a config
void freeConfig(Config *c);

// this takes in a filename, and returns an array of Config structs of size numStrs
// optionally filters the loci to only be of the type specified 
// eg, AUTOSOMES
vector<Config>* parseConfig(char *file, unsigned *numStrs, char *filt);

char *revcompCstring(const char *dna, int len);

#endif
