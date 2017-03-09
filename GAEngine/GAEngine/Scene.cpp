#include "Scene.h"
#include "Sprite.h"

using namespace sf;
using namespace std;

GameEntity::GameEntity()
{
	m_pParent = NULL;
	active = false;
}

//void GameEntity::MoveScene(int speed, char* dir) {
//	int j = 0
//	for (vector<ptr>::iterator i = m_Children.begin(); i < m_Children.end(); i++) {
//		if (dir == "right") {
//			//m_CSprite->Get()->SetPosition(m_CSprite->Get()->GetPosition().x - speed, m_CSprite->Get()->GetPosition().y);
//		}
//		j++;
//	}
//}

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

void GameEntity::Draw(RenderWindow *window)
{
	for (vector<ptr>::iterator i = m_Children.begin(); i < m_Children.end(); i++) {
		(*i)->Draw(window);
	}
}