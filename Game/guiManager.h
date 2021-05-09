#pragma once
#include<SFML/Graphics.hpp>
#include<sstream>



class guiManager
{
	// On screen display manager for Game state, shows points and bonuses

	sf::Text scoreText;
	sf::Text bonusText;
	sf::Sprite mailSprite;

	
	size_t bonusTimer;
	size_t bonusTime;
	

public:

	guiManager(sf::Font* const font, sf::Texture* const  mailTexture);
	~guiManager();
	
	void showBonus(unsigned int extraPoints);
	void update(const unsigned int& points);
	void render(sf::RenderTarget* target, const unsigned int& points);
};

