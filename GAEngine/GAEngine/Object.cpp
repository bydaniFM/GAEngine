#include "Object.h"

CObject::CObject(char* name, CSprite *s_object, bool active) {
	this->name = name;
	this->s_object = s_object;
	this->active = active;
	/*pPrev = NULL;
	pNext = NULL;*/
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