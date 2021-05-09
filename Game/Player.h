#pragma once
#include<SFML/Graphics.hpp>

class Player
{
	// Player object- sprite with animation and movement control

	//sprite
	sf::Sprite sprite;
	sf::Texture textureSheet;
	
	//move control
	bool mouseClicked;
	int upMovingTimer;
	int upMoveTime;//in frames
	float movementSpeed;

	//animation elements
	sf::IntRect currentFrame;
	sf::Clock animationTimer;


	void initVars();

	void updateInput();
	void updatePos();
	void updateAnimation();

public:
	Player(sf::Texture*playerTextureSheet, float x = 0, float y = 0);
	~Player();

	//gets bounds and modifies it on the go to limit fake collisions
	const sf::FloatRect& getBounds();

	void update();
	void render(sf::RenderTarget * target);
};

