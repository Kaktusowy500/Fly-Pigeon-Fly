#include "Menu.h"
#include "Game.h"
#include "StateManager.h"
#include "AssetsManager.h"


void Menu::initSprites()
{
	playButton.setTexture(*assetsMan->getTexture("play"));
	playButton.setPosition(290, 400);
	playButton.setScale(sf::Vector2f(4, 4));

	title.setTexture(*assetsMan->getTexture("title"));
	title.setPosition(-40, 50);
	title.setScale(sf::Vector2f(5.5, 5.5));

	backgroundSprite.setTexture(*assetsMan->getTexture("menuBack"));
}

Menu::Menu(StateManager* stateMan, AssetsManager* assetsMan) :GameState(stateMan, assetsMan)
{
	this->playHover = false;
	this->exitHover = false;
	initSprites();
}

void Menu::handleInput()
{
	while (stateMan->getWindow()->pollEvent(gameEvent))
	{
		switch (gameEvent.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (gameEvent.key.code == sf::Keyboard::Escape)
				window->close();
			break;
		}

	}

	auto mousePosWindow = sf::Mouse::getPosition(*window);
	auto mousePosView = window->mapPixelToCoords(mousePosWindow);

	//check if play button is hovered or clicked, change texture
	if (playButton.getGlobalBounds().contains(mousePosView)) {
		if (!playHover) {
			playButton.setTexture(*assetsMan->getTexture("playHover"));
			playHover = true;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			//start game
			stateMan->changeState(std::make_unique<Game>(stateMan, assetsMan));
		}
	}
	else if (playHover)
	{
		playButton.setTexture(*assetsMan->getTexture("play"));
		playHover = false;
	}


}

void Menu::render()
{

	window->clear();//clear old frame

	window->draw(backgroundSprite);
	window->draw(title);
	window->draw(playButton);

	window->display();
}

