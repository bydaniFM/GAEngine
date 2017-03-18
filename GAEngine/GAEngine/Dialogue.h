#ifndef __DIALOGUE
#define __DIALOGUE

#include <windows.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "XMLReader.h"

using namespace sf;

class Dialogue {
private:
	Text *t_text;
	string s_name;
	int index;
	Font Arial;
public:
	Dialogue();
	Dialogue(char* name, XMLReader myReader);
	Text NextLine();
	Text getText();
};

#endif // !__DIALOGUE