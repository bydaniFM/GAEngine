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
	bool			canMove;

public:
	GameEntity();

	//CSprite* GetChildren();
	void AddChild(ptr);
	void AddChild(ptr, bool canMove);
	virtual void Draw(RenderWindow *window);
	virtual void Move(int speed);
};

#endif  // __SCENE