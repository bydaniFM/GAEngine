#include "GameManager.h"

GameManager::GameManager() {
	points = 0;
	quest1 = false;
}

void GameManager::startQuest(int num) {
	/*switch (num) {
	case 1:
		Quest *quest1 = new Quest(num);
		myQuests.push_back(quest1);
	default:
		break;
	}*/
	myQuests.push_back(new Quest(num));
}

void GameManager::endQuest(int num) {
	switch (num) {
	case 1:
		quest1 = true;
	default:
		break;
	}
}