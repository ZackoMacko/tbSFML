#include  <SFML/Graphics.hpp>
#include "Player.h"
#include "LoadData.h"
//Memory leaks detetection
#include "windows.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>  
#include <crtdbg.h>
#include <list>
#include "Food.h"
#include "MainMenu.h"

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

bool _isFoodEaten = false;
bool _gameOver = false;
bool _win = false;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    int score = 0;
    int points = 100;
    //Läs mer här: https://learn.microsoft.com/en-us/cpp/c-runtime-library/find-memory-leaks-using-the-crt-library?view=msvc-170
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    int windowWidth = 800, windowHeight = 600;
    /* float windowWidth1 = 800, windowHeight1 = 600;*/
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "TB Snake");
    window.setFramerateLimit(60);

    MainMenu mainMenu(windowWidth, windowHeight);
    bool isMenuActive = true;
    sf::Clock clock;
    

    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("fonts/Trends.ttf"))
    {
        // error...

    }

    LoadData loadData;
    loadData.DisplayText(text, font, windowHeight, windowWidth);
    bool loading = true;
    std::thread thread(&LoadData::LoadMethod, &loadData, &loading);

    sf::Texture texture;
    if (!texture.loadFromFile("img/Vagg.png"))
    {
        // error...
    }
    sf::Sprite gameOver;
    sf::Texture GO;
    if (!GO.loadFromFile("img/newgameover.png"))
    {

    }
    gameOver.setTexture(GO);
    sf::Sprite winScreen;
    sf::Texture wS;
    if (!wS.loadFromFile("img/winscreen.png"))
    {

    }
    winScreen.setTexture(wS);

    std::vector<SimpleSquare> squares = {};
    std::vector<sf::Vector2f> positions = {};
    std::vector<sf::Vector2f> positionQueue = {};
    std::vector<Player> playerParts = {};

    Player playerHead(windowWidth / 2, windowHeight / 2, texture);
  /*  playerParts.push_back(playerHead);*/

    sf::Color color(0, 150, 0, 100);

    Food apple(250, 250, 50, sf::Color::Red);
    std::vector<Food> food = { apple };

    while (window.isOpen())
    {
        while (loading)
        {
            window.clear(sf::Color::Green);
            window.draw(text);
            window.display();

        }
        sf::Event event;
        while (window.pollEvent(event)&&loading==false)
        {
           
            if (event.type == sf::Event::Closed)
            {
                window.close();
                
            }       
            else
            {             
                if (isMenuActive == true)
                {
                    if (event.type == (sf::Event::KeyPressed))
                    {
                        switch (event.key.code)
                        {
                        case sf::Keyboard::Enter:
                        {                            
                            int selectedItem = mainMenu.GetPressedItem();
                            if (selectedItem == 0) // "Start" is selected
                            {
                            
                                isMenuActive = false; // Start the game
                            }
                            else if (selectedItem == 1) // "Info" is selected
                            {
                                mainMenu.toggleInfoImage(); // Show/hide the info image
                            }
                            else if (selectedItem == 2) // "Exit" is selected
                            {
                                window.close(); // Close the window
                            }
                            break;
                        }
                        case sf::Keyboard::Up:
                            mainMenu.MoveUp();
                            break;
                        case sf::Keyboard::Down:
                            mainMenu.MoveDown();
                            break;
                        }
                    }

                }
            }
        }
        
        if (isMenuActive)
        {
            window.clear(sf::Color::Green);
            mainMenu.Draw(window);
            window.display();
        }
        else if (mainMenu.isInfoImageVisible())
        {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                mainMenu.toggleInfoImage();
            }
        }

        while (isMenuActive != true&&_gameOver!=true)
        {
           
            window.clear();
            //Test
            window.setTitle("TB Snake - Score: " + std::to_string(score));

            squares = CreateGrid(texture, windowWidth, windowHeight, color);
            for (int i = 0; i < squares.size(); i++)
            {
                squares[i].Update();
                squares[i].Draw(window);
            }

            
          
            

            if(clock.getElapsedTime().asSeconds() >= 0.2f)
            {
                playerHead.UpdateHead();            
                positionQueue = playerHead.RecentPositions(playerHead, playerParts, positionQueue);     
                clock.restart();
            }
            playerHead.Draw(window);
            
            _gameOver=playerHead.DetectWallCollision(float(windowWidth), float(windowHeight));
            if (_gameOver==true)
            {
                break;
            }
            _gameOver = playerHead.SnakeToSnakeCollision(playerParts, playerHead, positionQueue);
           
            
            


            if (playerParts.size() > 0)
            {
                for (int i = 0; i < playerParts.size(); i++)
                {                  
                    playerParts[i].UpdateBody(playerHead, playerParts, positionQueue, i);
                    playerParts[i].Draw(window);                   
                }
                           
            }
         
            _isFoodEaten = apple.DetectCollision(playerHead);
            if (_isFoodEaten == true)
            {
                score += points;
                Player playerBody(float(-100), float(-100), texture);

                positions = apple.GeneratePositions(float(windowWidth), float(windowHeight), texture);

                positions = apple.AvailablePositions(playerHead, positions);
                apple._position = apple.ChangePosition(positions);

                _isFoodEaten = false;
                playerParts.push_back(playerBody);            

            }
            apple.Update();
            apple.Draw(window);

            if (playerParts.size()==squares.size())
            {
                _win = true;
            }


          window.display();

        }

        if (_gameOver==true&&isMenuActive==false)
        {
            window.clear();
            window.draw(gameOver);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                playerHead._position.x= windowWidth/2;
                playerHead._position.y =  windowHeight/2;
                playerHead._direction.x=0;
                playerHead._direction.y = 0;
              
                playerParts.clear();
                _gameOver = false;
               /* isMenuActive = true;*/
                playerHead._isHorisontalMovementLocked = false;
                playerHead._isVerticalMovementLocked = false;
                score = 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            {
                playerHead._position.x = windowWidth / 2;
                playerHead._position.y = windowHeight / 2;
                playerHead._direction.x = 0;
                playerHead._direction.y = 0;

                playerParts.clear();
                _gameOver = false;
                isMenuActive = true;
                playerHead._isHorisontalMovementLocked = false;
                playerHead._isVerticalMovementLocked = false;
                score = 0;
            }
        }
        //Måndag 20/01-2025
        //Testa så att man kan vinna
        //Antal rutor är 221
        //Efter detta spara till github
        //Hädanefter ska du läsa igenom det kopplade projektdokumentet
        //Lämna in
        else if (_win == true)
        {
            window.clear();
            window.draw(winScreen);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                playerHead._position.x = windowWidth / 2;
                playerHead._position.y = windowHeight / 2;
                playerHead._direction.x = 0;
                playerHead._direction.y = 0;

                playerParts.clear();
                _gameOver = false;
                _win = false;
                playerHead._isHorisontalMovementLocked = false;
                playerHead._isVerticalMovementLocked = false;
                score = 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            {
                playerHead._position.x = windowWidth / 2;
                playerHead._position.y = windowHeight / 2;
                playerHead._direction.x = 0;
                playerHead._direction.y = 0;

                playerParts.clear();
                _gameOver = false;
                _win = false;
                isMenuActive = true;
                playerHead._isHorisontalMovementLocked = false;
                playerHead._isVerticalMovementLocked = false;
                score = 0;

            }
        }
                  
        
    }

    thread.join();

    return 0;
}