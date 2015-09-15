#ifndef GAMETUTLETTER_H
#define GAMETUTLETTER_H

#include "GameClassicLetter.h"
#include <ctype.h>
#include <cstring>
#include <string>

class GameTutLetter : public GameClassicLetter
{
private:
	std::string m_sText;
	sf::Color m_sfColour;
	sf::Font m_sfFont;
	
protected:

public:
	GameTutLetter(std::string sLetter, sf::Vector2f vPosition);
	GameTutLetter(std::string sLetter, sf::Vector2f vPosition, int iIdleTime, int iHoldTime, int iOverTime);

	bool isOverlapping(GameLetter* gameLetter);
	void positionCorrect(GameLetter* gameLetter);
	void onPressed();
	bool onReleased();
	bool checkIdle();
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // GAMETUTLETTER_H 