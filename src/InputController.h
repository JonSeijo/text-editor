#ifndef InputController_H
#define InputController_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TextDocument.h"
#include "TextView.h"


class InputController {
    public:
        void handleConstantInput(TextDocument &document, TextView &view);
        void handleEvents(TextDocument &document, TextView &view, sf::Event &event);
};

#endif