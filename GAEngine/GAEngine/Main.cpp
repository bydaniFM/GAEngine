//#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "Scene.h"
#include "Sprite.h"
#include "Text.h"
#include "Dialogue.h"
#include "Inventory.h"
#include "Object.h"
#include "XMLReader.h"

//void RefreshWindow(RenderWindow& window, GameEntity scene, Text text);
bool checkButtonClicked(Vector2i mousePos, CSprite *button);
//bool checkCollision(CSprite a, CSprite b);
bool checkCollision(CAnimatedSprite *a, CSprite *b);
Dialogue StartDialogue(Dialogue myDialogue, char* route);
Dialogue NextDialogue(Dialogue myDialogue, CText *dialogueText);

Font Arial;
Text debug("Hi", Arial, 12);

XMLReader myReader;

SoundBuffer soundBuffer;
Sound sound;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int){

	Event event;
	//XMLReader myReader;

	GameEntity menu;
	GameEntity credits;
	GameEntity scene1;
	GameEntity scene2;
	GameEntity scene3;
	GameEntity *activeScene;
	CInventory myInventory;
	Dialogue myDialogue;

	const int windowWidth = 640;	// In pixels
	const int windowHeight = 480;

	bool isPressed = false;
	int playerScale = 6;
	float posX = 0;
	float posY = 0;
	float backgroundPosX = 0;
	float backgroundPosY = 0;
	int speed = 3;
	int levelLenght = 0;
	bool npc1_Talked = false;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "GAEngine", Style::Titlebar | Style::Close | !Style::Resize);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(true);

	//Font Arial;
	Arial.loadFromFile("Resources/Fonts/Arial.ttf");
	//Text debug("Hi", Arial, 12);
	debug.setFillColor(Color::Black);

	Music mainTheme;
	mainTheme.openFromFile("Resources/Audio/mainTheme.wav");
	mainTheme.setLoop(true);
	mainTheme.play();

	/*SoundBuffer soundBuffer;
	Sound sound;*/
	soundBuffer.loadFromFile("Resources/Audio/beep3.wav");
	sound.setBuffer(soundBuffer);

#pragma region Menu

	CSprite *menu_spr = new CSprite(myReader.Load("menu_spr"));
	menu.AddChild(menu_spr, "CSprite");
	menu_spr->Get()->setPosition(64, 80);
	CSprite *button_play_spr = new CSprite(myReader.Load("button_play"));
	menu.AddChild(button_play_spr, "CSprite");
	button_play_spr->Get()->setPosition(192, 169);

	CSprite *button_credits_spr = new CSprite(myReader.Load("button_credits"));
	menu.AddChild(button_credits_spr, "CSprite");
	button_credits_spr->Get()->setPosition(192, 240);

	CSprite *button_exit_spr = new CSprite(myReader.Load("button_exit"));
	menu.AddChild(button_exit_spr, "CSprite");
	button_exit_spr->Get()->setPosition(192, 311);
	//button_exit_spr->SetVisible(false);

	//CText *menuText;
	//menuText = new CText("Menu"); //myReader.Load("TextAlgo"));
	//menu.AddChild(menuText);

#pragma endregion

#pragma region Inventory

	CSprite *inventory_spr = new CSprite(myReader.Load("inventory_spr"));
	myInventory.AddChild(inventory_spr, "CSprite");
	inventory_spr->Get()->setPosition(64, 80);

	CObject *key = new CObject("key", new CSprite(myReader.Load("obj_key")), true);
	myInventory.AddItem(key);

	CObject *map = new CObject("map", new CSprite(myReader.Load("obj_key")), false);
	myInventory.AddItem(map);

	CObject *o3 = new CObject("map", new CSprite(myReader.Load("obj_key")), false);
	myInventory.AddItem(o3);

	CObject *o4 = new CObject("map", new CSprite(myReader.Load("obj_key")), false);
	myInventory.AddItem(o4);

	CObject *o5 = new CObject("map", new CSprite(myReader.Load("obj_key")), false);
	myInventory.AddItem(o5);

	CObject *o6 = new CObject("map", new CSprite(myReader.Load("obj_key")), false);
	myInventory.AddItem(o6);

	CObject *o7 = new CObject("map", new CSprite(myReader.Load("obj_key")), false);
	myInventory.AddItem(o7);

#pragma endregion

#pragma region Dialogue
	CSprite *dialogueBox = new CSprite(myReader.Load("DialogueBox"));
	myDialogue.AddChild(dialogueBox, "CSprite");
	CSprite *buttonNext = new CSprite(myReader.Load("button_next"));
	myDialogue.AddChild(buttonNext, "CSprite");
	buttonNext->Get()->setPosition(530, 390);

	CText *dialogueText = new CText("", Arial, 24);
	myDialogue.AddText(dialogueText);
	dialogueText->Get()->setPosition(16, 370);
#pragma endregion

#pragma region Scene 1

	CSprite *background;
	background = new CSprite(myReader.Load("background5"));
	//background->Get()->setPosition(-10, 0);
	scene1.AddChild(background, "CSprite");
	levelLenght = background->Get()->getTexture()->getSize().x;

	/*CSprite *player;
	player = new CSprite(myReader.Load("player"));*/
	CAnimatedSprite *player;
	player = new CAnimatedSprite(myReader.Load("anim_player"), 8, 100, false);
	player->Get()->setOrigin(32, 32);
	//player->Get()->setScale(4, 4);
	player->SetScale(playerScale);
	player->Get()->setPosition(windowWidth / 2, windowHeight - player->Get()->getTextureRect().height * (playerScale / 2));
	scene1.AddChild(player, "CSprite");

	CSprite *npc1;
	npc1 = new CSprite(myReader.Load("npc1"));
	scene1.AddChild(npc1, "CSprite");
	npc1->Get()->setPosition(600, windowHeight - npc1->Get()->getTextureRect().height);

	CSprite *npc2;
	npc2 = new CSprite(myReader.Load("npc1"));
	scene1.AddChild(npc2, "CSprite");
	npc2->Get()->setPosition(32, windowHeight - npc2->Get()->getTextureRect().height);


	/*CText *ttext = new CText(myReader.Load("1_01"), Arial);
	scene1.AddChild(ttext, "CText");
	ttext->Get()->setFillColor(Color::White);*/

#pragma endregion

	menu.active = true;
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
					if (myInventory.active)
						myInventory.active = false;
					else
						myInventory.active = true;
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
				if (menu.active) {
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
				if (myDialogue.active) {
					if (checkButtonClicked(Mouse::getPosition(window), buttonNext)) {
						myDialogue = NextDialogue(myDialogue, dialogueText);
					}
				}
			}
		}
#pragma endregion
		
		if (!menu.active && !myInventory.active && !myDialogue.active) {

#pragma region Movement

			posX = player->Get()->getPosition().x;
			posY = player->Get()->getPosition().y;
			backgroundPosX = background->Get()->getPosition().x;
			backgroundPosY = background->Get()->getPosition().y;

			/*debug.setString("posX = " + std::to_string(posX) + "\n" +
				"posY = " + std::to_string(posY) + "\n" +
				"backgroundPosX = " + std::to_string(backgroundPosX) + "\n" +
				"backgroundPosY = " + std::to_string(backgroundPosY) + "\n");*/

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
		
#pragma region Collisions
			if (checkCollision(player, npc2)) {
				//menu.active = true;

				/*CText *ttext = new CText(myReader.Load("1_01"), Arial, 24);
				scene1.AddChild(ttext, "CText");
				ttext->Get()->setFillColor(Color::White);*/
				if (!myDialogue.active && !npc1_Talked) {
					myDialogue = StartDialogue(myDialogue, "1_01");
					npc1_Talked = true;
				}
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

		/*GameEntity scenes[] = { scene1, scene2, scene3, menu, inventory, credits };*/
		GameEntity scenes[] = { *activeScene, myDialogue, menu, myInventory, credits };
		window.clear();
		for (int i = 0; i < sizeof(scenes)/sizeof(*scenes); i++) {
			if(scenes[i].active)
				scenes[i].Draw(&window);
		}
		//window.draw(myDialogue.getText());
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
		sound.play();
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

	debug.setString("\nPos A = " + std::to_string(rectA.left) + "\n" +
		"Pos B = " + std::to_string(rectB.left - rectB.width) + "\n");

	if (rectA.left >= rectB.left - rectB.width && rectA.left <= rectB.left)
		return true;
	else
		return false;
}

Dialogue StartDialogue(Dialogue myDialogue, char* route) {
	//CText *cText = new CText(myReader.Load(route), Arial, 24)
	myDialogue.setText(myReader.Load(route), route);
	myDialogue.active = true;
	return myDialogue;
}

Dialogue NextDialogue(Dialogue myDialogue, CText *dialogueText) {
	string route = myDialogue.getRoute();
	route.back() = route.back() + 1;
	
	if (myReader.Load(route) != NULL) {
		myDialogue.setText(myReader.Load(route), route);
		//dialogueText->Get()->setString(myReader.Load(route));
	} else {
		myDialogue.active = false;
	}
	return myDialogue;
}

//Dialogue createDialogue(string route, GameEntity scene) {
//	Dialogue *myDialogue = new Dialogue();
//	CText *text;
//	string routeHead = route;
//	route.pop_back();
//	string str;
//	char* cstr;
//	bool condition = false;
//	for (int i = routeHead.back(); !condition; i++) {//(str.c_str(), str.c_str() + str.size() + 1)
//		str = route + to_string(i);
//		cstr = new char[str.length() + 1];
//		strcpy(cstr, str.c_str());
//
//		text = new CText(myReader.Load(route + to_string(i)), Arial, 16);
//		myDialogue->AddText(*text);
//
//		if (myReader.Load(cstr) != NULL)
//			condition = true;
//
//		delete[] cstr;
//	}
//	//delete[] cstr;
//	scene.AddChild(text,"CText");
//	return *myDialogue;
//}

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