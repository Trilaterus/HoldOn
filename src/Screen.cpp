/** \file Screen.cpp
-
*/

#include "Screen.h"

Screen::Screen()
{
	m_needsChange = false;
	m_aScreenChange.fill(0);
}

Screen::Screen(std::string sFileName)
{
	init(sFileName);
}

Screen::Screen(std::string sFileName, sf::RenderWindow* window)
{
	init(sFileName);
	m_sfWindow = window;
}

void Screen::init(std::string sFileName)
{
	m_isClockTransitionReset = false;
	m_animViewZoom = 1;
	m_needsChange = false;
	m_aScreenChange.fill(0);
	std::ifstream layout(sFileName, std::ifstream::ios_base::in);
	if (layout.is_open())
	{
		std::string line;
		while (getline(layout, line))
		{
			std::string s;
			std::istringstream is(line);
			std::vector<std::string> sParameters;
			std::vector<float> parameters;
			std::string name;
			std::string enumPos;
			std::string textureName;
			std::string sParam;
			float param;

			is >> s;

			if (s == "#" ||
				s == "")
			{
				// Ignore line
			}
			else if (s == "Image:")
			{
				is >> name;
				is >> enumPos;
				if (convertToEnum(enumPos) == 9) // If it is relative->
				{
					std::string parent;
					is >> parent;
					is >> param;
					parameters.push_back(param);
					is >> param;
					parameters.push_back(param);
					is >> textureName;
					UIImage* tmp = new UIImage();
					tmp->setName(name);
					for (std::vector<UIObject*>::iterator it = m_AllUIObjects.begin(); it != m_AllUIObjects.end(); ++it)
					{
						if ((*it)->getName() == parent)
						{
							tmp->setParent((*it));
							break;
						}
					}
					tmp->setRelativePosition(parameters.at(0), parameters.at(1));
					m_AllUIObjects.push_back(tmp);
				}
				else
				{
					is >> param;
					parameters.push_back(param);
					is >> param;
					parameters.push_back(param);
					is >> textureName;
					m_AllUIObjects.push_back(new UIImage(convertToEnum(enumPos), parameters.at(0), parameters.at(1), TextureManager::getInstance().getTexRef(textureName)));
					m_AllUIObjects.back()->setName(name);
				}
			}
			else if (s == "Text:")
			{
				while (is >> sParam)
				{
					sParameters.push_back(sParam);
				}
				m_AllUIObjects.push_back(new UIText(convertToEnum(sParameters.at(1)), std::stof(sParameters.at(2)), std::stof(sParameters.at(3)), sParameters.at(0)));
				m_AllUIObjects.back()->setName(sParameters.at(0));
				if (sParameters.size() > 4)
				{
					UIText* text = dynamic_cast<UIText*>(m_AllUIObjects.back());
					text->setFont(sParameters.at(4));
					if (sParameters.size() >= 9)
					{
						text->setColour(sf::Color(std::stof(sParameters.at(5)), std::stof(sParameters.at(6)), std::stof(sParameters.at(7)), std::stof(sParameters.at(8))));
						if (sParameters.size() >= 10)
						{
							text->setCharSize(std::stof(sParameters.at(9)));
						}
					}
				}
			}
			else if (s == "GameText:")
			{
				while (is >> sParam)
				{
					sParameters.push_back(sParam);
				}
				m_AllUIObjects.push_back(new UIGameText(convertToEnum(sParameters.at(1)), std::stof(sParameters.at(2)), std::stof(sParameters.at(3)), sParameters.at(0)));
				m_AllUIObjects.back()->setName(sParameters.at(0));
				if (sParameters.size() > 4)
				{
					UIGameText* text = dynamic_cast<UIGameText*>(m_AllUIObjects.back());
					text->setFont(sParameters.at(4));
					if (sParameters.size() >= 9)
					{
						text->setColour(sf::Color(std::stof(sParameters.at(5)), std::stof(sParameters.at(6)), std::stof(sParameters.at(7)), std::stof(sParameters.at(8))));
						if (sParameters.size() >= 10)
						{
							text->setCharSize(std::stof(sParameters.at(9)));
							if (sParameters.size() >= 11)
							{
								text->setKey(sParameters.at(10));
								text->setFunctionName(sParameters.at(11));
							}
						}
					}
				}
			}
			else
			{
				std::cout << "Unrecognisable line at: " << s << std::endl;
			}
		}
	}
}

int Screen::convertToEnum(std::string name)
{
	if (name == "top_left")
	{
		return 0;
	}
	else if (name == "top_right")
	{
		return 1;
	}
	else if (name == "bot_left")
	{
		return 2;
	}
	else if (name == "bot_right")
	{
		return 3;
	}
	else if (name == "centre")
	{
		return 4;
	}
	else if (name == "top_centre")
	{
		return 5;
	}
	else if (name == "left_centre")
	{
		return 6;
	}
	else if (name == "right_centre")
	{
		return 7;
	}
	else if (name == "bot_centre")
	{
		return 8;
	}
	else if (name == "relative->")
	{
		return 9;
	}
	else
	{
		std::cout << "Unrecognisable enum name" << std::endl;
	}
}

bool Screen::screenAnimation(int iTransitionNum)
{
	int windowWidth = m_sfWindow->getSize().x;
	int windowHeight = m_sfWindow->getSize().y;
	int doubleWindowWidth = windowWidth * 2;
	int doubleWindowHeight = windowHeight * 2;
	int halfWindowWidth = windowWidth / 2;
	int halfWindowHeight = windowHeight / 2;

	if (iTransitionNum == 0)
	{
		m_needsChange = true;
		return true;
	}
	else if (iTransitionNum == 1) // the old tv switch off
	{
		if (m_sfWindow->getView().getViewport().width <= 0)
		{
			m_needsChange = true;
			m_animViewZoom = 1;
			m_isAnimating = false;
			// this bit is causing the
			sf::View* view = new sf::View(sf::Vector2f(halfWindowWidth, halfWindowHeight), sf::Vector2f(windowWidth, windowHeight));
			m_sfWindow->setView(*view);
			// screen glitch on transition, gotta get it to set it after it has been changed
			m_isClockTransitionReset = false;
			return true;
		}
		else if (m_sfWindow->getView().getViewport().height > 0.1)
		{
			if (!m_isAnimating)
			{
				m_isAnimating = true;
			}
			if (!m_isClockTransitionReset)
			{
				m_clockScreenTransitions.restart();
				m_isClockTransitionReset = true;
			}
			sf::View* view = new sf::View(m_sfWindow->getView());
			float i = m_clockScreenTransitions.getElapsedTime().asMilliseconds();
			float j = i / 1000; // 1000 means 1 second
			m_animViewZoom = 1 - (j * 2); // 1 is it's init value
			if (m_animViewZoom <= 0)
			{
				m_animViewZoom = 0.01;
			}
			view->setViewport(sf::FloatRect(0, 0, 1, m_animViewZoom));
			float newPortHeight = view->getViewport().height * windowHeight;
			view->setViewport(sf::FloatRect(0, (windowHeight - newPortHeight) / doubleWindowHeight, 1, m_animViewZoom)); // 800 is screen height, 1600 is double that
			if (m_sfWindow->getView().getViewport().height <= 0.2)
			{
				m_isAnimating = false;
			}
			m_sfWindow->setView(*view);
		}
		else
		{
			if (!m_isAnimating)
			{
				m_animViewZoom = 1;
				m_isAnimating = true;
				m_clockScreenTransitions.restart();
			}
			sf::View* view = new sf::View(m_sfWindow->getView());
			float i = m_clockScreenTransitions.getElapsedTime().asMilliseconds();
			float j = i / 1000; // 1000 means 1 second
			m_animViewZoom = 1 - (j * 2); // 1 is it's init value
			if (m_animViewZoom <= 0)
			{
				m_animViewZoom = 0;
			}
			float newPortWidth = view->getViewport().width * windowWidth;
			view->setViewport(sf::FloatRect((windowWidth - newPortWidth) / doubleWindowWidth, 0.5, m_animViewZoom, 0.01));
			m_sfWindow->setView(*view);
		}
	}
	return false;
}

void Screen::setNeedChange(bool bValue)
{
	m_needsChange = bValue;
}

bool Screen::getNeedChange()
{
	return m_needsChange;
}

std::array<int, 2> Screen::getScreenChange()
{
	return m_aScreenChange;
}

void Screen::addUIObjects(UIObject* uiObject)
{
	m_AllUIObjects.push_back(uiObject);
}

const std::vector<UIObject*>& Screen::getAllUIObjects()
{
	return m_AllUIObjects;
}

std::string Screen::handleEvents(sf::Event sfEvent)
{
	if (sfEvent.type == sf::Event::KeyPressed) // If a key is pressed
	{
		if (sfEvent.key.code == sf::Keyboard::Escape)
		{
			return "ESCAPE";
		}
		else
		{
			for (std::vector<UIObject*>::iterator it = m_AllUIObjects.begin(); it != m_AllUIObjects.end(); ++it)
			{
				std::string sObjName = typeid(**it).name();

				if (sObjName == "class UIGameText")
				{
					UIGameText* uiGameText = dynamic_cast<UIGameText*>(*it);
					uiGameText->onPressed(sfEvent);
				}
			}
		}
	}
	else if (sfEvent.type == sf::Event::KeyReleased) // If a key is release
	{
		for (std::vector<UIObject*>::iterator it = m_AllUIObjects.begin(); it != m_AllUIObjects.end(); ++it)
		{
			std::string sObjName = typeid(**it).name();

			if (sObjName == "class UIGameText")
			{
				UIGameText* uiGameText = dynamic_cast<UIGameText*>(*it);

				if (uiGameText->onReleased(sfEvent))
				{
					return uiGameText->getFunctionName();
				}
			}
		}
	}

	else if (sfEvent.type == sfEvent.MouseButtonPressed) // If the mouse click has been clicked
	{
		for (std::vector<UIObject*>::iterator it = m_AllUIObjects.begin(); it != m_AllUIObjects.end(); ++it)
		{
			std::string sObjName = typeid(**it).name();
			sf::Vector2i iMousePos = sf::Mouse::getPosition(*m_sfWindow);

			if (sObjName == "class UIGameText")
			{
				UIGameText* uiGameText = dynamic_cast<UIGameText*>(*it);

				if (uiGameText->getSFText().getGlobalBounds().contains(iMousePos.x, iMousePos.y))
				{
					uiGameText->onClicked();
				}
			}
		}
	}

	else if (sfEvent.type == sfEvent.MouseButtonReleased) // If the mouse click has been released
	{
		for (std::vector<UIObject*>::iterator it = m_AllUIObjects.begin(); it != m_AllUIObjects.end(); ++it)
		{
			std::string sObjName = typeid(**it).name();
			sf::Vector2i iMousePos = sf::Mouse::getPosition(*m_sfWindow);

			if (sObjName == "class UIGameText")
			{
				UIGameText* uiGameText = dynamic_cast<UIGameText*>(*it);

				if (uiGameText->getSFText().getGlobalBounds().contains(iMousePos.x, iMousePos.y))
				{
					uiGameText->onUnclicked();
					return uiGameText->getFunctionName();
				}
				else
				{
					uiGameText->onUnclicked();
				}
			}
		}
	}

	return "";
}

bool Screen::changeScreen(int iScreenNum, int iTransitionNum)
{
	m_aScreenChange.at(0) = iScreenNum;
	m_aScreenChange.at(1) = iTransitionNum;
	
	return this->screenAnimation(iTransitionNum);
}

void Screen::update(const sf::RenderWindow& window)
{
	for (std::vector<UIObject*>::iterator it = m_AllUIObjects.begin(); it != m_AllUIObjects.end(); ++it)
	{
		(*it)->update(window);
	}
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (std::vector<UIObject*>::const_iterator it = m_AllUIObjects.begin(); it != m_AllUIObjects.end(); ++it)
	{
		target.draw(**it);
	}
}