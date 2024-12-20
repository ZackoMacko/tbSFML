#include "LoadData.h"
#include <iostream>
#include <thread>



void LoadData::LoadMethod(bool* _loading)
{
    
    std::this_thread::sleep_for(std::chrono::seconds(5)); //L�tsasladda i 5 sekunder

    *_loading = false;
}

sf::Text LoadData::DisplayText(sf::Text &text,sf::Font &font, int windowHeight, int windowWidth)
{
    
    
  
    text.setFont(font);
    text.setString("Loading...");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Black);
    text.setPosition((windowWidth / 2) - text.getGlobalBounds().width/2, windowHeight / 2);
    
  /*
  * N�r vi laddar en bild
  * Hita en bild online
  * skapa en lista som ska h�lla sprites. 
  * Listan ska sedan skickas in i en metod d�r spriten roterar fr�n 0 grader med 1 grader intervall.
  * N�r metoden �r slut ska listan med sprites vara fyllda med en sprite som �r har blivit roterat 360 grader
  * Sedan kan vi anv�nda en if-satsen f�r loading d�r varenda sprite i listan skrivs ritas ut
  * Detta ska ge illusionen att spriten roterar
  */

    
    return text;
    
}
void LoadData::Draw(sf::RenderWindow& win,sf::Text &text)const 
{
    win.draw(text);
}


