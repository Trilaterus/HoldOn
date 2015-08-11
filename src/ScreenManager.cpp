/** \file ScreenManager.cpp
-
*/

#include "ScreenManager.h"

/* CONSTRUCTORS */

ScreenManager::ScreenManager()
{
	m_isFullscreen = false;
}

ScreenManager::ScreenManager(Screen* screen)
{
	m_isFullscreen = false;
	m_AllScreens.push_back(screen);
	m_CurrentScreen = screen;
}

/* GETTERS */

Screen* ScreenManager::getCurrentScreen()
{
	return m_CurrentScreen;
}

bool ScreenManager::isFullscreen()
{
	return m_isFullscreen;
}

int ScreenManager::getScreenWidth()
{
	return m_iScreenWidth;
}

int ScreenManager::getScreenHeight()
{
	return m_iScreenHeight;
}

/* SETTERS */

void ScreenManager::setIsFullscreen(bool value)
{
	m_isFullscreen = value;
}

void ScreenManager::setScreenSize(int iWidth, int iHeight)
{
	m_iScreenWidth = iWidth;
	m_iScreenHeight = iHeight;
}

/* CLASS SPECIFIC */

void ScreenManager::addScreen(Screen* screen)
{
	m_AllScreens.push_back(screen);
	if (m_CurrentScreen == nullptr) // First screen added becomes current screen
	{
		m_CurrentScreen = screen;
	}
}

void ScreenManager::changeScreen(int iScreenNumber, int iTransitionNumber)
{
	if (iScreenNumber > m_AllScreens.size())
	{
		return;
	}
	else
	{
		// Add transition stuff here
		m_CurrentScreen = m_AllScreens.at(iScreenNumber);
	}
}

void ScreenManager::update(const sf::RenderWindow& window)
{
	if (m_CurrentScreen->getNeedChange())
	{
		this->changeScreen(m_CurrentScreen->getScreenChange().at(0), m_CurrentScreen->getScreenChange().at(1));
		m_CurrentScreen->setNeedChange(false);
	}
	m_CurrentScreen->update(window);
}

/* INHERITED */

void ScreenManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_CurrentScreen);
}