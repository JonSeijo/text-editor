#pragma once
#include "SFML/Graphics.hpp"
#include "Content.h"
#include <cmath>

#define LINE_HEIGHT     30


class EditorView {
	public:
        EditorView(const sf::RenderWindow& window,
            const sf::String& workingDirectory,
            EditorContent& editorContent);

        void draw(sf::RenderWindow& window);
        void setFontSize(int fontSize);

        void scrollUp(sf::RenderWindow& window);
        void scrollDown(sf::RenderWindow& window);
        void scrollLeft(sf::RenderWindow& window);
        void scrollRight(sf::RenderWindow& window);
        void FontSizeScrollChangeDown();
        void FontSizeScrollChangeUp();

        void scrollTo(float x, float y);

        void rotateLeft();
        void rotateRight();

        void zoomIn();
        void zoomOut();

        int getLineHeight();
        int getCharWidth();

        float getRightLimitPx();
        float getBottomLimitPx();

        sf::View getCameraView();
        void setCameraBounds(int width, int height);

        void setDeltaScroll(float delta);
        void setDeltaRotation(float delta);

        // TODO: Replace std::pair with coordinates object
        std::pair<int, int> getDocumentCoords(float mouseX, float mouseY);

private:
    EditorContent& content;

    void drawLines(sf::RenderWindow& window);
    void drawCursor(sf::RenderWindow& window);

    sf::Font font;
    int fontSize = 13;
    int marginXOffset;
    sf::Color colorMargin;

    int MaxFontSize = 40;
    int MinFontSize = 9;

    int lineHeight;
    int charWidth;

    float rightLimitPx;
    float bottomLimitPx;

    sf::Color colorChar;
    sf::Color colorSelection;

    sf::View camera;
    float deltaScroll;
    float deltaRotation;
    float deltaZoomIn, deltaZoomOut;


};