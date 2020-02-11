/**
 * TODO: This file implements HCTree class
 *
 * Author: Tomoya Tokunaga
 */
#include "HCTree.hpp"

/* TODO */
HCTree::~HCTree() {}

/* TODO */
void HCTree::build(const vector<unsigned int>& freqs) {
    // initializes a priority queue
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> queue;

    for (int ascii = 0; ascii < freqs.size(); ascii++) {
        unsigned int curr = freqs.at(ascii);
        // when a current ascii character has more than one frequency, push it
        // to the priority queue
        if (curr > 0) {
            HCNode* node = new HCNode(curr, (byte)ascii);
            queue.push(node);
        }
    }

    // Comparator used for which is more prioritized
    HCNodePtrComp cmp;

    while (queue.size() > 1) {
        // a node with a smallest count
        HCNode* smaller = queue.top();
        queue.pop();
        // a node with a second smallest count
        HCNode* larger = queue.top();
        queue.pop();

        // finds which node is more prioritized
        HCNode* high = cmp(smaller, larger) ? smaller : larger;
        HCNode* low = cmp(smaller, larger) ? larger : smaller;

        // initializes a new node based on above two nodes states
        HCNode* parent =
            new HCNode(high->count + low->count, high->symbol, high, low);
        // sets parent-child relation
        high->p = parent;
        low->p = parent;

        queue.push(parent);
    }

    // sets a root node to a last node of a priority queue
    root = queue.top();
}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {}

/* TODO */
void HCTree::encode(byte symbol, ostream& out) const {}

/* TODO */
byte HCTree::decode(BitInputStream& in) const { return ' '; }

/* TODO */
byte HCTree::decode(istream& in) const { return ' '; }
