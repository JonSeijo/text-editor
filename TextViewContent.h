#ifndef TextViewContent_H
#define TextViewContent_H

#include <SFML/Graphics.hpp>
#include "TextDocument.h"
#include "TextViewContent.h"
#include "SelectionData.h"
#include "Cursor.h"

class TextViewContent {
    public:
        TextViewContent();

        void setFontSize(int fontSize);
        void drawLines(sf::RenderWindow &window, TextDocument &document);

        void selectText(int startLineN, int startCharN, int endLineN, int endCharN);
        void removeSelections();
        SelectionData::Selection getLastSelection();


        void moveCursorDown();
        void setCursorPos(int line, int charPos);

        int getLineHeight();
        int getCharWidth();

    private:
        int fontSize;
        int lineHeight;
        int charWidth;
        sf::Font font;
        sf::String toUtf32(const std::string& text);

        SelectionData selections;
        Cursor cursor;
};

#endif
