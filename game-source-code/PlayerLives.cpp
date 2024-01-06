#include "PlayerLives.h"

PlayerLives::PlayerLives(){

    livesEmpty.loadFromFile(lifeEmptyFile);
    livesFull.loadFromFile(lifeFullFile);
}

void PlayerLives::checkPlayerLives(sf::Clock collisionClock){
        reducePlayerLives();
        collisionClock.restart();
        updateLifeBar();
}

int PlayerLives::availableLives = 3; 

void PlayerLives::setLifeBarPosition(){
    livesVector[0].setPosition(sf::Vector2f(50.0f ,25.0f));
    livesVector[1].setPosition(sf::Vector2f(105.0f ,25.0f));
    livesVector[2].setPosition(sf::Vector2f(160.0f ,25.0f));
}

void PlayerLives::fullLifeBar(){
    for(auto i = 0 ; i < livesVector.capacity(); i++){
        livesVector.push_back(livesFullSymbol);
    }
}

void PlayerLives::initialiseLifeBar(){
    livesEmptySymbol.setTexture(&livesEmpty);
    livesFullSymbol.setTexture(&livesFull);
    livesEmptySymbol.setSize(sf::Vector2f(40.0f,40.0f));
    livesFullSymbol.setSize(sf::Vector2f(40.0f,40.0f));

    livesVector.reserve(totalLives);
    fullLifeBar();
    setLifeBarPosition();
}

void PlayerLives::updateLifeBar(){

    switch (availableLives)
    {        
        case 2:
            livesVector.pop_back();
            livesVector.push_back(livesEmptySymbol);
            setLifeBarPosition();
            break;
        case 1:
            livesVector.erase(livesVector.begin()+1);
            livesVector.push_back(livesEmptySymbol);
            setLifeBarPosition();
            break;
        case 0:
            livesVector.erase(livesVector.begin());
            livesVector.push_back(livesEmptySymbol);
            setLifeBarPosition();
            break;
    }
}

std::vector<sf::RectangleShape>& PlayerLives::getLivesBar(){

        return livesVector;
    
}

void PlayerLives::reducePlayerLives(){
    availableLives--;
}

int PlayerLives::getPlayerLives(){
    return availableLives;
}

void PlayerLives::reset(){
    availableLives = 3 ;
    livesVector.clear();
    fullLifeBar();
    setLifeBarPosition();
}

PlayerLives::~PlayerLives(){
}