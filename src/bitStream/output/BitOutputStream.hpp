/**
 * TODO: file header
 *
 * Author:
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** TODO: class header */
class BitOutputStream {
  private:
    ostream& out;          // reference to the output stream to use
    char* buf;             // buffer of an char array
    unsigned int bufSize;  // size of buffer in byte
    unsigned int nbits;    // number of bits have been writen to buf

  public:
    /*
     * a constructor of BitOutputStream
     * @param ostream: an output stream a program write bytes
     * @param int: an integer specifying the size of char* buf
     */
    explicit BitOutputStream(ostream& os, unsigned int bufSize) : out(os) {
        // initializes a buffer with a given size
        buf = new char[8 * bufSize];
        this->bufSize = bufSize;
        nbits = 0;
    };

    /* TODO: add function header */
    void flush();

    /* TODO: add function header */
    void writeBit(unsigned int i);
};

#endif
