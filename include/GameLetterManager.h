#ifndef GAMELETTERMANAGER_H
#define GAMELETTERMANAGER_H

#include <SFML/Graphics.hpp>
#include "GameLetter.h"
#include "GameClassicLetter.h"
#include "AlphabetResource.h"
#include "RandomResource.h"
#include "ScoreController.h"
#include "TextureManager.h"

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

	void letterReleasedAnimation(bool bValue, GameLetter* gameLetter);

protected:

public:
	GameLetterManager(sf::Sprite spawnRect, ScoreController* pScoreController); 
	// spawnRect is the outermost line of the UI, shows the area in which the letters should spawn in
	// scorecontroller is needed to transfer score information from screen to screen

	ScoreController* getScoreController();
	int getAmountOfLetters();

	void spawnRandom();
	void spawnNormalLetter();
	void spawnUnseqChain();
	void spawnSeqChain();
	void spawnPinata();
	void spawnTapper();
	void reset();

	void handleEvents(sf::Event sfEvent);

	virtual bool update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // GAMELETTERMANAGER_H