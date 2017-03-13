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
	vector<CSprite>	m_Sprites;

public:
	GameEntity();

	void AddChild(ptr);
	void AddChild(CSprite sprite);
	virtual void Draw(RenderWindow *window);

	void MoveScene(int speed);
	//CSprite* GetChildren();
};

#endif  // __SCENE

//class Scene {
//private:
//	vector
//};