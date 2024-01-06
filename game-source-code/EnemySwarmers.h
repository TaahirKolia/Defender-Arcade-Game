#ifndef ENEMYSWARMER_H
#define ENEMYSWARMER_H

#include <SFML/Graphics.hpp>
#include <iostream> 
#include "Enemies.h"

/**
 * \class EnemySwarmers
 * @brief Derived class of the Enemies base class
 * 
 */
class EnemySwarmers:virtual public Enemies{

    public:
    /**
     * @brief Construct a new Enemy Swarmers object
     * 
     * @param screenHeight Height of the game screen
     * @param screenWidth Width of the scrollable game screen
     * @param mapHeight  Height at which the map ends
     * @param spaceshipWidth Width of the space ship
     * @param spaceshipHeight Height of the space ship
     */
        EnemySwarmers(float screenHeight, float screenWidth, float mapHeight,float spaceshipWidth, float spaceshipHeight);
        /**
         * @brief Determines which side of player's ship the pod died and spawns the swarmers the swarmers at an offet position near it
         * 
         * @param podXCord X coordinate of where the pod is eliminated
         * @param podYCord Y coordinate of where the pod is eliminated
         * @param shipXCord The x coordinate of the player's spaceship
         * @param shipYCord The y coordinate of the player's spaceship
         * @param spawnTime The minimum elapsed time before swarmers can spawn 
         */
        void swarmerSpawnConditions(int podXCord, int podYCord, int shipYCord, int shipXCord ,float spawnTime);
        /**
         * @brief Calls the swarmerSpawnConditions for a specific spawn time
         * 
         * @param podXCord X coordinate of where the pod is eliminated
         * @param podYCord Y coordinate of where the pod is eliminated
         * @param shipXCord The x coordinate of the player's spaceship
         * @param shipYCord The y coordinate of the player's spaceship
         */
        void spawnSwarmers(float podXCord, float podYCord,  int shipYCord, int shipXCord);
        /**
         * @brief Calculaets the target coordinate for each swarmer
         * 
         * @param shipXCord The x coordinate of the player's spaceship
         * @param shipYCord The y coordinate of the player's spaceship
         * @param sampleTime The time at which the the player's spaceship position is sampled 
         */
        void determineTargetPoisition(float shipXCord, float shipYCord, float& sampleTime);
        /**
         * @brief Performs the closest path calculation for each swarmer
         * 
         * @param moveDistance Move distance of the swarmers in the x and y direction 
         */
        void swarmerMovement(float moveDistance);
        /**
         * @brief Calculates the shortest path to player ship and moves a swarmer in that direction 
         * 
         * @param moveDistance Move distance of the swarmers x and y direction 
         * @param i index for the swarmers vector 
         */
        void closestPath(float moveDistance, int i);
        /**
         * @brief Samples postions of the player's spaceship.
         * 
         * @param shipXCord The x coordinate of the player's spaceship
         * @param shipYCord The y coordinate of the player's spaceship
         */
        void samplingOperations(float shipXCord, float shipYCord);
        /**
         * @brief Determines the relative displacement between the swarmers and the spaceship 
         * 
         * @param i index for the swarmers vector 
         */
        void calcTargetCords(int i);
        /**
         * @brief Calls the necessary movement functions to move all the swarmers accordingly
         * 
         * @param shipXCord 
         * @param shipYCord 
         */
        void moveSwarmers(float shipXCord, float shipYCord) ;
        /**
         * @brief Checks that the swarmers dont leave the vertical bounds of teh map and enables scrolling 
         * 
         * @param index index for the swarmers vector 
         */
        void checkSwarmerBounds(int index);
        /**
         * @brief Dtermines the angle between the swarmers and the player's spaceship
         * 
         * @param target The target x coordinate
         * @param moveDistance Move distance of the swarmers x and y direction 
         * @param index index for the swarmers vector 
         */
        void determineAngle(float target, float moveDistance, int index);
        /**
         * @brief Destroy the Enemy Swarmers object
         * 
         */
        ~EnemySwarmers();
    
    private:
        std::vector<float> targetXCord_;
        std::vector<float> targetYCord_;
        sf::Clock sampleClock;
        float angle;
        float xCord_;
        float yCord_;
};
#endif  