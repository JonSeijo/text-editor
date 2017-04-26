#include "TextView.h"

TextView::TextView(const sf::RenderWindow &window)
    : camera(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)),
      deltaScroll(10), deltaRotation(2), deltaZoomIn(0.8f), deltaZoomOut(1.2f) {

    this->content.selectText(0, 12);
    this->content.selectText(100, 120);
}

void TextView::drawLines(sf::RenderWindow &window, TextDocument &document) {
    this->content.drawLines(window, document);
}

// Esta funcion se encarga de transformar las cordenadas de mouse en coordenadas de texto
// TODO: Renombrarla
void TextView::mouseClick(float mouseX, float mouseY, const TextDocument &document) {

    // No considera que los tabs existen
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

    // Eliminar selecciones
    this->content.setCursorPos(lineN, charN);
}

void TextView::setFontSize(int fontSize) {
    this->content.setFontSize(fontSize);
}

// [begin, end] inclusive
void TextView::selectText(int begin, int end) {
    this->content.selectText(begin, end);
}

void TextView::removeSelections() {
    this->content.removeSelections();
}

void TextView::scrollUp() {
    this->camera.move(0, this->deltaScroll);
}

void TextView::scrollDown() {
    this->camera.move(0, -this->deltaScroll);
}

void TextView::scrollLeft() {
    this->camera.move(this->deltaScroll, 0);
}

void TextView::scrollRight() {
    this->camera.move(-this->deltaScroll, 0);
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
