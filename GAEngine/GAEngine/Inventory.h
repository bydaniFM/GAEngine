#ifndef __INVENTORY
#define __INVENTORY

#include "Object.h"

class CInventory : public GameEntity {
private:
	/*CObject *pFirst;
	CObject *pLast;*/
	int numObjects;
	vector<CObject*> inventory;
public:
	CInventory();
	/*void Push(CObject *pObject);
	void Pop(CObject *pObject);*/
	void AddItem(CObject *pObject);
	void DeleteItem(CObject *pObject);
	int getNumObjects();
};

#endif // !__INVENTORY