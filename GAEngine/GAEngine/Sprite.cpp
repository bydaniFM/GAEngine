#include "Scene.h"
#include "Sprite.h"

// -------------------------------------------------------

CSprite::CSprite() : GameEntity()
{
}

CSprite::CSprite(char *szFileName)
{
	if (m_Texture.loadFromFile(szFileName)) {
		m_Sprite.setTexture(m_Texture);
	}
}

void CSprite::Draw(RenderWindow *window)
{
	window->draw(m_Sprite);
	GameEntity::Draw(window);
}

Sprite *CSprite::Get(void)
{
	return(&m_Sprite);
}

// -------------------------------------------------------

CAnimatedSprite::CAnimatedSprite(char *szFileName, int nFrames, int nTime) : CSprite(szFileName)
{
	m_nFrames = nFrames;
	m_nTime = nTime;
	m_nIndex = 0;
	timer.restart();

	rect = m_Sprite.getTextureRect();
}

void CAnimatedSprite::Draw(RenderWindow *window)
{
	int width = rect.width / m_nFrames;

	m_Sprite.setTextureRect(IntRect(m_nIndex*width, 0, rect.height, width));
	if (timer.getElapsedTime().asMilliseconds() > m_nTime) {
		m_nIndex++;
		if (m_nIndex == m_nFrames) m_nIndex = 0;
		timer.restart();
	}
	CSprite::Draw(window);
}