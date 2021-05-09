#include "guiManager.h"


void guiManager::showBonus(unsigned int extraPoints =50)
{
	bonusTimer = bonusTime;
	std::stringstream ss;
	ss << "+" << extraPoints;
	bonusText.setString(ss.str());
	
}

guiManager::guiManager(sf::Font* const font, sf::Texture* const  mailTexture)
{	
	
	bonusTime = 60;
	bonusTimer = 0;
	
	//init texts
	scoreText.setFont(*font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(sf::Vector2f(10, 0));
	scoreText.setString("0");

	bonusText.setFont(*font);
	bonusText.setCharacterSize(22);
	bonusText.setFillColor(sf::Color::Green);

	
	//init bonus info
	mailSprite.setTexture(*mailTexture);
	mailSprite.setScale(0.9, 0.9);
	sf::FloatRect scoreTextBounds = scoreText.getGlobalBounds();
	mailSprite.setPosition(30, scoreTextBounds.top + scoreTextBounds.height*1.5);
	sf::FloatRect mailSpriteBounds = mailSprite.getGlobalBounds();
	bonusText.setPosition(mailSpriteBounds.left + mailSpriteBounds.width, mailSpriteBounds.top);

	
}

guiManager::~guiManager()
{
}

void guiManager::update(const unsigned int & points)
{	
	std::stringstream ss;
	ss << "Points: " << points;
	scoreText.setString(ss.str());
	if (bonusTimer > 0)
		bonusTimer--;
	
	
}

void guiManager::render(sf::RenderTarget* target, const unsigned int &  points )
{
	target->draw(scoreText);
	if (bonusTimer > 0) {
		target->draw(bonusText);
		target->draw(mailSprite);
	}


}
