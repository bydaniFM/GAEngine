#ifndef __SCENE
#define __SCENE

#include <windows.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "Sprite.h"

using namespace sf;
using namespace std;

class GameEntity;

typedef GameEntity*	ptr;

class GameEntity
{
public:
	ptr				m_pParent;
	vector<ptr>		m_Children;
	bool			active;
	//CSprite			*m_CSprite;

public:
	GameEntity();

	//void MoveScene(int speed, char* dir);
	//CSprite* GetChildren();
	void AddChild(ptr);
	virtual void Draw(RenderWindow *window);
};

#endif  // __SCENE