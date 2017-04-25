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

    std::string fileName = "textoDePrueba.txt";

    TextView textView(window);
    TextDocument doc;

    doc.init(fileName);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                std::cout << "click\n";
                // textView.mouseClick(event.x, event.y);
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

        window.clear();

        window.setView(textView.getCameraView());

        textView.drawLines(window, doc);

        window.display();
    }

    return 0;
}
