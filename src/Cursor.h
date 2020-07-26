#ifndef Cursor_H
#define Cursor_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Cursor {
   public:
    Cursor();
    Cursor(int lineN, int charN);

    void moveUp();
    void moveDown();
    void moveLeft(bool updateMaxChar = false);
    void moveRight(bool updateMaxChar = false);

    void moveToEnd(int charsInLine, bool updateMaxChar = false);
    void moveToStart(bool updateMaxChar = false);

    void nextLine();

    int getLineN();
    int getCharN();

    void setPosition(int lineN, int charN, bool updateMaxChar = false);

    void moveDownToMaxCharN();
    void moveUpToMaxCharN();

    void setMaxCharNReached(int charN);
    int getMaxCharNReached();

   private:
    int lineN, charN;
    int maxCharNReached;

    void updatePos(int posY, int posX);
};

#endif
