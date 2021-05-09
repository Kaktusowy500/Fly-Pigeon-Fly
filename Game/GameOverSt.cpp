#include "GameOverSt.h"
#include "Game.h"
#include "StateManager.h"
#include "AssetsManager.h"

void GameOverSt::initSprites()
{
	

	replayButton.setTexture(*assetsMan->getTexture("replay"));
	replayButton.setPosition(290, 400);
	replayButton.setScale(sf::Vector2f(4, 4));

	scoreBack.setTexture(*assetsMan->getTexture("infoBack"));
	scoreBack.setPosition(200, 50);
	scoreBack.setScale(sf::Vector2f(10, 10));
}

void GameOverSt::initTexts()
{
	gameScoreText.setFont(*assetsMan->getFont("joyMono"));
	gameScoreText.setFillColor(sf::Color::Black);
	gameScoreText.setCharacterSize(30);
	gameScoreText.setPosition(sf::Vector2f(280, 180));

	gameOverText.setFont(*assetsMan->getFont("joyMono"));
	gameOverText.setFillColor(sf::Color::Black);
	gameOverText.setCharacterSize(35);
	gameOverText.setPosition(sf::Vector2f(270, 100));
	gameOverText.setString("GAME OVER");
}

GameOverSt::GameOverSt(StateManager* stateMan, AssetsManager * assetsMan, std::unique_ptr<sf::RenderTexture> lastFrame, const unsigned int& points, const unsigned int& highscore): GameState(stateMan, assetsMan)
{
	this->points = points;
	this->highscore = highscore;
	this->lastFrame = move(lastFrame);// holds texture for sprite(last frame from gameplay
	this->lastFrameSprite = sf::Sprite(this->lastFrame->getTexture());
	this->replayHover = false;
	initSprites();
	initTexts();

	
	 
	
}


void GameOverSt::handleInput()
{
	while(stateMan->getWindow()->pollEvent(gameEvent))
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

	//check if replay button is hovered or clicked
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

void GameOverSt::render()
{
	window->clear();//clear old frame
	std::stringstream ss;
	ss << "Score: \n" << points << "\n\nHighscore: \n" << highscore;
	gameScoreText.setString(ss.str());

	window->draw(lastFrameSprite);
	window->draw(scoreBack);
	window->draw(gameOverText);
	window->draw(gameScoreText);
	window->draw(replayButton);

	window->display();
	
}


