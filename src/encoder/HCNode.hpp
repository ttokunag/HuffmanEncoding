/**
 * This file implements HCNode class used in HCTree
 *
 * Author: Tomoya Tokunaga
 */
#ifndef HCNODE_HPP
#define HCNODE_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class HCNode {
  public:
    unsigned int count;  // the freqency of the symbol
    byte symbol;         // byte in the file we're keeping track of
    HCNode* c0;          // pointer to '0' child
    HCNode* c1;          // pointer to '1' child
    HCNode* p;           // pointer to parent

    /* Constructor that initialize a HCNode */
    HCNode(unsigned int count, byte symbol, HCNode* c0 = 0, HCNode* c1 = 0,
           HCNode* p = 0)
        : count(count), symbol(symbol), c0(c0), c1(c1), p(p) {}
};

/* For printing an HCNode to an ostream. Possibly useful for debugging */
ostream& operator<<(ostream&, const HCNode&) __attribute__((weak));
// ostream& operator<<(ostream& stm, const HCNode& n) {
//     stm << "[" << n.count << "," << (int)(n.symbol) << "]";
//     return stm;
// }

/* Comparator of HCNode pointer. In priority queue, HCNode ptr with lower count
 * has higher priority, and if count is the same, HCNode ptr with larger symbol
 * has higher prioruty.
 */
struct HCNodePtrComp {
    /*
     * Overloads the operator() which takes two HCNode references as paramters
     * Returns true is the first HCNode contains smaller count OR two nodes
     * contains the same count and a first node contains an alphabetically
     * earlier symbol
     */
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        // when a two nodes have different count, compare them by their counts
        if (lhs->count != rhs->count) {
            return lhs->count > rhs->count;
        }

        // otherwise, compare them with their symbols
        //  (smaller one should have higher priority)
        return lhs->symbol < rhs->symbol;
    }
};
#endif  // HCNODE_HPP
