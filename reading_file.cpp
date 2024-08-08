#include "reading_file.h"

map<char, int> getfrequentchar(const string &filename) {
    map<char, int> frequent;

    ifstream fin;
    fin.open(filename);
    if (!fin) {
        cout << "file doesn't exist" << endl;
    } else {
        char c;
        while (fin >> noskipws >> c) {
            bool found = false;
            for (map<char, int>::iterator it = frequent.begin(); it != frequent.end(); it++) {
                if (c == it->first) {
                    it->second += 1;
                    found = true;
                    break;
                }
            }
            if (!found) {
                frequent[c] = 1;
            }
        }
    }
    
    fin.close();
    return frequent;
}

ostream& operator<<(ostream &out, const map<string, string> &cmap) {
    for (map<string, string>::const_iterator it = cmap.begin(); it != cmap.end(); ++it) {
        out << it->first << ":" << it->second << "\n";
    }
    out <<  "END_OF_CODES\n";
    return out;
}

