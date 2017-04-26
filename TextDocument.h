#ifndef TextDocument_H
#define TextDocument_H

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

#include <string>

typedef void* HANDLE;

using std::string;
using std::vector;


class TextDocument {

    public:
        TextDocument();
        ~TextDocument();

        bool init(string &filename);
        string getLine(int lineNumber);
        int charsInLine(int line) const;
        int getLineCount() const;

    private:
        bool init_linebuffer();
        string buffer;
        int length;
        vector<int> lineBuffer;
};

#endif
