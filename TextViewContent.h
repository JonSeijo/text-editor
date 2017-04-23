#ifndef TextViewContent_H
#define TextViewContent_H

#include <SFML/Graphics.hpp>
#include "TextDocument.h"
#include "TextViewContent.h"
#include "SelectionData.h"

class TextViewContent {
    public:
        TextViewContent();

        void setFontSize(int fontSize);
        void drawLines(sf::RenderWindow &window, TextDocument &document);

        void selectText(int start, int end);

    private:
        int fontSize;
        sf::Font font;
        sf::String toUtf32(const std::string& text);

        SelectionData selections;
};

#endif
