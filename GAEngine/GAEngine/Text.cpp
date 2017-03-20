#include "Scene.h"
#include "Text.h"

CText::CText() : GameEntity() {

}

CText::CText(char *szFileName, Font f_font, int size) {
	Arial = f_font;
	s_text = szFileName;
	t_text = new Text(szFileName, Arial, size);
}

void CText::Draw(RenderWindow *window) {
	window->draw(*t_text);
	GameEntity::Draw(window);
}

Text *CText::Get(void) {
	return(t_text);
}