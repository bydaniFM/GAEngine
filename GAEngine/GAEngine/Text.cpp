#include "Scene.h"
#include "Text.h"

CText::CText() : GameEntity() {

}

CText::CText(char *szFileName) {
	s_text = szFileName;
	//t_text.setString(s_text);
	t_text.setString("Algo de prueba");
	//t_text = szFileName;
}

void CText::Draw(RenderWindow *window) {
	window->draw(t_text);
	GameEntity::Draw(window);
}

Text *CText::Get(void) {
	return(&t_text);
}