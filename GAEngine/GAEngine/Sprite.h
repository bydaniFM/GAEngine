#ifndef __SPRITE
#define __SPRITE

#include "Scene.h"

// ------------------------------------------------------------

class CSprite : public GameEntity
{
protected:
	Texture			m_Texture;
	Sprite			m_Sprite;

public:
	CSprite();
	CSprite(char *szFileName);

	virtual void Draw(RenderWindow *window);
	Sprite *CSprite::Get(void);
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
	CAnimatedSprite(char *szFileName, int nFrames, int nTime);
	void SetAnimation(int animation);
	void SetScale(int scale);
	virtual void Draw(RenderWindow *window);
};

#endif // B_SPRITE