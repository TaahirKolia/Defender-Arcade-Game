#ifndef ENEMYLANDERS_H
#define ENEMYLANDERS_H

#include <SFML/Graphics.hpp>
#include <iostream> 
#include "Enemies.h"

/** \class EnemyLanders
 * @brief Derived class of the Enemies base class
 * 
 */
class EnemyLanders:public Enemies{

    public:

    /**
     * @brief Construct a new Enemy Landers object
     * 
     * @param screenHeight Height of the game screen
     * @param scrollableWidth Width of the scrollable game screen
     * @param mapHeight  Height at which the map ends
     * @param spaceshipWidth Width of the space ship
     * @param spaceshipHeight Height of the space ship
     */
        EnemyLanders(float screenHeight, float scrollableWidth, float mapHeight,float spaceshipWidth, float spaceshipHeight);
        /**
         * @brief overridden function which resets the same parameters as the base class's resetEnemies function but resets 
         * an additional variable- the landersDestroyed.
         * 
         */
        virtual void resetEnemies() override;
        /**
         * @brief overridden function that is tailored to set the spawn time of landers
         * 
         * @param shipXCord The x coordinate of the player's spaceship
         * @param shipYCord The y coordinate of the player's spaceship
         */
        virtual void spawnEnemies(float shipXCord, float shipYCord) override;   
        /**
         * @brief Increments the landerDestroyed variable when a lander is eliminated.
         * 
         */
        void incrementLandersDestroyed();
        /**
         * @brief Destroy the Enemy Landers object
         * 
         */
        ~EnemyLanders();
        /**
         * @brief variable that tracks the number of landers that have been eliminated
         * 
         */
        static int landersDestroyed ; 
    private:
     
};
#endif