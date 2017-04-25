#include "TextViewContent.h"

TextViewContent::TextViewContent() {
    this->fontSize = 20;
    this->font.loadFromFile("FreeMono.ttf");

    // TODO: que el 4 deje de ser un magic number
    this->cursor = Cursor(20, 20, 0, 4);
}

void TextViewContent::moveCursorDown() {
    this->cursor.moveDown();
}

// TODO: Reemplazar fontSize por fontHeight especifica para cada tipo de font.
// TODO: Que el texto de seleccion tenga tambien un rectangulo coloreado de fondo
void TextViewContent::drawLines(sf::RenderWindow &window, TextDocument &document) {
    int charIndexInFullText = 0;

    for (int lineNumber = 0; lineNumber < document.getLineCount(); lineNumber++) {

        string line = document.getLine(lineNumber);

        string currentLineText = "";
        float offsetx = 0;
        bool previousSelected = false;

        for (int charIndexInLine = 0; charIndexInLine < (int)line.size(); charIndexInLine++) {

            // En general hay una unica seleccion, en el futuro podria haber mas de una
            bool currentSelected = this->selections.isSelected(charIndexInFullText);

            // Cuando hay un cambio, dibujo el tipo de seleccion anterior (que fue acumulado en charIndexInFullText)
            // Tambien dibujo cuando es el fin de la linea actual
            if (currentSelected != previousSelected || charIndexInLine == (int)line.size()-1) {

                sf::Text texto;
                texto.setColor(previousSelected ? sf::Color::Magenta : sf::Color::White);
                texto.setFont(font);
                texto.setString(this->toUtf32(currentLineText));
                texto.setCharacterSize(this->fontSize);
                texto.setPosition(offsetx, lineNumber*this->fontSize);

                window.draw(texto);

                previousSelected = currentSelected;
                currentLineText = "";
                offsetx += texto.getLocalBounds().width;
            }

            // Voy acumulando la string de la linea actual
            currentLineText += line[charIndexInLine];

            // Importante para saber cual es el caracter actual pertenece a una seleccion
            charIndexInFullText++;
        }
    }

    this->cursor.draw(window);
}

// [start, end] is inclusive
void TextViewContent::selectText(int start, int end) {
    this->selections.addSelection(start, end);
}

void TextViewContent::removeSelections() {
    this->selections.removeSelections();
}

void TextViewContent::setFontSize(int fontSize) {
    this->fontSize = fontSize;
}

sf::String TextViewContent::toUtf32(const std::string& inString) {
    sf::String outString = "";
    auto iterEnd = inString.cend();

    // Decode avanza el iterador
    for (auto iter = inString.cbegin(); iter != iterEnd; ) {
        sf::Uint32 out;
        iter = sf::Utf8::decode(iter, iterEnd, out);
        outString += out;
    }

    return outString;
}

