#ifndef InputController_H
#define InputController_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TextDocument.h"
#include "TextView.h"

class InputController {
   public:
    InputController();
    void handleConstantInput(TextDocument &document, TextView &view, sf::RenderWindow &window);
    void handleEvents(TextDocument &document, TextView &view, sf::RenderWindow &window, sf::Event &event);
    bool isMouseDown();

   private:
    void handleMouseEvents(TextDocument &document, TextView &view, sf::RenderWindow &window, sf::Event &event);
    void handleKeyPressedEvents(TextDocument &document, TextView &view, sf::Event &event);
    void handleKeyReleasedEvents(sf::Event &event);
    void handleTextEnteredEvent(TextDocument &document, TextView &view, sf::Event &event);
    bool mouseDown;
    bool shiftPresionado;
    sf::String stringCopied;
};

#endif
