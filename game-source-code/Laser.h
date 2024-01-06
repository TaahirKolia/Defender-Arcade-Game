#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * \class Laser
 * @brief Handles the spawning and movement of the player's lasers
 * 
 */
class Laser{
public:
    /**
     * @brief Construct a new Laser object
     * 
     * @param screenWidth Width of the game window
     * @param spaceshipWidth Width of the player's spaceship
     * @param spaceshipHeight Height of the player's spaceship
     */
    Laser(float screenWidth, float spaceshipWidth, float spaceshipHeight);
    /**
     * @brief Sets the initial parameters of the laser
     * 
     */
    void initialiseLaser();
    /**
     * @brief Determines if a laser should be shot and the direction of the laser
     * 
     * @param shootingInputs Bools indicating if the 
     * @param shipDirection Indicates the direction the ship is facing when a laser is shot
     * @return std::tuple<bool, bool> Bools indicating which direction the laser has been shot in
     */
    std::tuple<bool, bool> getMovementInputs(std::tuple<bool, bool> shootingInputs, bool shipDirection);
    /**
     * @brief Executes the shooting of the player's lasers
     * 
     * @param shootRight Bool determining if a laser should be shot to the right
     * @param shootLeft Bool determining if a laser should be shot to the left
     * @param shipXCord The current x coordinate of the player's spaceship
     * @param shipYCord The current y coordinate of the player's spaceship
     */
    void shoot(bool shootRight, bool shootLeft, float shipXCord, float shipYCord);
    /**
     * @brief Moves the lasers in the appropriate directions
     * 
     */
    void moveLasers();
    /**
     * @brief Get the Right Laser Vector object
     * 
     * @return std::vector<sf::RectangleShape>& vector of rectangleshapes containing all current lasers capable of moving to the right 
     */
    std::vector<sf::RectangleShape>& getRightLaserVector();
    /**
     * @brief Get the Left Laser Vector object
     * 
     * @return std::vector<sf::RectangleShape>& vector of rectangleshapes containing all current lasers capable of moving to the left 
     */
    std::vector<sf::RectangleShape> &getLeftLaserVector();
    /**
     * @brief Resets all variables and clears all vectors relating to lasers
     * 
     */
    void resetLasers();
    /**
     * @brief Get the Right Laser Pos Vector object
     * 
     * @return std::vector<float>& vector of floats indicating how far right a laser has travelled
     */
    std::vector<float> &getRightLaserPosVector();
    /**
     * @brief Get the Left Laser Pos Vector object
     * 
     * @return std::vector<float>& vector of floats indicating how far left a laser has travelled
     */
    std::vector<float> &getLeftLaserPosVector();

private:
    float laserHeight = 6.0f;
    float laserWidth = 50.0f;
    sf::RectangleShape laser_;

    std::vector<sf::RectangleShape> right_laser_vect;
    std::vector<sf::RectangleShape> left_laser_vect;

    sf::Clock laserTimer;
    float laserTime = 0.3f;
    float laserSpeed = 15.0f;
    
    float screenWidth_;
    float spaceshipHeight_;
    float spaceshipWidth_;

    std::vector<float> rightLaserPosVect;
    std::vector<float> leftLaserPosVect;
    float maxLaserMovements = 800.0f/laserSpeed;

};

#endif