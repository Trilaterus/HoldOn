#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "Screen.h"
#include "TextureManager.h"
#include "SoundManager.h"

class GameOverScreen : public Screen
{
private:
	UIText* m_textScoreValue;
	ScoreController* m_pScoreController;
	int m_iAnimScoreCounter;
	sf::Clock m_sfDelayClock;
	bool m_isCurrentScreen;

protected:

public:
	GameOverScreen();
	GameOverScreen(std::string sFileName, sf::RenderWindow* window, ScoreController* pScoreController);

	virtual std::string handleEvents(sf::Event sfEvent);
	virtual void functionHandler(std::string sFunctionName);

	void gotoMainMenu();
	void playAgain();

	virtual void update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // GAMEOVERSCREEN_H