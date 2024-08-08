#include "HuffmanCoding.h"
#include <bitset>
#include <vector>
#include <sstream>


HuffmanCoding::HuffmanCoding(){
    root= NULL;
}
// Constructor to build Huffman tree from minHeap
HuffmanCoding::HuffmanCoding(minHeap& heap) {
    root = buildHuffmanTree(heap);
    generateCodes(root, "");
}

// Constructor to build Huffman tree from Huffman codes map
HuffmanCoding::HuffmanCoding(const map<string, string> &huffmanCodes) {
    root = new element();
    for (map<string, string>::const_iterator it = huffmanCodes.begin(); it != huffmanCodes.end(); ++it) {
        insertCode(it->first, it->second);
    }
}

element* HuffmanCoding::buildHuffmanTree(minHeap& heap) {
    while (heap.getNum() > 1) {
        element left = heap.getAr()[1];
        heap.removemin();
        element right = heap.getAr()[1];
        heap.removemin();

        element internalNode("NOCHAR", left.count + right.count);
        internalNode.left = new element(left);
        internalNode.right = new element(right);

        heap.insertelement(internalNode);
    }
    return new element(heap.getAr()[1]);
}

void HuffmanCoding::inorderPrinting(element* root) const {
    if (root == NULL) return;

    queue<element*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        while (levelSize > 0) {
            element* current = q.front();
            q.pop();
            cout << current->character << ": " << current->count << " ";

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);

            --levelSize;
        }
        cout << endl;  // Newline for new level
    }
}

void HuffmanCoding::generateCodes(element* root, const string& str) {
    if (!root) return;

    if (root->character != "NOCHAR") {
        huffmanCodes[root->character] = str;
    }

    generateCodes(root->left, str + "0");
    generateCodes(root->right, str + "1");
}

void HuffmanCoding::insertCode(const string &character, const string &code) {
    element* current = root;
    for (int i = 0; i < code.size(); ++i) {
        char bit = code[i];
        if (bit == '0') {
            if (current->left == nullptr) {
                current->left = new element();
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = new element();
            }
            current = current->right;
        }
    }
    current->character = character;
}

void writeHuffmanCodes(ofstream &fout, const map<string, string> &huffmanCodes) {
    for (map<string, string>::const_iterator it = huffmanCodes.begin(); it != huffmanCodes.end(); ++it) {
        fout << it->first << ":" << it->second << "\n";
    }
    fout << "END_OF_CODES\n"; // Mark the end of Huffman codes
}

map<string, string> readHuffmanCodes(ifstream &fin) {
    map<string, string> huffmanCodes;
    string line;

    while (getline(fin, line)) {
        if (line == "END_OF_CODES") {
            break;
        }

        size_t delimPos = line.find(':');
        if (delimPos == string::npos) {
            // Ignore invalid format without printing an error message
            continue;
        }

        string key = line.substr(0, delimPos);
        string value = line.substr(delimPos + 1);
        huffmanCodes[key] = value;
    }

    fin.clear(); // Clear EOF flag
    fin.seekg(0, ios::cur); // Move to the current position (after END_OF_CODES)
    return huffmanCodes;
}

void writeBits(const string &inputFilename, ofstream &fout, const map<string, string> &huffmanCodes) {
    ifstream fin(inputFilename, ios::binary);
    if (!fin) {
        cerr << "Failed to open input file: " << inputFilename << endl;
        return;
    }

    vector<bool> bits;
    char c;
    while (fin.get(c)) {
        string key(1, c); // Convert character to string to use as a key
        if (huffmanCodes.find(key) != huffmanCodes.end()) {
            string code = huffmanCodes.at(key);
            for (int i = 0; i < code.size(); ++i) {
                bits.push_back(code[i] == '1');
            }
        } else {
            cerr << "Character '" << c << "' not found in Huffman codes map." << endl;
        }
    }

    // Add EOF code
    if (huffmanCodes.find("EOF") != huffmanCodes.end()) {
        string eofCode = huffmanCodes.at("EOF");
        for (int i = 0; i < eofCode.size(); ++i) {
            bits.push_back(eofCode[i] == '1');
        }
    }

    // Ensure the encoded bits are a multiple of 8
    while (bits.size() % 8 != 0) {
        bits.push_back(false); // Padding with zeros
    }

    // Writing bits to file
    for (size_t i = 0; i < bits.size(); i += 8) {
        bitset<8> byte;
        for (size_t j = 0; j < 8; ++j) {
            byte[j] = bits[i + j];
        }
        fout.put(static_cast<unsigned char>(byte.to_ulong()));
    }

    fin.close();
}

void HuffmanCoding::decodeBits(const string &inputFilename, const string &outputFilename) {
    ifstream fin(inputFilename, ios::binary);
    if (!fin) {
        cerr << "Failed to open input file: " << inputFilename << endl;
        return;
    }

    ofstream fout(outputFilename, ios::binary);
    if (!fout) {
        cerr << "Failed to open output file: " << outputFilename << endl;
        return;
    }

    // Read the Huffman map from the file
    map<string, string> huffmanCodes = readHuffmanCodes(fin);

    // Reconstruct the Huffman tree from the Huffman codes map
    HuffmanCoding huffman(huffmanCodes);

    // Read bits from file
    vector<bool> bits;
    char byte;
    while (fin.get(byte)) {
        bitset<8> b(byte);
        for (int i = 0; i < 8; ++i) {
            bits.push_back(b[i]);
        }
    }

    // Decode bits using Huffman tree
    element* current = huffman.root;
    for (size_t i = 0; i < bits.size(); ++i) {
        if (bits[i]) {
            current = current->right;
        } else {
            current = current->left;
        }

        if (current->left == nullptr && current->right == nullptr) {
            if (current->character == "EOF") {
                break;
            }
            fout.put(current->character[0]);
            current = huffman.root;
        }
    }

    fin.close();
    fout.close();
}
