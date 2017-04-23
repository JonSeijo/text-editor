#ifndef TextView_H
#define TextView_H

#include <SFML/Graphics.hpp>
#include "TextDocument.h"
#include "TextViewCamera.h"

class TextView {
    public:
        TextView();
        ~TextView();
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
