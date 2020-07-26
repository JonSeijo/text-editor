#ifndef EditorContent_H
#define EditorContent_H

#include <SFML/Graphics.hpp>
#include "SelectionData.h"
#include "TextDocument.h"
#include "Cursor.h"

class EditorContent {
   public:
    EditorContent(const sf::String &workingDirectory);

    void setFontSize(int fontSize);
    void drawLines(sf::RenderWindow &window, TextDocument &document);

    void createNewSelection(int anclaLine, int anclaChar);
    void updateLastSelection(int lineN, int charN);

    void removeSelections();
    SelectionData::Selection getLastSelection();

    int getLineHeight();
    int getCharWidth();

    float getRightLimitPx();
    float getBottomLimitPx();

    void duplicateCursorLine(TextDocument &document);
    void swapCursorLine(TextDocument &document, bool swapWithUp);
    void swapSelectedLines(TextDocument &document, bool swapWithUp);

    bool deleteSelections(TextDocument &document);
    sf::String copySelections(TextDocument &document);

    // TODO: Se puede pasar los valores por defecto al .cpp ?
    bool moveCursorLeft(const TextDocument &document, bool updateActiveSelections=false);
    void moveCursorRight(const TextDocument &document, bool updateActiveSelections=false);
    void moveCursorUp(const TextDocument &document, bool updateActiveSelections=false);
    void moveCursorDown(const TextDocument &document, bool updateActiveSelections=false);

    void moveCursorToEnd(const TextDocument &document, bool updateActiveSelections=false);
    void moveCursorToStart(const TextDocument &document, bool updateActiveSelections=false);

    void addTextInCursorPos(sf::String text, TextDocument &document);
    void deleteTextAfterCursorPos(int amount, TextDocument &document);
    void deleteTextBeforeCursorPos(int amount, TextDocument &document);

    // TODO: SHOULD NOT BE PUBLIC, JUST FOR REFACTOR
    Cursor& getCursor();


   private:
    int fontSize;
    int lineHeight;
    int charWidth;

    float rightLimitPx;
    float bottomLimitPx;

    sf::Font font;

    sf::Color colorChar;
    sf::Color colorSelection;

    Cursor cursor;
    SelectionData selections;

    void handleSelectionOnCursorMovement(bool updateActiveSelections);
};

#endif
