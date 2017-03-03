#ifndef __Object
#define __Object

class CObject {
private:
	char* name;
	bool active;
public:
	CObject *pPrev;
	CObject *pNext;

	CObject(char* name, bool active);
	char* getName();
	bool getActive();
};

#endif // B_SPRITE