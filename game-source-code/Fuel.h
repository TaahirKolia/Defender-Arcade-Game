#ifndef FUEL
#define FUEL

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

/**
 * \class Fuel
 * @brief Class that handles the spawning of fuel cans and updating the fuel bar
 * 
 */
class Fuel{
public:
    /**
     * @brief Construct a new Fuel object
     * 
     * @param screenWidth width of the game window
     * @param screenHeight height of the game window
     */
    Fuel(float screenWidth, float screenHeight);
    /**
     * @brief sets default attributes of the basic fuel objects
     * 
     */
    void initialiseFuel();
    /**
     * @brief calls functions to spawn in fuel and amend the fuel bar
     * 
     * @param spaceshipIsMoving bool to indicate whether the player is currently moving
     */
    void doFuelOperations(bool spaceshipIsMoving);
    /**
     * @brief Sets the location of fuel cans
     * 
     * @param xCord x coordinate of fuel can
     * @param yCord y coordinate of fuel can
     */
    void placeFuel(float xCord, float yCord);
    /**
     * @brief Get the Fuelcan Vect object
     * 
     * @return std::vector<sf::RectangleShape>& vector of rectangelShapes containing all currently spawned fuel cans
     */
    std::vector<sf::RectangleShape>& getFuelcanVect();
    /**
     * @brief Get the Fuel Bar object
     * 
     * @return std::vector<sf::RectangleShape>& vector of rectangleShapes containing all elements relating to the fuel bar
     */
    std::vector<sf::RectangleShape>& getFuelBar();
    /**
     * @brief Get the Fuel Level object
     * 
     * @return float of the fuel level of the player
     */
    float getFuelLevel();
    /**
     * @brief informs if the player has fuel remaining
     * 
     * @return true if the player has fuel remaining
     * @return false if the player has no fuel remaining
     */
    bool checkFuelLevel();
    /**
     * @brief resets all private variables to their default values, and clears all vectors
     * 
     */
    void resetFuel();
    /**
     * @brief increases the players fuel level
     * 
     */
    void addFuel();
    
private:
    float screenHeight_;
    float screenWidth_;

    float fuelcanHeight = 50.0f;
    float fuelcanWidth = 50.0f;
    sf::RectangleShape fuelcan_;
    sf::Texture fuelcanTexture;
    std::string fuelcan_texture_file = "resources\\Fuel_potion.png";

    std::vector<sf::RectangleShape>fuelcan_vect;
    std::vector<sf::RectangleShape>fuelBar_vect;
    sf::Clock fuelSpawnTimer;

    float maxFuelLevel = 100;
    float fuelLevel = maxFuelLevel;
    float fuelBarHeight = 50.0f;
    float fuelDecay = 0.05f;
    float fuelBarWidth = 3*fuelLevel;
    sf::RectangleShape fuelBar_;
    float fuelBarXpos = 25;
    float fuelBarYpos = 150;

    float maxFuelcans = 10;

    int xRange = screenWidth_ - fuelcanWidth/2;
    float yCord = screenHeight_-fuelcanHeight/2;
    float fuelSpawnTime = 3.0f;

    void doFuelBarOperations(bool spaceshipIsMoving);
    void doFuelcanOperations();
    void initialiseFuelcan();
    void initialiseFuelBar();

    sf::RectangleShape fuelBarBackground;
    float fuelBarBackgroundOutlineThickness = 6.0f;
    float fuelBarBackgroundWidth = fuelBarWidth;
    float fuelBarBackgroundHeight = fuelBarHeight;
    
    sf::RectangleShape fuelBarIcon;
    float fuelBarIconSize = fuelBarHeight+2*fuelBarBackgroundOutlineThickness;

    float fuelPickup = 10;
    
};

#endif