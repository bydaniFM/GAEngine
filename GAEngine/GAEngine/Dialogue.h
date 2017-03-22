#ifndef __DIALOGUE
#define __DIALOGUE

//#include <windows.h>
//#include <iostream>
//#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Sprite.h"
#include "Text.h"

class Dialogue : public GameEntity {
private:
	CText *t_Text;
	vector<CText> t_Children;
	int index;
	char* route;
public:
	Dialogue();
	//Dialogue(int index);
	void AddText(CText *t_text);
	CText NextLine();
	CText getText();
	void setText(char* text, char* route);
	void setText(char* text);
	char* getRoute();
};

#endif // !__DIALOGUE