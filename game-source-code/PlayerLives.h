#ifndef PLAYERLIVES_H
#define PLAYERLIVES_H

#include <SFML/Graphics.hpp>

/** \class PlayerLives
 * @brief Keeps track of the player's lives
 * 
 */
class PlayerLives{

    public:
        /**
         * @brief Construct a new Player Lives object
         * 
         */
        PlayerLives();
        /**
         * @brief Reduces player lives and updates the life bar
         * 
         * @param collisionClock Clock used to ensure that player cant lose a life immediately after having lost a life
         */
        void checkPlayerLives(sf::Clock collisionClock);
        /**
         * @brief Reduces the player's lives
         * 
         */
        void reducePlayerLives();
        /**
         * @brief Get the Player Lives object
         * 
         * @return returns the available player's lives as int  
         */
        static int getPlayerLives();
        /**
         * @brief Resets the life bar adn available lives
         * 
         */
        void reset();
        /**
         * @brief Sets the properties of the life bar
         * 
         */
        void initialiseLifeBar();
        /**
         * @brief Updates the life bar if  a player loses a life
         * 
         */
        void updateLifeBar();
        /**
         * @brief Sets the life bar's position 
         * 
         */
        void setLifeBarPosition();
        /**
         * @brief Places three full hearts in a vector 
         * 
         */
        void fullLifeBar();
        /**
         * @brief Get the Lives Bar object
         * 
         * @return returns a std::vector<sf::RectangleShape>& which contains the life bar 
         */
        std::vector<sf::RectangleShape>& getLivesBar();
        /**
         * @brief Destroy the Player Lives object
         * 
         */
        ~PlayerLives();

    private:
        static int availableLives;
        sf::RectangleShape livesFullSymbol;
        sf::RectangleShape livesEmptySymbol;
        std::string lifeFullFile = "resources/fullHeart.png";
        std::string lifeEmptyFile = "resources/emptyHeart.png";
        std::vector<sf::RectangleShape> livesVector;
        sf::Texture livesFull;
        sf::Texture livesEmpty;
        size_t totalLives = 3; 
};

#endif


