#include "GameScreen.h"

GameScreen::GameScreen(std::string sFileName, sf::RenderWindow* window, ScoreController* pScoreController)
: Screen(sFileName, window)
{
	m_tCamOutline = TextureManager::getInstance().getTexRef("CamOutline");
	m_sfSpawnClock.restart();
	m_sfRandSpawnClock.restart();
	m_sfSpawnClock.restart();
	m_isRandSpawnClockSet = true;
	m_iRandSpawnClockTimer = m_RandomGenerator.generateInt(10, 25);

	sf::Sprite sprite;
	sprite.setTexture(m_tCamOutline);
	sprite.setOrigin(m_tCamOutline.getSize().x / 2, m_tCamOutline.getSize().y / 2);
	sprite.setPosition(window->getSize().x / 2, window->getSize().y / 2);

	m_pScoreController = pScoreController;
	m_GameLetterManager = new GameLetterManager(sprite, m_pScoreController);
	m_fDifficulty = 4;
	m_fDifficultyModifier = 0; // should always start 0, to change the strength look in update function
	m_isCurrentScreen = false;
	m_iWaveNumber = 2;
	m_iSpawnModeTimer = 20;
	m_sCurrentSpawnMode = "continuous";
	m_isWaveIncremented = false;
}

std::string GameScreen::handleEvents(sf::Event sfEvent)
{
	// This is for the functionHandler
	std::string s = Screen::handleEvents(sfEvent);
	if (s != "")
	{
		this->functionHandler(s);
	}

	// This is for the GameLetters
	m_GameLetterManager->handleEvents(sfEvent);

	return ""; // not really used for anything...
}

void GameScreen::functionHandler(std::string sFunctionName)
{
	if (sFunctionName == "")
	{
		
	}
}

void GameScreen::continuousSpawnMode(float fDifficulty)
{
	if (m_sfSpawnClock.getElapsedTime().asSeconds() > std::max(fDifficulty, 1.f))
	{
		m_GameLetterManager->spawnNormalLetter();
		m_sfSpawnClock.restart();
	}
}

void GameScreen::waveSpawnMode(float fDifficulty)
{
	if (m_sfSpawnClock.getElapsedTime().asSeconds() > 4.1 + (0.5 * m_iWaveNumber-1)) // adds 0.5 seconds to clear the wave per letters per wave
	{
		for (int i = 0; i < m_iWaveNumber; i++)
		{
			m_GameLetterManager->spawnNormalLetter();
		}
		m_sfSpawnClock.restart();
	}
}

void GameScreen::update(const sf::RenderWindow& window)
{
	// Logarithmic difficulty modifier, gets harder based on score
	m_fDifficultyModifier = log10(std::max(m_pScoreController->getScore() / 1, 1)); // ty Umar, divide by more to make the diff increase less steep

	// Restarts all the clocks when this is the screen that is showing
	if (!m_isCurrentScreen) 
	{
		m_isCurrentScreen = true;
		m_sfRandSpawnClock.restart();
		m_sfSpawnClock.restart();
		m_sfSpawnModeClock.restart();
		SoundManager::getInstance().playBGMusic("Rhino_Game");
	}

	// Just changes spawn mode after some time
	if (m_sfSpawnModeClock.getElapsedTime().asSeconds() > m_iSpawnModeTimer)
	{
		if (m_sCurrentSpawnMode == "wave")
		{
			m_sCurrentSpawnMode = "continuous";
			m_sfSpawnModeClock.restart();
			std::cout << "cont mode" << std::endl;
		}
		else if (m_sCurrentSpawnMode == "continuous")
		{
			m_sCurrentSpawnMode = "wave";
			if (m_isWaveIncremented)
			{
				m_iWaveNumber++;
				m_isWaveIncremented = false;
			}
			else if (!m_isWaveIncremented)
			{
				m_isWaveIncremented = true;
			}
			m_sfSpawnModeClock.restart();
			std::cout << "wave mode" << std::endl;
		}
	}
	
	// carries out current spawn mode spawning
	if (m_sCurrentSpawnMode == "wave")
	{
		this->waveSpawnMode(m_fDifficulty - m_fDifficultyModifier);
	}
	else if (m_sCurrentSpawnMode == "continuous")
	{
		this->continuousSpawnMode(m_fDifficulty - m_fDifficultyModifier);
	}

	// Random clock to spawn an extra one randomly
	if (!m_isRandSpawnClockSet)
	{
		m_iRandSpawnClockTimer = m_RandomGenerator.generateInt(10, 25);
	}
	else if (m_sfRandSpawnClock.getElapsedTime().asSeconds() > m_iRandSpawnClockTimer)
	{
		m_GameLetterManager->spawnNormalLetter();
		m_sfRandSpawnClock.restart();
		m_isRandSpawnClockSet = false;
		std::cout << "rand spawned" << std::endl;
	}

	// check if game is over and what to do when it is
	if (m_GameLetterManager->update(window))
	{
		Screen::changeScreen(4, 1);
		m_GameLetterManager->reset();
		m_isCurrentScreen = false;
		m_fDifficulty = 4;
		m_fDifficultyModifier = 0;
		m_sCurrentSpawnMode = "continuous";
		m_isWaveIncremented = false;
		m_iWaveNumber = 2;
	}

	Screen::update(window);
}

void GameScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Cam outline
	sf::Sprite sprite;
	sprite.setTexture(m_tCamOutline);
	sprite.setOrigin(m_tCamOutline.getSize().x / 2, m_tCamOutline.getSize().y / 2);
	sprite.setPosition(target.getSize().x / 2, target.getSize().y / 2);
	target.draw(sprite);
	
	// Draw letters spawned from GameLetterManager
	target.draw(*m_GameLetterManager);

	// Draw elements specified in .txt file
	Screen::draw(target, states);
}