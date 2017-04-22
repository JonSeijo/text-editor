#include <SFML/Graphics.hpp>
#include "TextView.h"
#include "TextDocument.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(720, 405), "text-editor", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    std::string fileName = "textoDePrueba.txt";
    TextView textView;
    TextDocument doc;

    doc.init(fileName);

    sf::View cameraview(sf::FloatRect(0, 0, 720, 405));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            cameraview.move(0, -8);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            cameraview.move(0, 8);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            cameraview.rotate(1.5f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            cameraview.rotate(-1.5f);
        }

        window.clear();

        window.setView(cameraview);

        textView.drawLines(window, doc);
        window.display();
    }

    return 0;
}
