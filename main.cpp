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

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        textView.drawLines(window, doc);
        window.display();
    }

    return 0;
}
