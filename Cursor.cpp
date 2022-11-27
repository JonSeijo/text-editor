#include "Cursor.h"

Curs::Cursor::Cursor() : Cursor(0, 0){};

Curs::Cursor::Cursor(int lineN, int charN) {
    this->maxCharNReached = 0;
    this->updatePos(lineN, charN);
}

// updateMaxChar=false por defecto
void Curs::Cursor::setPosition(int lineN, int charN, bool updateMaxChar) {
    this->updatePos(lineN, charN);
    if (updateMaxChar) {
        this->setMaxCharNReached(this->charN);
    }
}

int Curs::Cursor::getLineN() {
    return this->lineN;
}

int Curs::Cursor::getCharN() {
    return this->charN;
}

void Curs::Cursor::setMaxCharNReached(int charN) {
    this->maxCharNReached = charN;
}

int Curs::Cursor::getMaxCharNReached() {
    return this->maxCharNReached;
}

void Curs::Cursor::moveUp() {
    this->updatePos(this->lineN - 1, this->charN);
}

void Curs::Cursor::moveDown() {
    this->updatePos(this->lineN + 1, this->charN);
}

void Curs::Cursor::moveUpToMaxCharN() {
    this->updatePos(this->lineN - 1, this->maxCharNReached);
}

void Curs::Cursor::moveDownToMaxCharN() {
    this->updatePos(this->lineN + 1, this->maxCharNReached);
}

// updateMaxChar=false por defecto
void Curs::Cursor::moveLeft(bool updateMaxChar) {
    if (updateMaxChar) {
        this->setMaxCharNReached(this->charN - 1);
    }
    this->updatePos(this->lineN, this->charN - 1);
}

// updateMaxChar=false por defecto
void Curs::Cursor::moveRight(bool updateMaxChar) {
    if (updateMaxChar) {
        this->setMaxCharNReached(this->charN + 1);
    }
    this->updatePos(this->lineN, this->charN + 1);
}

void Curs::Cursor::moveToEnd(int charsInLine, bool updateMaxChar) {
    if (updateMaxChar) {
        this->setMaxCharNReached(charsInLine);
    }
    this->updatePos(this->lineN, charsInLine);
}

void Curs::Cursor::moveToStart(bool updateMaxChar) {
    if (updateMaxChar) {
        this->setMaxCharNReached(0);
    }
    this->updatePos(this->lineN, 0);
}

void Curs::Cursor::nextLine() {
    this->charN = 0;
    this->moveDown();
}

void Curs::Cursor::updatePos(int l, int c) {
    this->lineN = l;
    this->charN = c;
}