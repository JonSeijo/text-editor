#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(720, 405), "text-editor", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    
    sf::Font font;
    font.loadFromFile("FreeMono.ttf");

    sf::Text texto;
    texto.setFont(font);
    texto.setString("Testtesttest");
    texto.setCharacterSize(24);



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(texto);

        window.display();
    }

    return 0;
}