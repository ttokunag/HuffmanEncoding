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
        HCNode* c0Node = cmp(smaller, larger) ? larger : smaller;
        HCNode* c1Node = cmp(smaller, larger) ? smaller : larger;

        // initializes a new node based on above two nodes states
        HCNode* parent = new HCNode(c0Node->count + c1Node->count,
                                    c0Node->symbol, c0Node, c1Node);
        // sets parent-child relation
        c0Node->p = parent;
        c1Node->p = parent;

        queue.push(parent);

        // leaf nodes should be added to leaves vector for efficiency
        if (c0Node->c0 == nullptr && c0Node->c1 == nullptr) {
            leaves.push_back(c0Node);
        }
        if (c1Node->c0 == nullptr && c1Node->c1 == nullptr) {
            leaves.push_back(c1Node);
        }
    }

    // sets a root node to a last node of a priority queue
    root = queue.top();
}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {}

/* TODO */
void HCTree::encode(byte symbol, ostream& out) const {
    // build() must be called before encoding a byte
    if (root == nullptr) {
        return;
    }

    // char* code;    // encoded letters of a given symbol
    vector<char> code;
    HCNode* node;  // a leaf node with a given symbol

    // finds a node which contains a given symbol
    for (HCNode* leaf : leaves) {
        if (leaf->symbol == symbol) {
            node = leaf;
            break;
        }
    }

    // add codes to a vector
    while (node->p != nullptr) {
        if (node->p->c0 == node) {
            code.insert(code.begin(), '0');
        } else {
            code.insert(code.begin(), '1');
        }
        node = node->p;
    }

    // writes bits to a given ostream
    out.write(&code[0], (streamsize)code.size());
}

/* TODO */
byte HCTree::decode(BitInputStream& in) const { return ' '; }

/* TODO */
byte HCTree::decode(istream& in) const { return ' '; }
