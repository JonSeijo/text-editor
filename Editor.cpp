#include <SFML/Graphics.hpp>
#include "TextView.h"
#include "TextDocument.h"

void controlarMovimientosTeclado(TextView &textView) {
    // Scrolling
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        textView.scrollUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        textView.scrollDown();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        textView.scrollLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        textView.scrollRight();
    }

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

    // std::string fileName = "textoDePrueba.txt";
    std::string fileName = "TextView.cpp";

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
                sf::String input(event.text.unicode);
                textView.addToLastLine(input, document);
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
