#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <map>
#include <string>


using namespace std;

struct element {
    int count;
    string character;
    element* left;
    element* right;

    element() {count=0; left=right=NULL;}
    element(string s, int cou) {count=cou; character = s ; left=right=NULL;}
};

class minHeap {
private:
    element* ar;
    int capacity;
    int num;

public:
   // minHeap();
    minHeap(map<char, int>&);
    void insertelement(element e);
    void bubbleup(int index);
    void removemin();
    void fixMinHeap(int index);

    element* buildTree();
    void inorderPrinting(element* root) const;

    int getNum() const { return num; }
    element* getAr() const { return ar; }
    void swap(element& a, element& b);
    ~minHeap();
};

#endif 
