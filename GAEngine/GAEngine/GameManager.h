#ifndef __GAMEMANAGER
#define __GAMEMANAGER

#include <iostream>
#include "Quest.h"
#include "Scene.h"

//using namespace std;

class GameManager {
private:
	// Not in use. Can be useful when adding new mechanics
	int points;
	// Vector of quests
	vector<Quest*> myQuests;
public:
	// Default constructor
	GameManager();
	// Initializes a new quest
	void startQuest(int num);
	// Ends and deletes a finished or dropped quest
	void endQuest(int num);
	// Finds a quest by ID and returns it
	Quest* getQuest(int num);
};
#endif // !__GAMEMANAGER
