#include "Shields.h"

Shields::Shields(float spaceshipXpos, float spaceshipYpos, float SpaceshipWidth, float SpaceshipHeight):
    spaceshipXpos_{spaceshipXpos},
    spaceshipYpos_{spaceshipYpos},
    spaceshipWidth_{SpaceshipWidth},
    spaceshipHeight_{SpaceshipHeight}
    {}

void Shields::checkPlayerShields(bool shieldLanderCollision, bool shieldLanderMissileCollision, bool downKidnapperShieldCollision, bool upKidnapperShieldCollision)
{
    if(shieldLanderCollision == true || shieldLanderMissileCollision == true || downKidnapperShieldCollision == true, upKidnapperShieldCollision == true)
    {
        destroyShield();
    }
}

int Shields::availableShields = 3; 

void Shields::initialiseShieldObjects()
{
    initialiseShieldBar();
}

void Shields::activateShield()
{
    shieldHeight_ = spaceshipHeight_+15.0f;
    shieldWidth_ = spaceshipWidth_+15.0f;
    shield_.setSize(sf::Vector2f(shieldWidth_, shieldHeight_));
    shield_.setOrigin(shieldWidth_/2, shieldHeight_/2);
    shield_.setFillColor(sf::Color::Transparent);
    shield_.setPosition(spaceshipXpos_, spaceshipYpos_);
    shield_.setOutlineThickness(5.0f);
    shield_.setOutlineColor(sf::Color::Green);
    isShieldActive = true;
    shieldTimer.restart();
}

void Shields::initialiseShieldBar()
{
    shieldsEmpty.loadFromFile(shieldEmptyFile);
    shieldsFull.loadFromFile(shieldFullFile);
    shieldsEmptySymbol.setTexture(&shieldsEmpty);
    shieldsFullSymbol.setTexture(&shieldsFull);
    shieldsEmptySymbol.setSize(sf::Vector2f(40.0f,40.0f));
    shieldsFullSymbol.setSize(sf::Vector2f(40.0f,40.0f));
    shieldsVector.reserve(totalshields);
    fullShieldBar();
    setShieldBarPosition();
}

void Shields::setShieldBarPosition()
{
    shieldsVector[0].setPosition(sf::Vector2f(215.0f,25.0f));
    shieldsVector[1].setPosition(sf::Vector2f(270.0f,25.0f));
    shieldsVector[2].setPosition(sf::Vector2f(325.0f,25.0f));
}

void Shields::fullShieldBar(){
    for(auto i = 0 ; i < shieldsVector.capacity(); i++){
        shieldsVector.push_back(shieldsFullSymbol);
    }
}

void Shields::updateShieldBar(){

    switch (availableShields)
    {        
        case 2:
            shieldsVector.pop_back();
            shieldsVector.push_back(shieldsEmptySymbol);
            setShieldBarPosition();
            break;
        case 1:
            shieldsVector.erase(shieldsVector.begin()+1);
            shieldsVector.push_back(shieldsEmptySymbol);
            setShieldBarPosition();
            break;
        case 0:
            shieldsVector.erase(shieldsVector.begin());
            shieldsVector.push_back(shieldsEmptySymbol);
            setShieldBarPosition();
            break;
    }
}

void Shields::reducePlayerShields(){
    availableShields--;
}

int Shields::getPlayerShields(){
    return availableShields;
}

void Shields::checkShieldInput()
{
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) && availableShields > 0 && isShieldActive == false))
    {
        activateShield();
        reducePlayerShields();
        updateShieldBar();
    }

    if(shieldTimer.getElapsedTime().asMilliseconds() > maxShieldTime)
    {
        destroyShield();
    }
}

void Shields::moveShield(float spaceshipXpos, float spaceshipYpos)
{
    shield_.setPosition(spaceshipXpos, spaceshipYpos);
    shield_.setOutlineColor(sf::Color{61, 201, 255, 255- shieldTimer.getElapsedTime().asMilliseconds()/maxShieldTime*255});
}

sf::RectangleShape &Shields::getShield()
{
    return shield_;
}

std::vector<sf::RectangleShape>& Shields::getShieldBar()
{
    return shieldsVector;
}

void Shields::destroyShield()
{
    shield_.setSize(sf::Vector2f(1.0f, 1.0f));
    shield_.setOrigin(0.0f, 0.0f);
    shield_.setFillColor(sf::Color::Transparent);
    shield_.setOutlineColor(sf::Color::Transparent);

    isShieldActive = false;
}

void Shields::reset(){
    availableShields = 3 ;
    shieldsVector.clear();
    fullShieldBar();
    setShieldBarPosition();
    destroyShield();
}