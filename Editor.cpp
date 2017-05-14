#include <SFML/Graphics.hpp>
#include "TextView.h"
#include "TextDocument.h"
#include "InputController.h"

void controlarMovimientosTeclado(TextView &textView) {
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
}

int main() {

    int resolutionX = 720;
    int resolutionY = 405;

    // TODO: Poder expandir la ventada a gusto
    sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "text-editor");
    window.setVerticalSyncEnabled(true);
    sf::Color backgroundColor = sf::Color(21, 29, 45);

    std::string saveFileName = "txt/textoDePruebaGuardado.txt";
    std::string fileName = "txt/textoDePruebaGuardado.txt";
    // std::string fileName = "TextView.cpp";

    TextView textView(window);
    TextDocument document;
    InputController inputController;

    document.init(fileName);

    bool isMouseDown = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                resolutionX = event.size.width;
                resolutionY = event.size.height;
                textView.setCameraBounds(resolutionX, resolutionY);
            }
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
                isMouseDown = true;
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                isMouseDown = false;
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

                if (event.key.code == sf::Keyboard::S && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    document.saveFile(saveFileName);
                    std::cout << "GUARDADO A: " << saveFileName << "\n";
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

        controlarMovimientosTeclado(textView);

        // TODO: Esto asume que siempre que esta el mouse presionado se esta seleccionando
        // TODO: Ubicar el textview con variables genericas (No magic numbers)
        // TODO: No permitir scrollear mas alla del textview
        if (isMouseDown) {
            auto mousepos = sf::Mouse::getPosition(window);
            auto mousepos_text = window.mapPixelToCoords(mousepos);

            textView.cursorActive(mousepos_text.x, mousepos_text.y, document);

            float scrollDeltaX = 0;
            float scrollDeltaY = 0;

            float textViewTop = 0;
            float textViewBottom = resolutionY - 5;
            float textViewLeft = 0;
            float textViewRight = resolutionX;

            float relativeFactor = 3;

            float distanceToTop = std::abs(mousepos.y - textViewTop);
            float distanceToBottom = std::abs(mousepos.y - textViewBottom);
            float distanceToLeft = std::abs(mousepos.x - textViewLeft);
            float distanceToRight = std::abs(mousepos.x - textViewRight);

            if (mousepos.x < textViewLeft) {
                scrollDeltaX = -distanceToLeft / relativeFactor;
            } else if (mousepos.x > textViewRight) {
                scrollDeltaX = distanceToRight / relativeFactor;
            }

            if (mousepos.y < textViewTop) {
                scrollDeltaY = -distanceToTop / relativeFactor;
            } else if (mousepos.y > textViewBottom) {
                scrollDeltaY = distanceToBottom / relativeFactor;
            }

            textView.scroll(scrollDeltaX, scrollDeltaY);
        }

        window.clear(backgroundColor);

        window.setView(textView.getCameraView());

        textView.draw(window, document);

        window.display();
    }

    return 0;
}
