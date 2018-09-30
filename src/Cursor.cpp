#include "Cursor.h"

Cursor::Cursor() : Cursor(0, 0){};

Cursor::Cursor(int height, int charWidth) : Cursor(height, charWidth, 0, 0) {}

Cursor::Cursor(int height, int charWidth, int lineN, int charN) {
    this->height = height;
    this->charWidth = charWidth;
    this->offsetY = 2;
    this->maxCharNReached = 0;
    this->rect = sf::RectangleShape(sf::Vector2f(2, height));
    this->rect.setFillColor(sf::Color::White);
    this->updatePos(lineN, charN);
}

void Cursor::draw(sf::RenderWindow &window) {
    window.draw(this->rect);
}

// updateMaxChar=false por defecto
void Cursor::setPosition(int lineN, int charN, bool updateMaxChar) {
    this->updatePos(lineN, charN);
    if (updateMaxChar) {
        this->setMaxCharNReached(this->charN);
    }
}

int Cursor::getLineN() {
    return this->lineN;
}

int Cursor::getCharN() {
    return this->charN;
}

void Cursor::setMaxCharNReached(int charN) {
    this->maxCharNReached = charN;
}

int Cursor::getMaxCharNReached() {
    return this->maxCharNReached;
}

void Cursor::moveUp() {
    this->updatePos(this->lineN - 1, this->charN);
}

void Cursor::moveDown() {
    this->updatePos(this->lineN + 1, this->charN);
}

void Cursor::moveUpToMaxCharN() {
    this->updatePos(this->lineN - 1, this->maxCharNReached);
}

void Cursor::moveDownToMaxCharN() {
    this->updatePos(this->lineN + 1, this->maxCharNReached);
}

// updateMaxChar=false por defecto
void Cursor::moveLeft(bool updateMaxChar) {
    if (updateMaxChar) {
        this->setMaxCharNReached(this->charN - 1);
    }
    this->updatePos(this->lineN, this->charN - 1);
}

// updateMaxChar=false por defecto
void Cursor::moveRight(bool updateMaxChar) {
    if (updateMaxChar) {
        this->setMaxCharNReached(this->charN + 1);
    }
    this->updatePos(this->lineN, this->charN + 1);
}

void Cursor::moveToEnd(int charsInLine, bool updateMaxChar) {
    if (updateMaxChar) {
        this->setMaxCharNReached(charsInLine);
    }
    this->updatePos(this->lineN, charsInLine);
}

void Cursor::moveToStart(bool updateMaxChar) {
    if (updateMaxChar) {
        this->setMaxCharNReached(0);
    }
    this->updatePos(this->lineN, 0);
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
        (this->lineN * this->height) + this->offsetY);
}
