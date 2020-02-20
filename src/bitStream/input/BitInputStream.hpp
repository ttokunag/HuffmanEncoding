/**
 * TODO: file header
 *
 * Author:
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** TODO: class header */
class BitInputStream {
  private:
    istream& in;           // reference to the input stream to use
    char* buf;             // buffer of an char array
    unsigned int bufSize;  // size of buffer in byte
    unsigned int nbits;    // number of bits that have been read from buf
    bool eofBit;           // true when trying to read past the end of the file

    /* TODO: add function header */
    bool atEndOfFile();

  public:
    /*
     * A constructor of BitInputStream
     */
    explicit BitInputStream(istream& is, unsigned int bufSize) : in(is) {
        // initialize a buffer array
        buf = new char[bufSize * 8];
        nbits = 0;
        this->bufSize = bufSize;
        eofBit = false;
    };

    /* TODO: add function header */
    void fill();

    /* TODO: add function header */
    bool eof();

    /* TODO: add function header */
    unsigned int readBit();
};

#endif