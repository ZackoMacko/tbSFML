#include "Player.h"
#include <list>

bool isHorisontalMovementLocked;
bool isVerticalMovementLocked;

Player::Player( float startX, float startY, sf::Texture& texture)
{
    _sprite.setTexture(texture);
    _speed.x = 50.0f;
    _speed.y = 50.0f;
    _position.x = startX;
    _position.y = startY;
}

std::vector<sf::Vector2f> Player:: RecentPositions(Player& playerHead, std::vector<Player>& playerParts, std::vector<sf::Vector2f>& positionQueue)
{
    
    positionQueue.push_back(playerHead._position);
    
    
    //ändra +2 till +1
    if (positionQueue.size() > playerParts.size() +1)
    {
        positionQueue.erase(positionQueue.begin() );
        
    }
    
    
    return positionQueue;
}

void Player::UpdateBody( Player &playerHead, std::vector<Player>& playerParts, std::vector<sf::Vector2f>& positionQueue,int& i)
{
    //När huvudet kolliderar med ett äpple och får en ny del av sin krop antar den positionen av huvudet
    //Fråga Jonas hur man kan lösa så att ormens kropp inte använder huvudets position när ett äpple äts
  
    if (playerParts[i]._position!=playerHead._position)
    {
        playerParts[i]._sprite.setPosition(playerParts[i]._position);
        playerParts[i]._position = positionQueue[i];
    }
    /*else
    {
        playerParts[i]._position = positionQueue[i];
    }
    */

    
        
    // if (isHorisontalMovementLocked && playerHead._direction.x == 1)
    // {

    ///*     playerParts[i]._position.x = positionQueue[i].x ;*/

    // }
    // else if (isHorisontalMovementLocked && playerHead._direction.x == -1)
    // {

    //     /*playerParts[i]._position.x = playerParts[i]._position.x ;*/
    // /*    playerParts[i]._position.x = positionQueue[i].x;*/
    // }
    // if (isVerticalMovementLocked && playerHead._direction.y == 1)
    // {
    //    /* playerParts[i]._position.y = playerParts[i]._position.y ;*/
    //   /*  playerParts[i]._position.y = positionQueue[i].y;*/

    // }
    // else if (isVerticalMovementLocked && playerHead._direction.y == -1)
    // {

    ///*     playerParts[i]._position.y = playerParts[i]._position.y;*/
    //    /* playerParts[i]._position.y = positionQueue[i].y;*/
    // }

               
    /* playerParts[i]._sprite.setPosition(playerParts[i]._position);  */ 
}

bool Player::DetectWallCollision(int winWidth, int winHeight)
{
   //To-do: När du har implementerat en game over screen ska denna metod returnera en true/false, bool.

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
    //Om du hittar en metod för att använda deltatime så att ormen rör sig 
    //varje 0.2 sekunder.Ta då bort i>10 här
    //Fråga Jonas
    for ( unsigned int i = 1; i < playerParts.size(); i++)
    {
        if (playerHead._sprite.getGlobalBounds().intersects(playerParts[i]._sprite.getGlobalBounds()))
        {
            //ändra till true då du har fixat problemet
            return true;
           
        }
    }
    return false;
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
       /* _sprite.move(_position);*/
        _sprite.setPosition(_position);

    }
    else if (isHorisontalMovementLocked&& _direction.x==1)
    {

        _position.x += _speed.x;
     /*   _sprite.move(_position);*/
        _sprite.setPosition(_position);
    }

    if (isVerticalMovementLocked && _direction.y == -1)
    {
        _position.y -= _speed.y;
     /*   _sprite.move(_position);*/
        _sprite.setPosition(_position);
    }
    else if (isVerticalMovementLocked&& _direction.y==1)
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
