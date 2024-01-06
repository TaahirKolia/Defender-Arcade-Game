#include "Spaceship.h"

// Spaceship Constructor
Spaceship::Spaceship(float screenWidth, float screenHeight, float spaceshipWidth, float spaceshipHeight, float mapHeight, float moveDistance):
    spaceshipHeight_{spaceshipHeight},
    spaceshipWidth_{spaceshipWidth},
    screenHeight_{screenHeight},
    screenWidth_{screenWidth},
    mapHeight_{mapHeight},
    moveDistance_{moveDistance},
    player_(sf::Vector2f(spaceshipWidth, spaceshipHeight))
{}

// Sets spaceship origin and initial position. Initialises textures
void Spaceship::initialiseShip()
{
    player_.setOrigin(spaceshipWidth_/2, spaceshipHeight_/2);
    player_.setPosition(screenWidth_/2, screenHeight_/2);

    playerTexture_right.loadFromFile(playerTexture_right_file);
    if(!playerTexture_right.loadFromFile(playerTexture_right_file))
    {
        throw CannotOpenPlayerTextureRight();
    }
    playerTexture_left.loadFromFile(playerTexture_left_file);
    if(!playerTexture_left.loadFromFile(playerTexture_left_file))
    {
        throw CannotOpenPlayerTextureLeft();
    }
    playerTexture_right_stationary.loadFromFile(playerTexture_right_stationary_file);
    if(!playerTexture_right_stationary.loadFromFile(playerTexture_right_stationary_file))
    {
        throw CannotOpenPlayerTextureRightStationary();
    }
    playerTexture_left_stationary.loadFromFile(playerTexture_left_stationary_file);
    if(!playerTexture_left_stationary.loadFromFile(playerTexture_left_stationary_file))
    {
        throw CannotOpenPlayerTextureLeftStationary();
    }

    player_.setTexture(&playerTexture_right);
}

// Returns player spaceship rectangle
sf::RectangleShape& Spaceship::getPlayer()
{
    return player_;
}

// Reads in player keyboard inputs for movement
std::tuple<bool, bool, bool, bool, bool> Spaceship::getMovementInputs(std::tuple<bool, bool, bool, bool, bool> movementInputs)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    { 
        std::get<0>(movementInputs) = true;
        std::get<4>(movementInputs) = true;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        std::get<1>(movementInputs) = true;
        std::get<4>(movementInputs) = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {   
        std::get<2>(movementInputs) = true;
        std::get<4>(movementInputs) = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        std::get<3>(movementInputs) = true;
        std::get<4>(movementInputs) = true;
    }

    return movementInputs;
}

// Executes player movements
void Spaceship::moveSpaceship(bool moveLeft, bool moveRight, bool moveUp, bool moveDown)
{
    if(moveLeft && (player_.getPosition().x - spaceshipWidth_/2 >= moveDistance_))
    {   
        player_.move(-moveDistance_, 0.0f);
        player_.setTexture(&playerTexture_left);
        spaceshipDirection = false;
    }

    else if(moveLeft && (0.0f < (player_.getPosition().x - spaceshipWidth_/2) && (player_.getPosition().x - spaceshipWidth_/2) < moveDistance_))
    {   
        player_.move(-(player_.getPosition().x-spaceshipWidth_/2) , 0.0f);
        player_.setTexture(&playerTexture_left);
        spaceshipDirection = false;
    }
    else if(moveLeft && (player_.getPosition().x - spaceshipWidth_/2 <= 0.0f))
    {   
        player_.setPosition(screenWidth_ - mapOffset-spaceshipWidth_/2, player_.getPosition().y);
        player_.setTexture(&playerTexture_left);
        spaceshipDirection = false;
    }

    if(moveRight && (player_.getPosition().x + spaceshipWidth_/2 <= screenWidth_ - mapOffset - moveDistance_))
    {   
        player_.move(moveDistance_, 0.0f);
        player_.setTexture(&playerTexture_right);
        spaceshipDirection = true;
    }

    else if(moveRight && ((screenWidth_ - mapOffset - moveDistance_) < (player_.getPosition().x + spaceshipWidth_/2) && (player_.getPosition().x + spaceshipWidth_/2) < screenWidth_ - mapOffset))
    {   
        player_.move((screenWidth_ - mapOffset - (player_.getPosition().x + spaceshipWidth_/2)), 0.0f);
        player_.setTexture(&playerTexture_right);
        spaceshipDirection = true;
    }

    else if(moveRight && player_.getPosition().x+spaceshipWidth_/2 == screenWidth_ - mapOffset)
    {
        player_.setPosition(0.0f, player_.getPosition().y);
    }


    if(moveUp && (player_.getPosition().y - spaceshipHeight_/2 >= mapHeight_ + moveDistance_))
    {   
        player_.move(0.0f, -moveDistance_);
    }

    else if(moveUp && (mapHeight_ < (player_.getPosition().y - spaceshipHeight_/2) && (player_.getPosition().y - spaceshipHeight_/2) <  mapHeight_ + moveDistance_))
    {   
        player_.move(0.0f, -(player_.getPosition().y-spaceshipHeight_/2-mapHeight_));
    }

    if(moveDown && (player_.getPosition().y + spaceshipHeight_/2 <= screenHeight_ - moveDistance_))
    {   
        player_.move(0.0f, moveDistance_);
    }

    else if(moveDown && (screenHeight_ > (player_.getPosition().y + spaceshipHeight_/2) && (player_.getPosition().y + spaceshipHeight_/2) >  screenHeight_ - moveDistance_))
    {   
        player_.move(0.0f, (screenHeight_ - (player_.getPosition().y+spaceshipHeight_/2)));
    }
}


void Spaceship::checkSpaceshipMovement(bool moveLeft, bool moveRight, bool moveUp, bool moveDown, bool hasFuel)
{
    if(hasFuel == true)
    {
        moveSpaceship(moveLeft, moveRight, moveUp, moveDown);
    }
    else
    {
        crashSpaceship();
    }
}

void Spaceship::crashSpaceship()
{
    bool moveLeft = false; 
    bool moveRight = false; 
    bool moveUp = false;
    bool moveDown = true;
    moveSpaceship(moveLeft, moveRight, moveUp, moveDown);
    
}
