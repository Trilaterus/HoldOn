#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	m_bFirstTime = true;
	m_isCurrentScreen = false;
}

PlayScreen::PlayScreen(std::string sFileName)
: Screen(sFileName)
{
	m_bFirstTime = true;
	m_isCurrentScreen = false;
}

PlayScreen::PlayScreen(std::string sFileName, sf::RenderWindow* window)
: Screen(sFileName, window)
{
	m_bFirstTime = true;
	m_isCurrentScreen = false;
}

std::string PlayScreen::handleEvents(sf::Event sfEvent)
{
	std::string s = Screen::handleEvents(sfEvent);
	if (s != "")
	{
		this->functionHandler(s);
	}
	return ""; // not really used for anything...
}

void PlayScreen::functionHandler(std::string sFunctionName)
{
	if (sFunctionName == "")
	{
		int i = 0;
	}
	else if (sFunctionName == "gotoClassic")
	{
		this->gotoClassic();
	}
	else if (sFunctionName == "gotoNormal")
	{
		this->gotoNormal();
	}
	else if (sFunctionName == "gotoRapid")
	{
		this->gotoRapid();
	}
	else if (sFunctionName == "gotoBack")
	{
		this->gotoBack();
	}
	else if (sFunctionName == "gotoTut")
	{
		this->gotoTut();
	}
	else if (sFunctionName == "ESCAPE")
	{
		Screen::changeScreen(0, 0);
	}
}

void PlayScreen::gotoClassic()
{
	//if (m_bFirstTime)
	//{
	//	Screen::changeScreen(5, 0);
	//}
	//else
	//{
		m_isCurrentScreen = false;
		Screen::changeScreen(3, 0);
	//}
}

void PlayScreen::gotoNormal()
{

}

void PlayScreen::gotoRapid()
{

}

void PlayScreen::gotoBack()
{
	m_isCurrentScreen = false;
	Screen::changeScreen(0, 0);
}

void PlayScreen::gotoTut()
{
	m_isCurrentScreen = false;
	Screen::changeScreen(5, 0);
}

void PlayScreen::update(const sf::RenderWindow& window)
{
	if (!m_isCurrentScreen)
	{
		SoundManager::getInstance().playBGMusic("Rhino_Menu");
		BackgroundController::getInstance().startSpawning();
		m_isCurrentScreen = true;
	}

	Screen::update(window);
}

void PlayScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Screen::draw(target, states);
}