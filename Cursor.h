#ifndef Cursor_H
#define Cursor_H

#include <SFML/Graphics.hpp>

class Cursor {
    public:
        Cursor(int height, int charWidth);
        Cursor(int height, int charWidth, int posX, int posY);

        void draw(sf::RenderWindow &window);

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void nextLine();

        void setHeight(int height);
        void setCharWidth(int charWidth);

    private:
        sf::RectangleShape rect;
        int height;
        int charWidth;
        int posX, posY;

        void updatePos(int posX, int posY);
};


#endif
