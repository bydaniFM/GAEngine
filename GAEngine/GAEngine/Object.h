#ifndef __Object
#define __Object

#include <windows.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sprite.h"

using namespace std;

class CObject {
private:
	CSprite *s_object;
	char* name;
	bool active;
	bool inInventory;
public:
	/*CObject *pPrev;
	CObject *pNext;*/

	CObject(char* name, CSprite *s_object, bool active);
	char* getName();
	CSprite* getSprite();
	bool getActive();
};

#endif // !__Object