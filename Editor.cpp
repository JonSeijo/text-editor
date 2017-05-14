#include <SFML/Graphics.hpp>
#include "TextView.h"
#include "TextDocument.h"
#include "InputController.h"

void controlarMovimientosTeclado(TextView &textView) {
    // Rotating
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                textView.rotateLeft();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                textView.rotateRight();
            }
        }
    }
}

int main() {

    int resolutionX = 720;
    int resolutionY = 405;

    // TODO: Poder expandir la ventada a gusto
    sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "text-editor");
    window.setVerticalSyncEnabled(true);
    sf::Color backgroundColor = sf::Color(21, 29, 45);

    std::string saveFileName = "txt/textoDePruebaGuardado.txt";
    std::string fileName = "txt/textoDePruebaGuardado.txt";
    // std::string fileName = "TextView.cpp";

    TextView textView(window);
    TextDocument document;
    InputController inputController;

    document.init(fileName);

    bool isMouseDown = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                resolutionX = event.size.width;
                resolutionY = event.size.height;
                textView.setCameraBounds(resolutionX, resolutionY);
            }
            if (event.key.code == sf::Keyboard::S && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                document.saveFile(saveFileName);
                std::cout << "GUARDADO A: " << saveFileName << "\n";
            }

            inputController.handleEvents(document, textView, window, event);
        }

        controlarMovimientosTeclado(textView);

        // TODO: Esto asume que siempre que esta el mouse presionado se esta seleccionando
        // TODO: Ubicar el textview con variables genericas (No magic numbers)
        // TODO: No permitir scrollear mas alla del textview
        if (inputController.isMouseDown()) {
            auto mousepos = sf::Mouse::getPosition(window);
            auto mousepos_text = window.mapPixelToCoords(mousepos);

            textView.cursorActive(mousepos_text.x, mousepos_text.y, document);

            float scrollDeltaX = 0;
            float scrollDeltaY = 0;

            float textViewTop = 0;
            float textViewBottom = resolutionY - 5;
            float textViewLeft = 0;
            float textViewRight = resolutionX;

            float relativeFactor = 3;

            float distanceToTop = std::abs(mousepos.y - textViewTop);
            float distanceToBottom = std::abs(mousepos.y - textViewBottom);
            float distanceToLeft = std::abs(mousepos.x - textViewLeft);
            float distanceToRight = std::abs(mousepos.x - textViewRight);

            if (mousepos.x < textViewLeft) {
                scrollDeltaX = -distanceToLeft / relativeFactor;
            } else if (mousepos.x > textViewRight) {
                scrollDeltaX = distanceToRight / relativeFactor;
            }

            if (mousepos.y < textViewTop) {
                scrollDeltaY = -distanceToTop / relativeFactor;
            } else if (mousepos.y > textViewBottom) {
                scrollDeltaY = distanceToBottom / relativeFactor;
            }

            textView.scroll(scrollDeltaX, scrollDeltaY);
        }

        window.clear(backgroundColor);

        window.setView(textView.getCameraView());

        textView.draw(window, document);

        window.display();
    }

    return 0;
}
