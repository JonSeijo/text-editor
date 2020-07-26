#include "InputController.h"

InputController::InputController(EditorContent &editorContent)
    : editorContent(editorContent) {
    this->mouseDown = false;
    this->shiftPressed = false;
}

void InputController::handleEvents(
    EditorView &textView,
    sf::RenderWindow &window,
    sf::Event &event) {

    this->handleMouseEvents(textView, window, event);
    this->handleKeyPressedEvents(textView, event);
    this->handleKeyReleasedEvents(event);
    this->handleTextEnteredEvent(textView, event);
}

void InputController::handleConstantInput(EditorView &textView,
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

        updateCursorInEditor(textView, mousepos_text.x, mousepos_text.y);

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

void InputController::handleMouseEvents(
    EditorView &textView,
    sf::RenderWindow &window,
    sf::Event &event) {

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
        textView.startSelectionFromMouse(mousepos_text.x, mousepos_text.y);
        this->mouseDown = true;
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        this->mouseDown = false;
    }
}

void InputController::handleKeyPressedEvents(EditorView &textView, sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        bool isCtrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);

        bool isShiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

        bool isEndPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::End);

        bool isHomePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Home);

        if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) {
            if (!this->shiftPressed && !isCtrlPressed) {
                this->shiftPressed = true;
                // Si no hay una seleccion activa, empiezo una seleccion donde esten los cursores
                textView.startSelectionFromCursor();
                return;
            }
        }

        //Move to END
        if (isEndPressed) {
            editorContent.moveCursorToEnd(isShiftPressed);
            return;
        } else if (isHomePressed) {  //Move to LINE_START
            editorContent.moveCursorToStart(isShiftPressed);
            return;
        }

        bool ctrlAndShift = isCtrlPressed && isShiftPressed;

        if (isCtrlPressed) {
            if (event.key.code == sf::Keyboard::D) {
                editorContent.duplicateCursorLine();
            } else if (event.key.code == sf::Keyboard::U) {
                editorContent.deleteSelections();
                sf::String emoji = "\\_('-')_/";
                editorContent.addTextInCursorPos(emoji);
            } else if (event.key.code == sf::Keyboard::C) {  //Copy command, Ctrl + C
                this->stringCopied = editorContent.copySelections();
            } else if (event.key.code == sf::Keyboard::V) {  //Paste command, Ctrl + V
                editorContent.addTextInCursorPos(stringCopied);
            } else if (event.key.code == sf::Keyboard::X) {  //Cut command, Ctrl + X
                this->stringCopied = editorContent.copySelections();
                editorContent.deleteSelections();
            }
        }

        // TODO: Swapping selections is buggy
        if (event.key.code == sf::Keyboard::Up) {
            if (ctrlAndShift) {
                editorContent.swapSelectedLines(true);
                editorContent.moveCursorUp(true);
                return;
            } else {
                editorContent.moveCursorUp(this->shiftPressed);
                return;
            }
        }
        if (event.key.code == sf::Keyboard::Down) {
            if (ctrlAndShift) {
                editorContent.swapSelectedLines( false);
                editorContent.moveCursorDown(true);
                return;
            } else {
                editorContent.moveCursorDown(this->shiftPressed);
                return;
            }
        }
        if (event.key.code == sf::Keyboard::Left) {
            editorContent.moveCursorLeft(this->shiftPressed && !isCtrlPressed);
            return;
        }
        if (event.key.code == sf::Keyboard::Right) {
            editorContent.moveCursorRight(this->shiftPressed && !isCtrlPressed);
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
            this->shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
        }
    }
}

void InputController::handleTextEnteredEvent(EditorView &textView, sf::Event &event) {
    if (event.type == sf::Event::TextEntered) {
        bool ctrlPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
        sf::String input(event.text.unicode);

        if (event.text.unicode == '\b') {
            bool selecionDeleted = editorContent.deleteSelections();
            if (!selecionDeleted) {
                editorContent.deleteTextBeforeCursorPos(1);
            }
        } else if (event.text.unicode == 127) {  // 127 = delete (supr)
            bool selecionDeleted = editorContent.deleteSelections();
            if (!selecionDeleted) {
                editorContent.deleteTextAfterCursorPos(1);
            }
            // Escribir normalmente solo si ctrl no esta presionado
        } else if (!ctrlPressed) {
            if (event.text.unicode == '\t') {
                // TODO: Cantidad de espacios de tab una variable
                input = "    ";
            }

            editorContent.deleteSelections();
            editorContent.addTextInCursorPos(input);
        }
    }
}

bool InputController::isMouseDown() {
    return this->mouseDown;
}

// TODO: Agregar parametros para saber si tengo que agregar otro, actualizar selecciones o lo que sea
// TODO: Esta funcion solo sirve para la ultima seleccion, manejarlo por parametros??
void InputController::updateCursorInEditor(EditorView &textView, float mouseX, float mouseY) {
    std::pair<int, int> docCoords = textView.getDocumentCoords(mouseX, mouseY);
    int line = docCoords.first;
    int column = docCoords.second;

    this->editorContent.resetCursor(line, column);

    // ESTO ASUME QUE PUEDO HACER UNA UNICA SELECCION
    // TODO: Usar los metodos moveSelections para mover todas las selecciones.
    this->editorContent.updateLastSelection(line, column);
}