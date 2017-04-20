#include "TextView.h"

TextView::TextView() {
    this->fontSize = 20;
}

TextView::~TextView() {

}

// TODO: Limites del textview podrian pasarse por parametros idk
// La idea es usar window.draw para dibujar las lineas del documento
void TextView::drawLines(sf::RenderWindow &window, const TextDocument &document) {
    sf::Vector2u windowSize = window.getSize();
    int fontSize = 20;

    // TEST
    for (int i = 0; i < windowSize.y; i += this->fontSize) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, i)),
            sf::Vertex(sf::Vector2f(windowSize.x, i))
        };
        window.draw(line, 2, sf::Lines);
    }
}


void TextView::setFontSize(int fontSize) {
    this->fontSize = fontSize;
}
