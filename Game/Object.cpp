#include "Object.h"

Object::Object(sf::Texture* texture, float x, float y, float widthScale, float heightScale)
{	
	sprite.setTexture(*texture);
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setScale(sf::Vector2f(widthScale, heightScale));
	movementSpeed = 3;
}

Object::~Object()
{

}

sf::FloatRect Object::getBounds()const
{
	sf::FloatRect col = sprite.getGlobalBounds();
	return col;
}

void Object::update()
{
	sprite.move(-movementSpeed, 0);
}

void Object::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}