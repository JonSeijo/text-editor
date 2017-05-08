#include "Cursor.h"

Cursor::Cursor() : Cursor(0, 0) {};

Cursor::Cursor(int height, int charWidth) : Cursor(height, charWidth, 0, 0) {}

Cursor::Cursor(int height, int charWidth, int posX, int posY) {
    this->height = height;
    this->charWidth = charWidth;
    this->offsetY = 2;
    this->rect = sf::RectangleShape(sf::Vector2f(2, height));
    this->rect.setFillColor(sf::Color::White);
    this->updatePos(posX, posY);
}

void Cursor::draw(sf::RenderWindow &window) {
    window.draw(this->rect);
}

void Cursor::setPosition(int lineN, int charN) {
    this->updatePos(lineN, charN);
}

int Cursor::getPosY() {
    return this->posY;
}

int Cursor::getPosX() {
    return this->posX;
}

void Cursor::moveUp() {
    this->updatePos(this->posX, this->posY - 1);
}

void Cursor::moveDown() {
    this->updatePos(this->posX, this->posY + 1);
}

void Cursor::moveLeft() {
    this->updatePos(this->posX - 1, this->posY);
}

void Cursor::moveRight() {
    this->updatePos(this->posX + 1, this->posY);
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
    this->posX = x;
    this->posY = y;
    this->rect.setPosition(x*this->charWidth, y*this->height + this->offsetY);
}
