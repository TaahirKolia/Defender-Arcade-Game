#ifndef ENEMYPODS_H
#define ENEMYPODS_H

#include <SFML/Graphics.hpp>
#include <iostream> 
#include "Enemies.h"

/** \class EnemyPods
 * @brief Derived class of the Enemies base class
 * 
 */
class EnemyPods:public Enemies{

    public:
    /**
     * @brief Construct a new Enemy Pods object
     * 
     * @param screenHeight Height of the game screen
     * @param scrollableWidth Width of the scrollable game screen
     * @param mapHeight  Height at which the map ends
     * @param spaceshipWidth Width of the space ship
     * @param spaceshipHeight Height of the space ship
     */
        EnemyPods(float screenHeight, float screenWidth, float mapHeight,float spaceshipWidth, float spaceshipHeight);
        /**
         * @brief  This function spawns the pods provided that the elapsed time between the previous and current spawnable pod is long enough
         * whilst also checking that there are not more than a maximum number of pods at one instant and that the total number of 
         * the pods spawned in has not reached the maximum limit. Additionally, there cannot be any swarmers on the map.
         * 
         * @param generatedXCord The randomly generated x spawn coordinates.
         * @param generatedYCord The randomly generated y spawn coordinates.
         * @param spawnTime The elasped clock time that will allow an enemy entity to spawn in.
         * @param numOfSwarmers Number of concurrent swarmers spawned on the map.
         */
        void spawnConditionsPods(int generatedXCord, int generatedYCord, float spawnTime, int numOfSwarmers);
        /**
         * @brief This function calls the different enemies spawnBounds to ensure that the random generation of coordinates and boundary checks are carried out
         * and the spawnConditionsPods function is called
         * 
         * @param shipXCord The x coordinate of the player's spaceship
         * @param shipYCord The y coordinate of the player's spaceship
         * @param numOfSwarmers Number of concurrent swarmers spawned on the map.
         */
        void spawnPods(float shipXCord, float shipYCord, int numOfSwarmers);
        /**
         *@brief The parameters required to for the enemyMovementConditions function are defined within this function and thereafter passed to the  enemyMovementConditions function.
         * 
         */
        virtual void declareMovements(int) override ;
        /**
           * @brief Carries out the movement for every pod. 
         * 
         */
        virtual void moveEnemies() override; 
        /**
         * @brief Destroy the Enemy Pods object
         * 
         */
        ~EnemyPods();
    protected:
};
#endif