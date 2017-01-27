
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


#endif
