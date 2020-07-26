#include "EditorView.h"

EditorView::EditorView(
    const sf::RenderWindow &window,
    const sf::String &workingDirectory,
    EditorContent &editorContent)
    : content(editorContent),
      cursor(editorContent.getCursor()),
      camera(sf::FloatRect(-50, 0, window.getSize().x, window.getSize().y)),
      deltaScroll(20), deltaRotation(2), deltaZoomIn(0.8f), deltaZoomOut(1.2f) {

    // this->font.loadFromFile("fonts/FreeMono.ttf");
    this->font.loadFromFile(workingDirectory + "fonts/DejaVuSansMono.ttf");
    this->fontSize = 18;

    // TODO: Cambiarlo en relacion a la fontsize
    this->marginXOffset = 45;
    this->colorMargin = sf::Color(32, 44, 68);
}

void EditorView::draw(sf::RenderWindow &window, TextDocument &document) {
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
EditorView::DocCoords EditorView::getDocumentCoords(float mouseX, float mouseY, const TextDocument &document) {
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

    return EditorView::DocCoords(lineN, charN);
}

// TODO: Agregar parametros para saber si tengo que agregar otro, actualizar selecciones o lo que sea
// TODO: Esta funcion solo sirve para la ultima seleccion, manejarlo por parametros??
void EditorView::cursorActive(float mouseX, float mouseY, const TextDocument &document) {
    EditorView::DocCoords docCoords = this->getDocumentCoords(mouseX, mouseY, document);
    int lineN = docCoords.lineN;
    int charN = docCoords.charN;

    this->cursor.setPosition(lineN, charN);
    this->cursor.setMaxCharNReached(charN);

    // ESTO ASUME QUE PUEDO HACER UNA UNICA SELECCION
    // TODO: Usar los metodos moveSelections para mover todas las selecciones.
    this->content.updateLastSelection(lineN, charN);
}

// Una seleccion inicial selecciona el propio caracter en el que estoy
void EditorView::startSelectionFromMouse(float mouseX, float mouseY, const TextDocument &document) {
    EditorView::DocCoords docCoords = this->getDocumentCoords(mouseX, mouseY, document);
    this->content.createNewSelection(docCoords.lineN, docCoords.charN);
}

void EditorView::startSelectionFromCursor() {
    this->content.removeSelections();
    this->content.createNewSelection(this->cursor.getLineN(), this->cursor.getCharN());
}

void EditorView::setFontSize(int fontSize) {
    this->content.setFontSize(fontSize);
}

void EditorView::removeSelections() {
    this->content.removeSelections();
}

void EditorView::scrollUp(sf::RenderWindow &window) {
    float height = window.getView().getSize().y;
    auto camPos = this->camera.getCenter();
    // Scrolleo arriba solo si no me paso del limite superior
    if (camPos.y - height / 2 > 0) {
        this->camera.move(0, -this->deltaScroll);
    }
}

void EditorView::scrollDown(sf::RenderWindow &window) {
    float height = window.getView().getSize().y;
    float bottomLimit = std::max(this->content.getBottomLimitPx(), height);
    auto camPos = this->camera.getCenter();
    // Numero magico 20 como un plus
    if (camPos.y + height / 2 < bottomLimit + 20) {
        this->camera.move(0, this->deltaScroll);
    }
}

void EditorView::scrollLeft(sf::RenderWindow &window) {
    float width = window.getView().getSize().x;
    auto camPos = this->camera.getCenter();
    // Scrolleo arriba si no me paso del limite izquierdo
    if (camPos.x - width / 2 > -this->marginXOffset) {
        this->camera.move(-this->deltaScroll, 0);
    }
}

void EditorView::scrollRight(sf::RenderWindow &window) {
    float width = window.getView().getSize().x;
    float rightLimit = std::max(this->content.getRightLimitPx(), width);
    auto camPos = this->camera.getCenter();
    // Numero magico 20 como un plus
    if (camPos.x + width / 2 < rightLimit + 20) {
        this->camera.move(this->deltaScroll, 0);
    }
}

void EditorView::rotateLeft() {
    this->camera.rotate(this->deltaRotation);
}

void EditorView::rotateRight() {
    this->camera.rotate(-this->deltaRotation);
}

void EditorView::zoomIn() {
    this->camera.zoom(this->deltaZoomIn);
}

void EditorView::zoomOut() {
    this->camera.zoom(this->deltaZoomOut);
}

void EditorView::setCameraBounds(int width, int height) {
    this->camera = sf::View(sf::FloatRect(-50, 0, width, height));
}

sf::View EditorView::getCameraView() {
    return this->camera;
}
