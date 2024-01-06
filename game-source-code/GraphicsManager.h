#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "splash_screen.h"
#include "GameBackground.h"
#include "Spaceship.h"
#include "LanderMissiles.h"
#include "Laser.h"
#include "Fuel.h"
#include "PlayerLives.h"
#include "Score.h"
#include "EndScreen.h"
#include "Enemies.h"
#include "EnemyLanders.h"
#include "EnemyPods.h"
#include "EnemySwarmers.h"
#include "KidnappingLanders.h"
#include "Humanoids.h"
#include "Shields.h"
#include "printObjects.h"

/**
 * \class Graphics
 * @brief Displays views and game entities
 * 
 */
class Graphics{
    public:
        /**
         * @brief Construct a new Graphics object
         * 
         * @param screenHeight Height of the game window
         * @param windowWidth Width of the visible game window
         * @param scrollableScreenWidth Width of the entire game window
         * @param mapHeight Height of the mini-map
         */
        Graphics(float screenHeight,float windowWidth, float scrollableScreenWidth, float mapHeight);
        /**
         * @brief Draws all enemy objects to the game window
         * 
         * @param window The render window to which the game is drawn
         * @param landers The lander object
         * @param pods The pods object
         * @param landerMissiles The lander missiles object
         * @param swarmers The swarmers object
         * @param kidnappers The kidnapping landers object
         * @param humanoids The humanoids object
         */
        void enemyObjects(sf::RenderWindow& window, EnemyLanders& landers, EnemyPods& pods, LanderMissiles& landerMissiles, EnemySwarmers& swarmers, KidnappingLanders& kidnappers, Humanoids& humanoids);
        /**
         * @brief Draws all objects related to the player spaceship to the game window
         * 
         * @param window The render window to which the game is drawn
         * @param myPlayer The player's spaceship object 
         * @param lasers The player's laser object
         * @param fuel The fuel object
         * @param shield The shields object
         */
        void shipObjects(sf::RenderWindow& window, Spaceship& myPlayer, Laser& lasers, Fuel& fuel, Shields& shield);
        /**
         * @brief 
         * 
         * @param window The render window to which the game is drawn
         * @param fuel The fuel object
         * @param playerLives The player lives object
         * @param gameScore The game score object
         * @param shield the shields object
         */
        void HUD(sf::RenderWindow& window, Fuel& fuel, PlayerLives& playerLives, Score& gameScore, Shields& shield);
        /**
         * @brief Calls the relevent functions of the game background class to set the game background
         * 
         */
        void initialiseBackgrounds();
        /**
         * @brief Sets the view size and viewports of each of the game's views
         * 
         */
        void initialiseViews();
        /**
         * @brief Sets the centre of each view and calls the draw functions for each object
         * 
         * @param window The render window to which the game is drawn
         * @param landers The lander object
         * @param pods The pods object
         * @param landerMissiles The lander missiles object
         * @param myPlayer The player's spaceship object
         * @param lasers The player's laser object
         * @param fuel The fuel object
         * @param swarmers The swarmers object 
         * @param kidnappers The kidnapping landers object
         * @param humanoids The humanoids object
         * @param shield The shields object
         */
        void gameScrolling(sf::RenderWindow& window, EnemyLanders& landers, EnemyPods& pods, LanderMissiles& landerMissiles,
        Spaceship& myPlayer, Laser& lasers, Fuel& fuel, EnemySwarmers& swarmers, KidnappingLanders& kidnappers, Humanoids& humanoids, Shields& shield);
        /**
         * @brief Sets the view of the mini-map and calls the draw functions for each object on the mini-map
         * 
         * @param window The render window to which the game is drawn
         * @param landers The lander object
         * @param pods The pods object
         * @param landerMissiles The lander missiles object`
         * @param myPlayer The player's spaceship object
         * @param lasers The player's laser object
         * @param fuel The fuel object
         * @param swarmers The swarmers object 
         * @param kidnappers The kidnapping landers object
         * @param humanoids The humanoids object
         * @param shield The shields object
         */
        void minimap(sf::RenderWindow& window, EnemyLanders& landers, EnemyPods& pods, LanderMissiles& landerMissiles,
        Spaceship& myPlayer, Laser& lasers, Fuel& fuel, EnemySwarmers& swarmers, KidnappingLanders& kidnappers, Humanoids& humanoids, Shields& shield);
        /**
         * @brief Sets the size and position of the bars around the mini-map, and draws these bars to the window
         * 
         * @param window The render window to which the game is drawn
         * @param myPlayer The player's spaceship object
         */
        void minimapPositionBars(sf::RenderWindow& window,Spaceship& myPlayer);
        
    private:
        float mapHeight_;
        float screenHeight_;
        float scrollableScreenWidth_;
        float windowWidth_;
        float mapSeparationLineThickness = 5;
        float mapLeftSeparationLinePos = 400.0f - mapSeparationLineThickness;
        float mapRightSeparationLinePos = 1200.0f;
        sf::Vector2f screenPosition = {windowWidth_/2, screenHeight_/2};
        sf::RectangleShape mapSeparationLine;
        sf::RectangleShape mapLeftSeparationLine;
        sf::RectangleShape mapRightSeparationLine;
        GameBackground myBackground; 
        sf::Sprite backgroundImage;
        sf::View gameView1;
        sf::View gameView2;
        sf::View hudView;
        sf::View mapView;
        float shipXPosRight;
        float shipXPosLeft;
        Print draw= Print{};
};

#endif