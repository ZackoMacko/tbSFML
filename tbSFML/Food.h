#pragma once
#include "GameObject.h"
#include "Player.h"
class Food: public GameObject
{
public:
	
	sf::Vector2f _size;
	sf::RectangleShape _shape;

	Food(float startX,float startY, float width,sf::Color color);
	
	Food(){
		
	}
	~Food() {

	}
	
	void Update();
	sf::Vector2f ChangePosition(std::vector<sf::Vector2f>& positions);
	std::vector<sf::Vector2f> GeneratePositions(int windowWidth,int windowHeight, sf::Texture texture);
	std::vector<sf::Vector2f> AvailablePositions(Player player, std::vector<sf::Vector2f> &positions);
	bool DetectCollision(Player player);
	void Draw(sf::RenderWindow& win)const;
};

