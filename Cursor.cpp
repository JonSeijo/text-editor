#include "Cursor.h"

Cursor::Cursor() : Cursor(0, 0) {};

Cursor::Cursor(int height, int charWidth) : Cursor(height, charWidth, 0, 0) {}

Cursor::Cursor(int height, int charWidth, int posX, int posY) {
    this->height = height;
    this->charWidth = charWidth;
    this->posX = posX;
    this->posY = posY;
    this->offsetY = 4;
    this->rect = sf::RectangleShape(sf::Vector2f(2, height));
    this->rect.setFillColor(sf::Color::White);
    this->updatePos(this->posX, this->posY);
}

void Cursor::draw(sf::RenderWindow &window) {
    window.draw(this->rect);
}

void Cursor::setPosition(int lineN, int charN) {
    this->posY = this->height * lineN;
    this->posX = this->charWidth * charN;
    this->updatePos(this->posX, this->posY);
}

void Cursor::moveUp() {
    this->posY -= this->height;
    this->updatePos(this->posX, this->posY);
}

void Cursor::moveDown() {
    this->posY += this->height;
    this->updatePos(this->posX, this->posY);
}

void Cursor::moveLeft() {
    this->posX -= this->charWidth;
    this->updatePos(this->posX, this->posY);
}

void Cursor::moveRight() {
    this->posX += this->charWidth;
    this->updatePos(this->posX, this->posY);
}

void Cursor::nextLine() {
    this->posX = 0;
    this->moveDown();
}

void Cursor::setHeight(int height) {
    this->height = height;
}

void Cursor::setCharWidth(int charWidth) {
    this->charWidth = charWidth;
}

void Cursor::updatePos(int x, int y) {
    this->rect.setPosition(x, y + this->offsetY);
}
