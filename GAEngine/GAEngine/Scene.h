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
private:
	ptr				spr_Parent;
	vector<ptr>		spr_Children;
	ptr				txt_Parent;
	vector<ptr>		txt_Children;
	Music			*m_theme;
	bool			active;

public:

	

	GameEntity();

	void AddChild(ptr, char* type);
	virtual void Draw(RenderWindow *window);
	virtual void Move(int speed);
	bool getActive();
	void setActive(bool active);
	void addMusic(Music *m_theme);
};

#endif  // __SCENE