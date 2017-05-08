#include "Cursor.h"

Cursor::Cursor() : Cursor(0, 0) {};

Cursor::Cursor(int height, int charWidth) : Cursor(height, charWidth, 0, 0) {}

Cursor::Cursor(int height, int charWidth, int lineN, int charN) {
    this->height = height;
    this->charWidth = charWidth;
    this->offsetY = 2;
    this->rect = sf::RectangleShape(sf::Vector2f(2, height));
    this->rect.setFillColor(sf::Color::White);
    this->updatePos(lineN, charN);
}

void Cursor::draw(sf::RenderWindow &window) {
    window.draw(this->rect);
}

void Cursor::setPosition(int lineN, int charN) {
    this->updatePos(lineN, charN);
}

int Cursor::getLineN() {
    return this->lineN;
}

int Cursor::getCharN() {
    return this->charN;
}

void Cursor::moveUp() {
    this->updatePos(this->lineN - 1, this->charN);
}

void Cursor::moveDown() {
    this->updatePos(this->lineN + 1, this->charN);
}

void Cursor::moveLeft() {
    this->updatePos(this->lineN, this->charN - 1);
}

void Cursor::moveRight() {
    this->updatePos(this->lineN, this->charN + 1);
}

void Cursor::nextLine() {
    this->charN = 0;
    this->moveDown();
}

void Cursor::setHeight(int height) {
    this->height = height;
}

void Cursor::setCharWidth(int charWidth) {
    this->charWidth = charWidth;
}

void Cursor::updatePos(int l, int c) {
    this->lineN = l;
    this->charN = c;
    this->rect.setPosition(
        this->charN * this->charWidth,
        (this->lineN * this->height) + this->offsetY
    );
}
