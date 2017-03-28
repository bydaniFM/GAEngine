#include "Scene.h"
#include "Sprite.h"

using namespace sf;
using namespace std;

GameEntity::GameEntity()
{
	spr_Parent = NULL;
	active = false;
}

void GameEntity::AddChild(ptr entity, char* type)
{
	if (type == "CSprite") {
		spr_Children.push_back(entity);
		entity->spr_Parent = this;
	} else {
		txt_Children.push_back(entity);
		entity->txt_Parent = this;
	}
}

void GameEntity::Draw(RenderWindow *window)
{
	for (vector<ptr>::iterator i = spr_Children.begin(); i < spr_Children.end(); i++) {
		(*i)->Draw(window);
	}
	for (vector<ptr>::iterator i = txt_Children.begin(); i < txt_Children.end(); i++) {
		(*i)->Draw(window);
	}
}

void GameEntity::Move(int speed) {
	for (vector<ptr>::iterator i = spr_Children.begin(); i < spr_Children.end(); i++) {
		(*i)->Move(speed);
	}
}

bool GameEntity::getActive() {
	return active;
}

void GameEntity::setActive(bool active) {
	this->active = active;
	if (m_theme != NULL) {
		if (active)
			m_theme->play();
		else
			m_theme->stop();
	}
}

void GameEntity::addMusic(Music *m_theme) {
	this->m_theme = m_theme;
	m_theme->setLoop(true);
}