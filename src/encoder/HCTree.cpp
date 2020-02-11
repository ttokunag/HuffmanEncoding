/**
 * TODO: This file implements HCTree class
 *
 * Author: Tomoya Tokunaga
 */
#include "HCTree.hpp"

/* TODO */
HCTree::~HCTree() {}

/*
 * Builds a HCTree based on a given vector which represents frequency of ascii
 * codes (a value at index i is frequecy of ascii code i)
 *
 * @param vector<unsigned int>: a vector which represents frequency
 */
void HCTree::build(const vector<unsigned int>& freqs) {
    // initializes a priority queue
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> queue;

    for (int ascii = 0; ascii < freqs.size(); ascii++) {
        unsigned int freq = freqs.at(ascii);
        // when a current ascii character has more than one frequency, push it
        // to the priority queue
        if (freq > 0) {
            HCNode* node = new HCNode(freq, (byte)ascii);
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
        HCNode* c0 = cmp(smaller, larger) ? larger : smaller;
        HCNode* c1 = cmp(smaller, larger) ? smaller : larger;

        // initializes a new node based on above two nodes states
        HCNode* parent = new HCNode(c0->count + c1->count, c0->symbol, c0, c1);
        // sets parent-child relation
        c0->p = parent;
        c1->p = parent;

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
