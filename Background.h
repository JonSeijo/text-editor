#pragma once

#include "SFML/Graphics.hpp"

// =======< MAIN BACKGROUND COLOR >==========

sf::Color bgColor = sf::Color{ 23, 25, 33 };

sf::ConvexShape polygon[6];

using namespace sf;

void Backgroundcolor(sf::RenderWindow &window) {
	
	polygon[0].setPointCount(10);
	polygon[0].setFillColor(bgColor);
	polygon[0].setPoint(0, Vector2f(4200, 300));
	polygon[0].setPoint(1, Vector2f(300, -420));
	polygon[0].setPoint(2, Vector2f(-220, 100));
	polygon[0].setPoint(3, Vector2f(120, 1400));
	polygon[0].setPoint(4, Vector2f(-440, 1200));
	polygon[0].setPoint(5, Vector2f(20, 100));
	polygon[0].setPosition(100, 50);



	for (int i = 0; i < 6; i++)
	{
		window.draw(polygon[i]);
	}

	window.display();
	
}