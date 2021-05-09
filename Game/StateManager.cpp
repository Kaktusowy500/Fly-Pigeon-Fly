#include "StateManager.h"
#include "GameState.h"

void StateManager::pushState(std::unique_ptr<GameState> state)
{
	states.push(move(state));
}

void StateManager::popState()
{
	states.pop();
}

void StateManager::changeState(std::unique_ptr<GameState> state)
{
	if (!states.empty())
		popState();
	states.push(move(state));
}

GameState* StateManager::getState()
{
	if (!states.empty())
		return states.top().get();
	return nullptr;
}

sf::RenderWindow * StateManager::getWindow()
{
	return window.get();
}

void StateManager::gameLoop()
{
	
	srand(static_cast<unsigned>(time(NULL)));

	//Game loop, state on the top of stack is active
	while (window->isOpen()) {
		//state could be changed in any time
		if (getState()) {
			getState()->handleInput();
			
			getState()->update();

			
			getState()->render();
		}
	}
}

StateManager::StateManager()
{
	videoMode = sf::VideoMode(800, 600);
	window.reset(new sf::RenderWindow(videoMode, "Fly, Pigeon, Fly!", sf::Style::Close | sf::Style::Titlebar));//smart pointer
	window->setFramerateLimit(60);
}

StateManager::~StateManager()
{
	while (!this->states.empty()) 
		popState();

}
