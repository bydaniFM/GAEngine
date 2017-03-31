#include "Object.h"

CObject::CObject(char* name, CSprite *s_object, bool active) {
	this->name = name;
	this->s_object = s_object;
	this->active = active;
}

char* CObject::getName() {
	return name;
}

CSprite* CObject::getSprite() {
	return s_object;
}

bool CObject::getActive() {
	return active;
}

bool CObject::getInInventory() {
	return inInventory;
}

void CObject::setInInventory(bool value) {
	inInventory = value;
}