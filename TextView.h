#ifndef TextView_H
#define TextView_H

#include <SFML/Graphics.hpp>
#include "TextViewContent.h"
#include <cmath>

class TextView {

    public:
        TextView(const sf::RenderWindow &window);

        void drawLines(sf::RenderWindow &window, TextDocument &document);
        void setFontSize(int fontSize);

        void selectText(int startLineN, int startCharN, int endLineN, int endCharN);
        void removeSelections();

        void cursorChange(float mouseX, float mouseY, const TextDocument &document, bool keepSelection=false);

        void scrollUp();
        void scrollDown();
        void scrollLeft();
        void scrollRight();

        void scroll(float deltaX, float deltaY);
        void scrollTo(float x, float y);

        void rotateLeft();
        void rotateRight();

        void zoomIn();
        void zoomOut();

        sf::View getCameraView();

        void setDeltaScroll(float delta);
        void setDeltaRotation(float delta);


    private:
        TextViewContent content;

        sf::View camera;
        float deltaScroll;
        float deltaRotation;
        float deltaZoomIn, deltaZoomOut;
};

#endif
