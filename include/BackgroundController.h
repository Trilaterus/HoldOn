#ifndef BACKGROUNDCONTROLLER_H
#define BACKGROUNDCONTROLLER_H

#include "BackgroundManager.h"

class BackgroundController
{
private:
	BackgroundController();
	BackgroundController(BackgroundController const&);
	void operator=(BackgroundController const&);

	BackgroundManager* m_Background;

protected:

public:
	static BackgroundController& getInstance();
	void bindToBackground(BackgroundManager* background);

	BackgroundManager* getBackground();
	int getMoveSpeed();
	void changeMoveSpeed(int iValue);
	void clearStars();
	void stopSpawning();
	void startSpawning();

	void update(const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // BACKGROUNDCONTROLLER_H