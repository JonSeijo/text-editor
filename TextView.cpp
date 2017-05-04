#include "TextView.h"

TextView::TextView(const sf::RenderWindow &window)
    : camera(sf::FloatRect(-45, 0, window.getSize().x, window.getSize().y)),
      deltaScroll(10), deltaRotation(2), deltaZoomIn(0.8f), deltaZoomOut(1.2f) {

    this->font.loadFromFile("FreeMono.ttf");
    this->fontSize = 20;

    // TODO: Cambiarlo en relacion a la fontsize
    this->marginXOffset = 45;
}

void TextView::draw(sf::RenderWindow &window, TextDocument &document) {
    // TODO: El content devuelve un vector diciendo que alto tiene cada linea,
    //      por ahora asumo que todas miden "1" de alto
    this->content.drawLines(window, document);

    // Dibujo los numeros de la izquierda

    // TODO: Hacer una clase separada para el margin
    for (int lineNumber = 1; lineNumber <= document.getLineCount(); lineNumber++) {
        int lineHeight = 1;
        sf::Text lineNumberText;
        lineNumberText.setColor(sf::Color::White);
        lineNumberText.setFont(this->font);
        lineNumberText.setString(std::to_string(lineNumber));
        lineNumberText.setCharacterSize(this->fontSize-1);
        lineNumberText.setPosition(-this->marginXOffset, lineHeight * (lineNumber-1) * this->fontSize);
        window.draw(lineNumberText);
    }
}

// TODO: Esto no considera que los tabs \t existen
TextView::DocCoords TextView::getDocumentCoords(float mouseX, float mouseY, const TextDocument &document) {
    int lineN = mouseY / this->content.getLineHeight();
    int charN = std::round(mouseX / this->content.getCharWidth());

    // Restrinjo numero de linea a la altura del documento
    int lastLine = document.getLineCount() - 1;
    if (lineN < 0 || lineN > lastLine) {
        charN = 0;
    }
    lineN = std::max(lineN, 0);
    lineN = std::min(lineN, lastLine);

    // Restrinjo numero de caracter a cant de caracteres de la linea
    int charsInLine = document.charsInLine(lineN);
    charN = std::max(charN, 0);
    charN = std::min(charN, charsInLine);

    return TextView::DocCoords(lineN, charN);
}

// TODO: Esta funcion no sirve para cambio de cursor con teclado, podria hacer que funcione con coords de texto,
//       y que la funcion de cursor change con mouse la llame despues de la conversion
// TODO: Agregar parametros para saber si tengo que agregar otro, actualizar selecciones o lo que sea
// TODO: Esta funcion solo sirve para la ultima seleccion, manejarlo por parametros??
void TextView::cursorActive(float mouseX, float mouseY, const TextDocument &document) {

    TextView::DocCoords docCoords = this->getDocumentCoords(mouseX, mouseY, document);
    int lineN = docCoords.lineN;
    int charN = docCoords.charN;

    this->content.setCursorPos(lineN, charN);
    SelectionData::Selection ultimaSelec = this->content.getLastSelection();
    // ESTO ASUME QUE PUEDO HACER UNA UNICA SELECCION
    // TODO: Usar los metodos moveSelections para mover todas las selecciones.
    this->content.updateLastSelection(lineN, charN);
}

// Una seleccion inicial selecciona el propio caracter en el que estoy
void TextView::startSelection(float mouseX, float mouseY, const TextDocument &document) {
    TextView::DocCoords docCoords = this->getDocumentCoords(mouseX, mouseY, document);
    this->content.createNewSelection(docCoords.lineN, docCoords.charN);
}

void TextView::setFontSize(int fontSize) {
    this->content.setFontSize(fontSize);
}

void TextView::removeSelections() {
    this->content.removeSelections();
}

void TextView::scrollUp() {
    this->camera.move(0, -this->deltaScroll);
}

void TextView::scrollDown() {
    this->camera.move(0, this->deltaScroll);
}

void TextView::scrollLeft() {
    this->camera.move(-this->deltaScroll, 0);
}

void TextView::scrollRight() {
    this->camera.move(this->deltaScroll, 0);
}

void TextView::scroll(float dx, float dy) {
    this->camera.move(dx, dy);
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

sf::View TextView::getCameraView() {
    return this->camera;
}
