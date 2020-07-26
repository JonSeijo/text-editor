#include "Cursor.h"

Cursor::Cursor() : Cursor(0, 0){};

Cursor::Cursor(int lineN, int charN) {
    this->maxCharNReached = 0;
    this->updatePos(lineN, charN);
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

void Cursor::updatePos(int l, int c) {
    this->lineN = l;
    this->charN = c;
}
