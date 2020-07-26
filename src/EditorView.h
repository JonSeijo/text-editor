#ifndef TextView_H
#define TextView_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Cursor.h"
#include "EditorContent.h"

class EditorView {
   public:
    EditorView(const sf::RenderWindow &window,
        const sf::String &workingDirectory,
        EditorContent &editorContent);

    void drawLines(sf::RenderWindow &window, TextDocument &document);

    void draw(sf::RenderWindow &window, TextDocument &document);
    void setFontSize(int fontSize);

    void selectText(int startLineN, int startCharN, int endLineN, int endCharN);
    void removeSelections();

    void startSelectionFromMouse(float mouseX, float mouseY, const TextDocument &document);
    void startSelectionFromCursor();
    void cursorActive(float mouseX, float mouseY, const TextDocument &document);

    void scrollUp(sf::RenderWindow &window);
    void scrollDown(sf::RenderWindow &window);
    void scrollLeft(sf::RenderWindow &window);
    void scrollRight(sf::RenderWindow &window);

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

   private:
    EditorContent &content;

    struct DocCoords {
        int lineN;
        int charN;
        DocCoords() : lineN(-1), charN(-1) {}
        DocCoords(int lineN, int charN) : lineN(lineN), charN(charN) {}
    };

    DocCoords getDocumentCoords(float mouseX, float mouseY, const TextDocument &document);
    void drawCursor(sf::RenderWindow &window);

    sf::Font font;
    int fontSize;
    int marginXOffset;
    sf::Color colorMargin;

    int lineHeight;
    int charWidth;

    float rightLimitPx;
    float bottomLimitPx;

    sf::Color colorChar;
    sf::Color colorSelection;

    // TODO: SHOULD REMOVE FROM VIEW
    Cursor &cursor;

    sf::View camera;
    float deltaScroll;
    float deltaRotation;
    float deltaZoomIn, deltaZoomOut;
};

#endif
