#include "BackgroundController.h"

BackgroundController::BackgroundController()
{

}

BackgroundController& BackgroundController::getInstance()
{
	static BackgroundController instance;
	return instance;
}

BackgroundManager* BackgroundController::getBackground()
{
	return m_Background;
}

void BackgroundController::bindToBackground(BackgroundManager* background)
{
	m_Background = background;
}

int BackgroundController::getMoveSpeed()
{
	return m_Background->getMoveSpeed();
}

void BackgroundController::changeMoveSpeed(int iValue)
{
	m_Background->changeMoveSpeed(iValue);
}

void BackgroundController::clearStars()
{
	m_Background->clearStars();
}

void BackgroundController::stopSpawning()
{
	m_Background->stopSpawning();
}

void BackgroundController::startSpawning()
{
	m_Background->startSpawning();
}

void BackgroundController::update(const sf::RenderWindow& window)
{
	m_Background->update(window);
}

void BackgroundController::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	m_Background->draw(target, states);
}