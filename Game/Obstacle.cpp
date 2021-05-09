#include "Obstacle.h"


Obstacle::Obstacle(sf::Texture* texture, float xPos, float yPos, float widthScale, float heightScale): Object(texture, xPos, yPos, widthScale, heightScale)
{
}

Obstacle::~Obstacle()
{

}

sf::FloatRect Obstacle::getBounds()const
{
	sf::FloatRect col = Object::getBounds();
	col.left += 0.04 * col.width;
	col.width -= 0.08 * col.width;
	return col;
}
