#include "Scene.h"
#include "Text.h"

CText::CText() : GameEntity() {

}

CText::CText(string s_string, Font font, int size) {
	f_font = font;
	s_text = s_string;
	t_text = new Text(s_string, f_font, size);
}

void CText::Draw(RenderWindow *window) {
	window->draw(*t_text);
	GameEntity::Draw(window);
}

void CText::setString(string s_string) {
	t_text->setString(s_string);
	s_text = s_string;
}

Text *CText::Get(void) {
	return(t_text);
}