#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

class AssetsManager;
class StateManager;
class Game;

class Menu : public GameState
{	
	// Main menu state
	//
	// inherited protected vars:
	// sf::Event gameEvent;
	// StateManager* stateMan;
	// AssetsManager* assetsMan;
	// sf::RenderWindow* window;

	sf::Sprite playButton;
	sf::Sprite backgroundSprite;
	sf::Sprite title;
	sf::Text titleText;

	bool playHover;
	bool exitHover;


	void initSprites();
public:
	Menu(StateManager* stateMan, AssetsManager* assetsMan);
	~Menu() {};

	void handleInput() override;
	void render() override;
	void update() override {};
};

