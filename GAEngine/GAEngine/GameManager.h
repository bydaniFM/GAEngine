#ifndef __GAMEMANAGER
#define __GAMEMANAGER

#include <iostream>
#include "Quest.h"
#include "Scene.h"

//using namespace std;

class GameManager {
private:
	int points;
	bool quest1;
	vector<Quest*> myQuests;
public:
	GameManager();
	void startQuest(int num);
	void endQuest(int num);
	Quest* getQuest(int num);
};
#endif // !__GAMEMANAGER
