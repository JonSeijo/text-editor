#ifndef TextDocument_H
#define TextDocument_H

#include <SFML/Graphics.hpp>
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
        bool init(string &filename);
        sf::String getLine(int lineNumber);
        int charsInLine(int line) const;
        int getLineCount() const;

    private:
        bool init_linebuffer();
        sf::String buffer;
        int length;
        vector<int> lineBuffer;

        sf::String toUtf32(const std::string& inString);
};

#endif
