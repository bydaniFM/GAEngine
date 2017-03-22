#include "Scene.h"
#include "Text.h"

CText::CText() : GameEntity() {

}

CText::CText(char *szFileName, Font font, int size) {
	f_font = font;
	s_text = szFileName;
	t_text = new Text(szFileName, f_font, size);
}

void CText::Draw(RenderWindow *window) {
	window->draw(*t_text);
	GameEntity::Draw(window);
}

Text *CText::Get(void) {
	return(t_text);
}