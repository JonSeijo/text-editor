#include "TextView.h"

TextView::TextView(const sf::RenderWindow &window)
    : camera(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)),
      deltaScroll(10), deltaRotation(2), deltaZoomIn(0.8f), deltaZoomOut(1.2f) {

    // this->content.selectText(0, 12);
    // this->content.selectText(100, 120);
}

void TextView::drawLines(sf::RenderWindow &window, TextDocument &document) {
    this->content.drawLines(window, document);
}

TextView::DocCoords TextView::getDocumentCoords(float mouseX, float mouseY, const TextDocument &document) {
    // TODO: Esto no considera que los tabs \t existen
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
void TextView::cursorChange(float mouseX, float mouseY, const TextDocument &document, bool keepSelection) {

    TextView::DocCoords docCoords = this->getDocumentCoords(mouseX, mouseY, document);
    int lineN = docCoords.lineN;
    int charN = docCoords.charN;

    if (keepSelection) {
        // Podria hacer un "hasSelection"
        SelectionData::Selection ultimaSelec = this->content.getLastSelection();

        // Quiero actualizar la ultima seleccion dependiendo de la ultimaActual

        // ESTO ASUME QUE PUEDO HACER UNA UNICA SELECCION
        // TODO: Usar los metodos moveSelections para mover todas las selecciones.

        // Si la linea nueva esta antes de la linea del principio, es porque me "movi hacia atras"
        if (lineN < ultimaSelec.startLineN) {
            this->content.removeSelections();
            this->content.selectText(lineN, charN, ultimaSelec.startLineN, ultimaSelec.startCharN);
        }

        // Si la linea nueva esta despues de la linea del principio, es porque me "movi hacia adelante"
        else if (lineN > ultimaSelec.endLineN) {
            this->content.removeSelections();
            this->content.selectText(ultimaSelec.startLineN, ultimaSelec.startCharN, lineN, charN);
        }

        // Caso me movi dentro de la misma seleccion
        else if (false) {

        }


    } else {
        this->content.removeSelections();
        // Agrego una seleccion fantasma que no contenga ningun caracter,
        // para en el caso de mantenerla activa siempre haya una que pueda expandir

        // this->content.addSelection();
    }


    this->content.setCursorPos(lineN, charN);
}

void TextView::setFontSize(int fontSize) {
    this->content.setFontSize(fontSize);
}

// [begin, end] inclusive
void TextView::selectText(int startLineN, int startCharN, int endLineN, int endCharN) {
    this->content.selectText(startLineN, startCharN, endLineN, endCharN);
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
