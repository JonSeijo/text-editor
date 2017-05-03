#include <SFML/Graphics.hpp>
#include "TextView.h"
#include "TextDocument.h"

void controlarMovimientos(TextView &textView) {
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
    sf::RenderWindow window(sf::VideoMode(720, 405), "text-editor", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

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
        }

        controlarMovimientos(textView);

        // TODO: Esto asume que siempre que esta el mouse presionado se esta seleccionando
        // TODO: Ubicar el textview con variables genericas (No magic numbers)
        // TODO: Que la velocidad del scroll varie dependiendo de cuan fuera de la ventana estoy
        // TODO: No permitir scrollear mas alla del textview
        if (isMouseDown) {
            auto mousepos = sf::Mouse::getPosition(window);
            auto mousepos_text = window.mapPixelToCoords(mousepos);

            textView.cursorActive(mousepos_text.x, mousepos_text.y, document);

            if (mousepos.y < 0) {
                textView.scrollUp();
            } else if (mousepos.y > 400) {
                textView.scrollDown();
            }

            if (mousepos.x < 0) {
                textView.scrollLeft();
            } else if (mousepos.x > 720) {
                textView.scrollRight();
            }

        }

        window.clear();

        window.setView(textView.getCameraView());

        textView.drawLines(window, document);

        window.display();
    }

    return 0;
}
