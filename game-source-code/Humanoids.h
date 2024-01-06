#ifndef HUMANOIDS
#define HUMANOIDS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

/**
 * \class Humanoids
 * @brief Spawns in humanoids and handles humanoid motion
 * 
 */
class Humanoids{
public:
    /**
     * @brief Construct a new Humanoids object
     * 
     * @param screenWidth Width of the game window
     * @param screenHeight Height of the game window
     * @param mapHeight Height of the mini-map
     */
    Humanoids(float screenWidth, float screenHeight, float mapHeight);

    float humanoidHeight = 42.0f;   //42

    /**
     * @brief sets the initial parameters of the humanoid object and sets its texture
     * 
     */
    void initialiseHumanoidObjects();
    /**
     * @brief Calls private functions to spawn and move humanoids
     * 
     */
    void doHumanoidOperations();
    /**
     * @brief sets the position of the humanoid object
     * 
     * @param xCord x coordinate of where the humanoid will spawn
     * @param yCord y coordinate of where the humanoid will spawn
     */
    void placeHumanoids(float xCord, float yCord);
    /**
     * @brief sets the position of humanoid hit boxes to match the position of the humanoids
     * 
     */
    void placeHumanoidHitBoxes();
    /**
     * @brief Get the Humanoid Hit Box Vector object
     * 
     * @return std::vector<sf::RectangleShape>& vector of rectangleShapes containing all humanoid hitboxes
     */
    std::vector<sf::RectangleShape> &getHumanoidHitBoxVector();
    /**
     * @brief Get the Ground Humanoids Vector object
     * 
     * @return std::vector<sf::RectangleShape>& vector of rectangleshapes containing all humanoids at ground level
     */
    std::vector<sf::RectangleShape> &getGroundHumanoidsVector();
    /**
     * @brief Get the Raising Humanoids Vector object
     * 
     * @return std::vector<sf::RectangleShape>& vector of rectangleshapes containing all humanoids that are currently being abducted
     */
    std::vector<sf::RectangleShape> &getRaisingHumanoidsVector();
    /**
     * @brief Get the Falling Humanoids Vector object
     * 
     * @return std::vector<sf::RectangleShape>& vector of rectangleshapes containing all humanoids that are currently falling to the ground
     */
    std::vector<sf::RectangleShape> &getFallingHumanoidsVector();
    /**
     * @brief Spawns a humanoid capable of moving upwards
     * 
     * @param landerPos The location of the collision between a lander and a humanoid on the ground
     */
    void spawnRaisingHumanoid(sf::Vector2f landerPos);
    /**
     * @brief Spawns a humanoid capable of moving downwards
     * 
     * @param landerPos Location of the collision between the lander and the player's ship, shield or laser
     */
    void spawnFallingHumanoid(sf::Vector2f landerPos);
    /**
     * @brief Spawns a new humanoid at ground level
     * 
     * @param landerPos Location at which the lander was placed on the ground
     */
    void spawnGroundHumanoid(sf::Vector2f landerPos);
    int maxHumanoidCount = 5;
    /**
     * @brief Increase the counter of how many humanoids have been killed
     * 
     */
    void incrementKilledHumanoids();
    /**
     * @brief Get the Killed Humanoids object
     * 
     * @return int of how many humanoids have been killed
     */
    int getKilledHumanoids();
    /**
     * @brief Moves humanoids capable of raising upwards at a constant rate
     * 
     */
    void moveRaisingHumanoids();
    /**
     * @brief Moves humanoids capable of falling downwards at a constant rate
     * 
     */
    void moveFallingHumanoids();
    static int killedHumanoids;
    /**
     * @brief Resets all variables relating to humanoids and clears all humanoid vectors
     * 
     */
    void reset();
    
private:
    float screenHeight_;
    float screenWidth_;
    float mapHeight_;
    void initialiseHumanoids();
    void initialiseHumanoidHitBoxes();
    sf::RectangleShape humanoid_;
    float humanoidWidth = 18.0f;    //18
    sf::Clock humanoidSpawnTimer;
    float humanoidSpawnTime = 3.0f;
    float humanoidsSpawnedCount = 0.0f;
    std::vector<sf::RectangleShape> groundHumanoidVector;
    std::vector<sf::RectangleShape> raisingHumanoidVector;
    std::vector<sf::RectangleShape> fallingHumanoidVector;
    sf::Texture humanoidTexture;
    std::string humanoid_texture_file = "resources\\Humanoid.png";
    float humanoidYcord = screenHeight_ - humanoidHeight/2;
    float humanoidXcord = 0.0f;
    int humanoidXrange = screenWidth_ - 2*humanoidWidth; 
    sf::RectangleShape humanoidHitBox_;
    float humanoidHitBoxWidth = humanoidWidth;
    float humanoidHitBoxHeight = screenHeight_ - mapHeight_;
    std::vector<sf::RectangleShape> humanoidHitBoxVector;
    float raisingMoveDistance = 1.0f;
    float fallingMoveDistance = 2.0f;
};

#endif