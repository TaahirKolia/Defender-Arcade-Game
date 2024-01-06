#include "Laser.h"

//Laser Constructor
Laser::Laser(float screenWidth, float spaceshipWidth, float spaceshipHeight):
screenWidth_{screenWidth},
spaceshipWidth_{spaceshipWidth},
spaceshipHeight_{spaceshipHeight}
{}

void Laser::initialiseLaser()
{
    laser_.setSize(sf::Vector2f(laserWidth, laserHeight));
    laser_.setOrigin(sf::Vector2f(laserWidth/2, laserHeight/2));
    laser_.setFillColor(sf::Color::Red);
}

std::tuple<bool, bool> Laser::getMovementInputs(std::tuple<bool, bool> shootingInputs, bool shipDirection)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && laserTimer.getElapsedTime().asSeconds()>=laserTime && shipDirection == true)
    {
        std::get<0>(shootingInputs) = true;    
    }
        
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && laserTimer.getElapsedTime().asSeconds()>=laserTime && shipDirection == false)
    {
        std::get<1>(shootingInputs) = true; 
    }

    return shootingInputs; 
} 

void Laser::shoot(bool shootRight, bool shootLeft, float shipXCord, float shipYCord)
{
    if(shootRight)
    {
        laser_.setPosition(shipXCord + spaceshipWidth_/2 - laserWidth/2, shipYCord + spaceshipHeight_/2 - laserHeight/2 - 6.0f);
        right_laser_vect.push_back(laser_);
        rightLaserPosVect.push_back(0.0f);
        laserTimer.restart();
    }
    if(shootLeft)
    {
        laser_.setPosition(shipXCord - spaceshipWidth_/2 + laserWidth/2, shipYCord + spaceshipHeight_/2 -laserHeight/2 - 6.0f);
        left_laser_vect.push_back(laser_);
        leftLaserPosVect.push_back(0.0f);
        laserTimer.restart();
    }
}


void Laser::moveLasers()
{
     for (auto i=0; i<right_laser_vect.size(); i++)
     {
        if (rightLaserPosVect[i] > maxLaserMovements)
        {
            rightLaserPosVect.erase(rightLaserPosVect.begin()+i);
            right_laser_vect.erase(right_laser_vect.begin()+i);
        }
     }

     for (auto i=0; i<right_laser_vect.size(); i++)
     {
        if(right_laser_vect[i].getPosition().x > 4782.0f)
        {
            right_laser_vect[i].setPosition(0.0f, right_laser_vect[i].getPosition().y);
            rightLaserPosVect[i]++;
        }

        right_laser_vect[i].move(laserSpeed, 0.0f);
        rightLaserPosVect[i]++;

    }

    for (auto i=0; i<left_laser_vect.size(); i++)
     {
        if (leftLaserPosVect[i] > maxLaserMovements)
        {
            leftLaserPosVect.erase(leftLaserPosVect.begin()+i);
            left_laser_vect.erase(left_laser_vect.begin()+i);
        }
     }

    for (auto i=0; i<left_laser_vect.size(); i++)
    {   
        if(left_laser_vect[i].getPosition().x <0)
        {
            left_laser_vect[i].setPosition(4782.0f, left_laser_vect[i].getPosition().y);
            leftLaserPosVect[i]++;
        }

        left_laser_vect[i].move(-laserSpeed, 0.0f);
        leftLaserPosVect[i]++;
    }
}

std::vector<sf::RectangleShape>& Laser::getLeftLaserVector()
{
    return left_laser_vect;
}

void Laser::resetLasers()
{
    left_laser_vect.clear();
    right_laser_vect.clear();
}

std::vector<sf::RectangleShape>& Laser::getRightLaserVector()
{
    return right_laser_vect;
}

std::vector<float>& Laser::getRightLaserPosVector()
{
    return rightLaserPosVect;
}

std::vector<float>& Laser::getLeftLaserPosVector()
{
    return leftLaserPosVect;
}