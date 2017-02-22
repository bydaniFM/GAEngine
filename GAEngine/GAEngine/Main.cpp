#include <Windows.h>
#include "Scene.h"
#include "Sprite.h"
#include "XMLReader.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int){

	Event event;
	XMLReader myReader;

	bool isPressed = false;
	GameEntity scene1;

	RenderWindow window(VideoMode(640, 480), "GAEngine", Style::Titlebar | Style::Close | !Style::Resize);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(true);

	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

	//char* route = myReader.Load("background1");
	//scene1.AddChild(new CSprite(route));
	scene1.AddChild(new CSprite(myReader.Load("background3")));
	//scene1.AddChild(new CSprite("Resources/Textures/background1.png"));

	while (window.isOpen()){
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		//window.draw(shape);
		scene1.Draw(&window);
		window.display();
	}

	return 0;
}