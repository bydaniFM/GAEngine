#ifndef __INVENTORY
#define __INVENTORY

#include "Object.h"

// Represents the inventory of the player
class CInventory : public GameEntity {
private:
	// Number of objects in the inventory
	int numObjects;
	// Vector of CObjects containing the Objects in the inventory
	vector<CObject*> inventory;
	// Inventory background
	CSprite *spr_back;
	//Frame of the objects
	CSprite *spr_frame;
public:
	// Default constructor
	CInventory();
	//Constructor with frame for the objects
	CInventory(CSprite *back_spr, CSprite *frame_spr);
	// Adds an Object to the Vector and positions the sprite in the inventory grid
	void AddItem(CObject *pObject);
	// Deletes a specific Object in the Vector
	void DeleteItem(CObject *pObject);
	// Returns the number of objects in the inventory
	int getNumObjects();
	// Returns the number of items found in the vector
	int searchItem(string name);
};

#endif // !__INVENTORY