#include "EditorContent.h"

EditorContent::EditorContent(const sf::String &workingDirectory) {
    this->cursor = Cursor(0, 0);
}

Cursor& EditorContent::getCursor() {
    return this->cursor;
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

bool EditorContent::isSelected(int lineNumber, int charIndexInLine) {
    return this->selections.isSelected(lineNumber, charIndexInLine);
}

SelectionData::Selection EditorContent::getLastSelection() {
    return this->selections.getLastSelection();
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
