#ifndef GAMELETTERMANAGER_H
#define GAMELETTERMANAGER_H

#include <SFML/Graphics.hpp>
#include "GameLetter.h"
#include "GameClassicLetter.h"
#include "AlphabetResource.h"
#include "RandomResource.h"
#include "ScoreController.h"
#include "TextureManager.h"
#include "GameTutLetter.h"

class GameLetterManager : public sf::Drawable
{
private:
	std::vector<GameLetter*> m_vGameLetters;
	sf::Sprite m_spawnRect;
	RandomResource m_RandomGenerator;
	ScoreController* m_pScoreController;
	sf::Texture m_texLetterDoneTrue;
	sf::Texture m_texLetterDoneFalse;
	std::vector<std::pair<sf::Sprite*, std::pair<sf::Clock*, bool*>>> m_vLetterDones; // has the sprite, then a pair of a clock and bool to reset the clock
	float m_fLetterDoneTimer; // time it takes for letters done animation to complete
	int m_iBonusHealthCounter; // when it reaches 10 grants a bonus health, gains a stack when a letter is dropped perfectly
	int m_iMaxLetterCap; // max amount of letters allowed to be on screen at one time
	bool m_shouldScreenShake; // initiate a screenshake in the screen this is in;
	bool m_bIsTutorial; // is this currently the tutorial
	
	bool m_bReleasedCorrect; // properly done
	bool m_bReleasedEarly; // let go too early
	bool m_bReleasedLate; // never let go
	bool m_bWentIdle; // letter went idle

	void letterReleasedAnimation(bool bValue, GameLetter* gameLetter);

protected:

public:
	GameLetterManager(sf::Sprite spawnRect, ScoreController* pScoreController); 
	// spawnRect is the outermost line of the UI, shows the area in which the letters should spawn in
	// scorecontroller is needed to transfer score information from screen to screen

	ScoreController* getScoreController();
	int getAmountOfLetters();
	bool getScreenShake();
	void setIsTut(bool bValue);
	
	bool getReleasedCorrect();
	bool getReleasedEarly();
	bool getReleasedLate();
	bool getWentIdle();
	void setReleasedCorrect(bool bValue);
	void setReleasedEarly(bool bValue);
	void setReleasedLate(bool bValue);
	void setWentIdle(bool bValue);

	void spawnRandom();
	void spawnNormalLetter();
	void spawnNormalLetter(int iIdleTime, int iHoldTime, int iOverTime); // parameter values should be in MILLISECONDS
	void spawnTutLetter(std::string sLetter, float fXOffset, float fYOffset, int iIdleTime, int iHoldTime, int iOverTime);
	void spawnUnseqChain();
	void spawnSeqChain();
	void spawnPinata();
	void spawnTapper();
	void setMaxLetterCap(int iValue);
	void reset();
	void setScreenShake(bool bValue);

	void handleEvents(sf::Event sfEvent);

	virtual bool update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // GAMELETTERMANAGER_H