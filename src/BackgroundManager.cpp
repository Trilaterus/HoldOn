#include "BackgroundManager.h"

BackgroundManager::BackgroundManager(sf::RenderWindow* window)
{
	m_texStar = new sf::Texture();
	*m_texStar = TextureManager::getInstance().getTexRef("Star");
	m_sfWindow = window;
	m_altStarColour = sf::Color(157, 211, 175, 255);
	for (int i = 0; i < 10; ++i)
	{
		this->addStar();
	}
	m_spawnClock.restart();
	m_updateClock.restart();
	m_iStarSpeed = 200; 
	m_fFPS = 240;
	m_shouldSpawn = true;
}

void BackgroundManager::addStar()
{
	sf::Sprite sprite;
	sprite.setTexture(*m_texStar);
	if (m_RandGen.generateBool() && m_RandGen.generateBool())
	{
		sprite.setColor(m_altStarColour);
	}
	sprite.setOrigin(m_texStar->getSize().x / 2, m_texStar->getSize().y / 2);
	sprite.setPosition(m_RandGen.generateInt(-10, m_sfWindow->getSize().x), m_RandGen.generateInt(-10, m_sfWindow->getSize().y));
	float starScale = m_RandGen.generateFloat(0.5, 1);
	sprite.setScale(starScale, starScale);
	m_AllStars.push_back(sprite);
}

void BackgroundManager::addStar(float xPos, float yPos)
{
	sf::Sprite sprite;
	sprite.setTexture(*m_texStar);
	if (m_RandGen.generateBool() && m_RandGen.generateBool())
	{
		sprite.setColor(m_altStarColour);
	}
	sprite.setOrigin(m_texStar->getSize().x / 2, m_texStar->getSize().y / 2);
	sprite.setPosition(xPos, yPos);
	float starScale = m_RandGen.generateFloat(0.5, 1);
	sprite.setScale(starScale, starScale);
	m_AllStars.push_back(sprite);
}

int BackgroundManager::getMoveSpeed()
{
	return m_iStarSpeed;
}

void BackgroundManager::changeMoveSpeed(int iValue)
{
	m_iStarSpeed = iValue;
}

void BackgroundManager::clearStars()
{
	m_AllStars.clear();
}

void BackgroundManager::stopSpawning()
{
	m_shouldSpawn = false;
}

void BackgroundManager::startSpawning()
{
	m_shouldSpawn = true;
}

void BackgroundManager::update(const sf::RenderWindow& window)
{
	sf::Vector2i windowCentre = sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2);

	// add new star every x seconds
	if (m_spawnClock.getElapsedTime().asSeconds() >= 0.1 && m_shouldSpawn)
	{
		int xPos;
		int yPos;
		int lowerBuffer = 15;
		int upperBuffer = 60;
		if (m_RandGen.generateBool())
		{
			xPos = m_RandGen.generateInt(0, window.getSize().x);
			if (m_RandGen.generateBool())
			{
				// y < 0
				yPos = -m_RandGen.generateInt(lowerBuffer, upperBuffer);
			}
			else
			{
				// y > 0
				yPos = m_RandGen.generateInt(window.getSize().y + lowerBuffer, window.getSize().y + upperBuffer);
			}
		}
		else
		{
			yPos = m_RandGen.generateInt(0, window.getSize().y);
			if (m_RandGen.generateBool())
			{
				// y < 0
				xPos = -m_RandGen.generateInt(lowerBuffer, upperBuffer);
			}
			else
			{
				// y > 0
				xPos = m_RandGen.generateInt(window.getSize().x + lowerBuffer, window.getSize().x + upperBuffer);
			}
		}
		this->addStar(xPos, yPos);
		m_spawnClock.restart();
	}

	// move and change scale of all stars
	if (m_updateClock.getElapsedTime().asSeconds() >= 1 / m_fFPS)
	{
		for (std::vector<sf::Sprite>::iterator it = m_AllStars.begin(); it != m_AllStars.end(); ++it)
		{
			it->move(-((it->getPosition().x - windowCentre.x) / m_iStarSpeed), -((it->getPosition().y - windowCentre.y) / m_iStarSpeed));
			if (it->getScale().x < 0)
			{
				it = m_AllStars.erase(it);
				break;
			}
			else
			{
				it->setScale(it->getScale().x - 0.003, it->getScale().y - 0.003);
			}
		}
		m_updateClock.restart();
	}
}

void BackgroundManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (std::vector<sf::Sprite>::const_iterator it = m_AllStars.begin(); it != m_AllStars.end(); ++it)
	{
		target.draw(*it);
	}
}