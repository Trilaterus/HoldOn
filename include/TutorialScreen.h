#ifndef TUTORIALSCREEN_H
#define TUTORIALSCREEN_H

#include "Screen.h"
#include "GameLetterManager.h"
#include "ScoreController.h"

class TutorialScreen : public Screen
{
private:
	sf::Texture m_tTutorialSheet;
	int m_iTutSheetXFrames;
	int m_iTutSheetYFrames;
	int m_iCurrentXFrame;
	int m_iCurrentYFrame;
	sf::Clock m_AnimationClock;
	bool m_isCurrentScreen;
	RandomResource m_Random;

	ScoreController* m_pScoreController;
	GameLetterManager* m_GameLetterManager;
	sf::Texture m_texSpawnRect;
	
	std::string m_sText;
	sf::Font m_sfFont;
	bool m_bDrawTip;

	sf::Clock m_clockSpawn;
	int m_iSpawnTime;

	void sheetAnimationUpdate();

protected:

public:
	TutorialScreen(std::string sFileName, sf::RenderWindow* window, ScoreController* scoreController);

	virtual std::string handleEvents(sf::Event sfEvent);
	virtual void functionHandler(std::string sFunctionName);

	// function handler functions

	virtual void update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // TUTORIALSCREEN_H