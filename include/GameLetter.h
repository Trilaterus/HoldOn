#ifndef GAMELETTER_H
#define GAMELETTER_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "AlphabetResource.h"
#include "SoundManager.h"

class GameLetter : public sf::Drawable // this is an abstract class
{
private:

protected:
	std::string m_sLetter;
	sf::Vector2f m_vPosition;
	sf::Keyboard::Key m_sfKey;
	sf::Vector2f m_vScaleFactor;
	int m_iTimeIdle;
	sf::Clock m_clockIdle;
	int m_iTimePressed;
	sf::Clock m_clockPressed;
	int m_iTimeOverPressed;
	sf::Clock m_clockOverPressed;
	int m_iScoreValue;
	float m_fHealthValue;
	bool m_isPressed;
	int m_iPercentFilled; // for the fill circles
	int m_iPercentDrained; // also for fill circles
	float m_fCollisionRadius;

public:
	GameLetter(std::string sLetter, sf::Vector2f vPosition);

	std::string getLetter();
	sf::Keyboard::Key getKey();
	int getScore();

	virtual sf::Vector2f getOrigin() = 0;
	virtual sf::Vector2f getPosition();
	virtual float getCollisionRadius();
	virtual bool isOverlapping(GameLetter* gameLetter) = 0;
	virtual void positionCorrect(GameLetter* gameLetter) = 0;
	virtual void onPressed() = 0;
	virtual bool onReleased() = 0;
	virtual bool checkIdle() = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

#endif // GAMELETTER_H