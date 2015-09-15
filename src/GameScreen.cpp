#include "GameScreen.h"

GameScreen::GameScreen(std::string sFileName, sf::RenderWindow* window, ScoreController* pScoreController)
: Screen(sFileName, window)
{
	m_tCamOutline = TextureManager::getInstance().getTexRef("CamOutline");
	m_tSpaceShip = TextureManager::getInstance().getTexRef("Spaceship");
	m_fShipSize = 0.f;

	m_sfShipSizeClock.restart();
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
	m_fDifficulty = 3;
	m_fDifficultyModifier = 0; // should always start 0, to change the strength look in update function
	m_isCurrentScreen = false;
	m_iWaveNumber = 3;
	m_iSpawnModeTimer = 20;
	m_sCurrentSpawnMode = "continuous";
	m_isWaveIncremented = false;
	m_alternateDoubleSpawn = false;

	m_iIdleTime = 6000;
	m_iHoldTime = 3000;
	m_iOverTime = 10000;

	m_fScreenShakeRadius = 40;
	m_fScreenShakeAngle = m_RandomGenerator.generateInt(0, 360);
	m_vfScreenShakeOffset = sf::Vector2f(sin(m_fScreenShakeAngle) * m_fScreenShakeRadius, cos(m_fScreenShakeAngle) * m_fScreenShakeRadius);
	m_ScreenShakeSet = false;
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
	else if (sFunctionName == "ESCAPE")
	{
		m_GameLetterManager->reset();
		m_isCurrentScreen = false;
		m_fDifficulty = 3;
		m_fDifficultyModifier = 0;
		m_sCurrentSpawnMode = "continuous";
		m_isWaveIncremented = false;
		m_iWaveNumber = 3;
		m_iIdleTime = 6000;
		m_iHoldTime = 3000;
		m_iOverTime = 10000;
		m_pScoreController->setHealth(3);
		m_pScoreController->setScore(0);
		Screen::changeScreen(2, 0);
	}
}

void GameScreen::continuousSpawnMode(float fDifficulty)
{
	if (m_sfSpawnClock.getElapsedTime().asSeconds() > std::max(fDifficulty, 1.f))
	{
		m_GameLetterManager->spawnNormalLetter(m_iIdleTime, m_iHoldTime, m_iOverTime);
		if (!m_alternateDoubleSpawn)
		{
			if (m_iWaveNumber >= 4)
			{
				m_GameLetterManager->spawnNormalLetter();
			}
			if (m_iWaveNumber >= 6)
			{
				m_GameLetterManager->spawnNormalLetter();
			}
			m_alternateDoubleSpawn = true;
		}
		else
		{
			m_alternateDoubleSpawn = false;
		}
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

void GameScreen::screenShake()
{
	if (!m_ScreenShakeSet)
	{
		m_sfShakeClock.restart();
		m_ScreenShakeSet = true;
	}

	if (m_sfShakeClock.getElapsedTime().asSeconds() >= 0.01) // 1 / fps
	{
		sf::View view = m_sfWindow->getView();

		m_fScreenShakeRadius = m_fScreenShakeRadius * 0.9; // 0.999 for fast comps
		m_fScreenShakeAngle += 150 + m_RandomGenerator.generateInt(-60, 60); // hard numbers cuz 360 max degree angle anyway
		m_vfScreenShakeOffset = sf::Vector2f(sin(m_fScreenShakeAngle) * m_fScreenShakeRadius, cos(m_fScreenShakeAngle) * m_fScreenShakeRadius);
		view.setCenter(m_sfWindow->getSize().x / 2, m_sfWindow->getSize().y / 2);
		view.move(m_vfScreenShakeOffset);

		if (m_fScreenShakeRadius <= 2.0)
		{
			m_GameLetterManager->setScreenShake(false);
			view.setCenter(1024 / 2, 768 / 2);
			m_ScreenShakeSet = false;
			// reset stuff
			m_fScreenShakeRadius = 40;
			m_fScreenShakeAngle = m_RandomGenerator.generateInt(0, 360);
		}

		m_sfWindow->setView(view);
		m_sfShakeClock.restart();
	}
}

void GameScreen::update(const sf::RenderWindow& window)
{
	// Logarithmic difficulty modifier, gets harder based on score
	//m_fDifficultyModifier = log10(std::max(m_pScoreController->getScore() / 10, 10)); // ty Umar, divide by 10 to cancel out score modifier

	// Change the size of the background enemy ship based on a timer
	if (m_sfShipSizeClock.getElapsedTime().asSeconds() >= 0.1)
	{
		m_fShipSize += 0.0001;
		m_sfShipSizeClock.restart();
	}

	// Restarts all the clocks when this is the screen that is showing
	if (!m_isCurrentScreen) 
	{
		m_isCurrentScreen = true;
		m_sfRandSpawnClock.restart();
		m_sfSpawnClock.restart();
		m_sfSpawnModeClock.restart();
		m_sfShipSizeClock.restart();
		m_sfShakeClock.restart();
		m_fShipSize = 0.f;
		SoundManager::getInstance().playBGMusic("Rhino_Game");
		BackgroundController::getInstance().startSpawning();
	}

	// Just changes spawn mode after some time
	/* commenting this out stops wave spawn mode happening
	if (m_sfSpawnModeClock.getElapsedTime().asSeconds() > m_iSpawnModeTimer)
	{
		if (m_sCurrentSpawnMode == "wave")
		{
			m_sCurrentSpawnMode = "continuous";
			m_sfSpawnModeClock.restart();
			std::cout << "cont mode" << std::endl;
			m_iSpawnModeTimer += 2;
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
			m_iSpawnModeTimer += 2;
		}
	}
	*/
	
	// changes speed of letter idle hold and over based on set score values
	if (m_pScoreController->getScore() >= 18)
	{
		if (m_pScoreController->getScore() >= 80)
		{
			if (m_pScoreController->getScore() >= 200)
			{
				if (m_pScoreController->getScore() >= 350)
				{
					m_iIdleTime = 10000;
					m_iHoldTime = 10000;
					m_fDifficulty = 1;
					m_GameLetterManager->setMaxLetterCap(10);
				}
				else // less than 350
				{
					m_iIdleTime = 8000;
					m_iHoldTime = 8000;
					m_fDifficulty = 1.5;
					m_GameLetterManager->setMaxLetterCap(8);
				}
			}
			else // less than 200
			{
				m_iIdleTime = 6000;
				m_iHoldTime = 6000;
				m_GameLetterManager->setMaxLetterCap(6);
			}
		}
		else // less than 80
		{
			m_iIdleTime = 6000;
			m_iHoldTime = 4000;
			m_fDifficulty = 2;
			m_GameLetterManager->setMaxLetterCap(4);
		}
	}
	else // less than 18
	{
		m_iIdleTime = 6000;
		m_iHoldTime = 2500;
		m_iOverTime = 10000;
	}

	// carries out current spawn mode spawning
	if (m_sCurrentSpawnMode == "wave")
	{
		this->waveSpawnMode(m_fDifficulty);// - m_fDifficultyModifier);
	}
	else if (m_sCurrentSpawnMode == "continuous")
	{
		this->continuousSpawnMode(m_fDifficulty - m_fDifficultyModifier);
	}

	// Random clock to spawn an extra one randomly
	if (!m_isRandSpawnClockSet)
	{
		m_iRandSpawnClockTimer = m_RandomGenerator.generateInt(15, 25);
		m_isRandSpawnClockSet = true;
	}
	else if (m_sfRandSpawnClock.getElapsedTime().asSeconds() > m_iRandSpawnClockTimer)
	{
		m_GameLetterManager->spawnNormalLetter(m_iIdleTime, m_iHoldTime, m_iOverTime);
		m_sfRandSpawnClock.restart();
		m_isRandSpawnClockSet = false;
		std::cout << "rand spawned" << std::endl;
	}

	// check for screenshake
	if (m_GameLetterManager->getScreenShake())
	{
		this->screenShake(); // stops itself in the function
	}

	// check if game is over and what to do when it is
	if (m_GameLetterManager->update(window))
	{
		Screen::changeScreen(4, 1);
		m_GameLetterManager->reset();
		m_isCurrentScreen = false;
		m_fDifficulty = 3;
		m_fDifficultyModifier = 0;
		m_sCurrentSpawnMode = "continuous";
		m_isWaveIncremented = false;
		m_iWaveNumber = 3;
		m_iIdleTime = 6000;
		m_iHoldTime = 3000;
		m_iOverTime = 10000;
		BackgroundController::getInstance().changeMoveSpeed(200);
		BackgroundController::getInstance().clearStars();
		BackgroundController::getInstance().stopSpawning();
	}

	Screen::update(window);
}

void GameScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Enemy space ship
	sf::Sprite ship;
	ship.setTexture(m_tSpaceShip);
	ship.setOrigin(m_tSpaceShip.getSize().x / 2, m_tSpaceShip.getSize().y / 2);
	ship.setPosition((target.getSize().x / 2), target.getSize().y / 2 - 250);
	ship.setScale(m_fShipSize, m_fShipSize);
	target.draw(ship);

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