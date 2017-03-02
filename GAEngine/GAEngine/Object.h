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