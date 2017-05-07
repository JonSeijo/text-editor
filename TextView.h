#ifndef TextView_H
#define TextView_H

#include <SFML/Graphics.hpp>
#include "TextViewContent.h"
#include <cmath>

class TextView {

    public:
        TextView(const sf::RenderWindow &window);

        void draw(sf::RenderWindow &window, TextDocument &document);
        void setFontSize(int fontSize);

        void selectText(int startLineN, int startCharN, int endLineN, int endCharN);
        void removeSelections();

        void startSelection(float mouseX, float mouseY, const TextDocument &document);
        void cursorActive(float mouseX, float mouseY, const TextDocument &document);

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

        void addToLastLine(sf::String text, TextDocument &document);

    private:
        TextViewContent content;

        struct DocCoords {
            int lineN;
            int charN;
            DocCoords() : lineN(-1), charN(-1) {}
            DocCoords(int lineN, int charN) : lineN(lineN), charN(charN) {}
        };

        DocCoords getDocumentCoords(float mouseX, float mouseY, const TextDocument &document);

        sf::Font font;
        int fontSize;
        int marginXOffset;
        sf::Color colorMargin;

        sf::View camera;
        float deltaScroll;
        float deltaRotation;
        float deltaZoomIn, deltaZoomOut;
};

#endif
