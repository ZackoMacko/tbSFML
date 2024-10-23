#pragma once
#include <SFML/Graphics.hpp>


class GameObject
{
public:
	//GameObject(sf::Sprite sprite, sf::Vector2f position, sf::RectangleShape boundingBox);
	GameObject()
	{

	}
	
		sf::Sprite _sprite;
		sf::Vector2f _position;
		sf::RectangleShape _boundingBox;

	void Draw();
	void Update();
};

