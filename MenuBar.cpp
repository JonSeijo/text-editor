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

void MenuBar::drawLines(sf::RenderWindow& window) {
 
    for (int lineNumber = 0; lineNumber < 10; lineNumber++) {
        sf::String line = this->content.getLine(lineNumber);
        
        sf::String currentLineText = "";

        // TODO: Esto es al pe?
        this->rightLimitPx = std::max((int)this->rightLimitPx, (int)(this->charWidth * line.getSize()));

        float offsetx = 0;
        bool previousSelected = false;

        for (int charIndexInLine = 0; charIndexInLine <= (int)line.getSize(); charIndexInLine++) {
            // En general hay una unica seleccion, en el futuro podria haber mas de una
            bool currentSelected = content.isSelected(lineNumber, charIndexInLine);

  

            // Voy acumulando la string de la linea actual
            currentLineText += line[charIndexInLine];
        }
    }
}

void MenuBar::draw(sf::RenderWindow& window) {
  //  this->drawLines(window);

    // Dibujo los numeros de la izquierda

    // TODO: Hacer una clase separada para el margin
    for (int lineNumber = 1; lineNumber <= 6; lineNumber++) {
        int lineHeight = 1;

        int blockHeight = lineHeight * this->fontSize;

      //  sf::Text lineNumberText;
      //  lineNumberText.setFillColor(sf::Color::White);
      //  lineNumberText.setFont(this->font);
      //  lineNumberText.setString(std::to_string(lineNumber));
      //  lineNumberText.setCharacterSize(this->fontSize - 1);
      //  lineNumberText.setPosition(-this->marginXOffset, blockHeight * (lineNumber - 1));

     //   sf::RectangleShape marginRect(sf::Vector2f(this->marginXOffset - 5, blockHeight));
     //  marginRect.setFillColor(this->colorMargin);
     //  marginRect.setFillColor(sf::Color{200,200,200});
     //   marginRect.setPosition(-this->marginXOffset, blockHeight * (lineNumber - 1));
     //
     //   window.draw(marginRect);
     //   window.draw(lineNumberText);

        sf::RectangleShape RectBar;
        RectBar.setSize(sf::Vector2f(1200, 520));
        RectBar.setOutlineColor(sf::Color::Red);
        RectBar.setOutlineThickness(5);
        RectBar.setPosition(110, 210);
        window.draw(RectBar);

    }

}