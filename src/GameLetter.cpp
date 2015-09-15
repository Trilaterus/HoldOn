#include "GameLetter.h"

/* CONSTRUCTORS */

GameLetter::GameLetter(std::string sLetter, sf::Vector2f vPosition)
{
	m_sLetter = sLetter;
	m_sfKey = AlphabetResource::getInstance().getSFKey(sLetter);
	m_vPosition = vPosition;
	m_vScaleFactor = sf::Vector2f(1, 1);
	m_iScoreValue = 1;
	m_fHealthValue = 1;
	m_iTimeIdle = 5000; // = 5 seconds in milliseconds
	m_iTimePressed = 4000;
	m_iTimeOverPressed = 10000;
	m_isPressed = false;
	//m_fxReleaseTrue.setBuffer(SoundManager::getInstance().getEffectRef("ReleaseTrue"));
	//m_fxLetterFill.setBuffer(SoundManager::getInstance().getEffectRef("LetterFill_3s"));
	//m_fxFlareFiring.setBuffer(SoundManager::getInstance().getEffectRef("FlareFiring"));
	//m_fxShipExplosion.setBuffer(SoundManager::getInstance().getEffectRef("ShipExplosion"));
}

/* GETTERS */

std::string GameLetter::getLetter()
{
	return m_sLetter;
}

sf::Keyboard::Key GameLetter::getKey()
{
	return m_sfKey;
}

int GameLetter::getScore()
{
	return m_iScoreValue;
}

sf::Vector2f GameLetter::getPosition()
{
	return m_vPosition;
}

float GameLetter::getCollisionRadius()
{
	return m_fCollisionRadius;
}

/* SETTERS */


/* CLASS SPECIFIC */


/* INHERITED */


/*
// draw outline (Credit to: http://en.sfml-dev.org/forums/index.php?topic=13158.0)
// This method may be inefficient and processor intensive as it is drawing multiple iterations of the font around the text

const float pi = 3.1415;
sf::Text outline = text;
outline.setColor(sf::Color::Black);
for (int theta = 0; theta <= 360; theta += 1)
{
float pos_x = std::cos(theta*pi / 180.0) * 3; // 3 == thickness
float pos_y = std::sin(theta*pi / 180.0) * 3;

outline.setPosition(text.getPosition() + sf::Vector2f(pos_x, pos_y));
target.draw(outline);
}
*/