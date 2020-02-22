/**
 * This file implements a custom output stream class for data compression and
 * decompression
 *
 * Author: Tomoya Tokunaga
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** A custom output stream class for data compression and decompression */
class BitOutputStream {
  private:
    ostream& out;          // reference to the output stream to use
    char* buf;             // buffer of an char array
    unsigned int bufSize;  // size of buffer in byte
    unsigned int nbits;    // number of bits have been writen to buf

    unsigned int totalBits;  // the number of btis in an output file
                             // to deal with 0s padding problem

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
        totalBits = 0;
    };

    /* write data on an original output stream  */
    void flush();

    /**
     * a function which writes a bit to a char buffer
     * @param unsigned int: a bit to be written on a buffer
     */
    void writeBit(unsigned int i);

    // destructor of a BitOutputStream class
    ~BitOutputStream() { delete[] buf; };

    // getter function for totalBits
    unsigned int getTotalBits();
};

#endif
