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
	ptr				spr_Parent;
	vector<ptr>		spr_Children;
	ptr				txt_Parent;
	vector<ptr>		txt_Children;
	Music			m_music;

	bool			active;

public:
	GameEntity();

	//CSprite* GetChildren();
	void AddChild(ptr, char* type);
	virtual void Draw(RenderWindow *window);
	virtual void Move(int speed);
	/*void setActive(bool active);
	void setMusic(Music m_music);*/
};

#endif  // __SCENE