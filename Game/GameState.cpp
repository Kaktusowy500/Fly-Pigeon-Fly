#include "GameState.h"
#include "StateManager.h"
#include "AssetsManager.h"


GameState::GameState(StateManager* stateMan, AssetsManager * assetsMan)
{
	this->stateMan = stateMan;
	this->window = stateMan->getWindow();
	this->assetsMan = assetsMan;
}

void GameState::handleInput()
{
	while (window->pollEvent(gameEvent))
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
}
