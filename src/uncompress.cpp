/**
 * TODO: file header
 *
 * Author:
 */
#include <fstream>
#include <iostream>

#include <cxxopts.hpp>
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {}

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

    // const int NUM_ARG = 4;
    FileUtils fu;
    const int ASCII_SIZE = 256;
    // // checks if all the necessary informations is given
    // if (sizeof(argv) / sizeof(argv[0]) != NUM_ARG) {
    //     std::cout << "Invalid number of arguments" << std::endl;
    // }
    // checks if a given file name is valid
    if (!fu.isValidFile(argv[2]) && !fu.isEmptyFile(argv[2])) {
        return -1;
    }

    // initializes a frequency array
    vector<unsigned int> freqs(ASCII_SIZE, 0);

    // counts frequecy of each character in a given file
    std::ifstream is(argv[2]);
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
    std::ofstream outputFile(argv[3]);

    while (!is.eof()) {
        byte next = tree->decode(is);
        if (next != NULL) {
            outputFile << next;
        }
    }
    outputFile.flush();

    return 0;
}
