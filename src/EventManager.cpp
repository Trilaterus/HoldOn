/** \file EventManager.cpp
-
*/

#include "EventManager.h"

EventManager::EventManager()
{

}

EventManager& EventManager::getInstance()
{
	static EventManager instance;
	return instance;
}

void EventManager::handleEvents(sf::Event eEvent, sf::RenderWindow* window, ScreenManager& screenManager)
{
	m_Event = eEvent;

	if (m_Event.type == sf::Event::Closed) //||
		//sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) remove comment to enable close by esc
	{
		window->close();
	}

	if (m_Event.type == sf::Event::Resized)
	{
		sf::FloatRect visibleArea(0, 0, m_Event.size.width, m_Event.size.height);
		window->setView(sf::View(visibleArea));
		screenManager.update(*window);
	}

	/* Keyboard controls */
	/*
	Key for keyboard, (t) = for testing purposes only
	1 (t) = Changes window width and height to 1920x1080
	2 (t) = Changes window width and height to 1366x768
	3 (t) = Changes window width and height to 1280x1024
	4 (t) = Changes window width and height to 1280x800
	5 (t) = Changes window width and height to 1024x768
	6 (t) = Toggles between fullscreen and not fullscreen
	*/
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		if (screenManager.isFullscreen())
		{
			delete window;
			window = new sf::RenderWindow(sf::VideoMode(1980, 1080), "SFML works!", sf::Style::Fullscreen);
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
			screenManager.update(*window);
		}
		else
		{
			window->setSize(sf::Vector2u(1980, 1080));
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		if (screenManager.isFullscreen())
		{
			delete window;
			window = new sf::RenderWindow(sf::VideoMode(1366, 768), "SFML works!", sf::Style::Fullscreen);
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
			screenManager.update(*window);
		}
		else
		{
			window->setSize(sf::Vector2u(1366, 768));
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		if (screenManager.isFullscreen())
		{
			delete window;
			window = new sf::RenderWindow(sf::VideoMode(1280, 1024), "SFML works!", sf::Style::Fullscreen);
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
			screenManager.update(*window);
		}
		else
		{
			window->setSize(sf::Vector2u(1280, 1024));
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		if (screenManager.isFullscreen())
		{
			delete window;
			window = new sf::RenderWindow(sf::VideoMode(1280, 800), "SFML works!", sf::Style::Fullscreen);
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
			screenManager.update(*window);
		}
		else
		{
			window->setSize(sf::Vector2u(1280, 800));
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		if (screenManager.isFullscreen())
		{
			delete window;
			window = new sf::RenderWindow(sf::VideoMode(1024, 768), "SFML works!", sf::Style::Fullscreen);
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
			screenManager.update(*window);
		}
		else
		{
			window->setSize(sf::Vector2u(1024, 768));
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		if (!screenManager.isFullscreen())
		{
			delete window;
			window = new sf::RenderWindow(sf::VideoMode(screenManager.getScreenWidth(), screenManager.getScreenHeight()), "SFML works!", sf::Style::Fullscreen);
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
			screenManager.setIsFullscreen(true);
			screenManager.update(*window);
		}
		else
		{
			delete window;
			window = new sf::RenderWindow(sf::VideoMode(screenManager.getScreenWidth(), screenManager.getScreenHeight()), "SFML works!");
			screenManager.setScreenSize(window->getSize().x, window->getSize().y);
			screenManager.setIsFullscreen(false);
			screenManager.update(*window);
		}
	}
	*/
	screenManager.getCurrentScreen()->handleEvents(eEvent);
}