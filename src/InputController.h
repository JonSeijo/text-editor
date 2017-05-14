#ifndef InputController_H
#define InputController_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TextDocument.h"
#include "TextView.h"


class InputController {
    public:
        void handleConstantInput(TextDocument &document, TextView &textView);
        void handleEvents(TextDocument &document, TextView &view, sf::RenderWindow &window, sf::Event &event);
        bool isMouseDown();

    private:
        bool mouseDown;

};

#endif