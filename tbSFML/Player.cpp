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

bool moveLeft;
bool moveRight;
void Player::UpdateImage()
{
   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _direction.x = -1;
        _position.x -= _speed.x;        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
    {         
        _direction.x = 1;
        _position.x += _speed.x;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        _direction.y = -1;
        _position.y -= _speed.y;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
    {
        _direction.y = 1;
        _position.y += _speed.y;
       
    }
   
   //Fråga Jonas för tips om hur man får spriten att fortsätta röra sig ett håll efter att ha tryckt knappen en gång
    
   
    _sprite.move(_position);
   
    
    
}

void Player::Draw(sf::RenderWindow& win) const
{
    win.draw(_sprite);
}
