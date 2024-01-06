#include "printObjects.h"

Print::Print()
{
}

void Print::printObject(sf::RenderWindow& window,std::vector<sf::RectangleShape>& entity)
{
    for(auto i = 0; i <entity.size(); i++){
        window.draw(entity[i]);
    }  
}

void Print::printRectObject(sf::RenderWindow& window,sf::RectangleShape& entity)
{
        window.draw(entity);  
}

void Print::printText(sf::RenderWindow& window,sf::Text& text)
{
        window.draw(text);  
}
