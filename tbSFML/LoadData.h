#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include  <SFML/Graphics.hpp>
#include <string>
class LoadData {
public:
    sf::Vector2f _position;
    
    void LoadMethod(bool* _loading);
    sf::Text DisplayText(sf::Text &text,sf::Font &font, int windowHeight, int windowWidth);
    void Draw(sf::RenderWindow& win, sf::Text &text)const;
};

    