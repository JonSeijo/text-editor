#include "TextViewContent.h"

TextViewContent::TextViewContent(const sf::String &workingDirectory) {
    this->bottomLimitPx = 1;
    this->rightLimitPx = 1;

    this->font.loadFromFile(workingDirectory + "fonts/DejaVuSansMono.ttf");
    this->setFontSize(18);  // Important to call
    this->colorChar = sf::Color::White;
    this->colorSelection = sf::Color(106, 154, 232);
}

// TODO: Reemplazar fontSize por fontHeight especifica para cada tipo de font.
// TODO: Multiples cursores similar a Selecciones, que los moveUp.. etc muevan todos
// TODO: Que devuelva un vector diciendo el alto que ocupa el dibujo de cada linea, para saber el tamaño de cada linea en el margen
void TextViewContent::drawLines(sf::RenderWindow &window, TextDocument &document) {
    this->bottomLimitPx = document.getLineCount() * this->fontSize;

    for (int lineNumber = 0; lineNumber < document.getLineCount(); lineNumber++) {
        sf::String line = document.getLine(lineNumber);
        sf::String currentLineText = "";

        this->rightLimitPx = std::max((int)this->rightLimitPx, (int)(this->charWidth * line.getSize()));

        float offsetx = 0;
        bool previousSelected = false;

        for (int charIndexInLine = 0; charIndexInLine <= (int)line.getSize(); charIndexInLine++) {
            // En general hay una unica seleccion, en el futuro podria haber mas de una
            bool currentSelected = this->selections.isSelected(lineNumber, charIndexInLine);

            // Cuando hay un cambio, dibujo el tipo de seleccion anterior
            // Tambien dibujo cuando es el fin de la linea actual
            if (currentSelected != previousSelected || charIndexInLine == (int)line.getSize()) {
                sf::Text texto;
                texto.setFillColor(this->colorChar);
                texto.setFont(font);
                texto.setString(currentLineText);
                texto.setCharacterSize(this->fontSize);
                texto.setPosition(offsetx, lineNumber * this->fontSize);

                if (previousSelected) {
                    sf::RectangleShape selectionRect(sf::Vector2f(this->charWidth * currentLineText.getSize(), this->fontSize));
                    selectionRect.setFillColor(this->colorSelection);
                    // TODO: Que el +2 no sea un numero magico
                    selectionRect.setPosition(offsetx, 2 + lineNumber * this->fontSize);
                    window.draw(selectionRect);
                }

                window.draw(texto);

                previousSelected = currentSelected;
                offsetx += this->charWidth * currentLineText.getSize();
                currentLineText = "";
            }

            // Voy acumulando la string de la linea actual
            currentLineText += line[charIndexInLine];
        }
    }
}

void TextViewContent::createNewSelection(int anclaLine, int anclaChar) {
    this->selections.createNewSelection(anclaLine, anclaChar);
}

void TextViewContent::updateLastSelection(int lineN, int charN) {
    this->selections.updateLastSelection(lineN, charN);
}

void TextViewContent::removeSelections() {
    this->selections.removeSelections();
}

SelectionData::Selection TextViewContent::getLastSelection() {
    return this->selections.getLastSelection();
}

// TODO: Divide fontsize from lineheight
void TextViewContent::setFontSize(int fontSize) {
    this->fontSize = fontSize;
    this->lineHeight = fontSize;

    // HACK: Because I use only monospace fonts, every char is the same width
    //       so I get the width drawing a single character (A WIDE ONE TO BE SURE)
    sf::Text tmpText;
    tmpText.setFont(this->font);
    tmpText.setCharacterSize(this->fontSize);
    tmpText.setString("_");
    float textwidth = tmpText.getLocalBounds().width;
    this->charWidth = textwidth;
}

float TextViewContent::getRightLimitPx() {
    return this->rightLimitPx;
}

float TextViewContent::getBottomLimitPx() {
    return this->bottomLimitPx;
}

int TextViewContent::getLineHeight() {
    return this->lineHeight;
}

int TextViewContent::getCharWidth() {
    return this->charWidth;
}
