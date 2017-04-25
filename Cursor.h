#ifndef Cursor_H
#define Cursor_H

#include <SFML/Graphics.hpp>
#include <iostream>

// TODO: Estoy teniendo que mantener las posiciones en posX, posY y tambien actualizarlas en el rect
//       Quiza convenga hacerlo de forma mas automatica, con algun "movePos" o algo asi

class Cursor {
    public:
        Cursor();
        Cursor(int height, int charWidth);
        Cursor(int height, int charWidth, int posX, int posY);

        void draw(sf::RenderWindow &window);

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void nextLine();

        void setPosition(int lineN, int charN);

        void setHeight(int height);
        void setCharWidth(int charWidth);

    private:
        sf::RectangleShape rect;
        int height;
        int charWidth;
        int posX, posY;
        int offsetY;

        void updatePos(int posX, int posY);
};


#endif
