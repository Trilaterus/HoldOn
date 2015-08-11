#include <SFML/Graphics.hpp>
#include "GameLetter.h"
#include "GameLetterManager.h"
#include "Screen.h"
#include "UIObject.h"
#include "UIImage.h"
#include "ScreenManager.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "UIText.h"
#include "MainMenuScreen.h"
#include "AlphabetResource.h"
#include "OptionsScreen.h"
#include "PlayScreen.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "SoundManager.h"

/*
BUG LIST:

- There is a bug that is hard to reproduce, if you have a letter ready and a letter not ready
and you release them in a certain way sometimes there is a vector issue :S
+++ FIXED, was being an idiot and was trying to use an iterator I had just deleted

- Sometimes letters may go outside of the desired lines, this is probably caused by the overlap
mechanism

- Sometimes the animation for letters after reaching a certain high fill just stops but the clock
are carrying on so you can still drop it properly

- If you go on for too long then the sounds stop playing

*/

int main()
{
	sf::ContextSettings settings;
	//settings.antialiasingLevel = 8;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1280, 800), "Hold On!", sf::Style::Default, settings);

	// Load in textures and fonts and sounds
	TextureManager::getInstance().loadTexture("ImageTest", "assets\\textures\\ui_textures\\image_texture_test.png");
	TextureManager::getInstance().loadTexture("ButtonTest", "assets\\textures\\ui_textures\\button_texture_test.png");
	TextureManager::getInstance().loadTexture("ButtonDefault", "assets\\textures\\ui_textures\\button_texture_default.png");
	TextureManager::getInstance().loadTexture("FillCircle", "assets\\textures\\game_textures\\fill_circle.png");
	TextureManager::getInstance().loadTexture("FillCircleOutline1", "assets\\textures\\game_textures\\fill_circle_outline1.png");
	TextureManager::getInstance().loadTexture("FillCircleOutline2", "assets\\textures\\game_textures\\fill_circle_outline2.png");
	TextureManager::getInstance().loadTexture("CamOutline", "assets\\textures\\game_textures\\game_cam_outline.png");
	TextureManager::getInstance().loadTexture("EndslateBG", "assets\\textures\\game_textures\\game_endslate.png");
	TextureManager::getInstance().loadTexture("DoneLetterTrue", "assets\\textures\\game_textures\\done_letter_outline_true.png");
	TextureManager::getInstance().loadTexture("DoneLetterFalse", "assets\\textures\\game_textures\\done_letter_outline_false.png");

	TextureManager::getInstance().loadFont("Ash", "assets\\fonts\\Ash.ttf");
	TextureManager::getInstance().loadFont("default", "assets\\fonts\\Mixolydian.ttf");
	TextureManager::getInstance().loadFont("GameLetter", "assets\\fonts\\BebasNeue.otf");
	TextureManager::getInstance().loadFont("second", "assets\\fonts\\Handschrift.ttf");
	TextureManager::getInstance().loadFont("M12", "assets\\fonts\\M12.ttf");
	TextureManager::getInstance().loadFont("Faktos", "assets\\fonts\\Faktos.ttf");

	SoundManager::getInstance().loadEffect("ReleaseTrue", "assets\\sounds\\effects\\ReleaseTrue.wav");
	SoundManager::getInstance().loadEffect("LetterFill_1s", "assets\\sounds\\effects\\SpaceDoorOpen_1s.wav");
	SoundManager::getInstance().loadEffect("LetterFill_3s", "assets\\sounds\\effects\\SpaceDoorOpen_3s.wav");
	SoundManager::getInstance().loadEffect("FlareFiring", "assets\\sounds\\effects\\FlareFiring.wav");
	SoundManager::getInstance().loadEffect("ShipExplosion", "assets\\sounds\\effects\\ShipExplosion.wav");

	SoundManager::getInstance().loadMusic("Rhino_Menu", "assets\\sounds\\music\\Rhino_Menu.ogg");
	SoundManager::getInstance().loadMusic("Rhino_Game", "assets\\sounds\\music\\Rhino_Game.ogg");

	// Initialise various managers
	ScreenManager myScreenManager;
	ScoreController* myScoreController = new ScoreController;

	// Initialise Different Screens
	myScreenManager.addScreen(new MainMenuScreen("assets\\screens\\mainmenu.txt", window));
	myScreenManager.addScreen(new OptionsScreen("assets\\screens\\options.txt", window));
	myScreenManager.addScreen(new PlayScreen("assets\\screens\\play.txt", window));
	myScreenManager.addScreen(new GameScreen("assets\\screens\\game.txt", window, myScoreController));
	myScreenManager.addScreen(new GameOverScreen("assets\\screens\\gameover.txt", window, myScoreController));
	myScreenManager.getCurrentScreen()->update(*window);

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			EventManager::getInstance().handleEvents(event, window, myScreenManager);
		}

		window->clear();
		myScreenManager.update(*window);
		window->draw(myScreenManager);
		window->display();
	}

	return 0;
}