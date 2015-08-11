/** \file ScoreController.h
This manages the score and the health, used in conjunction with the GameLetterManager

*/

#ifndef SCORECONTROLLER_H
#define SCORECONTROLLER_H

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "GameLetter.h"
#include "UIGameText.h"

class ScoreController : public sf::Drawable
{
private:
	int m_iScore;
	int m_iHealth;
	sf::Font m_sfFont; // font to display the score and health in

protected:

public:
	ScoreController();

	int getScore();
	int getHealth();

	void setScore(int iValue);
	void setHealth(int iValue);

	void modifyScore(GameLetter* gameLetter); // Can be used to increment or decrement the current score
	void modifyScore(int iValue); // Can be used to increment or decrement the current score
	void modifyHealth(int iValue); // Can be used to increment or decrement the current health

	void update(const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // SCORECONTROLLER