#ifndef Cursor_H
#define Cursor_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Cursor {
   public:
    Cursor();
    Cursor(int height, int charWidth);
    Cursor(int height, int charWidth, int lineN, int charN);

    void draw(sf::RenderWindow &window);
    void setHeight(int height);
    void setCharWidth(int charWidth);

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
    sf::RectangleShape rect;
    int height;
    int charWidth;
    int lineN, charN;
    int offsetY;
    int maxCharNReached;

    void updatePos(int posY, int posX);
};

#endif
