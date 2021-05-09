#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class Obstacle: public Object
{	
	// Obstacle(chimney) - game ends when collided by player
public:
	Obstacle(sf::Texture* texture, float xPos, float yPos, float widthScale = 2, float heightScale = 2);//position (left top corner cords)
	~Obstacle();
	sf::FloatRect getBounds()const override;
};

