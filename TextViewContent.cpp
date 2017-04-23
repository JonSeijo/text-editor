#include "TextViewContent.h"

TextViewContent::TextViewContent() {
    this->fontSize = 20;
    this->font.loadFromFile("FreeMono.ttf");
}

// TODO: Limites del textviewContent podrian pasarse por parametros idk
// La idea es usar window.draw para dibujar las lineas del documento
void TextViewContent::drawLines(sf::RenderWindow &window, TextDocument &document) {
    sf::Vector2u windowSize = window.getSize();
    int fontSize = 20;

    for (int i = 0; i < document.getLineCount(); i++) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, i * this->fontSize)),
            sf::Vertex(sf::Vector2f(windowSize.x, i * this->fontSize))
        };

        sf::Text textLine;
        textLine.setFont(font);

        // Estoy leyendo la misma string muchas veces, contando conversiones y todo..
        // Quiza me convenga usar sf::string[wide] desde el principio
        textLine.setString(this->toUtf32(document.getLine(i)));

        textLine.setCharacterSize(this->fontSize);
        textLine.setPosition(0, i * this->fontSize);

        // window.draw(line, 2, sf::Lines);
        window.draw(textLine);
    }
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

