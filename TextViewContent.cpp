#include "TextViewContent.h"

TextViewContent::TextViewContent() {
    this->font.loadFromFile("FreeMono.ttf");
    this->setFontSize(20);  // Important to call
    this->cursor = Cursor(this->lineHeight, this->charWidth);
}

void TextViewContent::moveCursorDown() {
    this->cursor.moveDown();
}

// TODO: Considerar la posicion correcta cuando no hay los suficientes caracteres o la linea no existe
//       Pensar si me conviene manejarlo desde aca o desde el TextView
void TextViewContent::setCursorPos(int line, int charPos) {
    this->cursor.setPosition(line, charPos);
}

// TODO: Reemplazar fontSize por fontHeight especifica para cada tipo de font.
// TODO: Que el texto de seleccion tenga tambien un rectangulo coloreado de fondo
// TODO: Multiples cursores similar a Selecciones, que los moveUp.. etc muevan todos
void TextViewContent::drawLines(sf::RenderWindow &window, TextDocument &document) {
    for (int lineNumber = 0; lineNumber < document.getLineCount(); lineNumber++) {

        string line = document.getLine(lineNumber);

        string currentLineText = "";
        float offsetx = 0;
        bool previousSelected = false;

        for (int charIndexInLine = 0; charIndexInLine < (int)line.size(); charIndexInLine++) {

            // En general hay una unica seleccion, en el futuro podria haber mas de una
            bool currentSelected = this->selections.isSelected(lineNumber, charIndexInLine);

            // Cuando hay un cambio, dibujo el tipo de seleccion anterior
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
        }
    }

    this->cursor.draw(window);
}

// [start, end] is inclusive
void TextViewContent::selectText(int startLineN, int startCharN, int endLineN, int endCharN) {
    this->selections.addSelection(startLineN, startCharN, endLineN, endCharN);
}

void TextViewContent::removeSelections() {
    this->selections.removeSelections();
}

SelectionData::Selection TextViewContent::getLastSelection() {
    return this->selections.getLastSelection();
}

void TextViewContent::setFontSize(int fontSize) {
    this->fontSize = fontSize;
    this->lineHeight = fontSize;

    // HACK: Because I use only monospace fonts, every char is the same width
    //       so I get the width drawing a single character
    sf::Text tmpText;
    tmpText.setFont(this->font);
    tmpText.setCharacterSize(this->fontSize);
    tmpText.setString("c");
    float textwidth = tmpText.getGlobalBounds().width;
    this->charWidth = textwidth;
}

// TODO: Divide fontsize from lineheight
int TextViewContent::getLineHeight() {
    return this->lineHeight;
}

int TextViewContent::getCharWidth() {
    return this->charWidth;
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

