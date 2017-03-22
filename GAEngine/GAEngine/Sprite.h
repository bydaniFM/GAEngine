#ifndef __SPRITE
#define __SPRITE

#include "Scene.h"

// ------------------------------------------------------------

class CSprite : public GameEntity
{
protected:
	Texture			m_Texture;
	Sprite			m_Sprite;
	bool			canMove;	//If the sprite can move in the window. Player should be false
	bool			visible;

public:
	CSprite();
	CSprite(char *szFileName);
	CSprite(char *szFileName, bool canMove);

	virtual void Draw(RenderWindow *window);
	Sprite *CSprite::Get(void);

	virtual void Move(int speed);
	void SetVisible(bool visible);

	//bool getCanMoove();
};

// ------------------------------------------------------------

class CAnimatedSprite : public CSprite
{
	int				m_nFrames;
	int				m_nIndex;
	int				m_nTime;
	int				m_nAnimation;	//0->Idle	1->WalkRight	2->WalkLeft
	int				m_nScale;
	Clock			timer;
	IntRect			rect;

public:
	CAnimatedSprite(char *szFileName, int nFrames, int nTime, bool canMove);
	void SetAnimation(int animation);
	void SetScale(int scale);
	virtual void Draw(RenderWindow *window);
};

#endif // B_SPRITE