#include "Pause.h"
#include "Game.h"
#include "StateManager.h"
#include "AssetsManager.h"




void Pause::initTexts()
{
	pausedText.setFont(*assetsMan->getFont("joyMono"));
	pausedText.setFillColor(sf::Color::Black);
	pausedText.setCharacterSize(35);
	pausedText.setPosition(sf::Vector2f(330, 100));
	pausedText.setString("Pause");

	toUnpauseText.setFont(*assetsMan->getFont("joyMono"));
	toUnpauseText.setFillColor(sf::Color::Black);
	toUnpauseText.setCharacterSize(25);
	toUnpauseText.setPosition(sf::Vector2f(290, 200));
	toUnpauseText.setString("  Press P\nto unpause");
}

Pause::Pause(StateManager* stateMan, AssetsManager* assetsMan, sf::RenderTexture* lastFrame):GameState(stateMan, assetsMan)
{
	
	initTexts();
	lastFrameSprite.setTexture(lastFrame->getTexture());
	
	backSprite.setTexture(*assetsMan->getTexture("infoBack"));
	backSprite.setPosition(200, 50);
	backSprite.setScale(sf::Vector2f(10, 10));

	replayButton.setTexture(*assetsMan->getTexture("replay"));
	replayButton.setPosition(290, 400);
	replayButton.setScale(sf::Vector2f(4, 4));

	

}


void Pause::render()
{
	//order sensitive!
	window->clear();//clear old frame
	window->draw(lastFrameSprite);
	window->draw(backSprite);
	window->draw(replayButton);
	window->draw(pausedText);
	window->draw(toUnpauseText);

	window->display();


}

void Pause::update()
{
	if (blinkTimer.getElapsedTime().asMilliseconds() > 800)
	{
		if (toUnpauseText.getFillColor() == sf::Color::Black)
			toUnpauseText.setFillColor(sf::Color::Transparent);
		else
			toUnpauseText.setFillColor(sf::Color::Black);
		blinkTimer.restart();
	}
}

void Pause::handleInput()
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
			if (gameEvent.key.code == sf::Keyboard::P) {
				//return to game
				stateMan->popState();
				return;
			}
			break;
		}
		
	}
	auto mousePosWindow = sf::Mouse::getPosition(*window);
	auto mousePosView = window->mapPixelToCoords(mousePosWindow);

	if (replayButton.getGlobalBounds().contains(mousePosView)) {
		if (!replayHover) {
			replayButton.setTexture(*assetsMan->getTexture("replayHover"));
			replayHover = true;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

			stateMan->changeState(std::make_unique<Game>(stateMan, assetsMan));
		}
	}
	else if (replayHover)
	{
		replayButton.setTexture(*assetsMan->getTexture("replay"));
		replayHover = false;
	}

	
}
