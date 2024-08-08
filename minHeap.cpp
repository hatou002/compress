#include "HuffmanCoding.h"
#include "minHeap.h"
#include "reading_file.h"
#include <queue>
#include <bitset>
#include <fstream>
#include <vector>
using namespace std ;
minHeap::minHeap(map<char, int>& q) {
    capacity = q.size() + 1;
    ar = new element[capacity];
    num = 0;
    for (map<char, int>::iterator it = q.begin(); it != q.end(); it++) {
        string s(1, it->first); 
        element e(s, it->second);
        insertelement(e);
    }
     element eofElement("EOF", 1);
    insertelement(eofElement);
}

void minHeap::insertelement(element e) {
    if (num >= capacity) {
        cout << "Heap is full" << endl;
        return;
    }
    ar[++num] = e;
    bubbleup(num);
}

void minHeap::bubbleup(int index) {
    int i = index;
    while (i > 1 && ar[i / 2].count > ar[i].count) {
        swap(ar[i], ar[i / 2]);
        i = i / 2;
    }
}

void minHeap::swap(element& a, element& b) {
    element temp = a;
    a = b;
    b = temp;
}

element* minHeap::buildTree() {
    if (num == 0) return NULL;

    for (int i = 1; i <= num; ++i) {
        if (2 * i <= num) ar[i].left = &ar[2 * i];
        if (2 * i + 1 <= num) ar[i].right = &ar[2 * i + 1];
    }
    return &ar[1];
}

void minHeap::removemin() {
    if (num == 0) return;
    ar[1] = ar[num--];
    fixMinHeap(1);
}

void minHeap::fixMinHeap(int index) {
    int i = index;
    while ((2 * i <= num && ar[i].count > ar[2 * i].count) ||
           (2 * i + 1 <= num && ar[i].count > ar[2 * i + 1].count)) {
        if (2 * i + 1 > num || ar[2 * i].count <= ar[2 * i + 1].count) {
            swap(ar[i], ar[2 * i]);
            i = 2 * i;
        } else {
            swap(ar[i], ar[2 * i + 1]);
            i = 2 * i + 1;
        }
    } 
}
minHeap::~minHeap() {
    delete[] ar;
}

