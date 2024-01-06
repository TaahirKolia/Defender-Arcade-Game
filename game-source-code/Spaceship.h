#ifndef SPACESHIP
#define SPACESHIP

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * \class CannotOpenPlayerTextureRight
 * @brief Exception that is thrown when the file for the texture of the player ship facing right cannot be opened
 * 
 */
class CannotOpenPlayerTextureRight{};
/**
 * \class CannotOpenPlayerTextureLeft;

 * @brief Exception that is thrown when the file for the texture of the player ship facing left cannot be opened
 * 
 */
class CannotOpenPlayerTextureLeft{};
/**
 * \class CannotOpenPlayerTextureRightStationary
 * @brief Exception that is thrown when the file for the texture of the player ship facing right while stationary cannot be opened
 * 
 */
class CannotOpenPlayerTextureRightStationary{};
/**
 * \class CannotOpenPlayerTextureLeftStationary
 * @brief Exception that is thrown when the file for the texture of the player ship facing left while stationary cannot be opened
 * 
 */
class CannotOpenPlayerTextureLeftStationary{};

/**
 * \class Spaceship
 * @brief Determines inputs for spaceship movements and executes spaceship movements
 * 
 */
class Spaceship{
public:
    /**
     * @brief Construct a new Spaceship object
     * 
     * @param screenWidth Width of the game window
     * @param screenHeight Height of the game window
     * @param spaceshipWidth Width of the player's spaceship
     * @param spaceshipHeight Height of the player's spaceship
     * @param mapHeight Height of the mini-map
     * @param moveDistance Amount of pixels the player ship can move for every movement
     */
    Spaceship(float screenWidth, float screenHeight, float spaceshipWidth, float spaceshipHeight, float mapHeight, float moveDistance);
    /**
     * @brief Sets the initial parameters of the spaceship object and sets its texture
     * 
     */
    void initialiseShip();
    /**
     * @brief Get the Player object
     * 
     * @return sf::RectangleShape& of the player spaceship
     */
    sf::RectangleShape& getPlayer();
    /**
     * @brief Get the Movement Inputs object
     * 
     * @param movementInputs current direction the ship is moving in
     * @return std::tuple<bool, bool, bool, bool, bool> Bools indicating the direction the ship should move in
     */
    std::tuple<bool, bool, bool, bool, bool> getMovementInputs(std::tuple<bool, bool, bool, bool, bool> movementInputs); 
    /**
     * @brief Move the spaceship in the desired directions
     * 
     * @param moveLeft Bool to indicate the ship should move left
     * @param moveRight Bool to indicate the ship should move right
     * @param moveUp Bool to indicate the ship should move up
     * @param moveDown Bool to indicate the ship should move down
     */
    void moveSpaceship(bool moveLeft = false, bool moveRight = false, bool moveUp = false, bool moveDown = false);
    /**
     * @brief Bool indicating which direction the spaceship is facing
     * 
     */
    bool spaceshipDirection = true;
    /**
     * @brief Bool indicating if the spaceship is currently moving
     * 
     */
    bool spaceshipIsMoving = false;
    /**
     * @brief Checks if the spaceship has fuel before executing a movement
     * 
     * @param moveLeft Bool to indicate the ship should move left
     * @param moveRight Bool to indicate the ship should move right
     * @param moveUp Bool to indicate the ship should move up
     * @param moveDown Bool to indicate the ship should move down
     * @param hasFuel Bool to indicate the ship has fuel available
     */
    void checkSpaceshipMovement(bool moveLeft = false, bool moveRight = false, bool moveUp = false, bool moveDown = false, bool hasFuel = true);
    /**
     * @brief Force the ship to move vertically downwards when out of fuel
     * 
     */
    void crashSpaceship();
    bool hasPassenger = false;

private:
    float spaceshipHeight_;
    float spaceshipWidth_;
    float screenHeight_;
    float screenWidth_;
    float mapHeight_;
    float moveDistance_;
    float mapOffset = 18.0f;

    sf::RectangleShape player_;
    sf::Texture playerTexture_right;
    sf::Texture playerTexture_left;
    sf::Texture playerTexture_right_stationary;
    sf::Texture playerTexture_left_stationary;

    std::string playerTexture_right_stationary_file = ("resources/Spaceship_right_stationary.png");
    std::string playerTexture_left_stationary_file = ("resources/Spaceship_left_stationary.png");
    std::string playerTexture_right_file = ("resources/Spaceship_right.png");
    std::string playerTexture_left_file = ("resources/Spaceship_left.png");
};
#endif