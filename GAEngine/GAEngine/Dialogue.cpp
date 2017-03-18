#include "Dialogue.h"

Dialogue::Dialogue() {
	Arial.loadFromFile("Resources/Fonts/Arial.ttf");
	index = 1;
};

Dialogue::Dialogue(char* name, XMLReader myReader) {
	Arial.loadFromFile("Resources/Fonts/Arial.ttf");
	index = 1;
	this->s_name = name;
	t_text = new Text(myReader.Load(name), Arial, 40);
}

Text Dialogue::NextLine() {
	//this->index = s_name.back + 1;
	return (*t_text);
}

Text Dialogue::getText() {
	return (*t_text);
}