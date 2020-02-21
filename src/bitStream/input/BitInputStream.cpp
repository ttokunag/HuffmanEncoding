/**
 * TODO: file header
 *
 * Author:
 */
#include "BitInputStream.hpp"

/* TODO */
void BitInputStream::fill() {
    // fill a buffer with a specified buffer size

    char* charBuf = new char[bufSize];
    in.read(charBuf, bufSize);

    int numRead = in.gcount();
    for (int i = 0; i < numRead; i++) {
        unsigned char currChar = charBuf[i];
        for (int j = 0; j < 8; j++) {
            buf[(8 * i) + j] = (currChar >> (7 - j)) & 1;
        }
    }

    delete[] charBuf;
}

/* TODO */
bool BitInputStream::atEndOfFile() {
    int numBytesRead = in.gcount();

    if (numBytesRead == 0 || nbits >= 8 * numBytesRead) {
        return true;
    }
    return false;
}

/* Returns true when trying to read past the end of the file, false otherwise */
bool BitInputStream::eof() { return eofBit; }

/* TODO */
unsigned int BitInputStream::readBit() {
    // checks if all the btis are already read
    if (nbits == 8 * bufSize) {
        fill();
        nbits = 0;
    }

    if (atEndOfFile()) {
        eofBit = true;
        return 0;
    }

    char nextBit = buf[nbits++];
    return nextBit;
}