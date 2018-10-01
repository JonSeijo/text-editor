#ifndef TextViewContent_H
#define TextViewContent_H

#include <SFML/Graphics.hpp>
#include "SelectionData.h"
#include "TextDocument.h"

class TextViewContent {
   public:
    TextViewContent(const sf::String &workingDirectory);

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

   private:
    int fontSize;
    int lineHeight;
    int charWidth;

    float rightLimitPx;
    float bottomLimitPx;

    sf::Font font;

    sf::Color colorChar;
    sf::Color colorSelection;

    SelectionData selections;
};

#endif
