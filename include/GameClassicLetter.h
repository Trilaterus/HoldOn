#ifndef GAMECLASSICLETTER_H
#define GAMECLASSICLETTER_H

#include "GameLetter.h"

class GameClassicLetter : public GameLetter
{
private:
	// Letter
	sf::Font m_sfFont;
	sf::Color m_colorLetter;
	int m_iCharSize;

	// various circles
	sf::Texture m_texFill;
	sf::Texture m_texFillOutline;
	sf::Texture m_texOuterline;
	sf::Color m_colorFill;

	// Extra
	bool m_isOverPressedClockStarted;
	int m_iPercentIdle;
	bool m_isReady;
	float m_fAnimationScale;
	bool m_isAnimating; // Is the spawn animation playing?
	sf::Clock m_clockAnimation; // timer used to make animation
	bool m_isClockAnimation; // has the timer been reset?
	float m_fSpawnAnimationDuration; // how quick should the spawn animation be (1s == 1000)

	void spawnAnimation();

protected:

public:
	GameClassicLetter(std::string sLetter, sf::Vector2f vPosition);

	int getWidth();
	int getHeight();

	void setPosition(sf::Vector2f vPosition);
	void setPosition(float fXPos, float fYPos);
	void setColor(sf::Color color); //tmp

	void idleUpdate();
	void move(float fXPos, float fYPos);

	virtual sf::Vector2f getOrigin();
	virtual bool isOverlapping(GameLetter* gameLetter);
	virtual void positionCorrect(GameLetter* gameLetter);
	virtual void onPressed();
	virtual bool onReleased();
	virtual bool checkIdle();
	virtual void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //GAMECLASSICLETTER_H