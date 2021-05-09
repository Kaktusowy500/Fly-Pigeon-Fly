#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>
#include <typeinfo>
#include "GameState.h"

class Player;
class guiManager;
class stateManager;
class Mail;
class Obstacle;
class Object;

class Game:public GameState
{	
	// Game state, controls game object spawning, deleting and colliding
	//
	// inherited protected vars:
	// sf::Event gameEvent;
	// StateManager* stateMan;
	// AssetsManager* assetsMan;
	// sf::RenderWindow* window;

	std::unique_ptr<Player> player;

	//	obstacles params
	int obsHeight; //useful height
	int spaceBtw; //space between obstacles
	int nObst; // number of obstacles
	int maxObst; //max number of obstacles

	//colliding objects(obstacles and mails) - for RTTI practice
	std::vector<std::unique_ptr<Object>> objects;

	//texture for content rendering, passed to GameOver and Pause states
	std::unique_ptr<sf::RenderTexture> screenTexture;
	
	//background
	std::vector<sf::Sprite> backgrounds;
	float backgroundMovementSpeed;

	//scores
	unsigned int points;
	unsigned int highscore;

	bool gameEnd;

	std::unique_ptr<guiManager> guiMan;


	void initVars();
	void initBackground();
	void initObjects();

	void highscoreCheck();
	void spawner();

	void updateCollision();
	void updateObjects();
	void updateBackground();

public:

	Game(StateManager *stateMan, AssetsManager  * assetsMan);
	~Game();
	void render();
	void update();
	void handleInput();
};

