#include "ScoreController.h"

/* CONSTRUCTORS */

ScoreController::ScoreController()
{
	m_iScore = 0;
	m_sfFont = TextureManager::getInstance().getFontRef("M12");
	m_iHealth = 3;
}

/* GETTERS */

int ScoreController::getScore()
{
	return m_iScore;
}

int ScoreController::getHealth()
{
	return m_iHealth;
}

/* SETTERS */

void ScoreController::setScore(int iValue)
{
	m_iScore = iValue;
}

void ScoreController::setHealth(int iValue)
{
	m_iHealth = iValue;
}

/* CLASS SPECIFIC */

void ScoreController::modifyScore(GameLetter* gameLetter)
{
	m_iScore += gameLetter->getScore();
}

void ScoreController::modifyScore(int iValue)
{
	m_iScore += iValue;
}

void ScoreController::modifyHealth(int iValue)
{
	m_iHealth += iValue;
}

void ScoreController::update(const sf::RenderWindow& window)
{
	
}

void ScoreController::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// should really move these to the screen that they are drawn from and
	// just pass the values to get the updated results
	sf::Text score;
	score.setFont(m_sfFont);
	score.setString("Score " + std::to_string(m_iScore));
	score.setPosition(285 - 115, 38 - 11);
	score.setColor(sf::Color(255, 255, 255, 255));
	score.setOrigin((score.getLocalBounds().width / 2.f) / score.getScale().x, (score.getLocalBounds().height / 2.f) / score.getScale().y);
	target.draw(score);

	sf::Text health;
	health.setFont(m_sfFont);
	health.setString("Health " + std::to_string(m_iHealth));
	health.setPosition(950 - 120, 765 - 20);
	health.setColor(sf::Color(255, 255, 255, 255));
	health.setOrigin((health.getLocalBounds().width / 2.f) / health.getScale().x, (health.getLocalBounds().height / 2.f) / health.getScale().y);
	target.draw(health);
}