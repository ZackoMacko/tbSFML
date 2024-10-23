#pragma once
#include "GameObject.h"


class Player : public GameObject
{
public:
	//Players konstruktor
	Player( float startX, float startY, sf::Texture& texture);
	sf::Vector2f _speed;
	sf::Vector2f _direction;
	sf::CircleShape _shape;
	

	void DetectCollision(int winWidth, int winHeight);
	void UpdatePlayer();
	void UpdateImage();
	void Draw(sf::RenderWindow& win)const;
};



