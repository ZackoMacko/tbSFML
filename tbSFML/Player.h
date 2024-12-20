#pragma once
#include "GameObject.h"



class Player : public GameObject
{
private:
	/*std::list<Player> _mainBody;
	std::list<Player>::iterator _mainHead;
	std::list<Player>::iterator _mainTail;*/

public:
	//Players konstruktor
	Player(float startX, float startY, sf::Texture& texture);
	~Player() {

	}
	Player() {

	}
	

	sf::Vector2f _speed;
	sf::Vector2f _direction;
	
	
	
	
	bool DetectWallCollision(int winWidth, int winHeight);
	bool SnakeToSnakeCollision(std::vector<Player>& playerParts, Player& playerHead,std::vector<sf::Vector2f>& positionQueue);
	
	std::vector<sf::Vector2f> RecentPositions(Player& playerHead, std::vector<Player>& playerParts, std::vector<sf::Vector2f>& positionQueue);
	void UpdateBody(Player &playerHead,std::vector<Player>& playerParts, std::vector<sf::Vector2f>& positionQueue,int &i);
	void UpdateHead();
	void Draw(sf::RenderWindow& win)const;
};



