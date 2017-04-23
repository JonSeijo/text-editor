#ifndef TextViewContent_H
#define TextViewContent_H

#include <SFML/Graphics.hpp>
#include "TextDocument.h"
#include "TextViewContent.h"

class TextViewContent {
    public:
        TextViewContent();
        ~TextViewContent();
        void setFontSize(int fontSize);
        void drawLines(sf::RenderWindow &window, TextDocument &document);
        sf::View getView();

    private:
        int fontSize;
        sf::Font font;
        sf::String toUtf32(const std::string& text);

        TextViewCamera cameraView;
};

#endif
