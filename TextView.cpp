#include "TextView.h"

TextView::TextView() {

}

TextView::~TextView() {

}

// TODO: Limites del textview podrian pasarse por parametros idk
// La idea es usar window.draw para dibujar las lineas del documento
void TextView::draw(const sf::RenderWindow &window, const TextDocument &document) {

    // TEST
    for (int i = 1; i < 20; i++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, i*20)),
            sf::Vertex(sf::Vector2f(200, i*20))
        };
        // window.draw(line);
    }


}
