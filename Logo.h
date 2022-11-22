#pragma once

#include "Background.h"

#include "SFML/Graphics.hpp"
#include <thread>
#include <chrono>

sf::Color whColor = sf::Color::White;
sf::Color lgColor = sf::Color{ 28, 30, 38 };
sf::Color Transparency = sf::Color{ 255,255,255,128 };

sf::ConvexShape polygonLogo[6];
using namespace sf;

int PosX = 200, PosY = 50;

sf::Event ev;

void Drawlogo(sf::RenderWindow& window) {


	for (int i = 0; i < 6; i++) {
		polygon[i].setFillColor(sf::Color::White);
	}

	polygonLogo[0].setPointCount(3);
	polygonLogo[0].setFillColor(whColor);
	polygonLogo[0].setPoint(0, Vector2f(300, 300));
	polygonLogo[0].setPoint(1, Vector2f(300, 0));
	polygonLogo[0].setPoint(2, Vector2f(0, 100));
	polygonLogo[0].setPosition(PosX, PosY);

	window.waitEvent(ev);
	
	polygonLogo[1].setPointCount(3);
	polygonLogo[1].setFillColor(whColor);
	polygonLogo[1].setPoint(0, Vector2f(300, 300));
	polygonLogo[1].setPoint(1, Vector2f(600, 100));
	polygonLogo[1].setPoint(2, Vector2f(300, 0));
	polygonLogo[1].setPosition(PosX, PosY);

	
	polygonLogo[2].setPointCount(3);
	polygonLogo[2].setFillColor(whColor);
	polygonLogo[2].setPoint(0, Vector2f(300, 300));
	polygonLogo[2].setPoint(1, Vector2f(600, 100));
	polygonLogo[2].setPoint(2, Vector2f(600, 500));
	polygonLogo[2].setPosition(PosX + 10, PosY);

	
	polygonLogo[3].setPointCount(3);
	polygonLogo[3].setFillColor(whColor);
	polygonLogo[3].setPoint(0, Vector2f(300, 300));
	polygonLogo[3].setPoint(1, Vector2f(600, 500));
	polygonLogo[3].setPoint(2, Vector2f(300, 600));
	polygonLogo[3].setPosition(PosX, PosY);

	
	polygonLogo[4].setPointCount(3);
	polygonLogo[4].setFillColor(whColor);
	polygonLogo[4].setPoint(0, Vector2f(300, 300));
	polygonLogo[4].setPoint(1, Vector2f(0, 500));
	polygonLogo[4].setPoint(2, Vector2f(300, 600));
	polygonLogo[4].setPosition(PosX, PosY);

	
	polygonLogo[5].setPointCount(3);
	polygonLogo[5].setFillColor(whColor);
	polygonLogo[5].setPoint(0, Vector2f(300, 300));
	polygonLogo[5].setPoint(1, Vector2f(0, 100));
	polygonLogo[5].setPoint(2, Vector2f(0, 500));
	polygonLogo[5].setPosition(PosX - 10, PosY);

	for (int i = 0; i < 6; i++)
	{
		
		window.draw(polygonLogo[i]);
		//polygonLogo[i].setPosition(30, 30);
	}
	window.display();

	for (int i = 0; i < 6; i++)
	{
		window.draw(polygonLogo[i]);
	}

	window.display();

	if (window.waitEvent(ev)) {
		for (int i = 0; i < 6; i++){		
			polygonLogo[i].setFillColor(lgColor);

				for (int i = 0; i < 6; i++) {
					window.draw(polygonLogo[i]);	
				}

			window.display();

			// ========< TIME CHANGE CIRCLE COLOR >=========
			std::this_thread::sleep_for(std::chrono::milliseconds(90));
		 }
	}
	window.display();

	int8_t TransparencyValue = 255;

	/*
	[&]() {
		while(TransparencyValue <= 0){

			for (int i = 0; i < 6; i++)
			{
				polygonLogo[i].setFillColor(sf::Color(255,255,255, TransparencyValue));
			}
			for (int i = 0; i < 6; i++)
			{
				window.draw(polygonLogo[i]);
			}
			TransparencyValue -= 2;
			std::this_thread::sleep_for(std::chrono::milliseconds(30));
		}
		window.display();
	};
	*/
}