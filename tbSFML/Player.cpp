#include "Player.h"


Player::Player( float startX, float startY, sf::Texture& texture)
{
	/*_sprite = sprite;*/   
	
	
	/*_speed = speed;
	_direction = direction;*/
    

    _sprite.setTexture(texture);
    

    /*_direction.x = 1;
    _direction.y = 1;*/

    _speed.x = 5.0f;
    _speed.y = 5.0f;
}
void Player::UpdatePlayer()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _position.x -= _speed.x;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _position.x += _speed.x;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        _position.y -= _speed.y;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _position.y += _speed.y;
    }

    _sprite.setPosition(_position);
}

void Player::DetectCollision(int winWidth, int winHeight)
{
   

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

bool isHorisontalMovementLocked;
bool isVerticalMovementLocked;
void Player::UpdateImage()
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

   /* if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        _direction.y = -1;
        _position.y -= _speed.y;

        isHorisontalMovementLocked = false; 
        isVerticalMovementLocked = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
    {
        _direction.y = 1;
        _position.y += _speed.y;
        isHorisontalMovementLocked = false;
        isVerticalMovementLocked = true;    
    }*/

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
   
   //Fråga Jonas för tips om hur man får spriten att fortsätta röra sig ett håll efter att ha tryckt knappen en gång
    
   
  
   
    
    
}

void Player::Draw(sf::RenderWindow& win) const
{
    win.draw(_sprite);
}
