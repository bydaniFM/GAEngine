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

	canMove = true;
}

void GameEntity::AddChild(ptr entity, bool canMove)
{
	m_Children.push_back(entity);
	entity->m_pParent = this;

	this->canMove = canMove;
}

void GameEntity::Draw(RenderWindow *window)
{
	for (vector<ptr>::iterator i = m_Children.begin(); i < m_Children.end(); i++) {
		(*i)->Draw(window);
	}
}

void GameEntity::Move(int speed) {
	for (vector<ptr>::iterator i = m_Children.begin(); i < m_Children.end(); i++) {
		(*i)->Move(speed);
	}
}