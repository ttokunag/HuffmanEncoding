/**
 * Application which compresses an input file using the Huffman coding tree
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

/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {
    // initializes a frequency array
    vector<unsigned int> freqs(ASCII_SIZE, 0);

    // counts frequecy of each character in a given file
    std::ifstream is(inFileName);
    int nextByte;
    while ((nextByte = is.get()) != EOF) {
        freqs[(unsigned int)nextByte] += 1;
    }

    // puts frequencies and the encoded to an output file
    std::ofstream outFile(outFileName);
    for (unsigned int i = 0; i < ASCII_SIZE; i++) {
        outFile << freqs[i];
        outFile << '\n';
    }
    outFile.flush();

    // build a HCTree
    HCTree* tree = new HCTree();
    tree->build(freqs);

    std::ifstream _is(inFileName);
    // int nextByte;
    while ((nextByte = _is.get()) != EOF) {
        tree->encode((byte)nextByte, outFile);
    }
    outFile.flush();
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {
    // initializes a frequency array
    vector<unsigned int> freqs(ASCII_SIZE, 0);

    // counts frequecy of each character in a given file
    std::ifstream is(inFileName);
    int nextByte;
    while ((nextByte = is.get()) != EOF) {
        freqs[(unsigned int)nextByte] += 1;
    }

    // puts frequencies and the encoded to an output file
    std::ofstream out(outFileName);
    for (unsigned int i = 0; i < ASCII_SIZE; i++) {
        out << freqs[i];
        out << '\n';
    }
    out.flush();

    // build a HCTree
    HCTree* tree = new HCTree();
    tree->build(freqs);

    BitOutputStream bos(out, 4000);

    std::ifstream _is(inFileName);
    while ((nextByte = _is.get()) != EOF) {
        tree->encode((byte)nextByte, bos);
    }
    bos.flush();

    ofstream anotherOut("tester.txt");
    ifstream anotherIn(outFileName);
    anotherOut << bos.getTotalBits();
    anotherOut << '\n';

    unsigned char nextChar;
    while (!anotherIn.eof()) {
        nextChar = (unsigned char)anotherIn.get();
        anotherOut << nextChar;
    }
    anotherOut.flush();
}

/* TODO: Main program that runs the compress */
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

    // checks if a given file name is valid
    if (!fu.isValidFile(argv[2]) || fu.isEmptyFile(argv[2])) {
        std::ofstream out(argv[3]);
        return -1;
    }

    if (strcmp(argv[1], "--ascii") == 0) {
        isAsciiOutput = true;
    }

    if (isAsciiOutput) {
        pseudoCompression(argv[2], argv[3]);
    } else {
        trueCompression(argv[1], argv[2]);
    }

    return 0;
}