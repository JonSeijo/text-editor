#include "TextView.h"

TextView::TextView(const sf::RenderWindow &window)
    : camera(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y)),
      deltaScroll(10), deltaRotation(2) {}

void TextView::drawLines(sf::RenderWindow &window, TextDocument &document) {
    this->content.drawLines(window, document);
}

void TextView::setFontSize(int fontSize) {
    this->content.setFontSize(fontSize);
}

void TextView::scrollUp() {
    this->camera.move(0, this->deltaScroll);
}

void TextView::scrollDown() {
    this->camera.move(0, -this->deltaScroll);
}

void TextView::rotateLeft() {
    this->camera.rotate(this->deltaRotation);
}

void TextView::rotateRight() {
    this->camera.rotate(-this->deltaRotation);
}

sf::View TextView::getCameraView() {
    return this->camera;
}