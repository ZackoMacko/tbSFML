#include "Player.h"
#include <list>

bool isHorisontalMovementLocked;
bool isVerticalMovementLocked;

Player::Player( float startX, float startY, sf::Texture& texture)
{
    _sprite.setTexture(texture);
    _speed.x = 5.0f;
    _speed.y = 5.0f;
    _position.x = startX;
    _position.y = startY;

  

}

std::vector<sf::Vector2f> Player:: RecentPositions(Player& playerHead, std::vector<Player>& playerParts, std::vector<sf::Vector2f>& positionQueue)
{
    
    positionQueue.push_back(playerHead._position);
    
    if (positionQueue.size() > playerParts.size() +1)
    {
        positionQueue.erase(positionQueue.begin() );
    }
    
    return positionQueue;
}

void Player::UpdateBody( Player &playerHead, std::vector<Player>& playerParts, std::vector<sf::Vector2f>& positionQueue, int &i)
{
   
        playerParts[i]._position = positionQueue[i];
        
        if (isHorisontalMovementLocked && playerHead._direction.x == 1)
        {

            playerParts[i]._position.x = playerParts[i]._position.x ;

        }
        else if (isHorisontalMovementLocked && playerHead._direction.x == -1)
        {

            playerParts[i]._position.x = playerParts[i]._position.x ;
        }
        if (isVerticalMovementLocked && playerHead._direction.y == 1)
        {
            playerParts[i]._position.y = playerParts[i]._position.y ;

        }
        else if (isVerticalMovementLocked && playerHead._direction.y == -1)
        {

            playerParts[i]._position.y = playerParts[i]._position.y  ;
        }

               
        playerParts[i]._sprite.setPosition(playerParts[i]._position);
       
   
    
        
    
}

void Player::DetectCollision(int winWidth, int winHeight)
{
   //To-do: När du har implementerat en game over screen ska denna metod returnera en true/false, bool.

    if (_position.x > winWidth - _sprite.getTextureRect().width)
    {
      
        _position.x = float(winWidth - _sprite.getTextureRect().width);
    }
    else if (_position.x < 0)
    {
       
        _position.x = 0;
    }

    if (_position.y > winHeight - _sprite.getTextureRect().height)
    {
        
        _position.y = float(winHeight - _sprite.getTextureRect().height);
    }
    else if (_position.y < 0)
    {
        
        _position.y = 0;
    }

    _sprite.setPosition(_position);


}


void Player::UpdateHead()
{
   
    if (!isVerticalMovementLocked)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _direction.y = -1;        
            isHorisontalMovementLocked = false;
            isVerticalMovementLocked = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _direction.y = 1;           
            isHorisontalMovementLocked = false;
            isVerticalMovementLocked = true;
        }
    }

   
    if (!isHorisontalMovementLocked)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {

            _direction.x = -1;
            isHorisontalMovementLocked = true;
            isVerticalMovementLocked = false;

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _direction.x = 1;
            isHorisontalMovementLocked = true;
            isVerticalMovementLocked = false;
        }
    }
    
    
    if (isHorisontalMovementLocked&& _direction.x==-1)
    {

        _position.x -= _speed.x;     
        _sprite.move(_position);

    }
    else if (isHorisontalMovementLocked&& _direction.x==1)
    {

        _position.x += _speed.x;
        _sprite.move(_position);
    }

    if (isVerticalMovementLocked && _direction.y == -1)
    {
        _position.y -= _speed.y;
        _sprite.move(_position);
    }
    else if (isVerticalMovementLocked&& _direction.y==1)
    {
        _position.y += _speed.y;
        _sprite.move(_position);
    }
   
}

void Player::Draw(sf::RenderWindow& win) const
{
    win.draw(_sprite);
}
