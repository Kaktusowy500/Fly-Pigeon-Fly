#pragma once
#include<SFML/Graphics.hpp>




class StateManager;
class AssetsManager;

class GameState
{
// Abstract base class for all game states,
// holds pointers to window, assets manager and state manager

protected:  
    sf::Event gameEvent;
    StateManager* stateMan;
    AssetsManager* assetsMan;
    sf::RenderWindow* window;

public:
    GameState(StateManager* stateMan, AssetsManager * assetMan);
    ~GameState() {};

    virtual void render() = 0;
    virtual void update() = 0;

    // default event handler
    virtual void handleInput();
};
