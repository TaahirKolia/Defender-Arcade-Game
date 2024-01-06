#ifndef SHIELDS_H
#define SHIELDS_H

#include <SFML/Graphics.hpp>

/**
 * \class Shields
 * @brief handles the creation of the shield object and the shield bar
 * 
 */
class Shields{

    public:
        /**
         * @brief Construct a new Shields object
         * 
         * @param spaceshipXpos x coordinate of the player's spaceship
         * @param spaceshipYpos y coordinate of the player's spaceship
         * @param spaceshipWidth Width of the player's spaceship
         * @param spaceshipHeight Height of the player's spaceship
         */
        Shields(float spaceshipXpos, float spaceshipYpos, float spaceshipWidth, float spaceshipHeight);
        /**
         * @brief Checks if a collision with the shield has occurred
         * 
         * @param shieldLanderCollision A collision between the shield and a lander has occurred
         * @param shieldLanderMissileCollision A collision between the shield and a lander missile has occurred
         * @param downKidnapperShieldCollision A collision between the shield and a kidnapping lander moving downwards has occurred
         * @param upKidnapperShieldCollision A collision between the shield and a kidnapping lander moving upwards has occurred
         */
        void checkPlayerShields(bool shieldLanderCollision, bool shieldLanderMissileCollision, bool downKidnapperShieldCollision,  bool upKidnapperShieldCollision);
        /**
         * @brief Decrease the number of player shields available
         * 
         */
        void reducePlayerShields();
        /**
         * @brief Get the Player Shields object
         * 
         * @return int indicating how many shields the player has left
         */
        static int getPlayerShields();
        /**
         * @brief Resets all variables and clears all vectors relating to shields
         * 
         */
        void reset();
        /**
         * @brief Calls functions to set the initial parameters of all shield objects
         * 
         */
        void initialiseShieldObjects();
        /**
         * @brief Sets the size of the shield to allow for protection of the player's spaceship 
         * 
         */
        void activateShield();
        /**
         * @brief Sets the initial parameters of the shield bar
         * 
         */
        void initialiseShieldBar();
        /**
         * @brief Changes the numeber of shields displayed based on the number of shields the player has remaining
         * 
         */
        void updateShieldBar();
        /**
         * @brief Set the Shield Bar object's position
         * 
         */
        void setShieldBarPosition();
        /**
         * @brief Sets the shield bar to being completely filled
         * 
         */
        void fullShieldBar();
        /**
         * @brief Reads in input to determine if a shield should be activated
         * 
         */
        void checkShieldInput();
        /**
         * @brief Moves the shield to match the spaceship's position
         * 
         * @param spaceshipXpos x coordinate of the ship at the cuerrent time
         * @param spaceshipYpos y coordinate of the ship at the cuerrent time
         */
        void moveShield(float spaceshipXpos, float spaceshipYpos);
        /**
         * @brief Get the Shield object
         * 
         * @return sf::RectangleShape& of the shield object
         */
        sf::RectangleShape& getShield();
        /**
         * @brief Get the Shield Bar object
         * 
         * @return std::vector<sf::RectangleShape>& vector of rectangleshapes containing all shield icons
         */
        std::vector<sf::RectangleShape>& getShieldBar();
        static int availableShields;
        /**
         * @brief resizes the player shield so that it no longer protects the player
         * 
         */
        void destroyShield();

    private:
        sf::RectangleShape shieldsFullSymbol;
        sf::RectangleShape shieldsEmptySymbol;
        std::string shieldFullFile = "resources/fullShield.png";
        std::string shieldEmptyFile = "resources/emptyShield.png";
        std::vector<sf::RectangleShape> shieldsVector;
        sf::Texture shieldsFull;
        sf::Texture shieldsEmpty;
        size_t totalshields = 3; 
        sf::RectangleShape shield_;
        float spaceshipXpos_;
        float spaceshipYpos_;
        float spaceshipWidth_;
        float spaceshipHeight_;
        float shieldRadius_;
        float shieldWidth_;
        float shieldHeight_;
        bool isShieldActive = false;
        sf::Clock shieldTimer;
        float maxShieldTime = 10000.0f;
};

#endif