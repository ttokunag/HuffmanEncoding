#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "BitOutputStream.hpp"

using namespace std;
using namespace testing;

TEST(BitOutputStreamTests, SIMPLE_TEST) {
    stringstream ss;
    BitOutputStream bos(ss, 1);
    for (int i = 0; i < 8; i++) {
        bos.writeBit(1);
    }
    // bos.writeBit(1);
    bos.flush();

    // string bitsStr = "10000000";
    // unsigned int asciiVal = stoi(bitsStr, nullptr, 2);

    string bitsStr1 = "11111111";
    unsigned int asciiVal2 = stoi(bitsStr1, nullptr, 2);

    ASSERT_EQ(ss.get(), asciiVal2);
}
