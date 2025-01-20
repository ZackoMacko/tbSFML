#include "Player.h"
#include <list>


bool isHorisontalMovementLocked= false;
bool isVerticalMovementLocked= false;

Player::Player( float startX, float startY, sf::Texture& texture)
{
    _sprite.setTexture(texture);
    _speed.x = 50.0f;
    _speed.y = 50.0f;
    _position.x = startX;
    _position.y = startY;
    _isVerticalMovementLocked = isVerticalMovementLocked;
    _isHorisontalMovementLocked = isHorisontalMovementLocked;
}

std::vector<sf::Vector2f> Player:: RecentPositions(Player& playerHead, std::vector<Player>& playerParts, std::vector<sf::Vector2f>& positionQueue)
{
    
    positionQueue.push_back(playerHead._position);
    
    
    //�ndra +2 till +1
    if (positionQueue.size() > playerParts.size() +1)
    {
        positionQueue.erase(positionQueue.begin() );
        
    }
    
    
    return positionQueue;
}

void Player::UpdateBody( Player &playerHead, std::vector<Player>& playerParts, std::vector<sf::Vector2f>& positionQueue,int& i)
{
    //N�r huvudet kolliderar med ett �pple och f�r en ny del av sin krop antar den positionen av huvudet
    //Fr�ga Jonas hur man kan l�sa s� att ormens kropp inte anv�nder huvudets position n�r ett �pple �ts
  
    if (playerParts[i]._position!=playerHead._position)
    {
        playerParts[i]._sprite.setPosition(playerParts[i]._position);
        playerParts[i]._position = positionQueue[i];
    }
   
}

bool Player::DetectWallCollision(int winWidth, int winHeight)
{
   //To-do: N�r du har implementerat en game over screen ska denna metod returnera en true/false, bool.

    if (_position.x > winWidth - _sprite.getTextureRect().width)
    {
      
      /*  _position.x = float(winWidth - _sprite.getTextureRect().width);*/
        return true;
    }
    else if (_position.x < 0)
    {
       
    /*    _position.x = 0;*/
        return true;
    }

    if (_position.y > winHeight - _sprite.getTextureRect().height)
    {
        
       /* _position.y = float(winHeight - _sprite.getTextureRect().height);*/
        return true;
    }
    else if (_position.y < 0)
    {
        
        /*_position.y = 0;*/
        return true;
    }

    _sprite.setPosition(_position);
    return false;


}

bool Player::SnakeToSnakeCollision(std::vector<Player>& playerParts, Player& playerHead,std::vector<sf::Vector2f>& positionQueue)
{
    //Om du hittar en metod f�r att anv�nda deltatime s� att ormen r�r sig 
    //varje 0.2 sekunder.Ta d� bort i>10 h�r
    //Fr�ga Jonas
    for ( unsigned int i = 1; i < playerParts.size(); i++)
    {
        if (playerHead._sprite.getGlobalBounds().intersects(playerParts[i]._sprite.getGlobalBounds()))
        {
            //�ndra till true d� du har fixat problemet
            return true;
           
        }
    }
    return false;
}


void Player::UpdateHead()
{
   
    if (!_isVerticalMovementLocked)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            _direction.y = -1;        
            _isHorisontalMovementLocked = false;
            _isVerticalMovementLocked = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            _direction.y = 1;           
            _isHorisontalMovementLocked = false;
            _isVerticalMovementLocked = true;
        }
    }

   
    if (!_isHorisontalMovementLocked)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {

            _direction.x = -1;
            _isHorisontalMovementLocked = true;
            _isVerticalMovementLocked = false;

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            _direction.x = 1;
            _isHorisontalMovementLocked = true;
            _isVerticalMovementLocked = false;
        }
    }
    
    
    if (_isHorisontalMovementLocked&& _direction.x==-1)
    {

        _position.x -= _speed.x;     
       /* _sprite.move(_position);*/
        _sprite.setPosition(_position);

    }
    else if (_isHorisontalMovementLocked&& _direction.x==1)
    {

        _position.x += _speed.x;
     /*   _sprite.move(_position);*/
        _sprite.setPosition(_position);
    }

    if (_isVerticalMovementLocked && _direction.y == -1)
    {
        _position.y -= _speed.y;
     /*   _sprite.move(_position);*/
        _sprite.setPosition(_position);
    }
    else if (_isVerticalMovementLocked&& _direction.y==1)
    {
        _position.y += _speed.y;
        /*_sprite.move(_position);*/
        _sprite.setPosition(_position);
    }
   
}

void Player::Draw(sf::RenderWindow& win) const
{
    win.draw(_sprite);
}
