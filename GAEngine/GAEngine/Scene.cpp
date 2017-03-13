#include "Scene.h"
#include "Sprite.h"

using namespace sf;
using namespace std;

GameEntity::GameEntity()
{
	m_pParent = NULL;
	active = false;
}

void GameEntity::MoveScene(int speed) {
	for (vector<CSprite>::iterator i = m_Sprites.begin(); i < m_Sprites.end(); i++) {
		i->Get().setPosition(i->Get().getPosition().x - speed, i->Get().getPosition().y);
	}
}

//CSprite* GameEntity::GetChildren() {
//	CSprite *spriteArr;
//	//int j = 0;
//	for (vector<ptr>::iterator i = m_Children.begin(), int j = 0; i < m_Children.end(); i++, j++) {
//		spriteArr[j] = m_Children.at(j);
//	}
//}

void GameEntity::AddChild(ptr entity)
{
	m_Children.push_back(entity);
	entity->m_pParent = this;
	//m_CSprite = entity;
}

void GameEntity::AddChild(CSprite sprite) {
	m_Sprites.push_back(sprite);
}

void GameEntity::Draw(RenderWindow *window)
{
	for (vector<ptr>::iterator i = m_Children.begin(); i < m_Children.end(); i++) {
		(*i)->Draw(window);
	}
	for (vector<CSprite>::iterator i = m_Sprites.begin(); i < m_Sprites.end(); i++) {
		//window->draw((*i).Get());
		window->draw(i->Get());
	}
}