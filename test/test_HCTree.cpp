#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCTree.hpp"

using namespace std;
using namespace testing;

class SimpleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    SimpleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 2;
        freqs['b'] = 3;
        tree.build(freqs);
    }
};

TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "0");
}

TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
    istringstream is("1");
    ASSERT_EQ(tree.decode(is), 'b');
}

TEST(SimpleHCTreeTest, BUILD_TEST) {
    HCTree tree;

    // int asciiCodes[] = {10, 20, 30, 40, 50, 60};
    int asciiCodes[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int frequencies[] = {32, 13, 32, 41, 55, 19};

    int idx = 0;

    vector<unsigned int> freqs;
    for (int i = 0; i < 256; i++) {
        if (idx < 6 && i == asciiCodes[idx]) {
            freqs.push_back(frequencies[idx]);
            idx++;
        } else {
            freqs.push_back(0);
        }
    }

    tree.build(freqs);
}

// TEST(SimpleHCTreeTest, ENCODER_TEST) {
//     const int ASCII_SIZE = 256;
//     // initializes a frequency array
//     vector<unsigned int> freqs(ASCII_SIZE, 0);

//     string inFileName = "data/input.txt";
//     string outFileName = "compressed.txt";

//     // counts frequecy of each character in a given file
//     std::ifstream is(inFileName);
//     int nextByte;
//     while ((nextByte = is.get()) != EOF) {
//         freqs[(unsigned int)nextByte] += 1;
//     }

//     // puts frequencies and the encoded to an output file
//     std::ofstream outFile(outFileName);
//     for (unsigned int i = 0; i < ASCII_SIZE; i++) {
//         outFile << freqs[i];
//         outFile << '\n';
//     }
//     outFile.flush();

//     // build a HCTree
//     HCTree* tree = new HCTree();
//     tree->build(freqs);

//     std::ifstream _is(inFileName);
//     // int nextByte;
//     while ((nextByte = _is.get()) != EOF) {
//         tree->encode((byte)nextByte, outFile);
//     }
//     outFile.flush();
// }

// TEST(SimpleHCTreeTest, DECODER_TEST) {
//     const int ASCII_SIZE = 256;

//     string inFileName = "compressed.txt";
//     string outFileName = "uncompressed.txt";

//     // initializes a frequency array
//     vector<unsigned int> freqs(ASCII_SIZE, 0);

//     // counts frequecy of each character in a given file
//     std::ifstream is(inFileName);
//     char nextline[ASCII_SIZE];
//     int asciiIdx = 0;
//     // better to read a line instead of read a char
//     while (asciiIdx < ASCII_SIZE && !is.eof()) {
//         is.getline(nextline, ASCII_SIZE);
//         // unsigned int freq = nextByte - '0';
//         unsigned int freq = atoi(nextline);
//         if (freq > 0) {
//             freqs[asciiIdx] = freq;
//         }
//         asciiIdx++;
//     }

//     // build a HCTree
//     HCTree* tree = new HCTree();
//     tree->build(freqs);

//     // puts frequencies and the encoded to an output file
//     std::ofstream outputFile(outFileName);

//     while (!is.eof()) {
//         byte next = tree->decode(is);
//         if (next != NULL) {
//             outputFile << next;
//         }
//     }
//     outputFile.flush();
// }