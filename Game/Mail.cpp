#include "Mail.h"

Mail::Mail(sf::Texture* texture, float xPos, float yPos, int points, float widthScale , float heightScale) : Object(texture, xPos, yPos, widthScale, heightScale)
{
	this->points = points;
}

Mail::~Mail()
{
}

int Mail::getPoints()
{
	return points;
}
