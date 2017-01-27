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
