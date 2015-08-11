#include "GameLetterManager.h"

GameLetterManager::GameLetterManager(sf::Sprite spawnRect, ScoreController* pScoreController)
{
	m_spawnRect = spawnRect;
	m_pScoreController = pScoreController;
	m_texLetterDoneTrue = TextureManager::getInstance().getTexRef("DoneLetterTrue");
	m_texLetterDoneFalse = TextureManager::getInstance().getTexRef("DoneLetterFalse");
	m_fLetterDoneTimer = 370; // in milliseconds
}

void GameLetterManager::letterReleasedAnimation(bool bValue, GameLetter* gameLetter)
{
	if (bValue)
	{
		sf::Sprite* tmp = new sf::Sprite();
		tmp->setTexture(m_texLetterDoneTrue);
		tmp->setOrigin(m_texLetterDoneTrue.getSize().x / 2, m_texLetterDoneTrue.getSize().y / 2);
		tmp->setPosition(gameLetter->getPosition());

		sf::Clock* clock = new sf::Clock();
		bool* isReset = new bool;
		*isReset = false;

		std::pair <sf::Sprite*, std::pair<sf::Clock*, bool*>> pair;
		pair.first = tmp;
		pair.second.first = clock;
		pair.second.second = isReset;

		m_vLetterDones.push_back(pair);
	}
	else
	{
		sf::Sprite* tmp = new sf::Sprite();
		tmp->setTexture(m_texLetterDoneFalse);
		tmp->setOrigin(m_texLetterDoneFalse.getSize().x / 2, m_texLetterDoneFalse.getSize().y / 2);
		tmp->setPosition(gameLetter->getPosition());

		sf::Clock* clock = new sf::Clock();
		bool* isReset = new bool;
		*isReset = false;

		std::pair <sf::Sprite*, std::pair<sf::Clock*, bool*>> pair;
		pair.first = tmp;
		pair.second.first = clock;
		pair.second.second = isReset;

		m_vLetterDones.push_back(pair);
	}
}

ScoreController* GameLetterManager::getScoreController()
{
	return m_pScoreController;
}

int GameLetterManager::getAmountOfLetters()
{
	int i = m_vGameLetters.size();
	if (i == 0)
	{
		int j = 0;
	}
	return i;
}

void GameLetterManager::spawnNormalLetter()
{
	// variables defining the edges of the spawn area
	GameClassicLetter tmp("a", sf::Vector2f(0,0));
	int x = m_spawnRect.getPosition().x;
	int y = m_spawnRect.getPosition().y;
	int x2 = m_spawnRect.getGlobalBounds().width / 2;
	int y2 = m_spawnRect.getGlobalBounds().height / 2;
	int offset = tmp.getWidth() / 2;

	bool b = true;
	while (b)
	{
		std::string s = AlphabetResource::getInstance().getRandomLower();
		if (m_vGameLetters.size() == 0)
		{
			int xPos = m_RandomGenerator.generateInt(x - x2 + offset, x + x2 - offset);
			int yPos = m_RandomGenerator.generateInt(y - y2 + offset, y + y2 - offset);

			GameClassicLetter* gameLetter = new GameClassicLetter(s, sf::Vector2f(xPos, yPos));

			m_vGameLetters.push_back(gameLetter);
			b = false;
			return;
		}
		else
		{
			for (std::vector<GameLetter*>::const_iterator it = m_vGameLetters.begin(); it != m_vGameLetters.end(); ++it)
			{
				if (s != (*it)->getLetter())
				{
					if (m_vGameLetters.end() - it == 1) // checks if last in vector (link: http://stackoverflow.com/questions/3516196/testing-whether-an-iterator-points-to-the-last-item)
					{
						int xPos = m_RandomGenerator.generateInt(x - x2 + offset, x + x2 - offset);
						int yPos = m_RandomGenerator.generateInt(y - y2 + offset, y + y2 - offset);

						GameClassicLetter* gameLetter = new GameClassicLetter(s, sf::Vector2f(xPos, yPos));

						int stuckCounter = 0;

						for (std::vector<GameLetter*>::const_iterator it = m_vGameLetters.begin(); it != m_vGameLetters.end(); ++it)
						{
							if (gameLetter->isOverlapping(*it)) // game letter overlaps another game letter
							{
								// move it or change it's position so that it isn't
								// check it again against all letters (unless that has the values of parameters don't change problem)
								//gameLetter->setColor(sf::Color::Red);
								gameLetter->positionCorrect(*it);
								it = m_vGameLetters.begin();
								// if a counter goes through 3/5 times generate a new random position and try again
								stuckCounter++;
								if (stuckCounter >= 5)
								{
									gameLetter->setPosition(m_RandomGenerator.generateInt(x - x2 + offset, x + x2 - offset), m_RandomGenerator.generateInt(y - y2 + offset, y + y2 - offset));
									stuckCounter = 0;
								}
							}
						}

						stuckCounter = 0;

						m_vGameLetters.push_back(gameLetter);
						b = false;
						return;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	return;
}

void GameLetterManager::reset()
{
	m_vGameLetters.clear();
	m_vLetterDones.clear();
}

void GameLetterManager::handleEvents(sf::Event sfEvent) // Always have events processed outside of the update functions otherwise you'll get the mouse move update speed bug... 
{
	for (std::vector<GameLetter*>::const_iterator it = m_vGameLetters.begin(); it != m_vGameLetters.end(); ++it)
	{
		if (sf::Keyboard::isKeyPressed((*it)->getKey())) // On pressed
		{
			(*it)->onPressed();
		}

		if (sfEvent.type == sf::Event::KeyReleased && sfEvent.key.code == (*it)->getKey()) // On released
		{
			if ((*it)->onReleased())
			{
				m_pScoreController->modifyScore(*it);
				GameLetter* gameLetter = *it;
				it = m_vGameLetters.erase(it);
				this->letterReleasedAnimation(true, gameLetter);
				if (m_vGameLetters.size() != 0)
				{
					it = m_vGameLetters.begin();
				}
				else
				{
					break;
				}
			}
			else
			{
				m_pScoreController->modifyHealth(-1);
				GameLetter* gameLetter = *it;
				it = m_vGameLetters.erase(it);
				this->letterReleasedAnimation(false, gameLetter);
				if (m_vGameLetters.size() != 0)
				{
					it = m_vGameLetters.begin();
				}
				else
				{
					break;
				}
			}
		}
	}
}

bool GameLetterManager::update(const sf::RenderWindow& window)
{
	if (m_pScoreController->getHealth() <= 0) // if the health is 0 then return true to trigger a change in GameScreen
	{
		// stuff gets reset via reset() which is called in GameScreen
		return true;
	}

	for (std::vector<GameLetter*>::const_iterator it = m_vGameLetters.begin(); it != m_vGameLetters.end(); ++it)
	{
		if ((*it)->checkIdle())
		{
			m_pScoreController->modifyHealth(-1);
			GameLetter* gameLetter = *it;
			this->letterReleasedAnimation(false, gameLetter);
			it = m_vGameLetters.erase(it);
			break; // check to see if breaking causes some keys not to be picked up, if that is the case then just make a bool that checks whether it was broken or not and restart the iteration if it has;
		}

		(*it)->update();
	}

	for (std::vector<std::pair<sf::Sprite*, std::pair<sf::Clock*, bool*>>>::const_iterator it = m_vLetterDones.begin(); it != m_vLetterDones.end(); ++it)
	{
		sf::Sprite& sprite = *(*it).first;
		sf::Clock& clock = *(*it).second.first;
		bool& isRestarted = *(*it).second.second;

		if (!isRestarted)
		{
			clock.restart();
			isRestarted = true;
		}

		if (sprite.getScale().x > 0)
		{
			float i = clock.getElapsedTime().asMilliseconds();
			float j = i / m_fLetterDoneTimer;
			sprite.setScale(1 - j, 1 - j);
		}
		else
		{
			it = m_vLetterDones.erase(it);
			break;
		}
	}

	return false;
}

void GameLetterManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_pScoreController);

	for (std::vector<GameLetter*>::const_iterator it = m_vGameLetters.begin(); it != m_vGameLetters.end(); ++it)
	{
		target.draw(**it);
	}

	for (std::vector<std::pair<sf::Sprite*, std::pair<sf::Clock*, bool*>>>::const_iterator it = m_vLetterDones.begin(); it != m_vLetterDones.end(); ++it)
	{
		target.draw(*it->first);
	}
}