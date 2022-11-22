#pragma once


#include "Content.h"
#include "SFML/Graphics.hpp"

class MenuBar {

public:

	MenuBar(const sf::RenderWindow &window, EditorContent &content);
	void draw(sf::RenderWindow &window);

private:

	EditorContent& content;
	
	// ===< BACKGROUND >===
	sf::RectangleShape rect;


	sf::Font font;

	float rightLimitPx;
	float bottomLimitPx;

	sf::View Camera;
	float deltaScroll;
	float deltaRotation;
	float deltaZoomIn, deltaZoomOut;
};