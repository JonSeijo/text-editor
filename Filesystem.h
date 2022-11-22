#pragma once

#include "SFML/Graphics.hpp"

sf::Event evt;

void Openfiledialog(sf::RenderWindow &window) {
  /*  TODO */ 
}

void Exitfromeditor(sf::RenderWindow& window) {

    // SAVIND BEFORE EXIT 
    // .....
    //

    if (evt.type == sf::Event::KeyPressed) {
        if (evt.key.code == sf::Keyboard::Escape)
            window.close();
    }
}