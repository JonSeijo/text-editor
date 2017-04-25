#include <SFML/Graphics.hpp>
#include "TextView.h"
#include "TextDocument.h"

void controlarMovimientos(TextView &textView) {
    // Scrolling
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        textView.scrollDown();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        textView.scrollUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        textView.scrollRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        textView.scrollLeft();
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

void controlarAccionesMouse(sf::RenderWindow &window, TextView &textView, bool isMouseDown) {
    if (isMouseDown) {
        auto mousepos = sf::Mouse::getPosition(window);
        auto mousepos_text = window.mapPixelToCoords(mousepos);
        textView.mouseClick(mousepos_text.x, mousepos_text.y);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(720, 405), "text-editor", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    // std::string fileName = "textoDePrueba.txt";
    std::string fileName = "TextView.cpp";

    TextView textView(window);
    TextDocument doc;

    doc.init(fileName);

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
                textView.mouseClick(mousepos_text.x, mousepos_text.y);
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
        controlarAccionesMouse(window, textView, isMouseDown);

        window.clear();

        window.setView(textView.getCameraView());

        textView.drawLines(window, doc);

        window.display();
    }

    return 0;
}
