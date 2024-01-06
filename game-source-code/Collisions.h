#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <SFML/Graphics.hpp>
#include <iostream> 
#include "LanderMissiles.h"

#define MOVEDISTANCE 10.0f

/**
 * \class Collisions
 * @brief detects if collisons have occurred between the objects passed into the functions
 * 
 */
class Collisions{

    public:
        /**
         * @brief Construct a new Collisions object
         * 
         */
        Collisions();
        /**
         * @brief Determines the next possible location of the player's spaceship after one movement
         * 
         * @param spaceShip player's spaceship object
         */
        void NextPosition(sf::RectangleShape& spaceShip);
        /**
         * @brief Checks if a single game entity has collided with the player's spaceship
         * 
         * @param Object Game entity that may collide with the player
         * @param spaceShip Player's spaceship object
         * @return std::tuple<bool, sf::Vector2f> Returns the position of the collision and a Bool indicating that the collision has taken place
         */
        std::tuple<bool, sf::Vector2f> checkObject(std::vector<sf::RectangleShape>& Object,sf::RectangleShape& spaceShip);
        /**
         * @brief Checks if enemy missiles have collided with the player's spaceship
         * 
         * @param EnemyMissile vector containing the missiles that have been fired
         * @param landerMissile Object of the lander missiles class
         * @param spaceShip player's spaceship object
         * @return true if a collision has occurred
         * @return false if no collision has occurred
         */
        bool checkEnemyMissiles(std::vector<sf::RectangleShape>& EnemyMissile, LanderMissiles& landerMissile, sf::RectangleShape& spaceShip);
        /**
         * @brief Checks if a collision between an enemy object and the ship's laser has occurred
         * 
         * @param Enemy Vector containing the enemy objects
         * @param Laser Vector containing the player's lasers that have been fired
         * @param laserPos Vector containing the distances each laser has travelled
         * @return std::tuple<bool, sf::Vector2f> Bool indicating whether the collision has occurred. Vector2f indicating the loaction of the collison on the screen
         */
        std::tuple<bool, sf::Vector2f> checkLaser(std::vector<sf::RectangleShape>& Enemy, std::vector<sf::RectangleShape>& Laser, std::vector<float>& laserPos);
        /**
         * @brief Checks if a lander has collided with a humanoid hitbox
         * 
         * @param hitbox vector containing all humanoid hitbox objects
         * @param lander vector containing all lander objects
         * @return std::tuple<bool, sf::Vector2f> Bool indicating whether the collision has occurred. Vector2f indicating the loaction of the collison on the screen
         */
        std::tuple<bool, sf::Vector2f> checkHumanoidHitBox(std::vector<sf::RectangleShape> &hitbox, std::vector<sf::RectangleShape> &lander);
        /**
         * @brief Checks if a collision between a kidnappingLander and a humanoid has occurred.
         * 
         * @param lander vector containing all kidnappingLanders that can move downwards
         * @param humanoid vector containing all humanoids currently on the ground
         * @param hitBox vector containing all hitboxes of humanoids currently on the ground
         * @return std::tuple<bool, sf::Vector2f> Bool indicating whether the collision has occurred. Vector2f indicating the loaction of the collison on the screen
         */
        std::tuple<bool, sf::Vector2f> checkHumanoid(std::vector<sf::RectangleShape> &lander, std::vector<sf::RectangleShape> &humanoid, std::vector<sf::RectangleShape> &hitBox);
        /**
         * @brief Checks if a kidnapper moving upwards has been shot by a player's laser
         * 
         * @param lander vector containing all kidnappingLanders that can move upwards
         * @param passenger vector containing whether a kidnapping lander moving upwards has an associated humanoid that has been kidnapped
         * @param human vector containing all humanoids that can move upwards
         * @param laser vector containing the player's lasers that have been fired
         * @param laserPos Vector containing the distances each laser has travelled
         * @return std::tuple<bool, sf::Vector2f> Bool indicating whether the collision has occurred. Vector2f indicating the loaction of the collison on the screen
         */
        std::tuple<bool, sf::Vector2f> checkKidnappersLaser(std::vector<sf::RectangleShape> &lander, std::vector<bool> &passenger, std::vector<sf::RectangleShape> &human, std::vector<sf::RectangleShape> &laser, std::vector<float> &laserPos);
        /**
         * @brief Checks if a kidnapping lander capable of moving upwards has collided with a game object
         * 
         * @param lander vector containing all kidnappingLanders that can move upwards
         * @param passenger vector containing whether a kidnapping lander moving upwards has an associated humanoid that has been kidnapped
         * @param human ector containing all humanoids that can move upwards
         * @param object Game entity that may collide with the kidnapping landers
         * @return std::tuple<bool, sf::Vector2f> Bool indicating whether the collision has occurred. Vector2f indicating the loaction of the collison on the screen
         */
        std::tuple<bool, sf::Vector2f> checkKidnappersObject(std::vector<sf::RectangleShape> &lander, std::vector<bool> &passenger, std::vector<sf::RectangleShape> &human, sf::RectangleShape &object);
        /**
         * @brief Checks if a humanoid moving upwards or downwards has been shot by the player's laser
         * 
         * @param Enemy Vector containing the humanoids that are moving either upwards or downwards
         * @param Passengers Vector indicating whether each humanoid is a passenger of a kidnapping lander that is capable of moving upwards
         * @param Laser vector containing the player's lasers that have been fired
         * @param laserPos Vector containing the distances each laser has travelled
         * @return true if the laser has collided with the humanoid
         * @return false if the laser has not collided with the humanoid
         */
        bool checkHumanoidLaser(std::vector<sf::RectangleShape> &Enemy, std::vector<bool> &Passengers, std::vector<sf::RectangleShape> &Laser, std::vector<float> &laserPos);
        ~Collisions();

    private:
        sf::FloatRect nextPos;
};
#endif