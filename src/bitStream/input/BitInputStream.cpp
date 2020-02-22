/**
 * This file implements a custom input straem class for data
 * compression/decompression
 *
 * Author: Tomoya Tokunaga
 */
#include "BitInputStream.hpp"

/**
 * fills a bit buffer of a given size from an input stream
 */
void BitInputStream::fill() {
    // fill a temporary buffer
    char* charBuf = new char[bufSize];
    in.read(charBuf, bufSize);

    int numRead = in.gcount();
    // fill a char buffer
    for (int i = 0; i < numRead; i++) {
        unsigned char currChar = charBuf[i];
        for (int j = 0; j < 8; j++) {
            buf[(8 * i) + j] = (currChar >> (7 - j)) & 1;
        }
    }

    // deallocate memory to avoid memory leak
    delete[] charBuf;
}

/**
 * returns true if there's no more bits to read from an input stream
 */
bool BitInputStream::atEndOfFile() {
    // the number of bytes read
    int numBytesRead = in.gcount();

    if (numBytesRead == 0 || nbits >= 8 * numBytesRead ||
        numBitsRead >= totalBits) {
        return true;
    }
    return false;
}

/* Returns true when trying to read past the end of the file, false otherwise */
bool BitInputStream::eof() { return eofBit; }

/**
 * reads a bit from a char buffer. return 0 if a read char is 0, otherwise
 * returns 1
 */
unsigned int BitInputStream::readBit() {
    // checks if all the btis are already read
    if (nbits == 8 * bufSize) {
        fill();
        nbits = 0;
    }

    // checks if a file is fully read
    if (atEndOfFile()) {
        eofBit = true;
        return 0;
    }

    char nextBit = buf[nbits++];
    numBitsRead++;  // increments the number of read bits

    return nextBit;
}

/* setter function for totalBits */
void BitInputStream::setTotalBits(unsigned int totalBits) {
    this->totalBits = totalBits;
}

/*  a function incrementing a nbits
    this is used when the case a huffman coding tree contains only one node */
void BitInputStream::incrementNBits() { nbits++; }

// getter function of nbits
unsigned int BitInputStream::getNBits() { return nbits; }