#ifndef PRINTOBJECTS_H
#define PRINTOBJECTS_H

#include <SFML/Graphics.hpp>
#include <iostream>

/** \class Print
    \brief Responsible for displaying all the in-game objects and text on the window

 */

class Print{
    public:
    /**
     * @brief Constructor for the Print class
     * 
     */
    Print();

    /**
     * @brief Responsible for printing the game objects that are encapsulated within a vector of type sf::RectangleShape to the display window.
     * 
     * @param window The display window that the function draws to.
     * @param entity The vector of game objects that are displayed on the window. 
     */
    void printObject(sf::RenderWindow& window, std::vector<sf::RectangleShape>& entity);

    /**
     * @brief Responsible for printing the game objects that are of type sf::RectangleShape to the display window.
     * 
     * @param window The display window that the function draws to.
     * @param entity The sf::Rectangle game object that is displayed on the display window. 
     */
    void printRectObject(sf::RenderWindow& window,sf::RectangleShape& entity);
    
    /**
     * @brief Responsible for printing a text string that is of type sf::Text to the display window.
     * 
     * @param window The display window that the function draws to.
     * @param text The sf::Text text string that is displayed on the display window
     */
    void printText(sf::RenderWindow& window,sf::Text& text);


private:
  

};

#endif