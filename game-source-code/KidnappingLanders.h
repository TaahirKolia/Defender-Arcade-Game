#ifndef KIDNAPINGLANDERS_H
#define KIDNAPPINGLANDERS_H

#include <SFML/Graphics.hpp>
#include <iostream> 
#include "Enemies.h"
#include "EnemyLanders.h"

/**
 * \class KidnappingLanders
 * @brief Handles the spawning and movement of landers that abduct humanoids
 * 
 */
class KidnappingLanders: public EnemyLanders
{
    public:
        /**
         * @brief Construct a new Kidnapping Landers object
         * 
         * @param screenHeight Height of teh game window
         * @param scrollableScreenWidth Width of the game window
         * @param mapHeight Height of the mini-map
         * @param spaceshipWidth Width of the player's spaceship
         * @param spaceshipHeight Height of the player's spaceship
         */
        KidnappingLanders(float screenHeight, float scrollableScreenWidth, float mapHeight,float spaceshipWidth, float spaceshipHeight);
        /**
         * @brief Sets the initial parameters of the landers, and sets its texture
         * 
         */
        virtual void initialiseEnemies() override;
        /**
         * @brief Spawns a lander capable of moving vertically downwards
         * 
         * @param landerPos location of collision between lander and humanoid hitbox
         */
        void spawnKidnapper(sf::Vector2f landerPos);
        /**
         * @brief  Spawns a lander capable of moving vertically upwards
         * 
         * @param landerPos location of collision between lander and humanoid
         */
        void spawnUpKidnapper(sf::Vector2f landerPos);
        /**
         * @brief Get the Down Kidnappers Vector object
         * 
         * @return std::vector<sf::RectangleShape>& vector of rectangleshapes containing all current landers capable of moving vertically downwards
         */
        std::vector<sf::RectangleShape> &getDownKidnappersVector();
        /**
         * @brief Get the Up Kidnappers Vector object
         * 
         * @return std::vector<sf::RectangleShape>&  vector of rectangleshapes containing all current landers capable of moving vertically upwards
         */
        std::vector<sf::RectangleShape> &getUpKidnappersVector();
        /**
         * @brief Get the Up Kidnappers Pasengers Vector object
         * 
         * @return std::vector<bool>& vector of bools containing whether or not a lander has a passenger or not
         */
        std::vector<bool> &getUpKidnappersPasengersVector();
        /**
         * @brief Calls specific move functions for movement of kidnapping landers
         * 
         */
        void moveKidnappers();
        /**
         * @brief Moves the appropriate landers vertically downwards
         * 
         */
        void moveDownKidnappers();
        /**
         * @brief Moves the appropriate landers vertically upwards
         * 
         */

        void moveUpKidnappers();
        /**
         * @brief Resets all variables and clears all vectors relating to kidnapping landers
         * 
         */
        virtual void resetEnemies() override;

    private:
        float kidnapperWidth_ = 54;
        float kidnapperHeight_ = 48;
        sf::RectangleShape kidnapper;
        std::vector<sf::RectangleShape> downKidnappers_;
        std::vector<sf::RectangleShape> upKidnappers_;
        std::vector<bool> upKidnappersPassengers_;

        float kidnapperMoveDistance = 1.0f;

};

#endif