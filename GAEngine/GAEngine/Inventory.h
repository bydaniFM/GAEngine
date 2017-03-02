#include "Object.h"

class CInventory {
private:
	CObject *pFirst;
	CObject *pLast;
	int numObjects;
public:
	CInventory();
	void Push(CObject *pObject);
	void Pop(CObject *pObject);
	int getNumObjects();
};