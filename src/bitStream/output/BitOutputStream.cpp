/**
 * This file implements a custom output stream class for data compression and
 * decompression
 *
 * Author: Tomoya Tokunaga
 */
#include "BitOutputStream.hpp"

/* write data on an original output stream  */
void BitOutputStream::flush() {
    int remainder = 0;
    int numBytes = 0;

    // checks if a buffer is entirely filled. if it's not put padding 0s
    if (nbits % 8 != 0) {
        remainder = nbits % 8;
        numBytes = (nbits - remainder) / 8;

        // fill padding zeros at the end of a current byte
        int endByteIdx = nbits + (8 - remainder);
        for (int i = nbits; i < endByteIdx; i++) {
            buf[i] = 0;
        }
    }
    // when a byte is entirely filled
    else {
        numBytes = nbits / 8;
    }

    // writes btis to an output stream
    int writeSize = (remainder == 0) ? numBytes : (numBytes + 1);

    for (int i = 0; i < writeSize; i++) {
        unsigned char nextChar = 0;
        for (int j = 0; j < 8; j++) {
            nextChar = nextChar << 1;
            nextChar += buf[(8 * i) + j];
        }
        out.put(nextChar);
    }
    // out.flush();

    // clear a buffer for a further flush
    delete[] buf;
    buf = new char[8 * bufSize];
    nbits = 0;
}

/**
 * a function which writes a bit to a char buffer
 * @param unsigned int: a bit to be written on a buffer
 */
void BitOutputStream::writeBit(unsigned int i) {
    // checks if a buffer still has spaces
    if (nbits == 8 * bufSize) {
        this->flush();
    }

    buf[nbits++] = i;
    totalBits++;  // increment the number of bits written
}

// getter function for totalBits
unsigned int BitOutputStream::getTotalBits() { return totalBits; }
