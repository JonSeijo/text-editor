#ifndef TextView_H
#define TextView_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Cursor.h"
#include "TextViewContent.h"

class TextView {
   public:
    TextView(const sf::RenderWindow &window, const sf::String &workingDirectory);

    void draw(sf::RenderWindow &window, TextDocument &document);
    void setFontSize(int fontSize);

    void selectText(int startLineN, int startCharN, int endLineN, int endCharN);
    void removeSelections();
    bool deleteSelections(TextDocument &document);
    sf::String copySelections(TextDocument &document);

    void startSelectionFromMouse(float mouseX, float mouseY, const TextDocument &document);
    void startSelectionFromCursor();
    void cursorActive(float mouseX, float mouseY, const TextDocument &document);

    void addTextInCursorPos(sf::String text, TextDocument &document);
    void deleteTextAfterCursorPos(int amount, TextDocument &document);
    void deleteTextBeforeCursorPos(int amount, TextDocument &document);

    bool moveCursorLeft(const TextDocument &document, bool updateActiveSelections = false);
    void moveCursorRight(const TextDocument &document, bool updateActiveSelections = false);
    void moveCursorUp(const TextDocument &document, bool updateActiveSelections = false);
    void moveCursorDown(const TextDocument &document, bool updateActiveSelections = false);

    void moveCursorToEnd(const TextDocument &document, bool updateActiveSelections = false);
    void moveCursorToStart(const TextDocument &document, bool updateActiveSelections = false);

    void duplicateCursorLine(TextDocument &document);
    void swapCursorLine(TextDocument &document, bool swapWithUp);
    void swapSelectedLines(TextDocument &document, bool swapWithUp);

    void scrollUp(sf::RenderWindow &window);
    void scrollDown(sf::RenderWindow &window);
    void scrollLeft(sf::RenderWindow &window);
    void scrollRight(sf::RenderWindow &window);

    void scrollTo(float x, float y);

    void rotateLeft();
    void rotateRight();

    void zoomIn();
    void zoomOut();

    sf::View getCameraView();
    void setCameraBounds(int width, int height);

    void setDeltaScroll(float delta);
    void setDeltaRotation(float delta);

   private:
    void handleSelectionOnCursorMovement(bool updateActiveSelections);

    TextViewContent content;

    struct DocCoords {
        int lineN;
        int charN;
        DocCoords() : lineN(-1), charN(-1) {}
        DocCoords(int lineN, int charN) : lineN(lineN), charN(charN) {}
    };

    DocCoords getDocumentCoords(float mouseX, float mouseY, const TextDocument &document);

    Cursor cursor;

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
