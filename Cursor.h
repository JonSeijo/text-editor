#ifndef Cursor_H
#define Cursor_H

class Cursor {
    public:
        Cursor(int height, int charWidth);
        Cursor(int height, int charWidth, int posX, int posY);

        void draw(sf::RendererWindow &window);

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void nextLine();

        void setHeight(int height);
        void setCharWidth(int charWidth);

    private:
        int height;
        int charWidth;
        int posX, posY;

};


#endif
