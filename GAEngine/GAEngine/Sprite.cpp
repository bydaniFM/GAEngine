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
	canMove = true;
}

CSprite::CSprite(char *szFileName, bool canMove) {
	if (m_Texture.loadFromFile(szFileName)) {
		m_Sprite.setTexture(m_Texture);
	}
	this->canMove = canMove;
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

void CSprite::Move(int speed) {
	if(canMove)
		m_Sprite.setPosition(m_Sprite.getPosition().x + speed, m_Sprite.getPosition().y);
	GameEntity::Move(speed);
}

bool CSprite::getCanMoove() {
	return canMove;
}

//FloatRect CSprite::getBoundingRect() const {
//	return getWorldTransform().transformRect(m_Sprite.getGlobalBounds());
//}

// -------------------------------------------------------

CAnimatedSprite::CAnimatedSprite(char *szFileName, int nFrames, int nTime, bool canMove) : CSprite(szFileName)
{
	m_nFrames = nFrames;
	m_nTime = nTime;
	m_nIndex = 0;
	m_nAnimation = 0;
	timer.restart();

	rect = m_Sprite.getTextureRect();

	this->canMove = canMove;
}

void CAnimatedSprite::SetAnimation(int animation) {
	m_nAnimation = animation;
	if (animation == 0) {

	}else if (animation == 1){
		m_Sprite.setScale(m_nScale, m_nScale);
		//m_Sprite.setPosition(m_Sprite.getPosition() + Vector2f(m_Sprite.getTextureRect().width, 0));
	} else if (animation == 2) {
		m_Sprite.setScale(-m_nScale, m_nScale);
		//m_Sprite.setPosition(m_Sprite.getPosition() + Vector2f(m_Sprite.getTextureRect().width, 0));
	}
}

void CAnimatedSprite::SetScale(int scale) {
	m_Sprite.setScale(scale, scale);
	m_nScale = scale;
}

void CAnimatedSprite::Draw(RenderWindow *window)
{
	int width = rect.width / m_nFrames;

	/*switch (m_nAnimation) {
	case 0:

		break;
	case 1:
		m_Sprite.setTextureRect(IntRect(m_nIndex*width, 0, rect.height, width));
		if (timer.getElapsedTime().asMilliseconds() > m_nTime) {
			m_nIndex++;
			if (m_nIndex == m_nFrames) m_nIndex = 0;
			timer.restart();
		}
		break;
	case 2:
		m_Sprite.setScale(-1, 1);
		break;
	default:
		break;
	}*/
	m_Sprite.setTextureRect(IntRect(m_nIndex*width, 0, rect.height, width));

	if (m_nAnimation != 0) {
		/*if (m_nAnimation == 1) {
			m_Sprite.setScale(1, 1);
			m_Sprite.setPosition(m_Sprite.getPosition() + Vector2f(m_Sprite.getTextureRect().width, 0));
		}
		if (m_nAnimation == 2) {
			m_Sprite.setScale(-1, 1);
			m_Sprite.setPosition(m_Sprite.getPosition() + Vector2f(m_Sprite.getTextureRect().width, 0));
		}*/
		
		if (timer.getElapsedTime().asMilliseconds() > m_nTime) {
			m_nIndex++;
			if (m_nIndex == m_nFrames) m_nIndex = 0;
			timer.restart();
		}
	}

	CSprite::Draw(window);
}