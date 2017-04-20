#ifndef TextView_H
#define TextView_H

#include <SFML/Graphics.hpp>
#include "TextDocument.h"

class TextView {
    public:
        TextView();
        ~TextView();
        void setFontSize(int fontSize);
        void drawLines(sf::RenderWindow &window, TextDocument &document);

    private:
        sf::Font font;
        int fontSize;
};

#endif
