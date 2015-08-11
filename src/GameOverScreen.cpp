#include "GameOverScreen.h"

GameOverScreen::GameOverScreen()
{
	// never used...
}

GameOverScreen::GameOverScreen(std::string sFileName, sf::RenderWindow* window, ScoreController* pScoreController)
: Screen(sFileName, window)
{
	m_textScoreValue = new UIText(UIText::TOP_CENTRE, 0, 230);
	m_textScoreValue->setFont("M12");
	m_textScoreValue->setColour(sf::Color(255, 255, 255, 255));
	m_textScoreValue->setCharSize(70);
	Screen::addUIObjects(m_textScoreValue);
	m_pScoreController = pScoreController;
	m_iAnimScoreCounter = 0;
	m_isCurrentScreen = false;
}

std::string GameOverScreen::handleEvents(sf::Event sfEvent)
{
	std::string s = Screen::handleEvents(sfEvent);
	if (s != "")
	{
		this->functionHandler(s);
	}
	return "";
}

void GameOverScreen::functionHandler(std::string sFunctionName)
{
	if (sFunctionName == "gotoMainMenu")
	{
		this->gotoMainMenu();
	}
	else if (sFunctionName == "playAgain")
	{
		this->playAgain();
	}
}

void GameOverScreen::gotoMainMenu()
{
	Screen::changeScreen(0, 0);
	m_pScoreController->setHealth(3); // Need to put this - or could make reset function on scorecontroller
	m_pScoreController->setScore(0);  // evertim change screen
	m_iAnimScoreCounter = 0; // and this
	m_isCurrentScreen = false; // also this
}

void GameOverScreen::playAgain()
{
	m_pScoreController->setHealth(3); // Need to put this
	m_pScoreController->setScore(0);  // evertim change screen
	m_iAnimScoreCounter = 0; // and this
	m_isCurrentScreen = false; // also this
	Screen::changeScreen(3, 0);
}

void GameOverScreen::update(const sf::RenderWindow& window)
{
	if (!m_isCurrentScreen) // restarts all clocks once when this screen is showing
	{
		m_isCurrentScreen = true;
		m_sfDelayClock.restart();
		SoundManager::getInstance().stopBGMusic();
	}
	if (m_iAnimScoreCounter < m_pScoreController->getScore()) // animates the score going up to its amount
	{
		m_iAnimScoreCounter += 5;
	}
	else
	{
		m_iAnimScoreCounter = m_pScoreController->getScore();
	}
	m_textScoreValue->setString(std::to_string(m_iAnimScoreCounter));
	Screen::update(window);
}

void GameOverScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_sfDelayClock.getElapsedTime().asSeconds() > 0.7)
	{
		Screen::draw(target, states);
	}
}