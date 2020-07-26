#ifndef InputController_H
#define InputController_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TextDocument.h"
#include "EditorView.h"

class InputController {
   public:
    InputController(EditorContent &editorContent);
    void handleConstantInput(TextDocument &document, EditorView &view, sf::RenderWindow &window);
    void handleEvents(TextDocument &document, EditorView &view, sf::RenderWindow &window, sf::Event &event);
    bool isMouseDown();

   private:
    void handleMouseEvents(TextDocument &document, EditorView &view, sf::RenderWindow &window, sf::Event &event);
    void handleKeyPressedEvents(TextDocument &document, EditorView &view, sf::Event &event);
    void handleKeyReleasedEvents(sf::Event &event);
    void handleTextEnteredEvent(TextDocument &document, EditorView &view, sf::Event &event);
    bool mouseDown;
    bool shiftPressed;
    sf::String stringCopied;

    EditorContent& editorContent;
};

#endif
