#pragma once
#include<SFML/Graphics.hpp>


class Object
{	
	//	General class for game objects like obstacles and bonuses

	sf::Sprite sprite;
	float movementSpeed;
public:
	Object(sf::Texture* texture,  float x = 400, float y = 400, float widthScale =1.2, float heightScale =1.2);//position (left top corner cords)
	virtual ~Object();
	virtual sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget* target);
};
