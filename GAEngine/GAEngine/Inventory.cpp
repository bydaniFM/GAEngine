#include "Inventory.h"

CInventory::CInventory() {
	/*pFirst = NULL;
	pLast = NULL;*/
	numObjects = 0;
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
	inventory.push_back(pObject);
	numObjects++;
}

void CInventory::DeleteItem(CObject *pObject) {
	if (pObject == inventory.back() || find(inventory.begin(), inventory.end(), pObject) != inventory.end()) {
		inventory.erase(find(inventory.begin(), inventory.end(), pObject));
		numObjects--;
	}
}

int CInventory::getNumObjects() {
	return numObjects;
}