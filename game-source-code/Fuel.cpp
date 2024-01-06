#include "Fuel.h"

Fuel::Fuel(float screenWidth, float screenHeight):
    screenWidth_{screenWidth},
    screenHeight_{screenHeight}
    {}

void Fuel::initialiseFuel()
{
    initialiseFuelcan();
    initialiseFuelBar();
}

void Fuel::initialiseFuelcan()
{
    fuelcan_.setSize(sf::Vector2f(fuelcanWidth, fuelcanHeight));
    fuelcan_.setOrigin(fuelcanWidth/2, fuelcanHeight/2);
    fuelcanTexture.loadFromFile(fuelcan_texture_file);
    fuelcan_.setTexture(&fuelcanTexture);
    fuelSpawnTimer.restart();
}

void Fuel::initialiseFuelBar()
{
    fuelBar_.setSize(sf::Vector2f(fuelBarWidth, fuelBarHeight));
    fuelBar_.setOrigin(0, fuelBarHeight/2);
    fuelBar_.setPosition(fuelBarXpos, fuelBarYpos);
    fuelBar_.setFillColor(sf::Color{0, 255, 0}); //Green

    fuelBarBackground.setSize(sf::Vector2f(fuelBarBackgroundWidth, fuelBarBackgroundHeight));
    fuelBarBackground.setOutlineThickness(fuelBarBackgroundOutlineThickness);
    fuelBarBackground.setOutlineColor(sf::Color::White);
    fuelBarBackground.setFillColor(sf::Color::Transparent);
    fuelBarBackground.setOrigin(fuelBar_.getOrigin().x, fuelBar_.getOrigin().y);
    fuelBarBackground.setPosition(fuelBar_.getPosition().x, fuelBar_.getPosition().y);
    fuelBarIcon.setSize(sf::Vector2f(fuelBarIconSize, fuelBarIconSize));
    fuelBarIcon.setOrigin(0, fuelBarIconSize/2);
    fuelBarIcon.setTexture(&fuelcanTexture);
    fuelBarIcon.setPosition(fuelBarBackgroundWidth+fuelBarBackground.getPosition().x+fuelBarBackgroundOutlineThickness, fuelBarBackground.getPosition().y);
}

void Fuel::doFuelOperations(bool spaceshipIsMoving)
{
    doFuelcanOperations();
    doFuelBarOperations(spaceshipIsMoving);
}

void Fuel::doFuelBarOperations(bool spaceshipIsMoving)
{
    if(spaceshipIsMoving == true && fuelLevel > 0)
    {
        fuelLevel -= fuelDecay;

        fuelBar_.setScale(fuelLevel/maxFuelLevel, 1.0f);
        fuelBar_.setFillColor(sf::Color{255-fuelLevel/maxFuelLevel*255, fuelLevel/maxFuelLevel*255, 0}); 
    }
    
}
void Fuel::doFuelcanOperations()
{
    auto xCord = rand() % xRange;

    if(fuelSpawnTimer.getElapsedTime().asSeconds() > fuelSpawnTime)
    {
        if(fuelcan_vect.size() >= maxFuelcans)
        {
            fuelcan_vect.erase(fuelcan_vect.begin());
        }
        placeFuel(xCord, yCord);
    }
}

void Fuel::placeFuel(float xCord, float yCord)
{
    fuelcan_.setPosition(xCord, yCord);
    fuelcan_vect.push_back(fuelcan_);
    fuelSpawnTimer.restart();
}

std::vector<sf::RectangleShape>& Fuel::getFuelcanVect()
{
    return fuelcan_vect;
}

std::vector<sf::RectangleShape>& Fuel::getFuelBar()
{   
    fuelBar_vect.clear();
    fuelBar_vect.push_back(fuelBar_);
    fuelBar_vect.push_back(fuelBarBackground);
    fuelBar_vect.push_back(fuelBarIcon);

    return fuelBar_vect;

}

float Fuel::getFuelLevel()
{
    return fuelLevel;
}

bool Fuel::checkFuelLevel()
{
    if(fuelLevel <= 0)
    {
        return false;
    }
    return true;
}

void Fuel::resetFuel()
{
    fuelLevel = maxFuelLevel;
    fuelcan_vect.clear();
    fuelBar_.setScale(1.0f, 1.0f);
    fuelBar_.setFillColor(sf::Color{0, 255, 0});
}

void Fuel::addFuel()
{
    if(fuelLevel <= maxFuelLevel - fuelPickup)
    {
        fuelLevel += fuelPickup;
    }
    else if(fuelLevel > maxFuelLevel-fuelPickup && fuelLevel < maxFuelLevel)
    {
        fuelLevel += (maxFuelLevel - fuelLevel);
    }
}
