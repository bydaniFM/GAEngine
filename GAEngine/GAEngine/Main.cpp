#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "Scene.h"
#include "Sprite.h"
#include "Text.h"
#include "Dialogue.h"
#include "Inventory.h"
#include "Object.h"
#include "XMLReader.h"
#include "GameManager.h"

// Functions declaration
bool checkButtonClicked(Vector2i mousePos, CSprite *button);
bool checkCollision(CAnimatedSprite *a, CSprite *b);
Dialogue StartDialogue(Dialogue myDialogue, char* route);
Dialogue NextDialogue(Dialogue myDialogue, CText *dialogueText);
int coolDown(int num);

Font Arial;
Text debug("Hi", Arial, 12);

XMLReader myReader;

SoundBuffer soundBuffer;
Sound sound;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int){

	Event event;

	GameManager gameManager;

	GameEntity menu;
	GameEntity credits;
	GameEntity scene1;
	GameEntity scene2;
	GameEntity scene3;
	GameEntity *activeScene;
	Dialogue dialogue1;
	Dialogue dialogue2;
	Dialogue dialogue_pickup;
	Dialogue *activeDialogue;

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
	int temp = 0;

	bool npc1_Talked = false;
	bool npc2_Talked = false;

	CSprite *collidingObj = NULL;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "GAEngine", Style::Titlebar | Style::Close | !Style::Resize);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(true);

	//Font Arial;
	Arial.loadFromFile("Resources/Fonts/Arial.ttf");
	//Text debug("Hi", Arial, 12);
	debug.setFillColor(Color::Black);

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

	CSprite *frame_spr = new CSprite(myReader.Load("obj_frame"));
	CSprite *inventory_spr = new CSprite(myReader.Load("inventory_spr"));

	CInventory myInventory(inventory_spr, frame_spr);

	/*myInventory.AddChild(inventory_spr, "CSprite");
	inventory_spr->Get()->setPosition(64, 80);*/

	CObject *key = new CObject("key", new CSprite(myReader.Load("obj_key")), true);
	myInventory.AddItem(key);/*

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
	myInventory.AddItem(o7);*/

#pragma endregion

#pragma region Dialogue1

	CSprite *dialogueBox = new CSprite(myReader.Load("DialogueBox"));
	dialogue1.AddChild(dialogueBox, "CSprite");
	CSprite *buttonNext = new CSprite(myReader.Load("button_next"));
	dialogue1.AddChild(buttonNext, "CSprite");
	buttonNext->Get()->setPosition(530, 390);

	CText *dialogueText1 = new CText("", Arial, 24);
	dialogue1.AddText(dialogueText1);
	dialogueText1->Get()->setPosition(16, 370);
	
#pragma endregion

#pragma region Dialogue2

	dialogue2.AddChild(dialogueBox, "CSprite");
	CText *dialogueText2 = new CText("", Arial, 24);
	dialogue2.AddText(dialogueText2);
	dialogueText2->Get()->setPosition(16, 320);

	CSprite *buttonYes = new CSprite(myReader.Load("button_yes"));
	dialogue2.AddChild(buttonYes, "CSprite");
	buttonYes->Get()->setPosition(16, 400);

	CSprite *buttonNo = new CSprite(myReader.Load("button_no"));
	dialogue2.AddChild(buttonNo, "CSprite");
	buttonNo->Get()->setPosition(350, 400);


#pragma endregion

#pragma region pickup dialogue

	dialogue_pickup.AddChild(dialogueBox, "CSprite");
	CText *dialogueText_pickup = new CText("", Arial, 24);
	dialogue_pickup.AddText(dialogueText_pickup);
	dialogueText_pickup->Get()->setPosition(16, 320);

	dialogue_pickup.AddChild(buttonYes, "CSprite");
	dialogue_pickup.AddChild(buttonNo, "CSprite");

#pragma endregion

#pragma region Scene 1

	Music mainTheme;
	mainTheme.openFromFile("Resources/Audio/mainTheme.wav");
	scene1.addMusic(&mainTheme);

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
	npc1->Get()->setPosition(900, windowHeight - npc1->Get()->getTextureRect().height);

	CSprite *npc2;
	npc2 = new CSprite(myReader.Load("npc1"));
	scene1.AddChild(npc2, "CSprite");
	npc2->Get()->setPosition(600, windowHeight - npc2->Get()->getTextureRect().height);

	CObject *obj_paper1 = new CObject("paper", new CSprite(myReader.Load("obj_paper")), true);
	obj_paper1->getSprite()->Get()->setPosition(1300, windowHeight - 70);
	scene1.AddChild(obj_paper1->getSprite(), "CSprite");

	CObject *obj_paper2 = new CObject("paper", new CSprite(myReader.Load("obj_paper")), true);
	obj_paper2->getSprite()->Get()->setPosition(1600, windowHeight - 70);
	scene1.AddChild(obj_paper2->getSprite(), "CSprite");

	CObject *obj_paper3 = new CObject("paper", new CSprite(myReader.Load("obj_paper")), true);
	obj_paper3->getSprite()->Get()->setPosition(1900, windowHeight - 70);
	scene1.AddChild(obj_paper3->getSprite(), "CSprite");

#pragma endregion

#pragma region Credits

	CSprite *credits_spr = new CSprite(myReader.Load("credits_spr"));
	credits.AddChild(credits_spr, "CSprite");
	credits_spr->Get()->setPosition(64, 80);

	CText *credits_txt = new CText(myReader.Load("credits_txt"), Arial, 16);
	//credits_txt->Get()->setString("Something\nsomething");
	credits.AddChild(credits_txt, "CText");
	credits_txt->Get()->setPosition(128, windowHeight / 3);

	CSprite *button_back_spr = new CSprite(myReader.Load("button_back"));
	credits.AddChild(button_back_spr, "CSprite");
	button_back_spr->Get()->setPosition(192, 320);


#pragma endregion

	//Active scenes at the start of te game
	menu.setActive(true);
	activeScene = &scene1;
	activeDialogue = &dialogue1;

#pragma region Update Loop

	while (window.isOpen()){

#pragma region Event management

		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape) {
					//isPressed = true;
					if (menu.getActive())
						menu.setActive(false);
					else
						menu.setActive(true);
				}
				if (event.key.code == Keyboard::I) {
					if (myInventory.getActive())
						myInventory.setActive(false);
					else
						myInventory.setActive(true);
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
				if (menu.getActive()) {
					if (checkButtonClicked(Mouse::getPosition(window), button_play_spr)) {
						sound.play();
						menu.setActive(false);
						activeScene->setActive(true);
					} else if (checkButtonClicked(Mouse::getPosition(window), button_credits_spr)) {
						sound.play();
						menu.setActive(false);
						credits.setActive(true);
					} else if (checkButtonClicked(Mouse::getPosition(window), button_exit_spr)) {
						sound.play();
						window.close();
					}
				}
				else if (dialogue1.getActive()) {
					if (checkButtonClicked(Mouse::getPosition(window), buttonNext)) {
						sound.play();
						dialogue1 = NextDialogue(dialogue1, dialogueText1);
					}
				}
				else if (dialogue2.getActive()) {
					if (checkButtonClicked(Mouse::getPosition(window), buttonYes)) {
						sound.play();
						dialogue2.setActive(false);
						gameManager.startQuest(1);
						npc1_Talked = true;
					}
					if (checkButtonClicked(Mouse::getPosition(window), buttonNo)) {
						sound.play();
						dialogue2.setActive(false);
						//do something different
						npc1_Talked = true;
					}
				}
				else if (dialogue_pickup.getActive()) {
					if (checkButtonClicked(Mouse::getPosition(window), buttonYes)) {
						sound.play();
						dialogue_pickup.setActive(false);
						if (collidingObj == obj_paper1->getSprite()) {
							myInventory.AddItem(obj_paper1);
							scene1.DeleteChild(obj_paper1->getSprite());
						}
						if (collidingObj == obj_paper2->getSprite()) {
							myInventory.AddItem(obj_paper2);
							scene1.DeleteChild(obj_paper2->getSprite());
						}
						if (collidingObj == obj_paper3->getSprite()) {
							myInventory.AddItem(obj_paper3);
							scene1.DeleteChild(obj_paper3->getSprite());
						}

					}
					if (checkButtonClicked(Mouse::getPosition(window), buttonNo)) {
						sound.play();
						dialogue_pickup.setActive(false);
					}
				}
				else if (credits.getActive()) {
					if (checkButtonClicked(Mouse::getPosition(window), button_back_spr)) {
						sound.play();
						credits.setActive(false);
						menu.setActive(true);
					}
				}
			}
		}
#pragma endregion
		
		if (!menu.getActive() && !myInventory.getActive() && !activeDialogue->getActive()) {

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

			if (checkCollision(player, npc1)) {
				if (!dialogue2.getActive() && !npc1_Talked) {
					activeDialogue = &dialogue2;
					dialogue2 = StartDialogue(dialogue2, "2_01");
				}
				if (myInventory.searchItem("paper") == 3) {
					myInventory.DeleteItem(obj_paper1);
					myInventory.DeleteItem(obj_paper2);
					myInventory.DeleteItem(obj_paper3);
					activeDialogue = &dialogue2;
					dialogue2 = NextDialogue(dialogue2, dialogueText2);
					dialogue2.DeleteChild(buttonYes);
					dialogue2.DeleteChild(buttonNo);
					gameManager.endQuest(1);
					npc1_Talked = true;
				}
			}
			if (checkCollision(player, npc2)) {
				if (!dialogue1.getActive() && !npc2_Talked) {
					activeDialogue = &dialogue1;
					dialogue1 = StartDialogue(dialogue1, "1_01");
					npc2_Talked = true;
				}
			}

			//Quest 1
			if (gameManager.getQuest(1) != NULL){
				if (gameManager.getQuest(1)->inProgress = true) {
					if (checkCollision(player, obj_paper1->getSprite()) && !obj_paper1->getInInventory()) {
						activeDialogue = &dialogue_pickup;
						dialogue_pickup = StartDialogue(dialogue_pickup, "3_01");
						collidingObj = obj_paper1->getSprite();
					}
					if (checkCollision(player, obj_paper2->getSprite()) && !obj_paper2->getInInventory()) {
						activeDialogue = &dialogue_pickup;
						dialogue_pickup = StartDialogue(dialogue_pickup, "3_01");
						collidingObj = obj_paper2->getSprite();
					}
					if (checkCollision(player, obj_paper3->getSprite()) && !obj_paper3->getInInventory()) {
						activeDialogue = &dialogue_pickup;
						dialogue_pickup = StartDialogue(dialogue_pickup, "3_01");
						collidingObj = obj_paper3->getSprite();
					}
				}
			}

			// npc1 coolDown
			if (gameManager.getQuest(1) == NULL || (!gameManager.getQuest(1)->finished && !gameManager.getQuest(1)->inProgress)) {
				if (npc1_Talked) {
					if (temp < 300) {
						temp = coolDown(temp);
					} else {
						npc1_Talked = false;
						temp = 0;
					}
				}
			}

#pragma endregion

		}

#pragma region Check quests

		//Quest 1
		/*if (myInventory.searchItem("paper") == 3) {

		}*/

#pragma endregion

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
		GameEntity scenes[] = { *activeScene, *activeDialogue, menu, myInventory, credits };
		window.clear();
		for (int i = 0; i < sizeof(scenes)/sizeof(*scenes); i++) {
			if(scenes[i].getActive())
				scenes[i].Draw(&window);
		}
		//window.draw(dialogue1.getText());
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

	int borderALeft = a->Get()->getPosition().x - rectA.width / 16;// rectA.left - rectA.width / 16;
	int borderARight = a->Get()->getPosition().x + rectA.width / 16;
	int borderBLeft = b->Get()->getPosition().x;
	int borderBRight = b->Get()->getPosition().x + rectB.width;

	debug.setString("\nborderALeft = " + to_string(borderALeft) + "\n" +
		"borderARight = " + to_string(borderARight) + "\n" + 
		"borderBLeft = " + to_string(borderBLeft) + "\n" +
		"borderBRight = " + to_string(borderBRight));

	if (borderALeft <= borderBRight && borderARight >= borderBLeft)	//if (rectA.left >= rectB.left - rectB.width && rectA.left <= rectB.left)
		return true;
	else
		return false;
}

Dialogue StartDialogue(Dialogue myDialogue, char* route) {
	myDialogue.setText(myReader.Load(route), route);
	myDialogue.setActive(true);
	return myDialogue;
}

Dialogue NextDialogue(Dialogue myDialogue, CText *dialogueText) {
	string route = myDialogue.getRoute();
	route.back() = route.back() + 1;
	
	if (myReader.Load(route) != NULL) {
		myDialogue.setText(myReader.Load(route), route);
		myDialogue.setActive(true);
	} else {
		myDialogue.setActive(false);
	}
	return myDialogue;
}

int coolDown(int num) {
	num++;
	return num;
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