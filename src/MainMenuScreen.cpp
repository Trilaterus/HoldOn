#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen()
{

}

MainMenuScreen::MainMenuScreen(std::string sFileName)
: Screen(sFileName)
{

}

MainMenuScreen::MainMenuScreen(std::string sFileName, sf::RenderWindow* window)
: Screen(sFileName, window)
{
	
}

std::string MainMenuScreen::handleEvents(sf::Event sfEvent)
{
	std::string s = Screen::handleEvents(sfEvent);
	if (s != "")
	{
		this->functionHandler(s);
	}
	return ""; // not really used for anything...
}

void MainMenuScreen::functionHandler(std::string sFunctionName)
{
	if (sFunctionName == "")
	{
		int i = 0;
	}
	else if (sFunctionName == "gotoPlay")
	{
		this->gotoPlay();
	}
	else if (sFunctionName == "gotoOptions")
	{
		this->gotoOptions();
	}
	else if (sFunctionName == "gotoQuit")
	{
		this->gotoQuit();
	}
}

void MainMenuScreen::gotoPlay()
{
	Screen::changeScreen(2, 0);
	m_isCurrentScreen = false;
}

void MainMenuScreen::gotoOptions()
{
	Screen::changeScreen(1, 0);
	m_isCurrentScreen = false;
}

void MainMenuScreen::gotoQuit()
{
	m_sfWindow->close();
}

void MainMenuScreen::update(const sf::RenderWindow& window)
{
	if (!m_isCurrentScreen) // do things only one time when this screen appears
	{
		SoundManager::getInstance().playBGMusic("Rhino_Menu");
		m_isCurrentScreen = true;
	}
	Screen::update(window);
}

void MainMenuScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Screen::draw(target, states);
}