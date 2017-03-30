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
	myQuests.at(num-1)->finished = true;
}

Quest* GameManager::getQuest(int num) {
	Quest *tmpQuest = NULL;
	for (vector<Quest*>::iterator it = myQuests.begin(); it < myQuests.end(); it++) {
		if ((*it)->ID == num)
			tmpQuest = (*it);
	}
	return tmpQuest;
}