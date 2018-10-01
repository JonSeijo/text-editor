#include <SFML/Graphics.hpp>
#include "TextView.h"
#include "TextDocument.h"
#include "InputController.h"
#include "ImplementationUtils.h"

int main(int argc, char* argv[]) {

    std::string workingDirectory = ImplementationUtils::getWorkingDirectory(argv[0]);

    std::string saveFileName;
    std::string loadFileName;

    if (argc == 2) {
        saveFileName = workingDirectory + argv[1];
        loadFileName = workingDirectory + argv[1];
    } else {
        saveFileName = workingDirectory + "txt/textoDePruebaGuardado.txt";
        loadFileName = workingDirectory + "txt/textoDePruebaGuardado.txt";
    }

    sf::RenderWindow window(sf::VideoMode(720, 405), "Jonno-text");
    window.setVerticalSyncEnabled(true);
    sf::Color backgroundColor = sf::Color(21, 29, 45);

    TextView textView(window, workingDirectory);
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
                if (document.hasChanged()){
                    
                    document.saveFile(saveFileName);
                    std::cout << "SAVED TO: " << saveFileName << "\n";
                }
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
