#include "MenuBar.h"
#include <iostream>

MenuBar::MenuBar(
	const sf::RenderWindow &window,
	EditorContent &EditorContent) : 
	content(EditorContent), Camera(sf::FloatRect(-40, 0, window.getSize().x, window.getSize().y)),
	deltaScroll(20), deltaRotation(2), deltaZoomIn(0.8f), deltaZoomOut(1.2f),
	rect(sf::Vector2f(500,30)) {

	// ===< FONT >===
	// this->font.loadFromFile("fonts/");

	
}

void MenuBar::draw(sf::RenderWindow& window) {
	// this->bottomLimitPx = this->content.linesCount() * 13;
	window.draw(this->rect);

	


}