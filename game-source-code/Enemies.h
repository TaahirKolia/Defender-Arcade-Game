#ifndef ENEMIES_H
#define ENEMIES_H

#include <SFML/Graphics.hpp>
#include <iostream> 
#include <cmath>
/**
 * \class Enemies
 * @brief Generic base class that handles the initialisation, the spawning, and the movement of enemies.   
 */

class Enemies{
    public:
        /**
         * @brief Construct a new Enemies object
         * 
         * @param screenHeight Height of the game screen
         * @param screenWidth  Width of the scrollable game screen
         * @param mapHeight  Height at which the map ends
         * @param spaceshipWidth Width of the space ship
         * @param spaceshipHeight Height of the space ship
         */
        Enemies(float screenHeight, float screenWidth, float mapHeight,float spaceshipWidth, float spaceshipHeight);
        /**
         * @brief Destroy the Enemies object
         * 
         */
        virtual ~Enemies();
        /**
         * @brief Sets the properties such as the origin, size, and texture of the enemy entity resets certain parameters
         * 
         */
        virtual void initialiseEnemies() ;
        /**
         * @brief This function spawns the enemies provided that the elapsed time between the previous and current spawnable entity is long enough
         * whilst also checking that there are not more than a maximum number of the enemy entity at one instant and that the  total number of 
         * the entities spawned in has not reached a limit. 
         * 
         * @param generatedXCord The randomly generated x spawn coordinates.
         * @param generatedYCord The randomly generated y spawn coordinates.
         * @param spawnTime The elasped clock time that will allow an enemy entity to spawn in.
         */
        virtual void spawnConditions(int generatedXCord, int generatedYCord, float spawnTime) ; 
        /**
         * @brief This function randomly generates a pair of coordinates that are guaranteed to be within the bounds of the designated map. 
         * 
         */
        void spawnCoordinates() ;
        /**
         * @brief Ensures that the randomly generated spawn coordinates for the enemy entities are not within a close proximity to the player ship.
         * If the randomly generated coordinates are within a close proximity, they are randomly regenarated until a satisfactorily pair of coordinates is obtained
         * 
         * @param shipXCord The x coordinate of the player's spaceship
         * @param shipYCord The y coordinate of the player's spaceship
         */
        void spawnBounds(float shipXCord, float shipYCord)  ;
        /**
         * @brief This function calls the different enemy spawn functions to ensure that the random generation of coordinates, boundary checks, and spawn conditions
         * are all carried out one after the other.
         * 
         * @param shipXCord The x coordinate of the player's spaceship
         * @param shipYCord The y coordinate of the player's spaceship
         */
        virtual void spawnEnemies(float shipXCord, float shipYCord) ;
        /**
         * @brief This function check what movement case been generated for one of the spawned entities at a time. It thereafter checks if the movement case generated 
         * for the enemy entity is valid and doesnt exceed the bounds of the map. If it is valid, the enemy entity is moved accordingly.
         * 
         * @param enemyIndex The index of the enemy entity vector whose movement is being validated
         * @param maxEnemyXCord The postion of the bottom of the enemy entity
         * @param minEnemyXCord The postion of the top of the enemy entity
         * @param maxEnemyYCord The postion of the right of the enemy entity
         * @param minEnemyYCord The postion of the left of the enemy entity
         * @param moveDistanceX The number of pixels the entity can move in the x direction
         * @param moveDistanceY The number of pixels the entity can move in the y direction
         * @param movementCase The randomly generated movement 
         */
        void enemyMovementConditions(int enemyIndex, float maxEnemyXCord, float minEnemyXCord, float maxEnemyYCord , float minEnemyYCord, 
                                    int moveDistanceX, int moveDistanceY, std::vector<int> movementCase);
        /**
         * @brief Randomly generates a different movement case for each enenmy entity that is spawned in at the time.
         * There are 8 possible different movement cases that can be generated. 
         * 
         */
        void generateMovementCases();
        /**
         * @brief The parameters required to for the enemyMovementConditions function are defined within this function and thereafter passed to the  enemyMovementConditions function.
         * 
         */
        virtual void declareMovements(int);
        /**
         * @brief Carries out the movement for every spawned enemy entity 
         * 
         */
        virtual void moveEnemies();
        /**
         * @brief Get the Enemy object
         * 
         * @return Returns a sf::RectangleShape of the enemy entity 
         */
        sf::RectangleShape& getEnemy();
        /**
         * @brief Get the Enemies Vector object
         * 
         * @return Returns a std::vector<sf::RectangleShape> which contains all the enemy entities that are spawned. 
         */
        std::vector<sf::RectangleShape>& getEnemiesVector(); 
        /**
         * @brief Resets the certain variables and clears the vectors used in the class.  
         * 
         */
        virtual void resetEnemies();

    protected:
        int xCord;
        int yCord;
        int xRange;
        int yRange;
        int concurrentEnemies; 
        int totalEnemies = 0;
        int total = 0;  
        int numOfEnemies = 0; 
        float mapHeight_;
        float screenHeight_;
        float scrollableScreenWidth_;
        float spaceshipWidth_;
        float spaceshipHeight_;
        float enemyWidth_;
        float enemyHeight_;
        std::vector<sf::RectangleShape> enemies_;
        sf::RectangleShape enemy_;    
        std::string enemyTextureFile;
        sf::Texture enemyTexture;
        sf::Clock spawnTimer;
        sf::Clock movementTime;
        sf::Clock caseClock;
        std::vector<int> movementCase;    

    private:
};
#endif