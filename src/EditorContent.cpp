#include "EditorContent.h"

EditorContent::EditorContent(const sf::String &workingDirectory) {
    this->bottomLimitPx = 1;
    this->rightLimitPx = 1;

    this->font.loadFromFile(workingDirectory + "fonts/DejaVuSansMono.ttf");
    this->setFontSize(18);  // Important to call
    this->colorChar = sf::Color::White;
    this->colorSelection = sf::Color(106, 154, 232);

    this->cursor = Cursor(getLineHeight(), getCharWidth());
}

Cursor& EditorContent::getCursor() {
    return this->cursor;
}

// TODO: Reemplazar fontSize por fontHeight especifica para cada tipo de font.
// TODO: Multiples cursores similar a Selecciones, que los moveUp.. etc muevan todos
// TODO: Que devuelva un vector diciendo el alto que ocupa el dibujo de cada linea, para saber el tamaño de cada linea en el margen
void EditorContent::drawLines(sf::RenderWindow &window, TextDocument &document) {
    this->bottomLimitPx = document.getLineCount() * this->fontSize;

    for (int lineNumber = 0; lineNumber < document.getLineCount(); lineNumber++) {
        sf::String line = document.getLine(lineNumber);
        sf::String currentLineText = "";

        this->rightLimitPx = std::max((int)this->rightLimitPx, (int)(this->charWidth * line.getSize()));

        float offsetx = 0;
        bool previousSelected = false;

        for (int charIndexInLine = 0; charIndexInLine <= (int)line.getSize(); charIndexInLine++) {
            // En general hay una unica seleccion, en el futuro podria haber mas de una
            bool currentSelected = this->selections.isSelected(lineNumber, charIndexInLine);

            // Cuando hay un cambio, dibujo el tipo de seleccion anterior
            // Tambien dibujo cuando es el fin de la linea actual
            if (currentSelected != previousSelected || charIndexInLine == (int)line.getSize()) {
                sf::Text texto;
                texto.setFillColor(this->colorChar);
                texto.setFont(font);
                texto.setString(currentLineText);
                texto.setCharacterSize(this->fontSize);
                texto.setPosition(offsetx, lineNumber * this->fontSize);

                if (previousSelected) {
                    sf::RectangleShape selectionRect(sf::Vector2f(this->charWidth * currentLineText.getSize(), this->fontSize));
                    selectionRect.setFillColor(this->colorSelection);
                    // TODO: Que el +2 no sea un numero magico
                    selectionRect.setPosition(offsetx, 2 + lineNumber * this->fontSize);
                    window.draw(selectionRect);
                }

                window.draw(texto);

                previousSelected = currentSelected;
                offsetx += this->charWidth * currentLineText.getSize();
                currentLineText = "";
            }

            // Voy acumulando la string de la linea actual
            currentLineText += line[charIndexInLine];
        }
    }
}

void EditorContent::createNewSelection(int anclaLine, int anclaChar) {
    this->selections.createNewSelection(anclaLine, anclaChar);
}

void EditorContent::updateLastSelection(int lineN, int charN) {
    this->selections.updateLastSelection(lineN, charN);
}

void EditorContent::removeSelections() {
    this->selections.removeSelections();
}

SelectionData::Selection EditorContent::getLastSelection() {
    return this->selections.getLastSelection();
}

// TODO: Divide fontsize from lineheight
void EditorContent::setFontSize(int fontSize) {
    this->fontSize = fontSize;
    this->lineHeight = fontSize;

    // HACK: Because I use only monospace fonts, every char is the same width
    //       so I get the width drawing a single character (A WIDE ONE TO BE SURE)
    sf::Text tmpText;
    tmpText.setFont(this->font);
    tmpText.setCharacterSize(this->fontSize);
    tmpText.setString("_");
    float textwidth = tmpText.getLocalBounds().width;
    this->charWidth = textwidth;
}

float EditorContent::getRightLimitPx() {
    return this->rightLimitPx;
}

float EditorContent::getBottomLimitPx() {
    return this->bottomLimitPx;
}

int EditorContent::getLineHeight() {
    return this->lineHeight;
}

int EditorContent::getCharWidth() {
    return this->charWidth;
}


// TODO: Duplicar seleccion en vez de removerla
void EditorContent::duplicateCursorLine(TextDocument &document) {
    this->removeSelections();

    int lineN = this->cursor.getLineN();
    sf::String lineToAdd = document.getLine(lineN);
    lineToAdd += '\n';
    document.addTextToPos(lineToAdd, lineN + 1, 0);

    this->moveCursorDown(document);
}

void EditorContent::swapSelectedLines(TextDocument &document, bool swapWithUp) {

    auto lastSelection = this->getLastSelection();
    // If there is no selection, consider the cursor a selection. Design choice.
    if (!lastSelection.activa) {
        this->swapCursorLine(document, swapWithUp);
        return;
    }
    // Range inclusive
    int rangeStart = SelectionData::getStartLineN(lastSelection);
    int rangeEnd = SelectionData::getEndLineN(lastSelection);

    int startLineN = SelectionData::getStartLineN(lastSelection);
    int startCharN = SelectionData::getStartCharN(lastSelection);
    int endLineN = SelectionData::getEndLineN(lastSelection);
    int endCharN = SelectionData::getEndCharN(lastSelection);

    if (swapWithUp && rangeStart > 0) {
        for (int i = rangeStart; i <= rangeEnd; i++) {
            document.swapLines(i, i - 1);
        }
        // this->moveCursorUp(document);
        this->removeSelections();
        this->createNewSelection(startLineN - 1, startCharN);
        this->updateLastSelection(endLineN - 1, endCharN);

    } else if (!swapWithUp && rangeEnd < document.getLineCount() - 1) {
        for (int i = rangeEnd; i >= rangeStart; i--) {
            document.swapLines(i, i + 1);
        }
        // this->moveCursorDown(document);
        this->removeSelections();
        this->createNewSelection(startLineN + 1, startCharN);
        this->updateLastSelection(endLineN + 1, endCharN);
    }
}

void EditorContent::swapCursorLine(TextDocument &document, bool swapWithUp) {
    int currentLine = this->cursor.getLineN();
    if (swapWithUp) {
        document.swapLines(currentLine, std::max(currentLine - 1, 0));
    } else {
        document.swapLines(currentLine, std::min(currentLine + 1, document.getLineCount() - 1));
    }
}


// Actualiza ademas el maximo char alcanzado
bool EditorContent::moveCursorLeft(const TextDocument &document, bool updateActiveSelections) {
    bool moved = (this->cursor.getLineN() != 0) || ((this->cursor.getLineN() == 0) && (this->cursor.getCharN() > 0));

    if (this->cursor.getCharN() <= 0) {
        int newCursorLine = std::max(this->cursor.getLineN() - 1, 0);
        int newCursorChar = 0;
        if (this->cursor.getLineN() != 0) {
            newCursorChar = document.charsInLine(newCursorLine);
        }
        this->cursor.setPosition(newCursorLine, newCursorChar, true);
    } else {
        this->cursor.moveLeft(true);
    }

    this->handleSelectionOnCursorMovement(updateActiveSelections);

    return moved;
}

// Actualiza ademas el maximo char alcanzado
void EditorContent::moveCursorRight(const TextDocument &document, bool updateActiveSelections) {
    int charsInLine = document.charsInLine(this->cursor.getLineN());
    if (this->cursor.getCharN() >= charsInLine) {
        int newCursorLine = std::min(this->cursor.getLineN() + 1, document.getLineCount());
        this->cursor.setPosition(newCursorLine, 0, true);
    } else {
        this->cursor.moveRight(true);
    }

    this->handleSelectionOnCursorMovement(updateActiveSelections);
}

void EditorContent::moveCursorUp(const TextDocument &document, bool updateActiveSelections) {
    if (this->cursor.getLineN() > 0) {
        int charsInPreviousLine = document.charsInLine(this->cursor.getLineN() - 1);
        int currentCharPos = this->cursor.getCharN();

        // Si el caracter actual existe en la linea de arriba, voy solo arriba, sino voy al final de la linea de arriba
        if (currentCharPos <= charsInPreviousLine && this->cursor.getMaxCharNReached() <= charsInPreviousLine) {
            this->cursor.moveUpToMaxCharN();
        } else {
            this->cursor.setPosition(this->cursor.getLineN() - 1, charsInPreviousLine);
        }
    }

    this->handleSelectionOnCursorMovement(updateActiveSelections);
}

void EditorContent::moveCursorDown(const TextDocument &document, bool updateActiveSelections) {
    if (this->cursor.getLineN() < document.getLineCount() - 1) {
        int charsInNextLine = document.charsInLine(this->cursor.getLineN() + 1);
        int currentCharPos = this->cursor.getCharN();

        if (currentCharPos <= charsInNextLine && this->cursor.getMaxCharNReached() <= charsInNextLine) {
            this->cursor.moveDownToMaxCharN();
        } else {
            this->cursor.setPosition(this->cursor.getLineN() + 1, charsInNextLine);
        }
    }

    this->handleSelectionOnCursorMovement(updateActiveSelections);
}

void EditorContent::moveCursorToEnd(const TextDocument &document, bool updateActiveSelections) {
    int charsInLine = document.charsInLine(this->cursor.getLineN());
    this->cursor.moveToEnd(charsInLine, true);
    this->handleSelectionOnCursorMovement(updateActiveSelections);
}

void EditorContent::moveCursorToStart(const TextDocument &document, bool updateActiveSelections) {
    this->cursor.moveToStart(true);
    this->handleSelectionOnCursorMovement(updateActiveSelections);
}


void EditorContent::deleteTextBeforeCursorPos(int amount, TextDocument &document) {
    int actuallyMoved = 0;
    for (int i = 0; i < amount; i++) {
        bool moved = this->moveCursorLeft(document);
        actuallyMoved += moved ? 1 : 0;
    }
    this->deleteTextAfterCursorPos(actuallyMoved, document);
}

void EditorContent::deleteTextAfterCursorPos(int amount, TextDocument &document) {
    int newLineN = this->cursor.getLineN();
    int newCharN = this->cursor.getCharN();
    document.removeTextFromPos(amount, newLineN, newCharN);
}


void EditorContent::addTextInCursorPos(sf::String text, TextDocument &document) {
    int textSize = text.getSize();
    int lineN = this->cursor.getLineN();
    int charN = this->cursor.getCharN();
    document.addTextToPos(text, lineN, charN);
    for (int i = 0; i < textSize; i++) {
        this->moveCursorRight(document);
    }
}

// Borra el texto contenido en la seleccion y tambien la seleccion en si
// Devuelve true si se borro una seleccion
bool EditorContent::deleteSelections(TextDocument &document) {
    SelectionData::Selection lastSelection = this->getLastSelection();
    this->removeSelections();

    // Tomar el inicio de lastSelection, calcular el largo y borrar desde el inicio,
    if (lastSelection.activa) {
        int startLineN = SelectionData::getStartLineN(lastSelection);
        int startCharN = SelectionData::getStartCharN(lastSelection);
        int endLineN = SelectionData::getEndLineN(lastSelection);
        int endCharN = SelectionData::getEndCharN(lastSelection);

        // Muevo el cursor al inicio de la seleccion
        this->cursor.setPosition(startLineN, startCharN, true);

        // -1 por como funcionan los extremos de la seleccion
        int amount = document.charAmountContained(startLineN, startCharN, endLineN, endCharN) - 1;
        this->deleteTextAfterCursorPos(amount, document);
    }

    return lastSelection.activa;
}

sf::String EditorContent::copySelections(TextDocument &document) {
    SelectionData::Selection lastSelection = this->getLastSelection();
    //this->removeSelections();

    sf::String copied = "";
    // Tomar el inicio de lastSelection, calcular el largo y borrar desde el inicio,
    if (lastSelection.activa) {
        int startLineN = SelectionData::getStartLineN(lastSelection);
        int startCharN = SelectionData::getStartCharN(lastSelection);
        int endLineN = SelectionData::getEndLineN(lastSelection);
        int endCharN = SelectionData::getEndCharN(lastSelection);

        // Muevo el cursor al inicio de la seleccion
        this->cursor.setPosition(startLineN, startCharN, true);

        // -1 por como funcionan los extremos de la seleccion
        int amount = document.charAmountContained(startLineN, startCharN, endLineN, endCharN) - 1;
        copied = document.getTextFromPos(amount, startLineN, startCharN);
    }
    return copied;
}

void EditorContent::handleSelectionOnCursorMovement(bool updateActiveSelections) {
    if (updateActiveSelections) {
        this->updateLastSelection(this->cursor.getLineN(), this->cursor.getCharN());
    } else {
        this->removeSelections();
    }
}
