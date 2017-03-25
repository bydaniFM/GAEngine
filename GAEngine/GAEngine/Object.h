#ifndef __Object
#define __Object

#include <windows.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class CObject {
private:
	char* name;
	bool active;
	bool inInventory;
public:
	/*CObject *pPrev;
	CObject *pNext;*/

	CObject(char* name, bool active);
	char* getName();
	bool getActive();
};

#endif // !__Object