#include "Scene.h"

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
}

void GameEntity::Draw(RenderWindow *window)
{
	for (vector<ptr>::iterator i = m_Children.begin(); i < m_Children.end(); i++) {
		(*i)->Draw(window);
	}
}