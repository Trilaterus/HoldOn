#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "GameLetterManager.h"
#include "TextureManager.h"
#include "RandomResource.h"
#include "SoundManager.h"

class GameScreen : public Screen
{
private:
	GameLetterManager* m_GameLetterManager;
	std::string m_sModeName;
	sf::Texture m_tCamOutline;
	sf::Texture m_tSpaceShip;
	float m_fShipSize;
	sf::Clock m_sfShipSizeClock;
	sf::Clock m_sfSpawnClock;
	ScoreController* m_pScoreController;
	float m_fDifficulty; // in seconds how long it takes for stuff to spawn
	float m_fDifficultyModifier; // subtracted from the fDifficulty to make the stuff spawn faster
	sf::Clock m_sfRandSpawnClock;
	bool m_isRandSpawnClockSet; // has this clock been set a random time to wait for?
	int m_iRandSpawnClockTimer;
	RandomResource m_RandomGenerator;
	bool m_isCurrentScreen;
	int m_iWaveNumber; // how many letters to spawn at a time
	sf::Clock m_sfSpawnModeClock;
	int m_iSpawnModeTimer; // how many seconds until the spawn mode should change
	std::string m_sCurrentSpawnMode;
	bool m_isWaveIncremented; // should the next wave be incremented or not?
	bool m_alternateDoubleSpawn; // in continuous spawn mode alternate between one and multiple spawns
	int m_iIdleTime; // in milliseconds
	int m_iHoldTime; // in milliseconds
	int m_iOverTime; // in milliseconds
	sf::Clock m_sfShakeClock; // clock for screen shaking
	bool m_ScreenShakeSet; // has the one time setup been done for the screenshake?
	float m_fScreenShakeRadius;
	float m_fScreenShakeAngle;
	sf::Vector2f m_vfScreenShakeOffset;

protected:

public:
	GameScreen(std::string sFileName, sf::RenderWindow* window, ScoreController* pScoreController);

	virtual std::string handleEvents(sf::Event sfEvent);
	virtual void functionHandler(std::string sFunctionName);

	// Function handler functions

	void continuousSpawnMode(float fDifficulty);
	void waveSpawnMode(float fDifficulty);
	void screenShake();

	virtual void update(const sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //GAMESCREEN_H