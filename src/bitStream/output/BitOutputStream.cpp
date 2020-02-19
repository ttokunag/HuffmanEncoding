/**
 * TODO: file header
 *
 * Author:
 */
#include "BitOutputStream.hpp"

/* TODO */
void BitOutputStream::flush() {
    int remainder = 0;
    int numBytes = 0;

    // checks if a buffer is entirely filled
    if (nbits % 8 != 0) {
        remainder = nbits % 8;
        numBytes = (nbits - remainder) / 8;

        // fill padding zeros at the end of a current byte
        int endByteIdx = nbits + (8 - remainder);
        for (int i = nbits; i < endByteIdx; i++) {
            buf[i] = 0;
        }
    }

    // writes btis to an output stream
    int writeSize = (remainder == 0) ? (8 * numBytes) : (8 * (numBytes + 1));
    out.write(buf, writeSize);

    // clear a buffer for a further flush
    delete[] buf;
    buf = new char[8 * bufSize];
    nbits = 0;
}

/* TODO */
void BitOutputStream::writeBit(unsigned int i) {
    // checks if a buffer still has spaces
    if (nbits == 8 * bufSize) {
        this->flush();
    }

    buf[nbits++] = i;
}
