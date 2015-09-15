#include "TutorialScreen.h"

TutorialScreen::TutorialScreen(std::string sFileName, sf::RenderWindow* window, ScoreController* scoreController)
: Screen(sFileName, window)
{
	m_tTutorialSheet = TextureManager::getInstance().getTexRef("TutorialSheet");
	m_iTutSheetXFrames = 5;
	m_iTutSheetYFrames = 4;
	m_iCurrentXFrame = 0;
	m_iCurrentYFrame = 0;
	m_isCurrentScreen = false;

	m_pScoreController = scoreController;
	m_texSpawnRect = TextureManager::getInstance().getTexRef("TutorialSpawnRect");

	sf::Sprite tmp;
	tmp.setTexture(m_texSpawnRect);
	tmp.setOrigin(m_texSpawnRect.getSize().x / 2, m_texSpawnRect.getSize().y / 2);
	tmp.setPosition(window->getSize().x / 2, window->getSize().y / 2);
	m_GameLetterManager = new GameLetterManager(tmp, m_pScoreController);
	m_GameLetterManager->setMaxLetterCap(1);
	m_GameLetterManager->setIsTut(true);
	
	m_bDrawTip = false;
	m_sText = "";
	m_sfFont = TextureManager::getInstance().getFontRef("Pixel");

	m_iSpawnTime = 2;
}

void TutorialScreen::sheetAnimationUpdate()
{
	if (m_AnimationClock.getElapsedTime().asSeconds() >= 1)
	{
		if (m_iCurrentXFrame < m_iTutSheetXFrames - 1)
		{
			m_iCurrentXFrame++;
		}
		else if (m_iCurrentYFrame == m_iTutSheetYFrames - 1)
		{
			m_iCurrentXFrame = 0;
			m_iCurrentYFrame = 0;
		}
		else
		{
			m_iCurrentXFrame = 0;
			m_iCurrentYFrame++;
		}
		m_AnimationClock.restart();
	}
}

std::string TutorialScreen::handleEvents(sf::Event sfEvent)
{
	// This is for the functionHandler
	std::string s = Screen::handleEvents(sfEvent);
	if (s != "")
	{
		this->functionHandler(s);
	}

	m_GameLetterManager->handleEvents(sfEvent);

	return ""; // not really used for anything...
}

void TutorialScreen::functionHandler(std::string sFunctionName)
{
	if (sFunctionName == "")
	{

	}
	else if (sFunctionName == "start")
	{
		m_isCurrentScreen = false;
		m_GameLetterManager->reset();
		Screen::changeScreen(3, 0); // play screen
	}
	else if (sFunctionName == "back")
	{
		m_isCurrentScreen = false;
		m_GameLetterManager->reset();
		Screen::changeScreen(0, 0);
	}
	else if (sFunctionName == "ESCAPE")
	{
		m_isCurrentScreen = false;
		m_GameLetterManager->reset();
		Screen::changeScreen(2, 0);
	}
}

void TutorialScreen::update(const sf::RenderWindow& window)
{
	if (!m_isCurrentScreen)
	{
		m_isCurrentScreen = true;
		SoundManager::getInstance().playBGMusic("Rhino_Menu");
		m_AnimationClock.restart();
		m_iCurrentXFrame = 0;
		m_iCurrentYFrame = 0;
		m_GameLetterManager->setMaxLetterCap(1);
		BackgroundController::getInstance().startSpawning();
	}

	//this->sheetAnimationUpdate();

	if (m_clockSpawn.getElapsedTime().asSeconds() > m_iSpawnTime)
	{
		std::string s = "b";
		while (s == "b" || s == "s")
		{
			s = AlphabetResource::getInstance().getLowerCase(m_Random.generateInt(0, 25));
		}
		m_GameLetterManager->spawnTutLetter(s, 0 + 150, m_texSpawnRect.getSize().y / 2, 9000, 5000, 10000);
		m_clockSpawn.restart();
	}

	if (m_GameLetterManager->getAmountOfLetters() == 1)
	{
		m_clockSpawn.restart();
		m_bDrawTip = false;
	}
	else
	{
		m_bDrawTip = true;
		if (m_GameLetterManager->getReleasedCorrect())
		{
			m_sText = "Good work Captain!";
			m_GameLetterManager->setReleasedCorrect(false);
		}
		else if (m_GameLetterManager->getReleasedEarly())
		{
			m_sText = "Hold on a little longer";
			m_GameLetterManager->setReleasedEarly(false);
		}
		else if (m_GameLetterManager->getWentIdle())
		{
			m_sText = "Red lines mean bad times";
			m_GameLetterManager->setWentIdle(false);
		}
	}

	m_GameLetterManager->update(window);
	Screen::update(window);
}

void TutorialScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// draw tutorial window
	/*
	sf::Sprite tut;
	float width = m_tTutorialSheet.getSize().x / m_iTutSheetXFrames;
	float height = m_tTutorialSheet.getSize().y / m_iTutSheetYFrames;
	tut.setTexture(m_tTutorialSheet);
	tut.setTextureRect(sf::IntRect(m_iCurrentXFrame * width, m_iCurrentYFrame * height, width , height));
	tut.setOrigin(width / 2, height / 2);
	tut.setPosition(target.getSize().x / 2, target.getSize().y / 2);
	target.draw(tut);
	*/

	// draw spawn rect
	sf::Sprite rect;
	rect.setTexture(m_texSpawnRect);
	rect.setOrigin(m_texSpawnRect.getSize().x / 2, m_texSpawnRect.getSize().y / 2);
	rect.setPosition(target.getSize().x / 2, target.getSize().y / 2);
	target.draw(rect);

	// draw advice tip thing
	if (m_bDrawTip)
	{
		sf::Text text;
		text.setFont(m_sfFont);
		text.setString(m_sText);
		text.setCharacterSize(75);
		text.setColor(sf::Color::White);
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(target.getSize().x / 2, target.getSize().y / 2 + 135);
		target.draw(text);
	}

	// draw letters
	target.draw(*m_GameLetterManager);

	// draw elements in .txt file (gametext start)
	Screen::draw(target, states);
}