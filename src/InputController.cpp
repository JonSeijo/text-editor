#include "InputController.h"

void InputController::handleEvents(TextDocument &document, TextView &textView, sf::RenderWindow &window, sf::Event &event) {

    if(event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            textView.scrollUp();
        } else {
            textView.scrollDown();
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        textView.removeSelections();
        auto mousepos = sf::Mouse::getPosition(window);
        auto mousepos_text = window.mapPixelToCoords(mousepos);

        // inicio seleccion cuando clickeo.
        // Borro desde fuera explicitamente las selecciones
        // TODO: Multiples selecciones, sin borrar anteriores si presiono ctrl
        textView.startSelection(mousepos_text.x, mousepos_text.y, document);
        this->mouseDown = true;
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        this->mouseDown = false;
    }

    if (event.type == sf::Event::KeyPressed) {

        if (event.key.code == sf::Keyboard::Up) {
            textView.moveCursorUp(document);
        }
        if (event.key.code == sf::Keyboard::Down) {
            textView.moveCursorDown(document);
        }
        if (event.key.code == sf::Keyboard::Left) {
            textView.moveCursorLeft(document);
        }
        if (event.key.code == sf::Keyboard::Right) {
            textView.moveCursorRight(document);
        }

        if (event.key.control) {
            if (event.key.code == sf::Keyboard::Add) {
                textView.zoomIn();
            }
            if (event.key.code == sf::Keyboard::Subtract) {
                textView.zoomOut();
            }
        }
    }

    if (event.type == sf::Event::TextEntered) {
        bool ctrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
        sf::String input(event.text.unicode);
        if (event.text.unicode == '\b') {
            bool selecionDeleted = textView.deleteSelections(document);
            if (!selecionDeleted) {
                textView.deleteTextBeforeCursorPos(1, document);
            }
        } else if (event.text.unicode == 127) {  // 127 = delete (supr)
            bool selecionDeleted = textView.deleteSelections(document);
            if (!selecionDeleted) {
                textView.deleteTextAfterCursorPos(1, document);
            }
        // Escribir normalmente solo si ctrl no esta presionado
        } else if (!ctrlPressed) {
            if (event.text.unicode == '\t') {
                // TODO: Cantidad de espacios de tab una variable
                input = "    ";
            }
            textView.deleteSelections(document);
            textView.addTextInCursorPos(input, document);
        }

    }

}

void InputController::handleConstantInput(TextDocument &document, TextView &view) {

}

bool InputController::isMouseDown() {
    return this->mouseDown;
}