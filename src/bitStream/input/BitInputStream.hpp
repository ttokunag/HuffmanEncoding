/**
 * A custom class of an input stream for data compression
 *
 * Author: Tomoya Tokunaga
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/**
 * This class is a custom input stream class for data compression/decompression
 */
class BitInputStream {
  private:
    istream& in;           // reference to the input stream to use
    char* buf;             // buffer of an char array
    unsigned int bufSize;  // size of buffer in byte
    unsigned int nbits;    // number of bits that have been read from buf
    bool eofBit;           // true when trying to read past the end of the file

    /**
     * returns true if there's no more bits to read from an input stream
     */
    bool atEndOfFile();

  public:
    unsigned int totalBits;
    unsigned int numBitsRead;
    /*
     * A constructor of BitInputStream
     * @param istream: input stream for reading a encoded file
     * @param unsigned int: the size of a buffer
     */
    explicit BitInputStream(istream& is, unsigned int bufSize) : in(is) {
        // initialize a buffer array
        buf = new char[bufSize * 8];
        nbits = 0;
        totalBits = INT64_MAX;
        numBitsRead = 0;
        this->bufSize = bufSize;
        eofBit = false;

        fill();
    };

    /**
     * fills a bit buffer of a given size from an input stream
     */
    void fill();

    /* Returns true when trying to read past the end of the file, false
     * otherwise */
    bool eof();

    /**
     * reads a bit from a char buffer. return 0 if a read char is 0, otherwise
     * returns 1
     */
    unsigned int readBit();

    // a destructor of BitInputStream object
    ~BitInputStream() { delete[] buf; }

    /* setter function for totalBits */
    void setTotalBits(unsigned int totalBits);

    /*  a function incrementing a nbits
        this is used when the case a huffman coding tree contains only one node
     */
    void incrementNBits();

    // getter function of nbits
    unsigned int getNBits();
};

#endif