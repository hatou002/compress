#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <fstream>
#include "minHeap.h"

using namespace std;

class HuffmanCoding {
private:
    element* root;
    map<string, string> huffmanCodes;
    void generateCodes(element* root, const string& str);
    void insertCode(const string &character, const string &code);

public:
    HuffmanCoding(); 
    HuffmanCoding(minHeap& heap);
    HuffmanCoding(const map<string, string> &huffmanCodes);
    element* buildHuffmanTree(minHeap& heap);
    void inorderPrinting(element* root) const;
    map<string, string> getHuffmanCodes() const { return huffmanCodes; };
    void decodeBits(const string &inputFilename, const string &outputFilename);
};

// Function declarations
void writeHuffmanCodes(ofstream &fout, const map<string, string> &huffmanCodes);
map<string, string> readHuffmanCodes(ifstream &fin);
void writeBits(const string &inputFilename, ofstream &fout, const map<string, string> &huffmanCodes);

#endif // HUFFMANCODING_H
