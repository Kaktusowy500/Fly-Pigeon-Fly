#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class Mail : public Object
{
	// Bonus object, player gets extra points when picked 

	int points;
public:
	Mail(sf::Texture* texture, float xPos, float yPos, int points = 50, float widthScale=1, float heightScale=1);
	~Mail();
	int getPoints();


};

