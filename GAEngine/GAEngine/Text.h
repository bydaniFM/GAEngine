#ifndef __CTEXT
#define __CTEXT

#include "Scene.h"

class CText : public GameEntity {
protected:
	Font f_font;
	string s_text;
	Text *t_text;
public:
	CText();
	CText(char *szFileName, Font f_font, int size);
	virtual void Draw(RenderWindow *window);
	Text *CText::Get(void);
};
#endif //B_CText