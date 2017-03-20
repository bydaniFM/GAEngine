//#ifndef __TEXT
//#define __TEXT

#include "Scene.h"

class CText : public GameEntity {
protected:
	Font Arial;
	string s_text;
	Text *t_text;
public:
	CText();
	CText(char *szFileName, Font f_font, int size);
	virtual void Draw(RenderWindow *window);
	Text *CText::Get(void);
};
//#endif //B_Text