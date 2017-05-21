#include <SFML/Graphics.hpp>
#include "TextView.h"
#include "TextDocument.h"
#include "InputController.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(720, 405), "text-editor");
    window.setVerticalSyncEnabled(true);
    sf::Color backgroundColor = sf::Color(21, 29, 45);

    std::string saveFileName = "txt/textoDePruebaGuardado.txt";
    std::string loadFileName = "txt/textoDePruebaGuardado.txt";
    // std::string loadFileName = "TextView.cpp";

    TextView textView(window);
    TextDocument document;
    InputController inputController;

    document.init(loadFileName);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                textView.setCameraBounds(event.size.width, event.size.height);
            }
            if (event.key.code == sf::Keyboard::S && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                document.saveFile(saveFileName);
                std::cout << "GUARDADO A: " << saveFileName << "\n";
            }

            inputController.handleEvents(document, textView, window, event);
        }

        inputController.handleConstantInput(document, textView, window);

        window.clear(backgroundColor);
        window.setView(textView.getCameraView());
        textView.draw(window, document);
        window.display();
    }

    return 0;
}
