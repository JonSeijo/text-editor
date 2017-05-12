#include <SFML/Graphics.hpp>
#include "TextView.h"
#include "TextDocument.h"

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
    // TODO: Poder expandir la ventada a gusto
    sf::RenderWindow window(sf::VideoMode(720, 405), "text-editor", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::Color backgroundColor = sf::Color(21, 29, 45);

    std::string saveFileName = "textoDePruebaGuardado.txt";
    std::string fileName = "textoDePruebaGuardado.txt";
    // std::string fileName = "TextView.cpp";

    TextView textView(window);
    TextDocument document;

    document.init(fileName);

    bool isMouseDown = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
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
                    std::cout << "CTRL + S = SAVE\n";
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
            float textViewBottom = 400;
            float textViewLeft = 0;
            float textViewRight = 720;

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
