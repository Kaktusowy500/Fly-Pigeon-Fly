#include "Player.h"

void Player::updateInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
		if (!mouseClicked && upMovingTimer <= 0) {
			upMovingTimer = upMoveTime;
			mouseClicked = true;
		}
		
	}
	else {
		mouseClicked = false;
	}
	


}

void Player::updatePos()
{
	if (upMovingTimer > 0)
		sprite.move(0, -1.6*movementSpeed);//up
	else
		sprite.move(0, 1.3*movementSpeed);//down
	upMovingTimer--;
}

void Player::initVars()
{
	mouseClicked = true;
	//moving params
	upMovingTimer = 0;
	upMoveTime = 22;
	movementSpeed = 3;
}



Player::Player(sf::Texture* playerTextureSheet, float x, float y)
{
	initVars();
	sprite.setTexture(*playerTextureSheet);
	currentFrame = sf::IntRect(0, 0, 55, 40);//takes part of texture(one of 7) - first state of animation
	sprite.setTextureRect(currentFrame);
	sprite.setPosition(x,y);
	sprite.setScale(sf::Vector2f(1.2, 1.2));
	//animation init
	animationTimer.restart();
	
}

Player::~Player()
{

}

const sf::FloatRect& Player::getBounds()
{
	sf::FloatRect col = sprite.getGlobalBounds();
	col.left += 0.15 * col.width;
	col.width -= 0.25 * col.width;
	col.top += 0.1 * col.height;
	col.height -= 0.2 * col.height;
	return col;
}

void Player::updateAnimation()
{
	if (animationTimer.getElapsedTime().asMilliseconds() >= 75) {
		if (upMovingTimer > 0) {
			currentFrame.left += 55;
			if (currentFrame.left >= 330)
				currentFrame.left = 0;
		}
		else
			currentFrame.left = 0;

		animationTimer.restart();
		sprite.setTextureRect(currentFrame);
	}
}



void Player::update()
{
	updateInput();
	updatePos();
	updateAnimation();
	

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
