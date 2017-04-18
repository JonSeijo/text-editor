#ifndef TextDocument_H
#define TextDocument_H

#include <iostream>
#include <string>
#include <fstream>

typedef void* HANDLE;

using std::string;
using std::vector;


class TextDocument {

    public:
        TextDocument();
        ~TextDocument();

        bool init(string &filename);
        int getline(int lineNumber);
        int linecount();

    private:
        bool init_linebuffer();
        string buffer;
        int length;
        vector<int> lineBuffer;
};

#endif
