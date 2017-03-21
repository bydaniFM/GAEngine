#include "Dialogue.h"

Dialogue::Dialogue() {
	t_Text = NULL;
	index = 1;
};

//Dialogue::Dialogue(char* name, XMLReader myReader) {
//	Arial.loadFromFile("Resources/Fonts/Arial.ttf");
//	index = 1;
//	this->s_name = name;
//	t_text = new Text(myReader.Load(name), Arial, 40);
//}

void Dialogue::AddText(CText text) {
	*t_Text = text;
	t_Children.push_back(text);
}

CText Dialogue::NextLine() {
	index++;
	return (t_Children.at(index));
}

CText Dialogue::getText() {
	return *t_Text;
	//for hasta el indice y retunr
}