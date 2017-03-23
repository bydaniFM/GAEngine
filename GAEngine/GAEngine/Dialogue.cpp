#include "Dialogue.h"

Dialogue::Dialogue() {
	t_Text = NULL;
	route = "";
	index = 1;
};

//Dialogue::Dialogue(char* name, XMLReader myReader) {
//	Arial.loadFromFile("Resources/Fonts/Arial.ttf");
//	index = 1;
//	this->s_name = name;
//	t_text = new Text(myReader.Load(name), Arial, 40);
//}

void Dialogue::AddText(CText *text) {
	t_Text = text;
	t_Children.push_back(*text);
	this->AddChild(t_Text, "CText");
}

CText Dialogue::NextLine() {
	index++;
	return (t_Children.at(index));
}

CText Dialogue::getText() {
	return *t_Text;
	//for hasta el indice y retunr
}

void Dialogue::setText(char* text, string route) {
	//t_Text->Get()->setString(text);
	t_Text->setString(text);
	this->route = route;
	this->AddChild(t_Text, "CText");
}

void Dialogue::setText(char* text) {
	t_Text->Get()->setString(text);
}

string Dialogue::getRoute() {
	return route;
}