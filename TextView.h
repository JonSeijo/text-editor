#ifndef TextView_H
#define TextView_H

#include <SFML/Graphics.hpp>
#include "TextDocument.h"

class TextView {
    public:
        TextView();
        ~TextView();
        void draw(const sf::RenderWindow &window, const TextDocument &document);

    private:


};

#endif
