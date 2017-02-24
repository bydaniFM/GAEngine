#include <Windows.h>
#include "Scene.h"
#include "Sprite.h"
#include "XMLReader.h"

void RefreshWindow(RenderWindow& window, GameEntity scene, Text text);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int){

	Event event;
	XMLReader myReader;

	GameEntity menu;
	GameEntity scene1;
	GameEntity scene2;
	GameEntity scene3;

	CSprite *background;
	CSprite *player;

	Font arial;
	arial.loadFromFile("Resources/Fonts/Arial.ttf");
	Text debug("Hi", arial, 12);
	//debug.setColor(Color::Black);
	debug.setFillColor(Color::Black);

	int windowWidth = 640;	// In pixels
	int windowHeight = 480;
	int activeScene = 1;
	bool isPressed = false;
	float posX = 0;
	float posY = 0;
	float backgroundPosX = 0;
	float backgroundPosY = 0;
	int speed = 5;
	int levelLenght = 0;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "GAEngine", Style::Titlebar | Style::Close | !Style::Resize);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(true);

	/*CircleShape shape(100.f);
	shape.setFillColor(Color::Green);*/

	//debug = new Text();

	//char* route = myReader.Load("background1");
	//scene1.AddChild(new CSprite(route));
	//scene1.AddChild(new CSprite("Resources/Textures/background1.png"));
	background = new CSprite(myReader.Load("background1"));
	background->Get()->setPosition(-10, 0);
	scene1.AddChild(background);
	levelLenght = background->Get()->getTexture()->getSize().x;

	player = new CSprite(myReader.Load("player"));
	player->Get()->setPosition(320, 350);
	scene1.AddChild(player);

	while (window.isOpen()){
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}

		// Movement
		posX = player->Get()->getPosition().x;
		posY = player->Get()->getPosition().y;
		backgroundPosX = background->Get()->getPosition().x;
		backgroundPosY = background->Get()->getPosition().y;

		debug.setString("posX = " + std::to_string(posX) + "\n" + 
						"posY = " + std::to_string(posY) + "\n" + 
						"backgroundPosX = " + std::to_string(backgroundPosX) + "\n" + 
						"backgroundPosY = " + std::to_string(backgroundPosY) + "\n");

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			if (backgroundPosX - speed >= -levelLenght + windowWidth && posX == windowWidth/2) {
				background->Get()->setPosition(backgroundPosX - speed, backgroundPosY);
			} else if (posX <= windowWidth-player->Get()->getTextureRect().width) {
				player->Get()->setPosition(posX + speed, posY);
			}
			/*if(backgroundPosX >= -levelLenght + 320 || backgroundPosX <= 320) {
				player->Get()->setPosition(posX + speed, posY);
			}*/
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			if (backgroundPosX + speed <= 0 && posX == windowWidth / 2) {
				background->Get()->setPosition(backgroundPosX + speed, backgroundPosY);
			} else if(posX >= 0) {
				player->Get()->setPosition(posX - speed, posY);
			}
			/*if (backgroundPosX >= -levelLenght + 320 || backgroundPosX <= 320) {
				player->Get()->setPosition(posX - speed, posY);
			}*/
			
		}

		switch (activeScene) {
		case 1:
			RefreshWindow(window, scene1, debug);
			break;
		case 2:
			RefreshWindow(window, scene2, debug);
			break;
		case 3:
			RefreshWindow(window, scene3, debug);
			break;
		default:
			RefreshWindow(window, menu, debug);
			break;
		}
		/*window.clear();
		scene1.Draw(&window);
		window.display();*/
	}

	return 0;
}

void RefreshWindow(RenderWindow& window, GameEntity scene, Text text) {
	window.clear();
	scene.Draw(&window);
	window.draw(text);
	window.display();
}