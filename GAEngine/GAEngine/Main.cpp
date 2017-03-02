#include <Windows.h>
#include "Scene.h"
#include "Sprite.h"
#include "Text.h"
#include "XMLReader.h"

//void RefreshWindow(RenderWindow& window, GameEntity scene, Text text);
bool checkButtonClicked(Vector2i mousePos, CSprite *button);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int){

	Event event;
	XMLReader myReader;

	GameEntity menu;
	GameEntity inventory;
	GameEntity credits;
	GameEntity scene1;
	GameEntity scene2;
	GameEntity scene3;

	CSprite *background;
	CSprite *player;

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

	Font arial;
	arial.loadFromFile("Resources/Fonts/Arial.ttf");
	Text debug("Hi", arial, 12);
	//debug.setColor(Color::Black);
	debug.setFillColor(Color::Black);

#pragma region Menu
	//Vector2f menuSize(50, 100);
	RectangleShape button1(Vector2f(50, 100));
	//menu.AddChild(button1);
	button1.setFillColor(Color::Green);
	button1.setPosition(300, 300);

	CSprite *menu_spr = new CSprite(myReader.Load("menu_spr"));
	menu.AddChild(menu_spr);
	menu_spr->Get()->setPosition(64, 80);

	CSprite *button_play_spr = new CSprite(myReader.Load("button_play"));
	menu.AddChild(button_play_spr);
	button_play_spr->Get()->setPosition(192, 169);

	CSprite *button_credits_spr = new CSprite(myReader.Load("button_credits"));
	menu.AddChild(button_credits_spr);
	button_credits_spr->Get()->setPosition(192, 240);

	CSprite *button_exit_spr = new CSprite(myReader.Load("button_exit"));
	menu.AddChild(button_exit_spr);
	button_exit_spr->Get()->setPosition(192, 311);

	//CText *menuText;
	//menuText = new CText("Menu"); //myReader.Load("TextAlgo"));
	//menu.AddChild(menuText);

#pragma endregion

#pragma region Scene 1

	background = new CSprite(myReader.Load("background4"));
	//background->Get()->setPosition(-10, 0);
	scene1.AddChild(background);
	levelLenght = background->Get()->getTexture()->getSize().x;

	player = new CSprite(myReader.Load("player"));
	player->Get()->setPosition(320, 350);
	scene1.AddChild(player);

#pragma endregion

	menu.active = true;
	//scene1.active = true;

#pragma region Update Loop

	while (window.isOpen()){
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				isPressed = true;
				if (menu.active)
					menu.active = false;
				else
					menu.active = true;
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				if (checkButtonClicked(Mouse::getPosition(window), button_play_spr)) {
					menu.active = false;
					scene1.active = true;
				} else if (checkButtonClicked(Mouse::getPosition(window), button_credits_spr)) {
					menu.active = false;
					credits.active = true;
				} else if (checkButtonClicked(Mouse::getPosition(window), button_exit_spr)) {
					window.close();
				}
			}
		}

		if (!menu.active && !inventory.active) {

#pragma region Movement

			posX = player->Get()->getPosition().x;
			posY = player->Get()->getPosition().y;
			backgroundPosX = background->Get()->getPosition().x;
			backgroundPosY = background->Get()->getPosition().y;

			debug.setString("posX = " + std::to_string(posX) + "\n" +
				"posY = " + std::to_string(posY) + "\n" +
				"backgroundPosX = " + std::to_string(backgroundPosX) + "\n" +
				"backgroundPosY = " + std::to_string(backgroundPosY) + "\n");

			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				if (backgroundPosX - speed >= -levelLenght + windowWidth && posX == windowWidth / 2) {
					background->Get()->setPosition(backgroundPosX - speed, backgroundPosY);
				} else if (posX <= windowWidth - player->Get()->getTextureRect().width) {
					player->Get()->setPosition(posX + speed, posY);
				}
				/*if(backgroundPosX >= -levelLenght + 320 || backgroundPosX <= 320) {
					player->Get()->setPosition(posX + speed, posY);
				}*/
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				if (backgroundPosX + speed <= 0 && posX == windowWidth / 2) {
					background->Get()->setPosition(backgroundPosX + speed, backgroundPosY);
				} else if (posX >= 0) {
					player->Get()->setPosition(posX - speed, posY);
				}
				/*if (backgroundPosX >= -levelLenght + 320 || backgroundPosX <= 320) {
					player->Get()->setPosition(posX - speed, posY);
				}*/

			}

#pragma endregion
		
		}
#pragma region Draw Scenes

		/*switch (activeScene) {
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
		}*/

		/*window.clear();
		scene1.Draw(&window);
		window.display();*/

		GameEntity scenes[] = { scene1, scene2, scene3, menu };
		window.clear();
		for (int i = 0; i < sizeof(scenes)/sizeof(*scenes); i++) {
			if(scenes[i].active)
				scenes[i].Draw(&window);
		}
		//menuText->Draw(&window);
		window.draw(debug);
		window.display();

#pragma endregion
	}
#pragma endregion
	return 0;
}

//void RefreshWindow(RenderWindow& window, GameEntity scene, Text text) {
//	window.clear();
//	scene.Draw(&window);
//	window.draw(text);
//	window.display();
//}

bool checkButtonClicked(Vector2i mousePosInt, CSprite *button) {
	Vector2f mousePos((float)mousePosInt.x, (float)mousePosInt.y);
	if (mousePos.x >= button->Get()->getPosition().x && mousePos.x <= button->Get()->getPosition().x + button->Get()->getTextureRect().width &&
		mousePos.y >= button->Get()->getPosition().y && mousePos.y <= button->Get()->getPosition().y + button->Get()->getTextureRect().height) {
		return true;
	} else {
		return false;
	}
}