#ifndef LANDERMISSILES_H
#define LANDERMISSILES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

/** \class LanderMissiles
 * @brief Produces missiles that periodically originate from the landers 
 * 
 */
class LanderMissiles{

    public:
        /**
         * @brief Construct a new Lander Missiles object
         * 
        * @param screenHeight Height of the game screen
        * @param screenWidth Width of the scrollable game screen
        * @param mapHeight  Height at which the map ends
         */
        LanderMissiles(float screenHeight, float screenWidth, float mapHeight);
        /**
         * @brief Places the missiles within a vector and sets its start position
         * 
         * @param landers_ vector containing lander entities 
         */
        void launchMissiles(std::vector<sf::RectangleShape> landers_);
        /**
         * @brief Periodically samples the position of the player's spaceship 
         * 
         * @param landers_ vector containing lander entities 
         */
        void samplePositions(std::vector<sf::RectangleShape> landers_);
        /**
         * @brief Periodically determines the relative position between each lander and the player's spaceship 
         * 
         * @param shipXCord The x coordinate of the player's spaceship
         * @param shipYCord The y coordinate of the player's spaceship
         * @param landers_ vector containing lander entities 
         * @param sampleTime Time at which the position is periodically sampled
         */
        void determineTargetPoisition(float& shipXCord, float& shipYCord, std::vector<sf::RectangleShape> landers_, float& sampleTime);
        /**
         * @brief Clears the necesseary vectors before sampling positions
         * 
         * @param shipXCord The x coordinate of the player's spaceship
         * @param shipYCord The y coordinate of the player's spaceship
         * @param landers_ vector containing lander entities 
         */
        void samplingOperations(float& shipXCord, float& shipYCord, std::vector<sf::RectangleShape> landers_);
        /**
         * @brief Determines the relative position of a lander and the player's spaceship
         * 
         * @param index index relating the lander coordinate's vector
         */
        void calcTargetPos(int index);
        /**
         * @brief Calculates the shortest path to the spaceship and moves the missiles in that direction 
         * 
         * @param moveDistance move distance of the missiles
         * @param i index used to access the missiles vector 
         */
        void moveShortestPath(float moveDistance, int i);
        /**
         * @brief Moves each missile along the shortest path while checking for collisions
         * 
         * @param moveDistance move distance of the missiles
         */
        void moveMissiles(float moveDistance);
        /**
         * @brief Set the Missiles entities properties such as its size and origin 
         * 
         * @param landers_ vector containing lander entities 
         */
        void setMissiles(std::vector<sf::RectangleShape> landers_);
        /**
         * @brief Checks if a missile wraps around the map or goes out of bounds 
         * 
         * @param index index used to access the missiles vector 
         */
        void checkMissileBounds(int index);
        /**
         * @brief Spawns and moves the lander missiles toward the player ship 
         * 
         * @param landers_ vector containing lander entities 
         * @param shipXCord The x coordinate of the player's spaceship
         * @param shipYCord The y coordinate of the player's spaceship
         */
        void start(std::vector<sf::RectangleShape> landers_, float shipXCord, float shipYCord);
        /**
         * @brief Clears the missiles vector
         * 
         */
        void resetMissiles();
        /**
         * @brief Get the Missiles Vector object
         * 
         * @return returns a std::vector<sf::RectangleShape>& containing the missile entities 
         */
        std::vector<sf::RectangleShape>& getMissilesVector();
        /**
         * @brief Get the Coordinates Vector object
         * 
         * @return returns a std::vector<sf::Vector2f>& which contains the lander's coordinates
         */
        std::vector<sf::Vector2f> & getCoordinatesVector();
        /**
         * @brief Deletes the accompanied information of the lander missile
         * 
         * @param missileIndex index used to access the missiles vector 
         */
        void deleteMissileInfo(int missileIndex);
        /**
         * @brief Destroy the Lander Missiles object
         * 
         */
        ~LanderMissiles();

    private:

        int totalMissiles = 5; 
        float screenHeight_;
        float scrollableScreenWidth_;
        float mapHeight_;
        float angle;
        float xCord_;
        float yCord_;
        std::vector<sf::RectangleShape> missiles;
        std::vector<sf::Vector2f> landerCenter;
        sf::Clock missileClock;
        sf::RectangleShape missile;
        std::vector<sf::Vector2f> landerCoordinates;
        std::vector<float> targetXCord_;
        std::vector<float> targetYCord_;
};

#endif