/**
 * TODO: file header
 *
 * Author:
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <string.h>
#include <fstream>
#include <queue>
#include <vector>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

/** TODO: class header */
class HCTree {
  private:
    HCNode* root;            // the root of HCTree
    vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes
    string codes[256];

    void deleteAll(HCNode* node);

    void buildCodeMap(HCNode* node, string code);

  public:
    /*
     * Constructor of HCTree, which initialize a root to a null pointer
     */
    HCTree() { root = nullptr; }

    /**
     * a destructor of a HCTree
     */
    ~HCTree();

    /* TODO: add function header */
    void build(const vector<unsigned int>& freqs);

    /* TODO: add function header */
    void encode(byte symbol, BitOutputStream& out) const;

    /* TODO: add function header */
    void encode(byte symbol, ostream& out) const;

    /* TODO: add function header */
    byte decode(BitInputStream& in) const;

    /* TODO: add function header */
    byte decode(istream& in) const;
};

#endif  // HCTREE_HPP
