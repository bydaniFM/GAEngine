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
	// Pointer to the last CSprite added to the scene
	ptr				spr_Parent;
	// Vector of CSprite
	vector<ptr>		spr_Children;
	// Pointer to the last CText added to the scene
	ptr				txt_Parent;
	// Vector of CText
	vector<ptr>		txt_Children;
	// Music object pointer. Points to the main theme in the scene
	Music			*m_theme;
	// True if the scene is being rendered in the game
	bool			active;

public:
	// Default constructor
	GameEntity();
	// Adds a child to the CSprite or CText vector
	void AddChild(ptr, char* type);
	// Draws the objects in both vectors
	virtual void Draw(RenderWindow *window);
	// Moves all the sprites in a scene but the main character 
	// (This last functionality is in the CSprite class)
	virtual void Move(int speed);
	// Gets "active" variable
	bool getActive();
	// Sets "active" variable and plays or stops the music in the scene if it has one
	void setActive(bool active);
	// Adds the music theme to the scene
	void addMusic(Music *m_theme);
};

#endif  // __SCENE