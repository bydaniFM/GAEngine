#ifndef __DIALOGUE
#define __DIALOGUE

#include "Scene.h"
#include "Sprite.h"
#include "Text.h"

// Custom class to manage dialogues
class Dialogue : public GameEntity {
private:
	// Text of the dialogue
	CText *t_Text;
	// Vector with all the lines of the dialogue
	vector<CText> t_Children;
	// Index with the number of the current line of the dialogue
	int index;
	// Route to the dialogue lines in the xml
	string route;
public:
	// Default constructor
	Dialogue();
	// Adds the CText to the class and the scene. And also puts it in the Vector
	void AddText(CText *t_text);
	// Returns the next line of the dialogue
	CText NextLine();
	// Returns the current line of the dialogue
	CText getText();
	// Changes the string of the Text from the xml
	void setText(char* text, string route);
	// Changes the string of the Text directly
	void setText(char* text);
	// Returns the route of the current dialogue
	string getRoute();
};

#endif // !__DIALOGUE