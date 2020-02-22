/**
 * This program uncompress a file encoded by compress.cpp
 *
 * Author: Tomoya Tokunaga
 */
#include <fstream>
#include <iostream>

#include <cxxopts.hpp>
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

const int ASCII_SIZE = 256;

/**
 * a fuction for pseudo-decompression, that is, reading a char of 0 or 1 and
 * decode using a huffman coding tree
 * @param string: name of an input file
 * @param string: name of an output file
 */
void pseudoDecompression(string inFileName, string outFileName) {
    // initializes a frequency array
    vector<unsigned int> freqs(ASCII_SIZE, 0);

    // counts frequecy of each character in a given file
    std::ifstream is(inFileName);
    char nextline[ASCII_SIZE];
    int asciiIdx = 0;

    // better to read a line instead of read a char
    while (asciiIdx < ASCII_SIZE && !is.eof()) {
        is.getline(nextline, ASCII_SIZE);
        // unsigned int freq = nextByte - '0';
        unsigned int freq = atoi(nextline);
        if (freq > 0) {
            freqs[asciiIdx] = freq;
        }
        asciiIdx++;
    }

    // build a HCTree
    HCTree* tree = new HCTree();
    tree->build(freqs);

    // puts frequencies and the encoded to an output file
    std::ofstream outputFile(outFileName);

    while (!is.eof()) {
        byte next = tree->decode(is);
        if (next != NULL) {
            outputFile << next;
        }
    }
    outputFile.flush();
}

/**
 * a fuction for pseudo-decompression, that is, reading binary codes and
 * decode using a huffman coding tree
 * @param string: name of an input file
 * @param string: name of an output file
 */
void trueDecompression(string inFileName, string outFileName) {
    // initializes a frequency array
    vector<unsigned int> freqs(ASCII_SIZE, 0);

    // counts frequecy of each character in a given file
    std::ifstream is(inFileName);
    char nextline[ASCII_SIZE];
    int asciiIdx = 0;

    is.getline(nextline, ASCII_SIZE);
    unsigned int totalBits = atoi(nextline);

    // better to read a line instead of read a char
    while (asciiIdx < ASCII_SIZE && !is.eof()) {
        is.getline(nextline, ASCII_SIZE);
        // unsigned int freq = nextByte - '0';
        unsigned int freq = atoi(nextline);
        if (freq > 0) {
            freqs[asciiIdx] = freq;
        }
        asciiIdx++;
    }

    // build a HCTree
    HCTree* tree = new HCTree();
    tree->build(freqs);

    // puts frequencies and the encoded to an output file
    std::ofstream out(outFileName);
    BitInputStream bis(is, 4000);
    bis.setTotalBits(totalBits);

    while (!bis.eof()) {
        byte next = tree->decode(bis);
        if (next != NULL) {
            out << next;
        } else {
            break;
        }
    }
    out.flush();
}

/* TODO: Main program that runs the uncompress */
int main(int argc, char* argv[]) {
    cxxopts::Options options("./compress",
                             "Compresses files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");

    bool isAsciiOutput = false;
    string inFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "ascii", "Write output in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAsciiOutput))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");

    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);

    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({""}) << std::endl;
    }

    FileUtils fu;

    // determine which decompression this program does based on a flag given
    if (strcmp(argv[1], "--ascii") == 0) {
        isAsciiOutput = true;
    }

    char* inFile = isAsciiOutput ? argv[2] : argv[1];
    char* outFile = isAsciiOutput ? argv[3] : argv[2];

    // checks if a given file name is valid
    if (!fu.isValidFile(inFile) || fu.isEmptyFile(inFile)) {
        std::ofstream out(outFile);
        return -1;
    }

    if (isAsciiOutput) {
        pseudoDecompression(inFile, outFile);
    } else {
        trueDecompression(inFile, outFile);
    }

    return 0;
}
