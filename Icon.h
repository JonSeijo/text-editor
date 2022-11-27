#pragma once

#include "SFML/Graphics.hpp"

void SetIcon(sf::RenderWindow& window) {
	sf::Image Icon;
	Icon.loadFromFile("Icon.png");
	window.setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());
}