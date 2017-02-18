#include <Windows.h>
#include "Scene.h"
#include "Sprite.h"
#include "rapidxml-1.13/rapidxml.hpp"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int){

	Event event;

	bool isPressed = false;
	GameEntity scene1;

	RenderWindow window(VideoMode(640, 480), "IO", Style::Titlebar | Style::Close | !Style::Resize);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(true);

	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

	while (window.isOpen()){
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(&window);
		window.display();
	}

	return 0;
}