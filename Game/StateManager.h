#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include <iostream>
#include <stack>
#include <memory>

class GameState;

class StateManager
{
	//Controls game states, manages the stack with them, creates aplication window

	sf::VideoMode videoMode;
	std::stack<std::unique_ptr<GameState>> states;
	std::unique_ptr<sf::RenderWindow> window;

public:
	StateManager();
	~StateManager();

	// stack manipulation methods
	void pushState(std::unique_ptr<GameState> state);
	void popState();
	void changeState(std::unique_ptr<GameState> state);

	GameState * getState();
	sf::RenderWindow * getWindow();

	// main game loop, updates state which is on the top of the stack
	void gameLoop();
};

