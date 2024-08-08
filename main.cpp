#include "minHeap.h"
#include "HuffmanCoding.h"
#include "reading_file.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

int main() {
    string filename = "test_file.txt";
    string outputFilename = "test_file.bin";
    string decompressedFilename = "test_file_decompressed.txt";

    // Compression
    map<char, int> freq = getfrequentchar(filename);
    minHeap heap(freq);
    HuffmanCoding huffman(heap);
    map<string, string> huffmanCodes = huffman.getHuffmanCodes();

    ofstream fout(outputFilename, ios::binary);
    if (!fout) {
        cerr << "Error: Unable to open output file: " << outputFilename << endl;
        return 1;
    }
    writeHuffmanCodes(fout, huffmanCodes);
    writeBits(filename, fout, huffmanCodes);
    fout.close();

    cout << "Compressed file created successfully: " << outputFilename << endl;

    // Decompression
    ifstream fin(outputFilename, ios::binary);
    if (!fin) {
        cerr << "Error: Unable to open compressed file: " << outputFilename << endl;
        return 1;
    }
    map<string, string> readCodes = readHuffmanCodes(fin);
    HuffmanCoding huffmanForDecompression(readCodes);

    huffmanForDecompression.decodeBits(outputFilename, decompressedFilename);

    cout << "Decompressed file created successfully: " << decompressedFilename << endl;

    return 0;
}
