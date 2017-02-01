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

#ifndef TRIE_H_

#include <limits.h>
#include <vector>
#include <string>

#include "constants.h"

#define NULLSTR UINT_MAX

struct TrieNode {
  struct TrieNode *a;
  struct TrieNode *c;
  struct TrieNode *g;
  struct TrieNode *t;
  std::vector<unsigned> *id; // the index of the str in *config
  std::vector<unsigned char> *type; // the type of the anchor (forward, reverse, reverse reverse-complemented ,...)
};


class Trie {
 public:
  TrieNode *root;

  Trie();
  ~Trie();

  unsigned findPrefixMatch(const char *w, unsigned wordLen, unsigned *outId, unsigned char *outType);
  // returns a boolean, whether or not the first wordLen characters of *w
  // exist in the trie AND, they MATCH the outId and outType
  bool existsPrefixMatch(const char *w, unsigned wordLen, unsigned outId, unsigned char outType);
  void initMem(unsigned numNodes); // note the init is done exactly once. you need to precompute how much memory it'll need.
// an easy upper bound = numLetters in (all anchors) + numAnchors

  void addWord(const char *w, unsigned wordLen, unsigned id, unsigned char type);
  // reverse complements the word and adds it
  void addWordRC(const char *w, unsigned wordLen, unsigned id, unsigned char type);


  // makes a trie of all of the anchors in the config file, +/- distance substitution (distance can be 0, 1 or 2)
  // plus it adds the motifs...
  void makeTrieFromConfig(std::vector<Config> *c, unsigned numStrs, unsigned char distance, unsigned char motifDistance);

  void addPermutations(std::string w, unsigned wordLen, unsigned id, unsigned char type1, unsigned char type2, unsigned char distance);

  unsigned nodesUsed();

 protected:
  TrieNode *mem;
  unsigned numNodes;


};

#endif
