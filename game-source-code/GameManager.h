#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <memory>
#include "splash_screen.h"
#include "GameBackground.h"
#include "Spaceship.h"
#include "LanderMissiles.h"
#include "Laser.h"
#include "Fuel.h"
#include "Collisions.h"
#include "PlayerLives.h"
#include "Score.h"
#include "EndScreen.h"
#include "Enemies.h"
#include "EnemyLanders.h"
#include "EnemyPods.h"
#include "GraphicsManager.h"
#include "EnemySwarmers.h"
#include "Humanoids.h"
#include "Shields.h"

#define SCREENWIDTH 1600.0f
#define SCREENHEIGHT 900.0f
#define MAPHEIGHT 200.0f
#define SPACESHIPHEIGHT 36.0f
#define SPACESHIPWIDTH 102.0f
#define MOVEDISTANCE 10.0f
#define SCROLLABLE_SCREEN_WIDTH 4800.0f

/** \class GameManager 
 * @brief Carries out the game loop whilst keeping track of all the game entities .
 * 
 */
class GameManager{

    public:
        /**
         * @brief Construct a new Game Manager object.
         * 
         */
        GameManager();
        /**
         * @brief Loads additional game resources.
         * 
         */
        void declarations();
        /**
         * @brief Polls to see if the window is closed.
         * 
         */
        void pollEvents();   
        /**
         * @brief Displays the splash screen and polls for user input. Loads additional game resources.
         * 
         */
        void startScreenOperations();
        /**
         * @brief  Displays the end game screens and polls for user input. 
         * 
         */
        void endScreenOperations();
        /**
         * @brief Switches between the splash screen, game screen, and end game screen.
         * 
         */
        void gameStates();
        /**
         * @brief Updates the game score.
         * 
         */
        void updateGameScore();
        /**
         * @brief Sets collisions variables to default state.
         * 
         */
        void defaultCollisionStates();
        /**
         * @brief Performs collision checks for all game entities .
         * 
         */
        void collisionOperations();
        /**
         * @brief Performs Humanoid collision checks.
         * 
         */
        void humanoidCollisions();
        /**
         * @brief Spawns and moves all game entities. 
         * 
         */
        void gameMechanics();
        /**
         * @brief Calls functions related to game mechanics, collisions, updating scores and lives, and drawing game entities .
         * 
         */
        void gameOperations();
        /**
         * @brief Checks if the game has ended.
         * 
         */
        void endGameChecks();
        /**
         * @brief Resets game parameters.
         * 
         */
        void resetParameters();
        /**
         * @brief Contains the game loop.
         * 
         */
        void play();
        /**
         * @brief Destroy the Game Manager object.
         * 
         */
        ~GameManager();
    
    private:
        sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "Defender", sf::Style::Close | sf::Style::Titlebar);    
        std::string backgroundFile = "resources\\SplashScreenBackground.png";        
        std::string fontFile = "resources\\PublicPixel.ttf";
        sf::Sprite backgroundImage;
        sf::Texture splashScreenTexture; 
        sf::Font font;
        sf::Clock collisionClock;
        float landerWidth = 54.0;
        float landerHeight = 48.0;
        bool gameHasStarted = false;
        int numOfLives = 3;
        bool gameHasEnded = false; 
        bool gameWon = false;
        bool landerCollision;
        bool landerMissileCollision;
        bool laserRightCollisionLander;
        bool laserLeftCollisionLander;
        bool fuelCollision;
        std::tuple<bool, sf::Vector2f>  podCollision;
        bool laserRightCollisionSwarmer;
        bool laserLeftCollisionSwarmer;
        bool swarmerCollision;
        std::tuple<bool, sf::Vector2f> laserRightCollisionPods;
        std::tuple<bool, sf::Vector2f> laserLeftCollisionPods;
        std::tuple <bool, sf::Vector2f> humanoidHitBoxLanderCollision;
        std::tuple <bool, sf::Vector2f> humanoidKidnapperCollision;
        std::tuple <bool, sf::Vector2f> upKidnapperLaserCollisionRight;
        std::tuple <bool, sf::Vector2f> upKidnapperLaserCollisionLeft;
        std::tuple <bool, sf::Vector2f> upKidnapperSpaceshipCollision;
        std::tuple <bool, sf::Vector2f> upKidnapperShieldCollision;
        bool laserRaisingHumanoidCollisionRight;
        bool laserRaisingHumanoidCollisionLeft;
        bool laserFallingHumanoidCollisionRight;
        bool laserFallingHumanoidCollisionLeft;
        std::tuple <bool, sf::Vector2f> shipHumanoidCollision;
        std::tuple <bool, sf::Vector2f> downKidnapperSpaceshipCollision;
        std::tuple <bool, sf::Vector2f> downKidnapperShieldCollision;
        bool shieldLanderCollision;
        bool shieldLanderMissileCollision;
        std::tuple<bool, sf::Vector2f> shieldPodCollision;
        bool shieldSwarmerCollision;

        std::unique_ptr<Spaceship> myPlayer = std::make_unique<Spaceship>(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);  
        EnemyLanders landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
        EnemyPods pods = EnemyPods(SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
        EnemySwarmers swarmers = EnemySwarmers (SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
        GameBackground myBackground; 
        SplashScreen splashScreen = SplashScreen(fontFile, backgroundFile, font, splashScreenTexture);
        LanderMissiles landerMissiles = LanderMissiles{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT};
        Laser myLaser = Laser(SCREENWIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
        Fuel myFuel = Fuel(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT);
        PlayerLives playerLives;
        Score gameScore = Score(fontFile);
        EndScreen endScreen = EndScreen(fontFile);
        Graphics graphics = Graphics(SCREENHEIGHT,SCREENWIDTH,SCROLLABLE_SCREEN_WIDTH, MAPHEIGHT);
        Collisions Collision = Collisions{};
        Humanoids humanoids = Humanoids {SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT};
        KidnappingLanders kidnappers = KidnappingLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
        Shields shield = Shields(SCREENWIDTH/2, SCREENHEIGHT/2, SPACESHIPWIDTH, SPACESHIPHEIGHT);

};
#endif