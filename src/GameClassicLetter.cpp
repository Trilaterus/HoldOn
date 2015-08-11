#include "GameClassicLetter.h"

/* CONSTRUCTORS */

GameClassicLetter::GameClassicLetter(std::string sLetter, sf::Vector2f vPosition)
: GameLetter(sLetter, vPosition)
{
	// Letter info
	m_sfFont = TextureManager::getInstance().getFontRef("M12");
	m_sLetter = sLetter;
	m_vPosition = vPosition;
	m_colorLetter = sf::Color::White;
	m_iCharSize = 60;

	// Fill circles info
	m_texFill = TextureManager::getInstance().getTexRef("FillCircle");
	m_texFillOutline = TextureManager::getInstance().getTexRef("FillCircleOutline1");
	m_texOuterline = TextureManager::getInstance().getTexRef("FillCircleOutline2");
	m_fCollisionRadius = m_texOuterline.getSize().x / 2;
	m_colorFill = sf::Color(255, 0, 0, 255);
	m_iPercentFilled = 0;
	m_iPercentDrained = 0;

	// Outline info
	m_iPercentIdle = 0;

	// Extra
	m_isOverPressedClockStarted = false;
	m_isReady = false;

	// Animation variables
	m_fAnimationScale = 0.f;
	m_isAnimating = true;
	m_isClockAnimation = false;
	m_fSpawnAnimationDuration = 500;
}

/* CLASS SPECIFIC */

void GameClassicLetter::spawnAnimation()
{
	if (m_fAnimationScale < 1)
	{
		if (!m_isClockAnimation)
		{
			m_clockAnimation.restart();
			m_isClockAnimation = true;
		}
		float i = m_clockAnimation.getElapsedTime().asMilliseconds();
		m_fAnimationScale = i / m_fSpawnAnimationDuration;
	}
	else
	{
		m_fAnimationScale = 1.f;
		m_isClockAnimation = false; // done so that it can be used again for releasedAnimation
		m_isAnimating = false;
	}
	m_clockIdle.restart();
}

int GameClassicLetter::getWidth()
{
	return m_texOuterline.getSize().x;
}

int GameClassicLetter::getHeight()
{
	return m_texOuterline.getSize().y;
}

void GameClassicLetter::setPosition(sf::Vector2f vPosition)
{
	m_vPosition = vPosition;
}

void GameClassicLetter::setPosition(float fXPos, float fYPos)
{
	m_vPosition.x = fXPos;
	m_vPosition.y = fYPos;
}

//tmp - changes the colour of the letter inside the circles (useful for testing specific letters in loops)
void GameClassicLetter::setColor(sf::Color color)
{
	m_colorLetter = color;
}

void GameClassicLetter::idleUpdate()
{
	if (!m_isPressed)
	{
		// do idle stuff like crop the filloutline
		float i = m_clockIdle.getElapsedTime().asMilliseconds();
		float j = i / m_iTimeIdle;
		m_iPercentIdle = 100 - (j * 100);
		if (m_iPercentIdle <= 50)
		{
			int i = 0;
		}
	}
}

void GameClassicLetter::move(float fXPos, float fYPos)
{
	m_vPosition.x += fXPos;
	m_vPosition.y += fYPos;
}

/* INHERITED */

sf::Vector2f GameClassicLetter::getOrigin()
{
	sf::Vector2f vector;
	vector.x = m_vPosition.x + (m_texOuterline.getSize().x / 2);
	vector.y = m_vPosition.y + (m_texOuterline.getSize().y / 2);
	return vector;
}

bool GameClassicLetter::isOverlapping(GameLetter* gameLetter)
{
	sf::Vector2f vDistance = gameLetter->getPosition() - m_vPosition;
	float fMagnitude = sqrt((vDistance.x * vDistance.x) + (vDistance.y * vDistance.y));
	float fRadiSum = this->getCollisionRadius() + gameLetter->getCollisionRadius();
	if (fMagnitude - fRadiSum <= 0)
	{
		if (fMagnitude == 0)
		{
			int i = 0;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void GameClassicLetter::positionCorrect(GameLetter* gameLetter)
{
	sf::Vector2f vDistance = gameLetter->getPosition() - m_vPosition;
	float fMagnitude = sqrt((vDistance.x * vDistance.x) + (vDistance.y * vDistance.y));
	float fRadiSum = this->getCollisionRadius() + gameLetter->getCollisionRadius();
	float fDepth = fMagnitude - fRadiSum;
	sf::Vector2f vUnitNormal(vDistance.x / fMagnitude, vDistance.y / fMagnitude);
	sf::Vector2f c;
	float slop = 0;
	float p = 1;
	fDepth = fDepth * -1;
	float b = std::max(fDepth - slop, 0.f);
	b = b / 0.007 + 0.007; // numbers taken from inverse mass of pinball project balls
	c.x = b * p * vUnitNormal.x;
	c.y = b * p * vUnitNormal.y;
	m_vPosition.x = m_vPosition.x - (c.x * 0.007);
	m_vPosition.y = m_vPosition.y - (c.y * 0.007);
}

void GameClassicLetter::onPressed()
{
	if (!m_isPressed)
	{
		m_clockPressed.restart();
		m_isPressed = true;
		m_fxLetterFill.play();
	}
}

bool GameClassicLetter::onReleased()
{
	if (m_iTimePressed <= m_clockPressed.getElapsedTime().asMilliseconds()) // If released at the right time
	{
		m_fxLetterFill.stop();
		m_fxFlareFiring.play();
		return true;
	}
	else if (m_iTimePressed > m_clockPressed.getElapsedTime().asMilliseconds()) // If released at the wrong time
	{
		m_fxLetterFill.stop();
		m_fxShipExplosion.play();
		return false;
	}
}

bool GameClassicLetter::checkIdle()
{
	if (m_isReady && m_iPercentFilled <= 0)
	{
		return true;
	}

	if (!m_isPressed)
	{
		if (m_clockIdle.getElapsedTime().asMilliseconds() >= m_iTimeIdle)
		{
			m_fxShipExplosion.play();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void GameClassicLetter::update()
{
	if (m_isAnimating)
	{
		this->spawnAnimation();
	}
	else if (m_isPressed)
	{
		if (m_clockPressed.getElapsedTime().asMilliseconds() <= m_iTimePressed) // if pressed and not ready
		{
			float i = m_clockPressed.getElapsedTime().asMilliseconds(); // get current time
			float l = i / m_iTimePressed; // divide by max time limit
			m_iPercentFilled = 100 * l; // calculate percentage by multiplying by 100
			if (m_iPercentFilled >= 100)
			{
				m_isReady = true;
				m_iPercentFilled = 100;
			}
			else if (m_iPercentFilled <= 50)
			{
				float j = m_iPercentFilled * 2;
				float k = j / 100;
				float l = k * 255;
				m_colorFill = sf::Color(255, l, 0, 255);
			}
			else if (m_iPercentFilled > 50)
			{
				float j = m_iPercentFilled * 2 - 100;
				float k = j / 100;
				float l = k * 255;
				m_colorFill = sf::Color(255 - l, 255, 0, 255);
			}
		}
		if (m_isReady) // if pressed and ready
		{
			if (!m_isOverPressedClockStarted)
			{
				m_fxReleaseTrue.play();
				m_clockOverPressed.restart();
				m_isOverPressedClockStarted = true;
			}
			float i = m_clockOverPressed.getElapsedTime().asMilliseconds();
			float l = i / m_iTimeOverPressed;
			m_iPercentDrained = 100 * l;
			m_iPercentFilled = 100 - m_iPercentDrained;
		}
	}
	
	this->idleUpdate();
}

void GameClassicLetter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Sprite fill;
	fill.setTexture(m_texFill);
	fill.setColor(m_colorFill);
	fill.setOrigin(m_texFill.getSize().x / 2, m_texFill.getSize().y / 2);
	fill.setPosition(m_vPosition);
	fill.setTextureRect(sf::IntRect(0, 0, 100, m_iPercentFilled));
	fill.rotate(180);
	target.draw(fill);

	sf::Sprite outline;
	outline.setTexture(m_texFillOutline);
	outline.setOrigin(m_texFillOutline.getSize().x / 2, m_texFillOutline.getSize().y / 2);
	outline.setPosition(m_vPosition);
	float bob = (m_texFillOutline.getSize().y / 100.f);
	float outlineHeight = bob * m_iPercentIdle;
	outline.setTextureRect(sf::IntRect(0, 0, m_texFillOutline.getSize().x, outlineHeight));
	outline.rotate(180);
	outline.setScale(m_fAnimationScale, m_fAnimationScale);
	target.draw(outline);

	if (m_isReady)
	{
		sf::Sprite doneOutline;
		doneOutline.setTexture(m_texOuterline);
		doneOutline.setOrigin(m_texOuterline.getSize().x / 2, m_texOuterline.getSize().y / 2);
		doneOutline.setPosition(m_vPosition);
		target.draw(doneOutline);
	}

	sf::Text letter;
	letter.setFont(m_sfFont);
	letter.setString(m_sLetter);
	letter.setPosition(m_vPosition);
	letter.setColor(m_colorLetter);
	letter.setCharacterSize(m_iCharSize);
	letter.setOrigin((letter.getLocalBounds().width / 2.f) / letter.getScale().x, (letter.getLocalBounds().height / 2.f) / letter.getScale().y);
	letter.setScale(m_fAnimationScale, m_fAnimationScale);
	target.draw(letter);
}