#pragma once


#include "Content.h"
#include "SFML/Graphics.hpp"

class MenuBar {

public:

	MenuBar(const sf::RenderWindow &window, EditorContent &content);
	void draw(sf::RenderWindow &window);
	void drawLines(sf::RenderWindow &window);

private:

	EditorContent& content;
	
	// ===< BACKGROUND >===
	sf::RectangleShape rect;


	sf::Font font;

	float rightLimitPx;
	float bottomLimitPx;


    int fontSize = 13;
    int marginXOffset;
    sf::Color colorMargin;

    int MaxFontSize = 40;
    int MinFontSize = 9;

    int lineHeight;
    int charWidth;

    sf::Color colorChar;
    sf::Color colorSelection;


	sf::View Camera;
	float deltaScroll;
	float deltaRotation;
	float deltaZoomIn, deltaZoomOut;
};