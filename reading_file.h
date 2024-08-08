#ifndef READING_FILE_H
#define READING_FILE_H

#include <iostream>
#include <map>
#include <fstream>
#include <string>

using namespace std;

map<char, int> getfrequentchar(const string &filename);

ostream& operator<<(ostream &out, const map<string, string> &cmap);

#endif // READING_FILE_H
