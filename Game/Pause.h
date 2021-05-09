#pragma once
#include "GameState.h"


class Pause : public GameState
{	
	//Pause state, pushed to the states stack when P pressed 
	//
	// inherited protected vars:
	// sf::Event gameEvent;
	// StateManager* stateMan;
	// AssetsManager* assetsMan;
	// sf::RenderWindow* window;


	sf::Sprite lastFrameSprite;
	sf::Sprite backSprite;
	sf::Sprite replayButton;
	

	sf::Text pausedText;
	sf::Text toUnpauseText;

	sf::Clock blinkTimer;
	bool replayHover;


	void initTexts();
public:
	Pause(StateManager* stateMan,AssetsManager * assetsMan, sf::RenderTexture* lastFrame);
	~Pause() {};
	void render();
	void update();
	void handleInput();
};

