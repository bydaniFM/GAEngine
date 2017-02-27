#ifndef __SCENE
#define __SCENE

#include <windows.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

public:
	GameEntity();

	void AddChild(ptr);
	virtual void Draw(RenderWindow *window);
};

#endif  // __SCENE