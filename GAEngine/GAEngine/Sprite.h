#ifndef __SPRITE
#define __SPRITE

#include "Scene.h"

// ------------------------------------------------------------

// Custom class for Sprites
class CSprite : public GameEntity {

protected:
	Texture			m_Texture;
	Sprite			m_Sprite;
	// If the sprite can move in the window. Player should be false
	bool			canMove;
	// If the sprite can be drawn in the window
	bool			visible;

public:
	// Default constructor
	CSprite();
	// Loads the Texture and creates the Sprite
	CSprite(char *szFileName);
	// Constructor overload, for non movable objects
	CSprite(char *szFileName, bool canMove);

	// Draws the Sprite in the window if visible
	virtual void Draw(RenderWindow *window);
	// Gets the Sprite
	Sprite *CSprite::Get(void);

	// Changes the position of the Sprite depending on the speed, if can be moved
	virtual void Move(int speed);
	// Sets if visible (can be rendered)
	void SetVisible(bool visible);

};

// ------------------------------------------------------------

// Compound Sprite that changes its offset, that results in an animation
class CAnimatedSprite : public CSprite {
private:
	// Number of frames in the animation (or number of images in the compound texture)
	int				m_nFrames;
	// Number of current frame
	int				m_nIndex;
	// Time each frame lasts (100 for a 8-frames animation)
	int				m_nTime;
	// ID of the animation
	// 0->Idle  1->WalkRight  2->WalkLeft
	int				m_nAnimation;
	// Scale of the sprite. Useful to turn it around with -1
	int				m_nScale;
	// Timer to manage the animation
	Clock			timer;
	// Rectangle that frames the texture
	IntRect			rect;

public:
	// Constructor that initialices the animation
	CAnimatedSprite(char *szFileName, int nFrames, int nTime, bool canMove);
	// Changes the ID of the animation to make a different one using the same texture
	// 0->Idle  1->WalkRight  2->WalkLeft
	void SetAnimation(int animation);
	// Sets the scale variable. Useful to turn it around with -1
	void SetScale(int scale);
	// Draws the animation, changing the index of the animation
	virtual void Draw(RenderWindow *window);
};

#endif // B_SPRITE