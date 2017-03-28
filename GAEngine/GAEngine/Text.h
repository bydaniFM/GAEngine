#ifndef __CTEXT
#define __CTEXT

#include "Scene.h"

// Custom class to manage Texts
class CText : public GameEntity {
protected:
	// Font used by the Text
	Font f_font;
	// String with the content of the Text
	string s_text;
	// Pointer to Text
	Text *t_text;
public:
	// Default constructor
	CText();
	// Initialices a CText
	CText(char *szFileName, Font f_font, int size);
	// Draws the Text in the window
	virtual void Draw(RenderWindow *window);
	// Changes the sting in the Text
	void setString(char* string);
	// Gets the Text object
	Text *CText::Get(void);
};
#endif //B_CText