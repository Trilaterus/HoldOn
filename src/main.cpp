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
#include "BackgroundManager.h"
#include "BackgroundController.h"
#include "TutorialScreen.h"

/*
--- THIS VERSION HAS DIFFICULTY SIMILAR TO A THOUSAND HANDS ---

BUG LIST:

- There is a bug that is hard to reproduce, if you have a letter ready and a letter not ready
and you release them in a certain way sometimes there is a vector issue :S
+++ FIXED, was being an idiot and was trying to use an iterator I had just deleted

- Sometimes letters may go outside of the desired lines, this is probably caused by the overlap
mechanism

- Sometimes the animation for letters after reaching a certain high fill just stops but the clock
are carrying on so you can still drop it properly
+++ FIXED, added a buffer to the completion detection

- On pressing again the bg game music doesn't play
+++ FIXED, was an issue with SoundManager::playBGMusic()

- If you go on for too long then the sounds stop playing
+++ FIXED, look at SoundManager::playSound() for details, TL;DR make sure to use function 'delete'
if you use function 'new' somewhere;

- rand seemed to stop spawning, maybe the bool for checking it is broken? or maybe not enough time
between waves for it to appear
+++ FIXED by changing classic mode to not change wave spawn types

- for the early letters the flare firing sound doesnt go off and its really clear that sounds cut
each other off

*/

int main()
{
	sf::ContextSettings settings;
	//settings.antialiasingLevel = 8;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1024, 768), "Hold On!", sf::Style::Close, settings);

	// Load in textures and fonts and sounds
	TextureManager::getInstance().loadTexture("FillCircle", "assets\\textures\\game_textures\\fill_circle.png");
	TextureManager::getInstance().loadTexture("FillCircleOutline1", "assets\\textures\\game_textures\\fill_circle_outline1.png"); // or use outline12 for crosshairs
	TextureManager::getInstance().loadTexture("FillCircleOutline2", "assets\\textures\\game_textures\\fill_circle_outline2.png");
	TextureManager::getInstance().loadTexture("CamOutline", "assets\\textures\\game_textures\\game_cam_outline.png");
	TextureManager::getInstance().loadTexture("EndslateBG", "assets\\textures\\game_textures\\game_endslate.png");
	TextureManager::getInstance().loadTexture("DoneLetterTrue", "assets\\textures\\game_textures\\done_letter_outline_true.png");
	TextureManager::getInstance().loadTexture("DoneLetterFalse", "assets\\textures\\game_textures\\done_letter_outline_false.png");
	TextureManager::getInstance().loadTexture("Spaceship", "assets\\textures\\game_textures\\spaceship.png");
	TextureManager::getInstance().loadTexture("Star", "assets\\textures\\game_textures\\star_3.png");
	TextureManager::getInstance().loadTexture("LetterAlert", "assets\\textures\\game_textures\\alert_crosshair.png");
	TextureManager::getInstance().loadTexture("TutorialSpawnRect", "assets\\textures\\game_textures\\tutorial_outline.png");

	TextureManager::getInstance().loadTexture("TutorialSheet", "assets\\textures\\ui_textures\\tut_sheet_5x4f.png");

	TextureManager::getInstance().loadFont("default", "assets\\fonts\\M12 edited.ttf");
	TextureManager::getInstance().loadFont("second", "assets\\fonts\\M12 edited.ttf");
	TextureManager::getInstance().loadFont("M12", "assets\\fonts\\M12 edited.ttf");
	TextureManager::getInstance().loadFont("Pixel", "assets\\fonts\\Pixeltype.ttf");

	SoundManager::getInstance().loadEffect("ReleaseTrue", "assets\\sounds\\effects\\ReleaseTrue.wav");
	SoundManager::getInstance().loadEffect("LetterFill_1s", "assets\\sounds\\effects\\SpaceDoorOpen_1s.wav");
	SoundManager::getInstance().loadEffect("LetterFill_3s", "assets\\sounds\\effects\\SpaceDoorOpen_3s.wav");
	SoundManager::getInstance().loadEffect("FlareFiring", "assets\\sounds\\effects\\FlareFiring.wav");
	SoundManager::getInstance().loadEffect("ShipExplosion", "assets\\sounds\\effects\\ShipExplosion.wav");
	SoundManager::getInstance().loadEffect("ReleasePerfect", "assets\\sounds\\effects\\ReleasePerfect.wav");
	SoundManager::getInstance().loadEffect("GainedHealth", "assets\\sounds\\effects\\GainedHealth.wav");

	SoundManager::getInstance().loadMusic("Rhino_Menu", "assets\\sounds\\music\\Rhino_Menu.ogg");
	SoundManager::getInstance().loadMusic("Rhino_Game", "assets\\sounds\\music\\Rhino_Game.ogg");

	BackgroundController::getInstance().bindToBackground(new BackgroundManager(window));

	// Initialise various managers
	ScreenManager myScreenManager;
	ScoreController* myScoreController = new ScoreController;

	// Initialise Different Screens --- TENTATIVE CHANGE!!! MOVED TUT SCREEN FIRST OVER MAIN MENU SCREEN
	myScreenManager.addScreen(new MainMenuScreen("assets\\screens\\mainmenu.txt", window));
	myScreenManager.addScreen(new OptionsScreen("assets\\screens\\options.txt", window));
	myScreenManager.addScreen(new PlayScreen("assets\\screens\\play.txt", window));
	myScreenManager.addScreen(new GameScreen("assets\\screens\\game.txt", window, myScoreController));
	myScreenManager.addScreen(new GameOverScreen("assets\\screens\\gameover.txt", window, myScoreController));
	myScreenManager.addScreen(new TutorialScreen("assets\\screens\\tutorial.txt", window, myScoreController));
	myScreenManager.getCurrentScreen()->update(*window);

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			EventManager::getInstance().handleEvents(event, window, myScreenManager);
		}

		window->clear(sf::Color(0, 5, 0, 100)); // makes the background slightly green
		myScreenManager.update(*window);
		BackgroundController::getInstance().update(*window);
		window->draw(*BackgroundController::getInstance().getBackground());
		window->draw(myScreenManager);
		window->display();
	}

	return 0;
}