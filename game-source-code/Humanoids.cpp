#include "Humanoids.h"

Humanoids::Humanoids(float screenWidth, float screenHeight, float mapHeight):
    screenWidth_(screenWidth),
    screenHeight_(screenHeight),
    mapHeight_(mapHeight)
{}
int Humanoids::killedHumanoids = 0;

void Humanoids::initialiseHumanoidObjects()
{
    initialiseHumanoids();
    initialiseHumanoidHitBoxes();
    humanoidSpawnTimer.restart();
}

void Humanoids::initialiseHumanoids()
{
    humanoid_.setSize(sf::Vector2f(humanoidWidth, humanoidHeight));
    humanoid_.setOrigin(humanoidWidth/2, humanoidHeight/2);
    humanoidTexture.loadFromFile(humanoid_texture_file);
    humanoid_.setTexture(&humanoidTexture);
}

void Humanoids::initialiseHumanoidHitBoxes()
{
    humanoidHitBox_.setSize(sf::Vector2f(humanoidHitBoxWidth,humanoidHitBoxHeight));
    humanoidHitBox_.setOrigin(humanoidHitBoxWidth/2, humanoidHitBoxHeight - humanoidHeight/2);
    humanoidHitBox_.setFillColor(sf::Color::Transparent);
}

void Humanoids::moveRaisingHumanoids()
{
    for(auto i=0; i< raisingHumanoidVector.size(); i++)
    {
        if(raisingHumanoidVector[i].getPosition().y < 200.0f)
        {
            raisingHumanoidVector.erase(raisingHumanoidVector.begin() + i);
            i--;
            killedHumanoids++; 
        }
        else
        {
            raisingHumanoidVector[i].move(0.0f, -raisingMoveDistance);
        }
    }
}

void Humanoids::moveFallingHumanoids()
{
    for(auto i=0; i< fallingHumanoidVector.size(); i++)
    {
        if(fallingHumanoidVector[i].getPosition().y > screenHeight_)
        {
            fallingHumanoidVector.erase(fallingHumanoidVector.begin() + i);
            i--;
            killedHumanoids++; 
        }
        else
        {
            fallingHumanoidVector[i].move(0.0f, fallingMoveDistance);
        }
    }
}

void Humanoids::doHumanoidOperations()
{
    auto humanoidXcord = (rand() % humanoidXrange) + humanoidWidth;

    if(humanoidSpawnTimer.getElapsedTime().asSeconds() > humanoidSpawnTime && humanoidsSpawnedCount < maxHumanoidCount)
    {
        placeHumanoids(humanoidXcord, humanoidYcord);
        placeHumanoidHitBoxes();
        humanoidsSpawnedCount++;
    }

    moveRaisingHumanoids();
    moveFallingHumanoids();
}

void Humanoids::placeHumanoids(float xCord, float yCord)
{
    humanoid_.setPosition(xCord, yCord);
    groundHumanoidVector.push_back(humanoid_);
    humanoidSpawnTimer.restart();
}

void Humanoids::placeHumanoidHitBoxes()
{
    humanoidHitBox_.setPosition(humanoid_.getPosition().x, humanoid_.getPosition().y);
    humanoidHitBoxVector.push_back(humanoidHitBox_);
}

std::vector<sf::RectangleShape> &Humanoids::getHumanoidHitBoxVector()
{
    return humanoidHitBoxVector;
}

std::vector<sf::RectangleShape> &Humanoids::getGroundHumanoidsVector()
{
    return groundHumanoidVector;
}
std::vector<sf::RectangleShape> &Humanoids::getRaisingHumanoidsVector()
{
    return raisingHumanoidVector;
}
std::vector<sf::RectangleShape> &Humanoids::getFallingHumanoidsVector()
{
    return fallingHumanoidVector;
}

void Humanoids::spawnRaisingHumanoid(sf::Vector2f landerPos)
{
    humanoid_.setPosition(landerPos);
    raisingHumanoidVector.push_back(humanoid_);
}

void Humanoids::spawnFallingHumanoid(sf::Vector2f landerPos)
{
    humanoid_.setPosition(landerPos);
    fallingHumanoidVector.push_back(humanoid_);
}

void Humanoids::spawnGroundHumanoid(sf::Vector2f landerPos)
{
    placeHumanoids(landerPos.x, landerPos.y);
    placeHumanoidHitBoxes();
}

void Humanoids::incrementKilledHumanoids()
{
    killedHumanoids++;
}

int Humanoids::getKilledHumanoids()
{
    return killedHumanoids;
}

void Humanoids::reset()
{
    groundHumanoidVector.clear();
    raisingHumanoidVector.clear();
    fallingHumanoidVector.clear();
    humanoidHitBoxVector.clear();
    humanoidsSpawnedCount = 0;
    killedHumanoids = 0;
    humanoidSpawnTimer.restart();
}