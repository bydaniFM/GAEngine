#include "Object.h"

CObject::CObject(char* name, bool active) {
	this->name = name;
	this->active = active;
	/*pPrev = NULL;
	pNext = NULL;*/
}

char* CObject::getName() {
	return name;
}

bool CObject::getActive() {
	return active;
}