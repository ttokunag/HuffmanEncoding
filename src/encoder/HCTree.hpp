/**
 * This file implements a huffman coding tree which is used for data compression
 * and decompression
 *
 * Author: Tomoya Tokunaga
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

/**
 * HCTree class is for implementing a Huffman coding tree. This data structure
 * is used for data compression and decompression
 */
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

    /*
     * Builds a HCTree based on a given vector which represents frequency of
     * ascii codes (a value at index i is frequecy of ascii code i)
     *
     * @param vector<unsigned int>: a vector which represents frequency
     */
    void build(const vector<unsigned int>& freqs);

    /**
     * A function which encodes a given symbol and writes encoded bits of the
     * symbol to BitOutputStream
     * @param byte: a symbol to be encoded
     * @param BitOutputStream: output stream to be written
     */
    void encode(byte symbol, BitOutputStream& out) const;

    /**
     * A function which encodes a given symbol and writes encoded bits of the
     * symbol to output stream
     * @param byte: a symbol to be encoded
     * @param ostream: output stream to be written
     */
    void encode(byte symbol, ostream& out) const;

    /**
     * decoder of btis of a given input stream
     * @param BitInputStream: an input stream to be decoded
     */
    byte decode(BitInputStream& in) const;

    /**
     * decoder of btis of a given input stream
     * @param istream: an input stream to be decoded
     */
    byte decode(istream& in) const;
};

#endif  // HCTREE_HPP
