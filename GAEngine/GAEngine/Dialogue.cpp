#include "Dialogue.h"

Dialogue::Dialogue() {
	t_Text = NULL;
	route = "";
	index = 1;
};

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
}

void Dialogue::setText(char* text, string route) {
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