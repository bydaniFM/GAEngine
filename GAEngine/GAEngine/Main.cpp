#include <Windows.h>
#include "Scene.h"
#include "Sprite.h"
#include "XMLReader.h"

void RefreshWindow(RenderWindow& window, GameEntity scene);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int){

	Event event;
	XMLReader myReader;

	GameEntity menu;
	GameEntity scene1;
	GameEntity scene2;
	GameEntity scene3;

	CSprite *background;

	int activeScene = 1;
	bool isPressed = false;
	float posX = 0;
	float posY = 0;
	int speed = 5;
	int levelLenght = 0;

	RenderWindow window(VideoMode(640, 480), "GAEngine", Style::Titlebar | Style::Close | !Style::Resize);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(true);

	/*CircleShape shape(100.f);
	shape.setFillColor(Color::Green);*/

	//char* route = myReader.Load("background1");
	//scene1.AddChild(new CSprite(route));
	//scene1.AddChild(new CSprite("Resources/Textures/background1.png"));
	background = new CSprite(myReader.Load("background4"));
	background->Get()->setPosition(-10, 0);
	scene1.AddChild(background);
	levelLenght = background->Get()->getTexture()->getSize().x;

	while (window.isOpen()){
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}

		// Movement
		posX = background->Get()->getPosition().x;
		posY = background->Get()->getPosition().y;
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (posX - speed >= -levelLenght+640)
				background->Get()->setPosition(posX - speed, posY);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if (posX + speed <= 0)
				background->Get()->setPosition(posX + speed, posY);
		}

		switch (activeScene) {
		case 1:
			RefreshWindow(window, scene1);
			break;
		case 2:
			RefreshWindow(window, scene2);
			break;
		case 3:
			RefreshWindow(window, scene3);
			break;
		default:
			RefreshWindow(window, menu);
			break;
		}
		/*window.clear();
		scene1.Draw(&window);
		window.display();*/
	}

	return 0;
}

void RefreshWindow(RenderWindow& window, GameEntity scene) {
	window.clear();
	scene.Draw(&window);
	window.display();
}