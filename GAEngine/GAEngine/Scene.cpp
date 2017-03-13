#include "Scene.h"
#include "Sprite.h"

using namespace sf;
using namespace std;

GameEntity::GameEntity()
{
	m_pParent = NULL;
	active = false;
}

void GameEntity::AddChild(ptr entity)
{
	m_Children.push_back(entity);
	entity->m_pParent = this;
	//m_CSprite = entity;
}

void GameEntity::Draw(RenderWindow *window)
{
	for (vector<ptr>::iterator i = m_Children.begin(); i < m_Children.end(); i++) {
		(*i)->Draw(window);
	}
}

Sprite *GameEntity::Get(ptr entity) {
	return(entity->Get(entity));
}

void GameEntity::Move(int speed) {
	for (vector<ptr>::iterator i = m_Children.begin(); i < m_Children.end(); i++) {
		(*i)->Move(speed);
	}
}

void GameEntity::MoveBut(int speed, ptr entity) {
	for (vector<ptr>::iterator i = m_Children.begin(); i < m_Children.end(); i++) {
		if ((*i)->Get((*i)) != entity->Get(entity)) {
			(*i)->MoveBut(speed, entity);
		}
	}
}