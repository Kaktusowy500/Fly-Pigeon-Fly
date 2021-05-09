#include "Game.h"
#include "Player.h"
#include "guiManager.h"
#include "GameOverSt.h"
#include "Pause.h"
#include "StateManager.h"
#include "AssetsManager.h"
#include "Mail.h"
#include "Obstacle.h"

	

void Game::initVars()
{
	gameEnd = false;
	obsHeight = 290;//useful height, total = 300
	spaceBtw = 180;
	nObst = 0;
	maxObst = 6;
	points = 0;
	highscore = 0;
	backgroundMovementSpeed = -0.5;
	player.reset(new Player(assetsMan->getTexture("pigeonSheet"), 50, 250));
	guiMan.reset(new guiManager(assetsMan->getFont("joyMono"), assetsMan->getTexture("mail")));
	screenTexture.reset(new sf::RenderTexture());
	screenTexture->create(800, 600);

	std::string highscoreFileName = "Saves/highscore.txt";

	std::ifstream file(highscoreFileName);
	if (file >> highscore)
		file.close();
	else
		throw std::invalid_argument("Cannot read file " + highscoreFileName);
}


void Game::initBackground()
{
	int i = 0;
	int backWidth = 860;
	do {
		sf::Sprite bck;
		bck.setTexture(*assetsMan->getTexture("background"));
		bck.setScale(2, 2);
		bck.setPosition(i * backWidth, 0);
		backgrounds.push_back(bck);
		i++;
	} while (backWidth * i < 2 * screenTexture->getSize().x );
}



void Game::initObjects()
{
	for(; nObst<maxObst; nObst+=2){
		int shift = rand() % 150 + 10;//10 to 159
		objects.push_back(std::make_unique<Obstacle>(assetsMan->getTexture("chimney"), nObst/2 * 300 + 800, -shift));
		objects.push_back(std::make_unique<Obstacle>(assetsMan->getTexture("chimney"), nObst/2 * 300 + 800, (obsHeight - shift + spaceBtw)));

	}
}

Game::Game(StateManager * stateMan, AssetsManager * assetsMan): GameState(stateMan, assetsMan)
{	
	
	//ORDER!
	initVars();
	initObjects();
	initBackground();
}

Game::~Game()
{
}


void Game::highscoreCheck()
{
	if (points > highscore) {
		highscore = points;
		std::ofstream file("Saves/highscore.txt");
		if (file) {
			file << highscore;
			file.close();
		}


	}

}

void Game::spawner()
{
	while(nObst < maxObst){
		int shift = rand() % 150 + 10;//10 to 159
		objects.push_back(std::make_unique<Obstacle>(assetsMan->getTexture("chimney"), 842, -shift));
		objects.push_back(std::make_unique<Obstacle>(assetsMan->getTexture("chimney"), 842, (obsHeight - shift + spaceBtw)));
		nObst+=2;
		//spawns mail
		if (!int(rand() % 2))
			objects.push_back(std::make_unique<Mail>(assetsMan->getTexture("mail"),842 + 150, obsHeight+(rand()%200 -100)));
	
	}
}


void Game::render()
{
	screenTexture->clear();

	for (auto& bck : backgrounds) 
		screenTexture->draw(bck);

	for (auto &obj : objects) 
		obj->render(screenTexture.get());

	player->render(screenTexture.get());

	//gui render
	guiMan->render(screenTexture.get(), points);
	
	//draw on Texture- ready to pass or show on window
	screenTexture->display();

	//if game end load game over screen
	if(gameEnd)
		stateMan->changeState(std::make_unique<GameOverSt>(stateMan, assetsMan, move(screenTexture), points, highscore));
	else {
		window->clear();//clear old frame
		window->draw(sf::Sprite(screenTexture->getTexture()));
		window->display();
	}
	
}


void Game::updateCollision()
{
	const sf::FloatRect plBounds = player->getBounds();//player's global bounds
	//check only top and bottom of window
	if (plBounds.top <= 0 || plBounds.top + plBounds.height >= window->getSize().y)
		gameEnd = true;
	

		//check collisions with objects
	for (int i = 0; i < objects.size(); i++) {
		if (plBounds.intersects(objects[i]->getBounds())) {
			if (typeid(*objects[i]) == typeid(Obstacle)) {
				highscoreCheck();
				gameEnd = true;
			}
			else {
				points += dynamic_cast<Mail*>(objects[i].get())->getPoints();
				guiMan->showBonus(dynamic_cast<Mail*>(objects[i].get())->getPoints());
				objects.erase(objects.begin() + i);
			}
		}

	}

}

void Game::updateObjects()
{

	//move objects
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->update();
	}

	//check if out of window
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getBounds().left + objects[i]->getBounds().width < 0) {
			if (typeid(*objects[i]) == typeid(Obstacle))
				nObst--;
			objects.erase(objects.begin() + i);
		}

	}
	
}

void Game::updateBackground()
{
	for (int i = 0; i < backgrounds.size(); i++) {
		float lastPoint = backgrounds[i].getGlobalBounds().left + backgrounds[i].getGlobalBounds().width;
		if (lastPoint < 0) {
			backgrounds[i].setPosition(backgrounds[i].getGlobalBounds().width * (backgrounds.size() - 1), 0);
			backgrounds[i].move(backgroundMovementSpeed, 0);
		}
		backgrounds[i].move(backgroundMovementSpeed, 0);
	}
}



void Game::update()
{
	
	if (!gameEnd) {
		points++;

		//spawners
		spawner();


		//updaters
		updateBackground();
		updateObjects();
		guiMan->update(points);
		player->update();
		updateCollision();
		
	}
	
}

void Game::handleInput()
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
			if (gameEvent.key.code == sf::Keyboard::P)
				//push pause state, pass last screen texture pointer
				stateMan->pushState(std::make_unique<Pause>(stateMan, assetsMan, screenTexture.get()));
			break;
		}

	}
	

}


