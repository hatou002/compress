// #include "compressor.h"
// #include "minHeap.h"
// #include "reading_file.h"
// #include "HuffmanCoding.h"
// #include <fstream>
// #include <iostream>
// #include <map>
// #include <string>

// extern "C" {

// void compress_file(const char *input_file, const char *output_file) {
//     string filename = input_file;
//    string outputFilename = output_file;

//    ifstream test_input(filename);
//     if (!test_input) {
//         cerr << "Error: Unable to open input file: " << filename << std::endl;
//         return;
//     }
//     test_input.close();

//     ofstream test_output(outputFilename);
//     if (!test_output) {
//         cerr << "Error: Unable to open output file: " << outputFilename << std::endl;
//         return;
//     }
//     test_output.close();

//     map<char, int> freq = getfrequentchar(filename);
//     minHeap heap(freq);
//     HuffmanCoding huffman(heap);
//     map<std::string, std::string> huffmanCodes = huffman.getHuffmanCodes();

//     ofstream fout(outputFilename, std::ios::binary);
//     if (!fout) {
//        cerr << "Error: Unable to write to output file: " << outputFilename << endl;
//         return;
//     }
//     fout << huffmanCodes;
//     writeBits(filename, fout, huffmanCodes);
//     fout.close();

//     cout << "Compressed file created successfully: " << outputFilename << endl;
// }

// }
#include "compressor.h"
#include "minHeap.h"
#include "reading_file.h"
#include "HuffmanCoding.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>

extern "C" {

void compress_file(const char *input_file, const char *output_file) {
    string filename = input_file;
    string outputFilename = output_file;

    ifstream test_input(filename);
    if (!test_input) {
        cerr << "Error: Unable to open input file: " << filename << std::endl;
        return;
    }
    test_input.close();

    ofstream test_output(outputFilename);
    if (!test_output) {
        cerr << "Error: Unable to open output file: " << outputFilename << std::endl;
        return;
    }
    test_output.close();

    map<char, int> freq = getfrequentchar(filename);
    minHeap heap(freq);
    HuffmanCoding huffman(heap);
    map<std::string, std::string> huffmanCodes = huffman.getHuffmanCodes();

    ofstream fout(outputFilename, std::ios::binary);
    if (!fout) {
       cerr << "Error: Unable to write to output file: " << outputFilename << endl;
        return;
    }
    fout << huffmanCodes;
    writeBits(filename, fout, huffmanCodes);
    fout.close();

    cout << "Compressed file created successfully: " << outputFilename << endl;
}

void decompress_file(const char *input_file, const char *output_file) {
    string inputFilename = input_file;
    string outputFilename = output_file;

    ifstream test_input(inputFilename);
    if (!test_input) {
        cerr << "Error: Unable to open input file: " << inputFilename << std::endl;
        return;
    }
    test_input.close();

    ofstream test_output(outputFilename);
    if (!test_output) {
        cerr << "Error: Unable to open output file: " << outputFilename << std::endl;
        return;
    }
    test_output.close();

    HuffmanCoding huffmanForDecompression;
    huffmanForDecompression.decodeBits(inputFilename, outputFilename);

    cout << "Decompressed file created successfully: " << outputFilename << endl;
}

}
