#include <Windows.h>
#include "Scene.h"
#include "Sprite.h"
#include "Text.h"
#include "Inventory.h"
#include "Object.h"
#include "XMLReader.h"

//void RefreshWindow(RenderWindow& window, GameEntity scene, Text text);
bool checkButtonClicked(Vector2i mousePos, CSprite *button);
bool checkCollision(CSprite a, CSprite b);
bool checkCollision(CAnimatedSprite *a, CSprite *b);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int){

	Event event;
	XMLReader myReader;

	GameEntity menu;
	GameEntity inventory;
	GameEntity credits;
	GameEntity scene1;
	GameEntity scene2;
	GameEntity scene3;
	GameEntity *activeScene;

	int windowWidth = 640;	// In pixels
	int windowHeight = 480;
	bool isPressed = false;
	int playerScale = 6;
	float posX = 0;
	float posY = 0;
	float backgroundPosX = 0;
	float backgroundPosY = 0;
	int speed = 3;
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
	/*Vector2f menuSize(50, 100);
	RectangleShape button1(Vector2f(50, 100));
	menu.AddChild(button1);
	button1.setFillColor(Color::Green);
	button1.setPosition(300, 300);*/

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

#pragma region Inventory

	CSprite *inventory_spr = new CSprite(myReader.Load("inventory_spr"));
	inventory.AddChild(inventory_spr);
	inventory_spr->Get()->setPosition(64, 80);
	CInventory *myInventory = new CInventory();

	CSprite *obj_key = new CSprite(myReader.Load("obj_key"));
	inventory.AddChild(obj_key);
	obj_key->Get()->setPosition(300, 200);
	CObject *key = new CObject("Key", true);
	myInventory->Push(key);

	CObject *map = new CObject("Map", true);
	myInventory->Push(map);

	CObject *stick = new CObject("Stick", true);
	myInventory->Push(stick);
	//myInventory->Pop(key);

#pragma endregion

#pragma region Scene 1

	CSprite *background;
	background = new CSprite(myReader.Load("background5"));
	//background->Get()->setPosition(-10, 0);
	scene1.AddChild(background);
	levelLenght = background->Get()->getTexture()->getSize().x;

	/*CSprite *player;
	player = new CSprite(myReader.Load("player"));*/
	CAnimatedSprite *player;
	player = new CAnimatedSprite(myReader.Load("anim_player"), 8, 100, false);
	player->Get()->setOrigin(32, 32);
	//player->Get()->setScale(4, 4);
	player->SetScale(playerScale);
	player->Get()->setPosition(windowWidth / 2, windowHeight - player->Get()->getTextureRect().height * (playerScale / 2));
	scene1.AddChild(player, false);

	CSprite *npc1;
	npc1 = new CSprite(myReader.Load("npc1"));
	scene1.AddChild(npc1);
	npc1->Get()->setPosition(600, windowHeight - npc1->Get()->getTextureRect().height);

#pragma endregion

	menu.active = true;
	//scene1.active = true;

	activeScene = &scene1;

#pragma region Update Loop

	while (window.isOpen()){
#pragma region Event management
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape) {
					//isPressed = true;
					if (menu.active)
						menu.active = false;
					else
						menu.active = true;
				}
				if (event.key.code == Keyboard::I) {
					if (inventory.active)
						inventory.active = false;
					else
						inventory.active = true;
				}
				if (event.key.code == Keyboard::Right) {
					if(!isPressed)
						player->SetAnimation(1);
				}
				if (event.key.code == Keyboard::Left) {
					if (!isPressed)
						player->SetAnimation(2);
				}
				isPressed = true;
			}
			
			if (event.type == Event::KeyReleased) {
				isPressed = false;
				if (event.key.code == Keyboard::Right) {
					player->SetAnimation(0);
				}
				if (event.key.code == Keyboard::Left) {
					player->SetAnimation(0);
				}
				
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				if (checkButtonClicked(Mouse::getPosition(window), button_play_spr)) {
					menu.active = false;
					activeScene->active = true;
				} else if (checkButtonClicked(Mouse::getPosition(window), button_credits_spr)) {
					menu.active = false;
					credits.active = true;
				} else if (checkButtonClicked(Mouse::getPosition(window), button_exit_spr)) {
					window.close();
				}
			}
		}
#pragma endregion
		
#pragma region Movement
		if (!menu.active && !inventory.active) {

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
					//background->Get()->setPosition(backgroundPosX - speed, backgroundPosY);
					activeScene->Move(-speed);					
				} else if (posX <= windowWidth - player->Get()->getTextureRect().width/2) {
					player->Get()->setPosition(posX + speed, posY);
				}
				/*if(backgroundPosX >= -levelLenght + 320 || backgroundPosX <= 320) {
					player->Get()->setPosition(posX + speed, posY);
				}*/
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				if (backgroundPosX + speed <= 0 && posX == windowWidth / 2) {
					//background->Get()->setPosition(backgroundPosX + speed, backgroundPosY);
					activeScene->Move(speed);
				} else if (posX >= player->Get()->getTextureRect().width / 2) {
					player->Get()->setPosition(posX - speed, posY);
				}
				/*if (backgroundPosX >= -levelLenght + 320 || backgroundPosX <= 320) {
					player->Get()->setPosition(posX - speed, posY);
				}*/

			}

#pragma endregion
		
			if (checkCollision(player, npc1)) {
				menu.active = true;
			}

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

		/*GameEntity scenes[] = { scene1, scene2, scene3, menu, inventory, credits };*/
		GameEntity scenes[] = { *activeScene, menu, inventory, credits };
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

bool checkButtonClicked(Vector2i mousePosInt, CSprite *button) {
	Vector2f mousePos((float)mousePosInt.x, (float)mousePosInt.y);
	if (mousePos.x >= button->Get()->getPosition().x && mousePos.x <= button->Get()->getPosition().x + button->Get()->getTextureRect().width &&
		mousePos.y >= button->Get()->getPosition().y && mousePos.y <= button->Get()->getPosition().y + button->Get()->getTextureRect().height) {
		return true;
	} else {
		return false;
	}
}

bool checkCollision(CSprite *a, CSprite *b) {
	FloatRect rectA = a->Get()->getGlobalBounds();
	FloatRect rectB = b->Get()->getGlobalBounds();

	if (rectA.left >= rectB.left)
		return true;
	else
		return false;
}

bool checkCollision(CAnimatedSprite *a, CSprite *b) {
	FloatRect rectA = a->Get()->getGlobalBounds();
	FloatRect rectB = b->Get()->getGlobalBounds();

	if (rectA.left + rectA.width/8 >= rectB.left)
		return true;
	else
		return false;
}

//bool checkCollision(CSprite *a, CSprite *b) {
//	if (a->Get()->getGlobalBounds().intersects(b->Get()->getGlobalBounds()))
//		return true;
//	else
//		return false;
//}
//
//bool checkCollision(CAnimatedSprite *a, CSprite *b) {
//	if (a->Get()->getGlobalBounds().intersects(b->Get()->getGlobalBounds()))
//		return true;
//	else
//		return false;
//}