#include "TextView.h"

TextView::TextView(const sf::RenderWindow &window, const sf::String &workingDirectory)
    : content(workingDirectory), camera(sf::FloatRect(-50, 0, window.getSize().x, window.getSize().y)), deltaScroll(20), deltaRotation(2), deltaZoomIn(0.8f), deltaZoomOut(1.2f) {
    this->cursor = Cursor(this->content.getLineHeight(), this->content.getCharWidth());

    // this->font.loadFromFile("fonts/FreeMono.ttf");
    this->font.loadFromFile(workingDirectory + "fonts/DejaVuSansMono.ttf");
    this->fontSize = 18;

    // TODO: Cambiarlo en relacion a la fontsize
    this->marginXOffset = 45;
    this->colorMargin = sf::Color(32, 44, 68);
}

void TextView::draw(sf::RenderWindow &window, TextDocument &document) {
    // TODO: El content devuelve un vector diciendo que alto tiene cada linea,
    //      por ahora asumo que todas miden "1" de alto
    this->content.drawLines(window, document);

    // Dibujo los numeros de la izquierda

    // TODO: Hacer una clase separada para el margin
    for (int lineNumber = 1; lineNumber <= document.getLineCount(); lineNumber++) {
        int lineHeight = 1;

        int blockHeight = lineHeight * this->fontSize;

        sf::Text lineNumberText;
        lineNumberText.setFillColor(sf::Color::White);
        lineNumberText.setFont(this->font);
        lineNumberText.setString(std::to_string(lineNumber));
        lineNumberText.setCharacterSize(this->fontSize - 1);
        lineNumberText.setPosition(-this->marginXOffset, blockHeight * (lineNumber - 1));

        sf::RectangleShape marginRect(sf::Vector2f(this->marginXOffset - 5, blockHeight));
        marginRect.setFillColor(this->colorMargin);
        marginRect.setPosition(-this->marginXOffset, blockHeight * (lineNumber - 1));

        window.draw(marginRect);
        window.draw(lineNumberText);
    }

    this->cursor.draw(window);
}

// TODO: Esto no considera que los tabs \t existen
TextView::DocCoords TextView::getDocumentCoords(float mouseX, float mouseY, const TextDocument &document) {
    int lineN = mouseY / this->content.getLineHeight();
    int charN = std::round(mouseX / this->content.getCharWidth());

    // Restrinjo numero de linea a la altura del documento
    int lastLine = document.getLineCount() - 1;

    if (lineN < 0) {
        lineN = 0;
        charN = 0;
    } else if (lineN > lastLine) {
        lineN = lastLine;
        charN = document.charsInLine(lineN);
    } else {
        lineN = std::max(lineN, 0);
        lineN = std::min(lineN, lastLine);

        // Restrinjo numero de caracter a cant de caracteres de la linea
        charN = std::max(charN, 0);
        charN = std::min(charN, document.charsInLine(lineN));
    }

    return TextView::DocCoords(lineN, charN);
}

// TODO: Agregar parametros para saber si tengo que agregar otro, actualizar selecciones o lo que sea
// TODO: Esta funcion solo sirve para la ultima seleccion, manejarlo por parametros??
void TextView::cursorActive(float mouseX, float mouseY, const TextDocument &document) {
    TextView::DocCoords docCoords = this->getDocumentCoords(mouseX, mouseY, document);
    int lineN = docCoords.lineN;
    int charN = docCoords.charN;

    this->cursor.setPosition(lineN, charN);
    this->cursor.setMaxCharNReached(charN);

    // ESTO ASUME QUE PUEDO HACER UNA UNICA SELECCION
    // TODO: Usar los metodos moveSelections para mover todas las selecciones.
    this->content.updateLastSelection(lineN, charN);
}

// TODO: Duplicar seleccion en vez de removerla
void TextView::duplicateCursorLine(TextDocument &document) {
    this->content.removeSelections();

    int lineN = this->cursor.getLineN();
    sf::String lineToAdd = document.getLine(lineN);
    lineToAdd += '\n';
    document.addTextToPos(lineToAdd, lineN + 1, 0);

    this->moveCursorDown(document);
}

void TextView::swapSelectedLines(TextDocument &document, bool swapWithUp) {
    
    auto lastSelection = this->content.getLastSelection();
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
        this->content.removeSelections();
        this->content.createNewSelection(startLineN - 1, startCharN);
        this->content.updateLastSelection(endLineN - 1, endCharN);

    } else if (!swapWithUp && rangeEnd < document.getLineCount() - 1) {
        for (int i = rangeEnd; i >= rangeStart; i--) {
            document.swapLines(i, i + 1);
        }
        // this->moveCursorDown(document);
        this->content.removeSelections();
        this->content.createNewSelection(startLineN + 1, startCharN);
        this->content.updateLastSelection(endLineN + 1, endCharN);
    }
}

void TextView::swapCursorLine(TextDocument &document, bool swapWithUp) {
    int currentLine = this->cursor.getLineN();
    if (swapWithUp) {
        document.swapLines(currentLine, std::max(currentLine - 1, 0));
    } else {
        document.swapLines(currentLine, std::min(currentLine + 1, document.getLineCount() - 1));
    }
}

// Una seleccion inicial selecciona el propio caracter en el que estoy
void TextView::startSelectionFromMouse(float mouseX, float mouseY, const TextDocument &document) {
    TextView::DocCoords docCoords = this->getDocumentCoords(mouseX, mouseY, document);
    this->content.createNewSelection(docCoords.lineN, docCoords.charN);
}

void TextView::startSelectionFromCursor() {
    this->content.removeSelections();
    this->content.createNewSelection(this->cursor.getLineN(), this->cursor.getCharN());
}

void TextView::addTextInCursorPos(sf::String text, TextDocument &document) {
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
bool TextView::deleteSelections(TextDocument &document) {
    SelectionData::Selection lastSelection = this->content.getLastSelection();
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

sf::String TextView::copySelections(TextDocument &document) {
    SelectionData::Selection lastSelection = this->content.getLastSelection();
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

void TextView::deleteTextBeforeCursorPos(int amount, TextDocument &document) {
    int actuallyMoved = 0;
    for (int i = 0; i < amount; i++) {
        bool moved = this->moveCursorLeft(document);
        actuallyMoved += moved ? 1 : 0;
    }
    this->deleteTextAfterCursorPos(actuallyMoved, document);
}

void TextView::deleteTextAfterCursorPos(int amount, TextDocument &document) {
    int newLineN = this->cursor.getLineN();
    int newCharN = this->cursor.getCharN();
    document.removeTextFromPos(amount, newLineN, newCharN);
}

// Actualiza ademas el maximo char alcanzado
bool TextView::moveCursorLeft(const TextDocument &document, bool updateActiveSelections) {
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
void TextView::moveCursorRight(const TextDocument &document, bool updateActiveSelections) {
    int charsInLine = document.charsInLine(this->cursor.getLineN());
    if (this->cursor.getCharN() >= charsInLine) {
        int newCursorLine = std::min(this->cursor.getLineN() + 1, document.getLineCount());
        this->cursor.setPosition(newCursorLine, 0, true);
    } else {
        this->cursor.moveRight(true);
    }

    this->handleSelectionOnCursorMovement(updateActiveSelections);
}

void TextView::moveCursorUp(const TextDocument &document, bool updateActiveSelections) {
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

void TextView::moveCursorDown(const TextDocument &document, bool updateActiveSelections) {
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

void TextView::moveCursorToEnd(const TextDocument &document, bool updateActiveSelections) {
    int charsInLine = document.charsInLine(this->cursor.getLineN());
    this->cursor.moveToEnd(charsInLine, true);
    this->handleSelectionOnCursorMovement(updateActiveSelections);
}

void TextView::moveCursorToStart(const TextDocument &document, bool updateActiveSelections) {
    this->cursor.moveToStart(true);
    this->handleSelectionOnCursorMovement(updateActiveSelections);
}

void TextView::handleSelectionOnCursorMovement(bool updateActiveSelections) {
    if (updateActiveSelections) {
        this->content.updateLastSelection(this->cursor.getLineN(), this->cursor.getCharN());
    } else {
        this->content.removeSelections();
    }
}

void TextView::setFontSize(int fontSize) {
    this->content.setFontSize(fontSize);
}

void TextView::removeSelections() {
    this->content.removeSelections();
}

void TextView::scrollUp(sf::RenderWindow &window) {
    float height = window.getView().getSize().y;
    auto camPos = this->camera.getCenter();
    // Scrolleo arriba solo si no me paso del limite superior
    if (camPos.y - height / 2 > 0) {
        this->camera.move(0, -this->deltaScroll);
    }
}

void TextView::scrollDown(sf::RenderWindow &window) {
    float height = window.getView().getSize().y;
    float bottomLimit = std::max(this->content.getBottomLimitPx(), height);
    auto camPos = this->camera.getCenter();
    // Numero magico 20 como un plus
    if (camPos.y + height / 2 < bottomLimit + 20) {
        this->camera.move(0, this->deltaScroll);
    }
}

void TextView::scrollLeft(sf::RenderWindow &window) {
    float width = window.getView().getSize().x;
    auto camPos = this->camera.getCenter();
    // Scrolleo arriba si no me paso del limite izquierdo
    if (camPos.x - width / 2 > -this->marginXOffset) {
        this->camera.move(-this->deltaScroll, 0);
    }
}

void TextView::scrollRight(sf::RenderWindow &window) {
    float width = window.getView().getSize().x;
    float rightLimit = std::max(this->content.getRightLimitPx(), width);
    auto camPos = this->camera.getCenter();
    // Numero magico 20 como un plus
    if (camPos.x + width / 2 < rightLimit + 20) {
        this->camera.move(this->deltaScroll, 0);
    }
}

void TextView::rotateLeft() {
    this->camera.rotate(this->deltaRotation);
}

void TextView::rotateRight() {
    this->camera.rotate(-this->deltaRotation);
}

void TextView::zoomIn() {
    this->camera.zoom(this->deltaZoomIn);
}

void TextView::zoomOut() {
    this->camera.zoom(this->deltaZoomOut);
}

void TextView::setCameraBounds(int width, int height) {
    this->camera = sf::View(sf::FloatRect(-50, 0, width, height));
}

sf::View TextView::getCameraView() {
    return this->camera;
}
