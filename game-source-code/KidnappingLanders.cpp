#include "KidnappingLanders.h"

KidnappingLanders::KidnappingLanders(float screenHeight, float scrollableScreenWidth, float mapHeight, float spaceshipWidth, float spaceshipHeight): 
    EnemyLanders(screenHeight,scrollableScreenWidth,mapHeight,spaceshipWidth,spaceshipHeight)
{
    enemyWidth_ = kidnapperWidth_;
    enemyHeight_ = kidnapperHeight_;
    enemyTextureFile = "resources/Lander.png";
}

void KidnappingLanders::initialiseEnemies()
{
    enemyTexture.loadFromFile(enemyTextureFile);
    kidnapper.setSize(sf::Vector2f(enemyWidth_,enemyHeight_));
    kidnapper.setTexture(&enemyTexture);
    kidnapper.setOrigin(enemyWidth_/2 , enemyHeight_/2);
    spawnTimer.restart();
    downKidnappers_.clear();
    upKidnappers_.clear();
    upKidnappersPassengers_.clear();

}

void KidnappingLanders::spawnKidnapper(sf::Vector2f landerPos)
{
    kidnapper.setPosition(landerPos);
    downKidnappers_.push_back(kidnapper);
}

void KidnappingLanders::spawnUpKidnapper(sf::Vector2f landerPos)
{
    kidnapper.setPosition(landerPos);
    upKidnappers_.push_back(kidnapper);
    upKidnappersPassengers_.push_back(true);
}

void KidnappingLanders::moveKidnappers()
{
    moveDownKidnappers();
    moveUpKidnappers();
}

void KidnappingLanders::moveDownKidnappers()
{    
    for(auto i=0; i< downKidnappers_.size(); i++)
    {
        if(downKidnappers_[i].getPosition().y > screenHeight_)
        {
            downKidnappers_.erase(downKidnappers_.begin() + i);
            i--; 
        }
        else
        {
            downKidnappers_[i].move(0.0f, kidnapperMoveDistance);
        }
    }
}

void KidnappingLanders::moveUpKidnappers()
{    
    for(auto i=0; i< upKidnappers_.size(); i++)
    {
        if(upKidnappers_[i].getPosition().y < 200.0f)
        {
            upKidnappers_.erase(upKidnappers_.begin() + i);
            upKidnappersPassengers_.erase(upKidnappersPassengers_.begin() + i);
            i--; 
        }
        else
        {
            upKidnappers_[i].move(0.0f, -kidnapperMoveDistance);
        }
    }
}

std::vector<sf::RectangleShape> &KidnappingLanders::getDownKidnappersVector()
{
    return downKidnappers_;
}

std::vector<sf::RectangleShape> &KidnappingLanders::getUpKidnappersVector()
{
    return upKidnappers_;
}

std::vector<bool> &KidnappingLanders::getUpKidnappersPasengersVector()
{
    return upKidnappersPassengers_;
}

void KidnappingLanders::resetEnemies()
{
    downKidnappers_.clear();
    upKidnappers_.clear();
    upKidnappersPassengers_.clear();
}