#include <iostream>


#include "SFML/Window.hpp"
#include "MenuBar.h"
#include "Logo.h"
#include "Icon.h"
#include "EditorView.h"
#include "Filesystem.h"
#include "Utills.h"
#include "Document.h"
#include "Content.h"
#include "Input.h" 

int main(int argc, char *argv[]) {

      sf::RectangleShape rectangle(sf::Vector2f(150, 80));
      sf::RenderWindow window(sf::VideoMode(1000, 700), "Nanoe");
      window.setVerticalSyncEnabled(true);
      SetIcon(window);


      // ======< WORKING DIRECTION >=========================
      std::string Direction = Implementation::WorkingDirection(argv[0]);

      std::string LoadFile, SaveFile;

      if (argc == 2) {
          LoadFile = Direction + argv[1];
          SaveFile = Direction + argv[1];
      }
      else {
          LoadFile = Direction + "text.txt";
          SaveFile = Direction + "text.txt";
      }

      // ===< DOCUMENT INIT >========== 
      TextDocument Document;
      Document.init(LoadFile);

      EditorContent Content(Document);
      
      EditorView View(window, Direction, Content);
      InputController Input(Content);

      // =======< MENU BAR >========
      MenuBar Menu(window, Content);
   //   Menu.draw(window);

   

      // =====< DRAWING LOGO BEFORE STARING >=========
      Drawlogo(window);



   
    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
           
            // ======< WINDOW CLOSE >=======
            if (ev.type == sf::Event::Closed) 
                window.close();

              // =====< CAMERA POSITION >=====
              if (ev.type == sf::Event::Resized)
                  View.setCameraBounds(ev.size.width, ev.size.height);

              // ========< FILE SAVE >========
              if (ev.key.code == sf::Keyboard::S && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                  if (Document.hasChanged()) {
                      Document.saveFile(SaveFile);
                      std::cout << "SAVED TO: " << SaveFile << "\n";
                  }
              }
              
              // =========< FONT SIZE CHANGE (ZOOM) >==========
              if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && ev.type == sf::Event::MouseWheelScrolled) {
                  if (ev.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                      if (ev.mouseWheelScroll.delta <= -1)
                          View.FontSizeScrollChangeDown();
                      else
                          View.FontSizeScrollChangeUp();
                  }   
                  break;
              }
            
            // =========< IMPL CTRL + A >=========
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && ev.key.code == sf::Keyboard::A) {
                std::cout << "ctrl + a" << std::endl;
                View.SelectAll();
            }

            Input.handleEvents(View, window, ev);
        }
        Input.handleConstantInput(View, window);

        window.clear(bgColor);
        window.setView(View.getCameraView());
        View.draw(window);
        window.display();
       //  Backgroundcolor(window);
    }
 

        
     return 0;
}