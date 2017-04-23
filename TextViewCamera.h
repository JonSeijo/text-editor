#ifndef TextViewCamera_H
#define TextViewCamera_H

#include <SFML/Graphics.hpp>

class TextViewCamera {

    public:
        TextViewCamera();
        TextViewCamera(float posX, float posY);

        void scrollUp();
        void scrollDown();
        void scrollLeft();
        void scrollRight();

        void scroll(float deltaX, float deltaY);
        void scrollTo(float x, float y);

        void rotateLeft();
        void rotateRight();

        sf::View getCameraView();

        void setDeltaScroll(float delta);
        void setDeltaRotation(float delta);

    private:
        float posX, posY;
        float deltaScroll;
        float deltaRotation;
        sf::View cameraView;

};

#endif