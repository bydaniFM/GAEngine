#include "Inventory.h"

CInventory::CInventory() {
	numObjects = 0;
}

CInventory::CInventory(CSprite *spr_back, CSprite *spr_frame) {
	this->spr_back = spr_back;
	this->AddChild(this->spr_back, "CSprite");
	this->spr_back->Get()->setPosition(64, 80);
	this->spr_frame = spr_frame;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			CSprite *tmp = new CSprite(*spr_frame);
			this->AddChild(tmp, "CSprite");
			tmp->Get()->setPosition(640 / 6 + 640 / 7 * j, 480 / 2 - 48 + 48 * 2 * i);
		}
	}
}

//void CInventory::Push(CObject *pObject) {
//	if (pLast == NULL) {
//		pFirst = pObject;
//		pLast = pObject;
//	} else {
//		pLast->pNext = pObject;
//		pObject->pPrev = pLast;
//		pLast = pObject;
//	}
//	numObjects++;
//}
//
//void CInventory::Pop(CObject *pObject) {
//	if (pObject == NULL) {
//		return;
//	}
//	if (pObject->getName() == pFirst->getName()) {
//		pFirst = pObject->pNext;
//		if (pFirst == NULL) {
//			pFirst->pPrev = NULL;
//		}
//		free(pObject);
//		numObjects--;
//		return;
//	}
//	if (pObject->getName() == pLast->getName()) {
//		pLast = pLast->pPrev;
//		if (pLast != NULL) {
//			pLast->pNext = NULL;
//		}
//		free(pObject);
//		numObjects--;
//		return;
//	}
//	CObject *pTemp = pFirst->pNext;
//	while (pTemp != pLast) {
//		if (pObject->getName() == pTemp->getName()) {
//			pTemp->pPrev->pNext = pTemp->pNext;
//			pTemp->pNext->pPrev = pTemp->pPrev;
//			free(pTemp);
//			numObjects--;
//		}
//	}
//}

void CInventory::AddItem(CObject *pObject) {
	if (numObjects < 10) {
		int windowW = 640;
		int windowH = 480;
		int posX = windowW / 6;
		int posY = windowH / 2;

		if (numObjects < 5) {
			posY = posY - 48;
			posX = posX + numObjects * (windowW / 7);
		} else {
			posY = posY + 48;
			posX = posX + (numObjects - 5) * (windowW / 7);
		}
		inventory.push_back(pObject);
		this->AddChild(pObject->getSprite(), "CSprite");
		pObject->getSprite()->Get()->setPosition(posX, posY);

		pObject->setInInventory(true);

		numObjects++;
	}
}

void CInventory::DeleteItem(CObject *pObject) {
	if (pObject == inventory.back() || find(inventory.begin(), inventory.end(), pObject) != inventory.end()) {
		inventory.erase(find(inventory.begin(), inventory.end(), pObject));
		this->DeleteChild(pObject->getSprite());
		numObjects--;
	}
}

int CInventory::getNumObjects() {
	return numObjects;
}

int CInventory::searchItem(string name) {
	int i = 0;
	for (vector<CObject*>::iterator it = inventory.begin(); it < inventory.end(); it++) {
		if ((*it)->getName() == name)
			i++;
	}
	return i;
}