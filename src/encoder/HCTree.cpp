/**
 * TODO: This file implements HCTree class
 *
 * Author: Tomoya Tokunaga
 */
#include "HCTree.hpp"

/*
 * Destructor of a HCTree object
 */
HCTree::~HCTree() {
    deleteAll(root);
    delete root;
}

/*
 * Free memory related to a given node
 *
 * @param HCNode*: a reference of a node to free memory
 */
void HCTree::deleteAll(HCNode* node) {
    if (node == nullptr) {
        return;
    }

    deleteAll(node->c0);
    deleteAll(node->c1);

    delete node->c0;
    delete node->c1;
}

/*
 * Builds a HCTree based on a given vector which represents frequency of ascii
 * codes (a value at index i is frequecy of ascii code i)
 *
 * @param vector<unsigned int>: a vector which represents frequency
 */
void HCTree::build(const vector<unsigned int>& freqs) {
    // initializes a priority queue
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> queue;

    for (unsigned int ascii = 0; ascii < freqs.size(); ascii++) {
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

    // when there's only one node
    if (root->c0 == nullptr && root->c1 == nullptr) {
        leaves.push_back(root);
    }

    buildCodeMap(root, "");
}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    string code = codes[symbol];
    for (int i = 0; i < code.size(); i++) {
        unsigned int nextBit = (code[i] == '0') ? 0 : 1;
        out.writeBit(nextBit);
    }
}

/* TODO */
void HCTree::encode(byte symbol, ostream& out) const {
    // string code = codes.at(symbol);
    string code = codes[symbol];
    out.write(code.c_str(), (streamsize)code.size());
}

void HCTree::buildCodeMap(HCNode* root, string code) {
    // base case when visiting an empty node
    if (root == nullptr) {
        return;
    }
    // when visiting a leaf node
    if (root->c0 == nullptr && root->c1 == nullptr) {
        string copy = (code.size() == 0) ? "0" : code;
        codes[root->symbol] = copy;
        // mapCode.insert(pair<byte, string>(root->symbol, copy));
    }

    buildCodeMap(root->c0, code + "0");
    buildCodeMap(root->c1, code + "1");
}

/* TODO */
byte HCTree::decode(BitInputStream& in) const {
    unsigned char symbol = 0;
    for (int i = 0; i < 8; i++) {
        unsigned int nextBit = in.readBit();
        symbol = (symbol << 1) | nextBit;
    }
    return (byte)symbol;
}

/*
 * Decodes a given input stream.
 */
byte HCTree::decode(istream& in) const {
    int nextByte;

    // build() must be called before decoding
    if (root == nullptr) {
        return NULL;
    } else if (root->c0 == nullptr && root->c1 == nullptr) {
        if ((nextByte = in.get()) != EOF) {
            return root->symbol;
        } else {
            return NULL;
        }
    }

    unsigned char nextChar;
    HCNode* node = root;

    // read input stream until hitting the end
    while ((nextByte = in.get()) != EOF) {
        nextChar = (unsigned char)nextByte;

        node = (nextChar == '0') ? node = node->c0 : node->c1;

        if (node->c0 == nullptr && node->c1 == nullptr) {
            return node->symbol;
        }
    }

    return NULL;
}
