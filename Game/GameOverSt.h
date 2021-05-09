#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

class AssetsManager;
class StateManager;

class GameOverSt : public GameState
{	// Game over state, shows score and replay option

	// inherited protected vars:
	// sf::Event gameEvent;
	// StateManager* stateMan;
	// AssetsManager* assetsMan;
	// sf::RenderWindow* window;

	std::unique_ptr<sf::RenderTexture> lastFrame;
	sf::Sprite lastFrameSprite;

	sf::Sprite replayButton;
	sf::Sprite scoreBack;

	sf::Text gameScoreText;
	sf::Text gameOverText;


	bool replayHover;
	unsigned int points; 
	unsigned int highscore;

	void initSprites();
	void initTexts();

public:
	GameOverSt(StateManager* stateMan, AssetsManager* assetsMan, std::unique_ptr<sf::RenderTexture> lastFrame, const unsigned int& points, const unsigned int& highscore);
	~GameOverSt() {};
	void handleInput();
	void render();
	void update() {};

};

