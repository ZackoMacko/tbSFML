#include "MainMenu.h"

MainMenu::MainMenu(float width, float height) : showInfoImage(false) {
    if (!font.loadFromFile("fonts/Trends.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Calculate the width based on the widest text ("Start" in this case)
    sf::Text tempText;
    tempText.setFont(font);
    tempText.setString("Start");
    tempText.setCharacterSize(50);
    float buttonWidth = tempText.getGlobalBounds().width + 40; // Adds padding

    // Setup menu items
    menu[0].setFont(font);
    menu[0].setString("Start");
    menu[0].setCharacterSize(50);
    menu[0].setPosition(sf::Vector2f(width / 2 - buttonWidth / 2, height / 2 - 100));

    menu[1].setFont(font);
    menu[1].setString("Info");
    menu[1].setCharacterSize(50);
    menu[1].setPosition(sf::Vector2f(width / 2 - buttonWidth / 2, height / 2));

    menu[2].setFont(font);
    menu[2].setString("Exit");
    menu[2].setCharacterSize(50);
    menu[2].setPosition(sf::Vector2f(width / 2 - buttonWidth / 2, height / 2 + 100));

    selectedItemIndex = 0;
 
    // Load the info image
    if (!infoTexture.loadFromFile("img/howtoplay.png")) { // Update to the actual image path
        std::cerr << "Error loading info image!" << std::endl;
    }
}

void MainMenu::Draw(sf::RenderWindow& window) {
    if (showInfoImage) {
        // Draw the info image
        sf::Sprite infoSprite(infoTexture);
        infoSprite.setPosition(0, 0); // Position it at the top-left corner
        window.draw(infoSprite);
        return; // Skip drawing the menu if the info image is shown
    }

    for (int i = 0; i < 3; i++) {
        // Set a fixed width background rectangle based on "Start" button size
        sf::RectangleShape backgroundRect(sf::Vector2f(menu[0].getGlobalBounds().width + 40, menu[0].getCharacterSize() + 20));
        backgroundRect.setPosition(menu[i].getPosition().x - 20, menu[i].getPosition().y - 10);

        // Set appearance based on selection
        if (i == selectedItemIndex) {
            backgroundRect.setFillColor(sf::Color::Black);      // Highlight background
            backgroundRect.setOutlineColor(sf::Color::White);     // Red border
            backgroundRect.setOutlineThickness(3.0f);           // Border thickness
            menu[i].setFillColor(sf::Color::White);               // Text color when selected
        }
        else {
            backgroundRect.setFillColor(sf::Color(30, 30, 30)); // Dark grey background for unselected
            backgroundRect.setOutlineColor(sf::Color(60, 60, 60)); // Subtle border
            backgroundRect.setOutlineThickness(1.0f);
            menu[i].setFillColor(sf::Color::White);             // White text for unselected
        }

        // Draw the background rectangle and then the text
        window.draw(backgroundRect);
        window.draw(menu[i]);
    }
}

void MainMenu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        selectedItemIndex--;
    }
}

void MainMenu::MoveDown() {
    if (selectedItemIndex + 1 < 3) { // Change to 3 to account for the three buttons
        selectedItemIndex++;
    }
}

int MainMenu::GetPressedItem() const {
    return selectedItemIndex;
}

void MainMenu::toggleInfoImage() {
    showInfoImage = !showInfoImage; // Toggle the visibility of the info image
}

bool MainMenu::isInfoImageVisible() const {
    return showInfoImage; // Return current visibility status
}
