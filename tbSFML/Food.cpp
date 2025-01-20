#include "Food.h"



Food::Food(float startX,float startY, float width,sf::Color color)
{
    _size.x = 50.0f;
    _size.y = _size.x;
    _shape.setSize(_size);
    _shape.setFillColor(color);
    _position.x = startX;
    _position.y = startY;
    
}

sf::Vector2f Food::ChangePosition(std::vector<sf::Vector2f>& positions)
{
    sf::Vector2f position(0,0);
    float randomNumber = rand() % positions.size() - 1;
    position = positions.at(randomNumber);
    return position;
}

std::vector<sf::Vector2f> Food::AvailablePositions(Player player, std::vector<sf::Vector2f>&positions)
{
    sf::Vector2f temporaryPosition( 0.0f,0.0f);
    for (int i = 0; i < positions.size() - 1; i++)
    {
      
        temporaryPosition = positions.at(i);
        
        if (player._sprite.getGlobalBounds().contains(temporaryPosition)==true)
        {
            
            positions.erase(positions.begin() + i);
        }
    }
    return positions;
}
/// <summary>
/// This method generates positions based the windows height and width by utilizing the square texture.
/// </summary>
/// <param name="windowHeight"></param>
/// <param name="windowWidth"></param>
/// <param name="texture"></param>
/// <returns></returns>
std::vector<sf::Vector2f> Food::GeneratePositions(int windowHeight,int windowWidth,sf::Texture texture)
{
    std::vector<sf::Vector2f> positions = {};

    for (float j = 0; j < windowWidth / texture.getSize().x; j++)
    {
        
        for (float i = 0; i < windowHeight / texture.getSize().y; i++)
        {

            sf::Vector2f temporaryPosition(i* texture.getSize().x, j * texture.getSize().y);
            
            positions.push_back(temporaryPosition);
        }
    }
    return positions;
}

bool Food::DetectCollision( Player player )
{
    if (_shape.getGlobalBounds().intersects(player._sprite.getGlobalBounds()))
    {
        return true;
    }
    return false;


}
void Food::Update()
{
    _shape.setPosition(_position);
}



void Food::Draw(sf::RenderWindow& win) const
{
    win.draw(_shape);
}