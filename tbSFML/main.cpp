#include  <SFML/Graphics.hpp>
#include "Player.h"
//Memory leaks detetection
#include "windows.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>  
#include <crtdbg.h>
#include <list>
#include "Food.h"
class SimpleSquare
{
private:
    sf::RectangleShape _shape;
    sf::Vector2f _position;
    sf::Vector2f _size;

public:
    SimpleSquare(float width, sf::Color color, float startX, float startY)
    {
        
        _size.x = 50.0f;
        _size.y =_size.x ;
        _shape.setSize(_size);
        _shape.setFillColor(color);
        _position.x = startX;
        _position.y = startY;
    }
    SimpleSquare(){

    }

    ~SimpleSquare()
    {

    }
    void Update()
    {
        _shape.setPosition(_position);
    }


    void Draw(sf::RenderWindow &win) const
    {
        win.draw(_shape);
    }

 
};



std::vector<SimpleSquare> CreateGrid(const sf::Texture texture, int windowWidth, int windowHeight, sf::Color color)
{
    sf::Color lightGreen(0, 200, 0);
    std::vector<SimpleSquare> squares = {};
    SimpleSquare square;
    for (int i = 0; i <= windowHeight / texture.getSize().y; i ++)
    {
        for (int j = 0; j <= windowWidth / texture.getSize().x; j ++)
        {
         
            if (j % 2 == 0 && i%2==0||j%2==1 && i%2==1)
            {
                SimpleSquare square(texture.getSize().x,lightGreen, j * texture.getSize().y, i * texture.getSize().x);
                squares.push_back(square);
            }
            else
            {
                 SimpleSquare square(texture.getSize().x, color, j * texture.getSize().y, i * texture.getSize().x);
                 squares.push_back(square);
            }
            
            
        }
    }
    return squares;
}
bool isProcessDone = false;
bool isFoodEaten = false;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    //Läs mer här: https://learn.microsoft.com/en-us/cpp/c-runtime-library/find-memory-leaks-using-the-crt-library?view=msvc-170
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    int windowWidth = 800, windowHeight = 600;
    float windowWidth1 = 800, windowHeight1 = 600;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "TB Snake");
    window.setFramerateLimit(60);
    
      
    sf::Texture texture;
    if (!texture.loadFromFile("img/Vagg.png"))
    {
        // error...
    }  
   


    
    sf::Clock clock;
    std::vector<SimpleSquare> squares = {};
    std::vector<sf::Vector2f> positions = {};
    std::vector<sf::Vector2f> positionQueue = {};
    std::vector<Player> playerParts = {};

    Player playerHead(windowWidth / 2, windowHeight / 2, texture);
    playerParts.push_back(playerHead);
    /*for (int i = 0; i < 3; i++)
    {
        Player playerBody(float(windowWidth / 2), float(windowHeight / 2), texture);
        playerParts.push_back(playerBody);
    }*/
    sf::Color color(0, 150,0,100);

   /* SimpleSquare square(50, sf::Color::Yellow,500,550);*/

    Food apple(250,250,50,sf::Color::Red);
    std::vector<Food> food = {apple};

   /* SimpleSquare tempSquare(50, color, -100.0f, -100.0f);*/


  
    
    while (window.isOpen())
    {
       
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();

       
       

        squares = CreateGrid(texture, windowWidth, windowHeight, color);
        for (int i = 0; i < squares.size() - 1; i++)
        {
            /* tempSquare = squares.at(i);*/
            //Kolla igenom så att funktionerna fungerar
            /* tempSquare.Update();
            tempSquare.Draw(window);*/
            squares[i].Update();
            squares[i].Draw(window);
               
                 
                
        }
           
        
   /*     square.Update();
        square.Draw(window);*/
        
       
        playerHead.UpdateHead();
        playerHead.DetectCollision(float(windowWidth), float(windowHeight));
        playerHead.Draw(window);
        positionQueue=playerHead.RecentPositions(playerHead, playerParts, positionQueue,clock);
        
        
        
       
        if (playerParts.size() > 1)
        {     
                for (int i = 1; i < playerParts.size(); i++)
                {
                    playerParts[i].UpdateBody(playerHead, playerParts, positionQueue, i,clock);
                    playerParts[i].Draw(window);
                }
           

        }
       
        
        apple.Update();
        apple.Draw(window);
        
        isFoodEaten=apple.DetectCollision(playerHead);
        if (isFoodEaten == true)
        {

            Player playerBody(float(windowWidth / 2), float(windowHeight / 2), texture);
          
            positions=apple.GeneratePositions(float(windowWidth), float(windowHeight), texture);
      
            positions=apple.AvailablePositions(playerHead, positions);
            apple._position=apple.ChangePosition(positions);
        
            isFoodEaten = false;
            playerParts.push_back(playerBody);
            
        }
      
       /* tempSquare.Update();*/
        /*tempSquare.Draw(window);*/

        window.display();
    }
    
    return 0;
}