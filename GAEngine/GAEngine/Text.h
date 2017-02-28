//#ifndef __TEXT
//#define __TEXT

#include "Scene.h"

class CText : public GameEntity {
protected:
	string s_text;
	Text t_text;
public:
	CText();
	CText(char *szFileName);
	virtual void Draw(RenderWindow *window);
	Text *CText::Get(void);
};
//#endif //B_Text