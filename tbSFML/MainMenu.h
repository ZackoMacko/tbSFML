#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

class MainMenu {
public:
    MainMenu(float width, float height);
    void Draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() const;
    void toggleInfoImage(); // Toggle visibility of the info image
    bool isInfoImageVisible() const; // Check if the info image is visible

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[3]; // Three menu items: Start, Info, Exit
    sf::Texture infoTexture; // Texture for the info image
    bool showInfoImage; // Flag to control the display of the info image
};

#endif // MAINMENU_H
