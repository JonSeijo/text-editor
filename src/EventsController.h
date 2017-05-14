#ifndef EventsController_H
#define EventsController_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TextDocument.h"
#include "TextView.h"


class EventsController {
    public:
        void handleEvents(TextDocument &document, TextView &view, sf::Event &event);
};

#endif