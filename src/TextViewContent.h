#ifndef TextViewContent_H
#define TextViewContent_H

#include <SFML/Graphics.hpp>
#include "TextDocument.h"
#include "SelectionData.h"

class TextViewContent {
    public:
        TextViewContent();

        void setFontSize(int fontSize);
        void drawLines(sf::RenderWindow &window, TextDocument &document);

        void createNewSelection(int anclaLine, int anclaChar);
        void updateLastSelection(int lineN, int charN);

        void removeSelections();
        SelectionData::Selection getLastSelection();

        int getLineHeight();
        int getCharWidth();

    private:
        int fontSize;
        int lineHeight;
        int charWidth;
        sf::Font font;

        sf::Color colorChar;
        sf::Color colorSelection;

        SelectionData selections;
};

#endif
