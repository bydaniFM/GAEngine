#ifndef __Object
#define __Object

#include <windows.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sprite.h"

using namespace std;

// Represents an item the player can hold in his inventory
class CObject {
private:
	// Sprite of the object, same as drawn in the scene (for the moment)
	CSprite *s_object;
	// Name of the object. Used as a ID
	char* name;
	// If the object can be used by the player
	bool active;
	// If the objects is held by the player or if it is in the ground
	bool inInventory;
public:
	// Constructor that initialices the Object
	CObject(char* name, CSprite *s_object, bool active);
	// Gets the name of the Object
	char* getName();
	// Gets the CSprite of the Object
	CSprite* getSprite();
	// Gets the active variable of the Object
	bool getActive();
	// Gets the inInventory variable of the Object
	bool getInInventory();
};

#endif // !__Object