#ifndef __DIALOGUE
#define __DIALOGUE

#include <windows.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Text.h"

using namespace sf;

class Dialogue {
private:
	CText *t_Text;
	vector<CText> t_Children;
	int index;
public:
	Dialogue();
	//Dialogue(int index);
	void AddText(CText t_text);
	CText NextLine();
	CText getText();
};

#endif // !__DIALOGUE