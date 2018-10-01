#include "InputController.h"

InputController::InputController() {
    this->mouseDown = false;
    this->shiftPresionado = false;
}

void InputController::handleEvents(TextDocument &document, TextView &textView,
                                   sf::RenderWindow &window, sf::Event &event) {
    this->handleMouseEvents(document, textView, window, event);
    this->handleKeyPressedEvents(document, textView, event);
    this->handleKeyReleasedEvents(event);
    this->handleTextEnteredEvent(document, textView, event);
}

void InputController::handleConstantInput(TextDocument &document, TextView &textView,
                                          sf::RenderWindow &window) {
    // Rotating
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                textView.rotateLeft();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                textView.rotateRight();
            }
        }
    }

    // TODO: Esto asume que siempre que esta el mouse presionado se esta seleccionando
    // TODO: Ubicar el textview con variables genericas (No magic numbers)
    // TODO: No permitir scrollear mas alla del textview
    if (this->isMouseDown()) {
        auto mousepos = sf::Mouse::getPosition(window);
        auto mousepos_text = window.mapPixelToCoords(mousepos);

        textView.cursorActive(mousepos_text.x, mousepos_text.y, document);

        float textViewTop = 0;
        float textViewBottom = window.getView().getSize().y - 5;
        float textViewLeft = 0;
        float textViewRight = window.getView().getSize().x;

        if (mousepos.x < textViewLeft) {
            textView.scrollLeft(window);
        } else if (mousepos.x > textViewRight) {
            textView.scrollRight(window);
        }

        if (mousepos.y < textViewTop) {
            textView.scrollUp(window);
        } else if (mousepos.y > textViewBottom) {
            textView.scrollDown(window);
        }
    }
}

void InputController::handleMouseEvents(TextDocument &document, TextView &textView,
                                        sf::RenderWindow &window, sf::Event &event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            if (event.mouseWheelScroll.delta > 0) {
                textView.scrollUp(window);
            } else {
                textView.scrollDown(window);
            }
        } else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
            if (event.mouseWheelScroll.delta > 0) {
                textView.scrollLeft(window);
            } else {
                textView.scrollRight(window);
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        textView.removeSelections();
        auto mousepos = sf::Mouse::getPosition(window);
        auto mousepos_text = window.mapPixelToCoords(mousepos);

        // inicio seleccion cuando clickeo.
        // Borro desde fuera explicitamente las selecciones
        // TODO: Multiples selecciones, sin borrar anteriores si presiono ctrl
        textView.startSelectionFromMouse(mousepos_text.x, mousepos_text.y, document);
        this->mouseDown = true;
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        this->mouseDown = false;
    }
}

void InputController::handleKeyPressedEvents(TextDocument &document, TextView &textView, sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        bool isCtrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

        bool isShiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

        bool isEndPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::End);

        bool isHomePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Home);

        if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) {
            if (!this->shiftPresionado && !isCtrlPressed) {
                this->shiftPresionado = true;
                // Si no hay una seleccion activa, empiezo una seleccion donde esten los cursores
                textView.startSelectionFromCursor();
                return;
            }
        }

        //Move to END
        if (isEndPressed) {
            textView.moveCursorToEnd(document, isShiftPressed);
            return;
        } else if (isHomePressed) {  //Move to LINE_START
            textView.moveCursorToStart(document, isShiftPressed);
            return;
        }

        bool ctrlAndShift = isCtrlPressed && isShiftPressed;

        if (isCtrlPressed) {
            if (event.key.code == sf::Keyboard::D) {
                textView.duplicateCursorLine(document);
            } else if (event.key.code == sf::Keyboard::U) {
                textView.deleteSelections(document);
                sf::String emoji = "\\_('-')_/";
                textView.addTextInCursorPos(emoji, document);
            } else if (event.key.code == sf::Keyboard::C) {  //Copy command, Ctrl + C
                this->stringCopied = textView.copySelections(document);
            } else if (event.key.code == sf::Keyboard::V) {  //Paste command, Ctrl + V
                textView.addTextInCursorPos(stringCopied, document);
            } else if (event.key.code == sf::Keyboard::X) {  //Cut command, Ctrl + X
                this->stringCopied = textView.copySelections(document);
                textView.deleteSelections(document);
            }
        }

        // TODO: Swapping selections is buggy
        if (event.key.code == sf::Keyboard::Up) {
            if (ctrlAndShift) {
                textView.swapSelectedLines(document, true);
                textView.moveCursorUp(document, true);
                return;
            } else {
                textView.moveCursorUp(document, this->shiftPresionado);
                return;
            }
        }
        if (event.key.code == sf::Keyboard::Down) {
            if (ctrlAndShift) {
                textView.swapSelectedLines(document, false);
                textView.moveCursorDown(document, true);
                return;
            } else {
                textView.moveCursorDown(document, this->shiftPresionado);
                return;
            }
        }
        if (event.key.code == sf::Keyboard::Left) {
            textView.moveCursorLeft(document, this->shiftPresionado && !isCtrlPressed);
            return;
        }
        if (event.key.code == sf::Keyboard::Right) {
            textView.moveCursorRight(document, this->shiftPresionado && !isCtrlPressed);
            return;
        }

        if (event.key.control) {
            if (event.key.code == sf::Keyboard::Add) {
                textView.zoomIn();
                return;
            }
            if (event.key.code == sf::Keyboard::Subtract) {
                textView.zoomOut();
                return;
            }
        }
    }
}

void InputController::handleKeyReleasedEvents(sf::Event &event) {
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) {
            this->shiftPresionado = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
        }
    }
}

void InputController::handleTextEnteredEvent(TextDocument &document, TextView &textView, sf::Event &event) {
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

bool InputController::isMouseDown() {
    return this->mouseDown;
}