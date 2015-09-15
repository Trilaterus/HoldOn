#include "GameTutLetter.h"

GameTutLetter::GameTutLetter(std::string sLetter, sf::Vector2f vPosition)
: GameClassicLetter(sLetter, vPosition)
{
	m_sText = "Hold the " + sLetter + " key";
	m_sfColour = sf::Color::White;
	m_sfFont = TextureManager::getInstance().getFontRef("Pixel");
}

GameTutLetter::GameTutLetter(std::string sLetter, sf::Vector2f vPosition, int iIdleTime, int iHoldTime, int iOverTime)
: GameClassicLetter(sLetter, vPosition, iIdleTime, iHoldTime, iOverTime)
{
	m_sText = "Hold the " + sLetter + " key";
	m_sfColour = sf::Color::White;
	m_sfFont = TextureManager::getInstance().getFontRef("Pixel");
}

bool GameTutLetter::isOverlapping(GameLetter* gameLetter)
{
	return GameClassicLetter::isOverlapping(gameLetter);
}

void GameTutLetter::positionCorrect(GameLetter* gameLetter)
{
	GameClassicLetter::positionCorrect(gameLetter);
}

void GameTutLetter::onPressed()
{
	GameClassicLetter::onPressed();
}

bool GameTutLetter::onReleased()
{
	return GameClassicLetter::onReleased();
}

bool GameTutLetter::checkIdle()
{
	return GameClassicLetter::checkIdle();
}

void GameTutLetter::update()
{
	GameClassicLetter::update();

	if (m_iPercentDrained >= 1)
	{
		m_sText = "Now you can\nlet go and earn points!";
		if (m_iPercentDrained >= 35)
		{
			m_sText = "The earlier you let go,\nthe more points you get!";
		}
		if (m_iPercentDrained >= 75)
		{
			m_sText = "If you don't,\nyou will lose health!";
		}
	}
	else if (m_isPressed)
	{
		m_sText = "Now hold on";
		if (m_iPercentFilled >= 35)
		{
			m_sText = "Keep going";
		}
		if (m_iPercentFilled >= 75)
		{
			m_sText = "Almost there...";
		}
	}
	else if (m_iPercentIdle <= 25)
	{
		m_sText = "If you don't,\nyou will lose health!";
	}
}

void GameTutLetter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	GameClassicLetter::draw(target, states);

	sf::Text text;
	text.setFont(m_sfFont);
	text.setString(m_sText);
	text.setColor(m_sfColour);
	text.setPosition(sf::Vector2f(m_vPosition.x + 75, m_vPosition.y + 50 - (100 - m_iPercentIdle)));
	text.setCharacterSize(60);
	target.draw(text);

	/* draws a line that moves with the idle timer
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(m_vPosition.x / 2, m_vPosition.y / 2)), // outside
		sf::Vertex(sf::Vector2f(m_vPosition.x - 50, m_vPosition.y + 50 - (100 - m_iPercentIdle))) // inside
	};

	target.draw(line, 2, sf::Lines);
	*/
}