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
        void moveLeft();
        void moveRight();

        void nextLine();

        int getLineN();
        int getCharN();

        void setPosition(int lineN, int charN);

    private:
        sf::RectangleShape rect;
        int height;
        int charWidth;
        int lineN, charN;
        int offsetY;

        void updatePos(int posY, int posX);
};


#endif
