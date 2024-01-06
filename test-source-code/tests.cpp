#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "splash_screen.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameBackground.h"
#include "Spaceship.h"
#include "Collisions.h"
#include "Laser.h"
#include "Fuel.h"
#include "LanderMissiles.h"
#include "EnemyLanders.h"
#include <cmath>
#include "Humanoids.h"
#include "KidnappingLanders.h"
#include "Shields.h"
#include "EnemyPods.h"
#include "EnemySwarmers.h"

#define SCREENWIDTH 1600.0f
#define SCREENHEIGHT 900.0f
#define SCROLLABLE_SCREEN_WIDTH 4800.0f
#define MAPHEIGHT 200.0f
#define SPACESHIPHEIGHT 36.0f
#define SPACESHIPWIDTH 102.0f
#define MOVEDISTANCE 10.0f

//Splash Screen Test Cases
TEST_CASE("Font and splash screen background load correctly from the .ttf and .png files") {
    const auto fontFile = std::string{"resources\\PublicPixel.ttf"};
    const auto backgroundFile = std::string{"resources\\SplashScreenBackground.png"};
    auto font = sf::Font{};
    auto texture = sf::Texture{};
    auto splashScreen = SplashScreen{fontFile,backgroundFile,font,texture};
    CHECK(font.loadFromFile(fontFile)==true);
    CHECK(texture.loadFromFile(backgroundFile)==true);
}


TEST_CASE("Invalid splash screen cannot be created due to incorrect font file") {
    const auto fontFile = std::string{"PublicPixel.ttf"};
    const auto backgroundFile = std::string{"resources\\SplashScreenBackground.png"};
    auto font = sf::Font{};
    auto texture = sf::Texture{};
    CHECK_THROWS_AS(SplashScreen(fontFile,backgroundFile,font,texture), cannotOpenFontFile);
}


TEST_CASE("Invalid splash screen cannot be created due to incorrect background file") {
    const auto fontFile = std::string{"resources\\PublicPixel.ttf"};
    const auto backgroundFile = std::string{"Background.jpeg"};
    auto font = sf::Font{};
    auto texture = sf::Texture{};
    CHECK_THROWS_AS(SplashScreen(fontFile,backgroundFile,font,texture), cannotOpenBackgroundFile);
}

// Space Ship Test Cases
TEST_CASE("New spaceship has origin set to middle of spaceship")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    auto player = myPlayer.getPlayer();
    CHECK(player.getOrigin().x == SPACESHIPWIDTH/2);
    CHECK(player.getOrigin().y == SPACESHIPHEIGHT/2);
}

TEST_CASE("New spaceship is in the middle of the screen")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    auto player = myPlayer.getPlayer();
    CHECK(player.getPosition().x == SCREENWIDTH/2);
    CHECK(player.getPosition().y == SCREENHEIGHT/2);
}

TEST_CASE("Spaceship moves one position to the left when A is pressed")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveLeft = true;
    myPlayer.moveSpaceship(moveLeft, false, false, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 - MOVEDISTANCE);
    CHECK(player.getPosition().y == SCREENHEIGHT/2);
}

TEST_CASE("Spaceship moves one position to the right when D is pressed")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveRight = true;
    myPlayer.moveSpaceship(false, moveRight, false, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 + MOVEDISTANCE);
    CHECK(player.getPosition().y == SCREENHEIGHT/2);
}

TEST_CASE("Spaceship moves one position up when W is pressed")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveUp = true;
    myPlayer.moveSpaceship(false, false, moveUp, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2);
    CHECK(player.getPosition().y == SCREENHEIGHT/2 - MOVEDISTANCE);
}

TEST_CASE("Spaceship moves one position down when S is pressed")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveDown = true;
    myPlayer.moveSpaceship(false, false, false, moveDown);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2);
    CHECK(player.getPosition().y == SCREENHEIGHT/2 + MOVEDISTANCE);
}
TEST_CASE("Spaceship moves three positions to the left when A is pressed thrice")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveLeft = true;
    myPlayer.moveSpaceship(moveLeft, false, false, false);
    myPlayer.moveSpaceship(moveLeft, false, false, false);
    myPlayer.moveSpaceship(moveLeft, false, false, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 - 3*MOVEDISTANCE);
    CHECK(player.getPosition().y == SCREENHEIGHT/2);
}

TEST_CASE("Spaceship moves three positions to the right when D is pressed thrice")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveRight = true;
    myPlayer.moveSpaceship(false, moveRight, false, false);
    myPlayer.moveSpaceship(false, moveRight, false, false);
    myPlayer.moveSpaceship(false, moveRight, false, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 + 3*MOVEDISTANCE);
    CHECK(player.getPosition().y == SCREENHEIGHT/2);
}

TEST_CASE("Spaceship moves three positions up when W is pressed thrice")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveUp = true;
    myPlayer.moveSpaceship(false, false, moveUp, false);
    myPlayer.moveSpaceship(false, false, moveUp, false);
    myPlayer.moveSpaceship(false, false, moveUp, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2);
    CHECK(player.getPosition().y == SCREENHEIGHT/2 - 3*MOVEDISTANCE);
}

TEST_CASE("Spaceship moves three positions down when S is pressed thrice")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveDown = true;
    myPlayer.moveSpaceship(false, false, false, moveDown);
    myPlayer.moveSpaceship(false, false, false, moveDown);
    myPlayer.moveSpaceship(false, false, false, moveDown);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2);
    CHECK(player.getPosition().y == SCREENHEIGHT/2 + 3*MOVEDISTANCE);
}

TEST_CASE("Spaceship moves one position to the left and one position up when A and W are pressed")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveLeft = true;
    bool moveUp = true;
    myPlayer.moveSpaceship(moveLeft, false, moveUp, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 - MOVEDISTANCE);
    CHECK(player.getPosition().y == SCREENHEIGHT/2 - MOVEDISTANCE);
}

TEST_CASE("Spaceship moves one position to the left and one position down when A and S are pressed")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveLeft = true;
    bool moveDown = true;
    myPlayer.moveSpaceship(moveLeft, false, false, moveDown);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 - MOVEDISTANCE);
    CHECK(player.getPosition().y == SCREENHEIGHT/2 + MOVEDISTANCE);
}

TEST_CASE("Spaceship moves one position to the right and one position up when D and W are pressed")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveRight = true;
    bool moveUp = true;
    myPlayer.moveSpaceship(false, moveRight, moveUp, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 + MOVEDISTANCE);
    CHECK(player.getPosition().y == SCREENHEIGHT/2 - MOVEDISTANCE);
}

TEST_CASE("Spaceship moves one position to the right and one position down when D and S are pressed")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveRight = true;
    bool moveDown = true;
    myPlayer.moveSpaceship(false, moveRight, false, moveDown);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 + MOVEDISTANCE);
    CHECK(player.getPosition().y == SCREENHEIGHT/2 + MOVEDISTANCE);
}

TEST_CASE("Spaceship moves in all directions correctly, starting with a move to the right")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveRight = true;
    bool moveLeft = true;
    bool moveUp = true;
    bool moveDown = true;  

    myPlayer.moveSpaceship(false, moveRight, false, false);
    myPlayer.moveSpaceship(false, moveRight, false, false);
    myPlayer.moveSpaceship(false, moveRight, false, false);
    myPlayer.moveSpaceship(false, false, moveUp, false);
    myPlayer.moveSpaceship(false, moveRight, false, false);
    myPlayer.moveSpaceship(false, moveRight, false, false);
    myPlayer.moveSpaceship(false, false, false, moveDown);
    myPlayer.moveSpaceship(false, false, false, moveDown);
    myPlayer.moveSpaceship(false, false, false, moveDown);
    myPlayer.moveSpaceship(false, false, false, moveDown);
    myPlayer.moveSpaceship(moveLeft, false, false, false);
    

    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 + 4*MOVEDISTANCE);
    CHECK(player.getPosition().y == SCREENHEIGHT/2 + 3*MOVEDISTANCE);
}

TEST_CASE("Spaceship does not move up when spaceship is at the top of the usable screen")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveUp = true;
    for(float i=0; i<SCREENHEIGHT-MAPHEIGHT; i++)
    {
        myPlayer.moveSpaceship(false, false, moveUp, false);
    }
    myPlayer.moveSpaceship(false, false, moveUp, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2);
    CHECK(player.getPosition().y == MAPHEIGHT + SPACESHIPHEIGHT/2);
}

TEST_CASE("Spaceship moves left when spaceship is at the top of the usable screen")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveUp = true;
    for(float i=0; i<SCREENHEIGHT-MAPHEIGHT; i++)
    {
        myPlayer.moveSpaceship(false, false, moveUp, false);
    }
    bool moveLeft = true;
    myPlayer.moveSpaceship(moveLeft, false, false, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 - MOVEDISTANCE);
    CHECK(player.getPosition().y == MAPHEIGHT + SPACESHIPHEIGHT/2);
}

TEST_CASE("Spaceship moves right when spaceship is at the top of the usable screen")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveUp = true;
    for(float i=0; i<SCREENHEIGHT-MAPHEIGHT; i++)
    {
        myPlayer.moveSpaceship(false, false, moveUp, false);
    }
    bool moveRight = true;
    myPlayer.moveSpaceship(false, moveRight, false, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 + MOVEDISTANCE);
    CHECK(player.getPosition().y == MAPHEIGHT + SPACESHIPHEIGHT/2);
}

TEST_CASE("Spaceship moves down when spaceship is at the top of the usable screen")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveUp = true;
    for(float i=0; i<SCREENHEIGHT-MAPHEIGHT; i++)
    {
        myPlayer.moveSpaceship(false, false, moveUp, false);
    }
    bool moveDown = true;
    myPlayer.moveSpaceship(false, false, false, moveDown);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2);
    CHECK(player.getPosition().y == MAPHEIGHT + SPACESHIPHEIGHT/2 + MOVEDISTANCE);
}

TEST_CASE("Spaceship does not move down when spaceship is at the bottom of the screen")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveDown = true;
    for(float i=0; i<SCREENHEIGHT/2; i++)
    {
        myPlayer.moveSpaceship(false, false, false, moveDown);
    }
    myPlayer.moveSpaceship(false, false, false, moveDown);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2);
    CHECK(player.getPosition().y == SCREENHEIGHT - SPACESHIPHEIGHT/2);
}

TEST_CASE("Spaceship moves left when spaceship is at the bottom of the screen")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveDown = true;
    for(float i=0; i<SCREENHEIGHT/2; i++)
    {
        myPlayer.moveSpaceship(false, false, false, moveDown);
    }
    bool moveLeft = true;
    myPlayer.moveSpaceship(moveLeft, false, false, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 - MOVEDISTANCE);
    CHECK(player.getPosition().y == SCREENHEIGHT - SPACESHIPHEIGHT/2);
}

TEST_CASE("Spaceship moves right when spaceship is at the bottom of the screen")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveDown = true;
    for(float i=0; i<SCREENHEIGHT/2; i++)
    {
        myPlayer.moveSpaceship(false, false, false, moveDown);
    }
    bool moveRight = true;
    myPlayer.moveSpaceship(false, moveRight, false, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2 + MOVEDISTANCE);
    CHECK(player.getPosition().y == SCREENHEIGHT - SPACESHIPHEIGHT/2);
}

TEST_CASE("Spaceship moves up when spaceship is at the bottom of the screen")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    bool moveDown = true;
    for(float i=0; i<SCREENHEIGHT/2; i++)
    {
        myPlayer.moveSpaceship(false, false, false, moveDown);
    }
    bool moveUp = true;
    myPlayer.moveSpaceship(false, false, moveUp, false);
    auto player = myPlayer.getPlayer();

    CHECK(player.getPosition().x == SCREENWIDTH/2);
    CHECK(player.getPosition().y == SCREENHEIGHT - SPACESHIPHEIGHT/2 - MOVEDISTANCE);
}

// Lander Test Cases
 TEST_CASE("Landers origin is set at half of its width and half of its height") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    auto landerInfo = landers.getEnemy();

    CHECK(landerInfo.getOrigin().x == landerWidth/2);
    CHECK(landerInfo.getOrigin().y == landerHeight/2);
} 

 TEST_CASE("False check for landers origin being set at half of its width and half of its height") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    auto landerInfo = landers.getEnemy();

    CHECK_FALSE(landerInfo.getOrigin().x == 0.0f);
    CHECK_FALSE(landerInfo.getOrigin().y == 0.0f);
}   

 TEST_CASE("Landers spawn at the correctly generated coordinates") {
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    auto landerInfo = landers.getEnemy();

    CHECK(landerInfo.getPosition().x == 300.0f);
    CHECK(landerInfo.getPosition().y == 300.0f);
}   

 TEST_CASE("False check for landers spawning at the correctly generated coordinates") {
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    auto landerInfo = landers.getEnemy();
    
    CHECK_FALSE(landerInfo.getPosition().x == 400.0f);
    CHECK_FALSE(landerInfo.getPosition().y == 400.0f);
} 

 TEST_CASE("Landers spawn randomly within the correct window dimesions ") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto shipXCord = int{300};
    auto shipYCord = int{300};


    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnEnemies(shipXCord,shipYCord);
    auto landerInfo = landers.getEnemy();

    CHECK(landerInfo.getPosition().x <= SCROLLABLE_SCREEN_WIDTH - landerWidth);
    CHECK(landerInfo.getPosition().y <= SCREENHEIGHT- MAPHEIGHT -  landerHeight);
}

 TEST_CASE("Landers move to the right and down by one pixel") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};
    auto xMax = 300.0f + landerWidth/2;
    auto xMin = 300.0f  - landerWidth/2;
    auto yMax = 300.0f  + landerHeight/2;
    auto yMin = 300.0f  - landerHeight/2; 
    auto moveDistanceX = 1.0f;
    auto moveDistanceY = 1.0f;
    std::vector<int> movementCase;
    movementCase.push_back(1.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto landerVector = landers.getEnemiesVector();

    CHECK(landerVector[0].getPosition().x == 301.0f);
    CHECK(landerVector[0].getPosition().y == 301.0f);
} 

TEST_CASE("Landers move to the left and down by one pixel") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};
    auto xMax = 300.0f + landerWidth/2;
    auto xMin = 300.0f  - landerWidth/2;
    auto yMax = 300.0f  + landerHeight/2;
    auto yMin = 300.0f  - landerHeight/2; 
    auto moveDistanceX = 1.0f;
    auto moveDistanceY = 1.0f;
    std::vector<int> movementCase;
    movementCase.push_back(2.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto landerVector = landers.getEnemiesVector();

    CHECK(landerVector[0].getPosition().x == 299.0f);
    CHECK(landerVector[0].getPosition().y == 301.0f);
} 

TEST_CASE("Landers move to the left and up by one pixel") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};
    auto xMax = 300.0f + landerWidth/2;
    auto xMin = 300.0f  - landerWidth/2;
    auto yMax = 300.0f  + landerHeight/2;
    auto yMin = 300.0f  - landerHeight/2; 
    auto moveDistanceX = 1.0f;
    auto moveDistanceY = 1.0f;
    std::vector<int> movementCase;
    movementCase.push_back(3.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto landerVector = landers.getEnemiesVector();

    CHECK(landerVector[0].getPosition().x == 299.0f);
    CHECK(landerVector[0].getPosition().y == 299.0f);
} 

TEST_CASE("Landers move to the right and up by one pixel") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};
    auto xMax = 300.0f + landerWidth/2;
    auto xMin = 300.0f  - landerWidth/2;
    auto yMax = 300.0f  + landerHeight/2;
    auto yMin = 300.0f  - landerHeight/2; 
    auto moveDistanceX = 1.0f;
    auto moveDistanceY = 1.0f;
    std::vector<int> movementCase;
    movementCase.push_back(4.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto landerVector = landers.getEnemiesVector();

    CHECK(landerVector[0].getPosition().x == 301.0f);
    CHECK(landerVector[0].getPosition().y == 299.0f);
} 

TEST_CASE("Landers move to the right by one pixel") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};
    auto xMax = 300.0f + landerWidth/2;
    auto xMin = 300.0f  - landerWidth/2;
    auto yMax = 300.0f  + landerHeight/2;
    auto yMin = 300.0f  - landerHeight/2; 
    auto moveDistanceX = 1.0f;
    auto moveDistanceY = 1.0f;
    std::vector<int> movementCase;
    movementCase.push_back(5.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto landerVector = landers.getEnemiesVector();

    CHECK(landerVector[0].getPosition().x == 301.0f);
    CHECK(landerVector[0].getPosition().y == 300.0f);
}

TEST_CASE("Landers move to the left by one pixel") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};
    auto xMax = 300.0f  + landerWidth/2;
    auto xMin = 300.0f  - landerWidth/2;
    auto yMax = 300.0f  + landerHeight/2;
    auto yMin = 300.0f  - landerHeight/2; 
    auto moveDistanceX = 1.0f;
    auto moveDistanceY = 1.0f;
    std::vector<int> movementCase;
    movementCase.push_back(6.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto landerVector = landers.getEnemiesVector();

    CHECK(landerVector[0].getPosition().x == 299.0f);
    CHECK(landerVector[0].getPosition().y == 300.0f);
}

TEST_CASE("Landers move up by one pixel") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};
    auto xMax = 300.0f  + landerWidth/2;
    auto xMin = 300.0f  - landerWidth/2;
    auto yMax = 300.0f  + landerHeight/2;
    auto yMin = 300.0f  - landerHeight/2; 
    auto moveDistanceX = 1.0f;
    auto moveDistanceY = 1.0f;
    std::vector<int> movementCase;
    movementCase.push_back(7.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto landerVector = landers.getEnemiesVector();

    CHECK(landerVector[0].getPosition().x == 300.0f);
    CHECK(landerVector[0].getPosition().y == 299.0f);
}

TEST_CASE("Landers move down by one pixel") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};
    auto xMax = 300.0f  + landerWidth/2;
    auto xMin = 300.0f  - landerWidth/2;
    auto yMax = 300.0f  + landerHeight/2;
    auto yMin = 300.0f  - landerHeight/2; 
    auto moveDistanceX = 1.0f;
    auto moveDistanceY = 1.0f;
    std::vector<int> movementCase;
    movementCase.push_back(8.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto landerVector = landers.getEnemiesVector();

    CHECK(landerVector[0].getPosition().x == 300.0f);
    CHECK(landerVector[0].getPosition().y == 301.0f);
}

TEST_CASE("Ship collides with lander when the lander moves to the left") {
    // this test case is applicable to any game object that is passed through
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{870};
    auto yCord = int{450};
    auto spawnTime = float{0.0};
    auto xMax = xCord  + landerWidth/2;
    auto xMin = xCord  - landerWidth/2;
    auto yMax = yCord  + landerHeight/2;
    auto yMin = yCord  - landerHeight/2; 
    auto moveDistanceX = 15.0f;
    auto moveDistanceY = 0.0f;
    std::vector<int> movementCase;
    movementCase.push_back(6.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto collisionCheck = Collisions();
    auto collisionResult = std::get<0>(collisionCheck.checkObject(landers.getEnemiesVector(),myPlayer.getPlayer()));

    CHECK(collisionResult == true);
}
//
TEST_CASE("Ship does not collide with lander when the lander moves to the left") { 
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{1200};
    auto yCord = int{450};
    auto spawnTime = float{0.0};
    auto xMax = xCord  + landerWidth/2;
    auto xMin = xCord  - landerWidth/2;
    auto yMax = yCord  + landerHeight/2;
    auto yMin = yCord  - landerHeight/2; 
    auto moveDistanceX = 15.0f;
    auto moveDistanceY = 0.0f;
    std::vector<int> movementCase;
    movementCase.push_back(6.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto collisionCheck = Collisions();
    auto collisionResult = std::get<0>(collisionCheck.checkObject(landers.getEnemiesVector(),myPlayer.getPlayer()));

    CHECK(collisionResult == false);
}

TEST_CASE("Laser shoots lander when lander is to the right of the spaceship") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{860}; //851+15
    auto yCord = int{450};
    auto spawnTime = float{0.0};
    auto xMax = xCord  + landerWidth/2;
    auto xMin = xCord  - landerWidth/2;
    auto yMax = yCord  + landerHeight/2;
    auto yMin = yCord  - landerHeight/2; 
    auto moveDistanceX = 0.0f; //1.0f
    auto moveDistanceY = 0.0f;
    std::vector<int> movementCase;
    movementCase.push_back(1.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)

    auto collisionCheck = Collisions();
    auto collisionResult = std::get<0>(collisionCheck.checkObject(landers.getEnemiesVector(),myPlayer.getPlayer()));

    CHECK(collisionResult == true);
}

TEST_CASE("Lander is destroyed after being hit by the laser to the right of the spaceship") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{860}; //851+15
    auto yCord = int{450};
    auto spawnTime = float{0.0};
    auto xMax = xCord  + landerWidth/2;
    auto xMin = xCord  - landerWidth/2;
    auto yMax = yCord  + landerHeight/2;
    auto yMin = yCord  - landerHeight/2; 
    auto moveDistanceX = 0.0f;
    auto moveDistanceY = 0.0f;
    std::vector<int> movementCase;
    movementCase.push_back(1.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto myLaser = Laser(SCREENWIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(true, false, myPlayer.getPlayer().getPosition().x,  myPlayer.getPlayer().getPosition().y);

    auto collisionCheck = Collisions();
    auto collisionResult = std::get<0>(collisionCheck.checkLaser(landers.getEnemiesVector(), myLaser.getRightLaserVector(), myLaser.getRightLaserPosVector()));

    CHECK(landers.getEnemiesVector().size() == 0);
}

TEST_CASE("Fuel collides with player"){
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto myFuel = Fuel(SCREENWIDTH, SCREENHEIGHT);
    myFuel.initialiseFuel();
    myFuel.placeFuel(myPlayer.getPlayer().getPosition().x, myPlayer.getPlayer().getPosition().y);

    auto collisionCheck = Collisions();
    auto collisionResult = std::get<0>(collisionCheck.checkObject(myFuel.getFuelcanVect(), myPlayer.getPlayer()));

    CHECK(collisionResult == true);
}

TEST_CASE("Fuel is picked up when collides with player"){
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto myFuel = Fuel(SCREENWIDTH, SCREENHEIGHT);
    myFuel.initialiseFuel();
    myFuel.placeFuel(myPlayer.getPlayer().getPosition().x, myPlayer.getPlayer().getPosition().y);

    bool spaceshipIsMoving = true;
    myFuel.doFuelOperations(spaceshipIsMoving);
    myFuel.addFuel();
    auto maxFuel = 100.0f;

    CHECK(myFuel.getFuelLevel() == maxFuel);
}


TEST_CASE("Check if the collided with object is destroyed when colliding with the ship") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{870};
    auto yCord = int{450};
    auto spawnTime = float{0.0};
    auto xMax = xCord  + landerWidth/2;
    auto xMin = xCord  - landerWidth/2;
    auto yMax = yCord  + landerHeight/2;
    auto yMin = yCord  - landerHeight/2; 
    auto moveDistanceX = 15.0f;
    auto moveDistanceY = 0.0f;
    std::vector<int> movementCase;
    movementCase.push_back(6.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto collisionCheck = Collisions();
    auto collisionResult = std::get<0>(collisionCheck.checkObject(landers.getEnemiesVector(),myPlayer.getPlayer()));
    CHECK(landers.getEnemiesVector().size() == 0);
}


TEST_CASE("The object is in tact if it doesn't collide with the ship") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{1200};
    auto yCord = int{450};
    auto spawnTime = float{0.0};
    auto xMax = xCord  + landerWidth/2;
    auto xMin = xCord  - landerWidth/2;
    auto yMax = yCord  + landerHeight/2;
    auto yMin = yCord  - landerHeight/2; 
    auto moveDistanceX = 15.0f;
    auto moveDistanceY = 0.0f;
    std::vector<int> movementCase;
    movementCase.push_back(6.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto collisionCheck = Collisions();
    auto collisionResult = std::get<0>(collisionCheck.checkObject(landers.getEnemiesVector(),myPlayer.getPlayer()));

    CHECK(landers.getEnemiesVector().size() == 1);
}

TEST_CASE("Laser makes single movement to the right when shot to the right") { 
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto myLaser = Laser(SCREENWIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(true, false, myPlayer.getPlayer().getPosition().x,  myPlayer.getPlayer().getPosition().y);
    myLaser.moveLasers();
    auto laserVect = myLaser.getRightLaserVector();
    auto currentXpos = laserVect[0].getPosition().x;
    auto laserWidth = 50.0f;
    auto laserSpeed = 15.0f;
    auto expectedXpos = myPlayer.getPlayer().getPosition().x + SPACESHIPWIDTH/2 - laserWidth/2 + laserSpeed;

    CHECK(currentXpos == expectedXpos);
}

TEST_CASE("Laser makes single movement to the left when shot to the left") { 
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto myLaser = Laser(SCREENWIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(false, true, myPlayer.getPlayer().getPosition().x,  myPlayer.getPlayer().getPosition().y);
    myLaser.moveLasers();
    auto laserVect = myLaser.getLeftLaserVector();
    auto currentXpos = laserVect[0].getPosition().x;
    auto laserWidth = 50.0f;
    auto laserSpeed = 15.0f;
    auto expectedXpos = myPlayer.getPlayer().getPosition().x - SPACESHIPWIDTH/2 + laserWidth/2 - laserSpeed;

    CHECK(currentXpos == expectedXpos);
}

TEST_CASE("Laser makes three movements to the right when shot to the right") { 
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto myLaser = Laser(SCREENWIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(true, false, myPlayer.getPlayer().getPosition().x,  myPlayer.getPlayer().getPosition().y);
    myLaser.moveLasers();
    myLaser.moveLasers();
    myLaser.moveLasers();
    auto laserVect = myLaser.getRightLaserVector();
    auto currentXpos = laserVect[0].getPosition().x;
    auto laserWidth = 50.0f;
    auto laserSpeed = 15.0f;
    auto expectedXpos = myPlayer.getPlayer().getPosition().x + SPACESHIPWIDTH/2 - laserWidth/2 + 3*laserSpeed;

    CHECK(currentXpos == expectedXpos);
}

TEST_CASE("Laser makes three movements to the left when shot to the left") { 
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto myLaser = Laser(SCREENWIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(false, true, myPlayer.getPlayer().getPosition().x,  myPlayer.getPlayer().getPosition().y);
    myLaser.moveLasers();
    myLaser.moveLasers();
    myLaser.moveLasers();
    auto laserVect = myLaser.getLeftLaserVector();
    auto currentXpos = laserVect[0].getPosition().x;
    auto laserWidth = 50.0f;
    auto laserSpeed = 15.0f;
    auto expectedXpos = myPlayer.getPlayer().getPosition().x - SPACESHIPWIDTH/2 + laserWidth/2 - 3*laserSpeed;

    CHECK(currentXpos == expectedXpos);
}

TEST_CASE("Two Lasers make single movements to the right when both shot to the right at different times") { 
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto myLaser = Laser(SCREENWIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(true, false, myPlayer.getPlayer().getPosition().x,  myPlayer.getPlayer().getPosition().y);
    myLaser.moveLasers();
    myLaser.shoot(true, false, myPlayer.getPlayer().getPosition().x,  myPlayer.getPlayer().getPosition().y);
    myLaser.moveLasers();
    auto laserVect = myLaser.getRightLaserVector();
    auto currentXpos1 = laserVect[0].getPosition().x;
    auto currentXpos2 = laserVect[1].getPosition().x;
    auto laserWidth = 50.0f;
    auto laserSpeed = 15.0f;
    auto expectedXpos1 = myPlayer.getPlayer().getPosition().x + SPACESHIPWIDTH/2 - laserWidth/2 + 2*laserSpeed;
    auto expectedXpos2= myPlayer.getPlayer().getPosition().x + SPACESHIPWIDTH/2 - laserWidth/2 + laserSpeed;

    CHECK(currentXpos1 == expectedXpos1);
    CHECK(currentXpos2 == expectedXpos2);
}

TEST_CASE("Two Lasers make single movements to the left when both shot to the left at different times") { 
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto myLaser = Laser(SCREENWIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(false, true, myPlayer.getPlayer().getPosition().x,  myPlayer.getPlayer().getPosition().y);
    myLaser.moveLasers();
    myLaser.shoot(false, true, myPlayer.getPlayer().getPosition().x,  myPlayer.getPlayer().getPosition().y);
    myLaser.moveLasers();
    auto laserVect = myLaser.getLeftLaserVector();
    auto currentXpos1 = laserVect[0].getPosition().x;
    auto currentXpos2 = laserVect[1].getPosition().x;
    auto laserWidth = 50.0f;
    auto laserSpeed = 15.0f;
    auto expectedXpos1 = myPlayer.getPlayer().getPosition().x - SPACESHIPWIDTH/2 + laserWidth/2 - 2*laserSpeed;
    auto expectedXpos2= myPlayer.getPlayer().getPosition().x - SPACESHIPWIDTH/2 + laserWidth/2 - laserSpeed;

    CHECK(currentXpos1 == expectedXpos1);
    CHECK(currentXpos2 == expectedXpos2);
}

TEST_CASE("Two Lasers make single movements to the left and right when shot at different times") { 
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)
    auto myLaser = Laser(SCREENWIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(true, false, myPlayer.getPlayer().getPosition().x,  myPlayer.getPlayer().getPosition().y); //Right
    myLaser.moveLasers(); 
    myLaser.shoot(false, true, myPlayer.getPlayer().getPosition().x,  myPlayer.getPlayer().getPosition().y); //Left
    myLaser.moveLasers();
    auto leftLaserVect = myLaser.getLeftLaserVector();
    auto rightLaserVect = myLaser.getRightLaserVector();
    auto currentXpos1 = rightLaserVect[0].getPosition().x;
    auto currentXpos2 = leftLaserVect[0].getPosition().x;
    auto laserWidth = 50.0f;
    auto laserSpeed = 15.0f;
    auto expectedXpos1 = myPlayer.getPlayer().getPosition().x + SPACESHIPWIDTH/2 - laserWidth/2 + 2*laserSpeed;
    auto expectedXpos2= myPlayer.getPlayer().getPosition().x - SPACESHIPWIDTH/2 + laserWidth/2 - laserSpeed;

    CHECK(currentXpos1 == expectedXpos1);
    CHECK(currentXpos2 == expectedXpos2);
}

TEST_CASE("Fuel is reduced when ship moves"){
    auto myFuel = Fuel(SCREENWIDTH, SCREENHEIGHT);
    myFuel.initialiseFuel();
    bool spaceshipIsMoving = true;
    myFuel.doFuelOperations(spaceshipIsMoving);
    auto maxFuel = 100.0f;
    auto fuelDecay = 0.05f;

    CHECK(myFuel.getFuelLevel() == maxFuel - fuelDecay);
}

TEST_CASE("Fuel is not reduced when ship does not moves"){
    auto myFuel = Fuel(SCREENWIDTH, SCREENHEIGHT);
    myFuel.initialiseFuel();
    bool spaceshipIsMoving = false;
    myFuel.doFuelOperations(spaceshipIsMoving);
    auto maxFuel = 100.0f;

    CHECK(myFuel.getFuelLevel() == maxFuel);
}

TEST_CASE("Fuel spawns in specified location"){
    auto myFuel = Fuel(SCREENWIDTH, SCREENHEIGHT);
    myFuel.initialiseFuel();
    auto fuelLocationX = 900;
    auto fuelLocationY = 900;
    myFuel.placeFuel(fuelLocationX, fuelLocationY);
    bool spaceshipIsMoving = true;
    myFuel.doFuelOperations(spaceshipIsMoving);
    auto fuelVect = myFuel.getFuelcanVect();
    auto fuelcanXpos = fuelVect[0].getPosition().x;
    auto fuelcanYpos = fuelVect[0].getPosition().y;
    
    CHECK(fuelcanXpos == fuelLocationX);
    CHECK(fuelcanYpos == fuelLocationY);
}


TEST_CASE("Lander missile moves vertically up 5 units if the ship is above the lander ") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{800};
    auto yCord = int{700};
    auto spawnTime = float{0.0};
    auto xMax = xCord  + landerWidth/2;
    auto xMin = xCord  - landerWidth/2;
    auto yMax = yCord  + landerHeight/2;
    auto yMin = yCord  - landerHeight/2; 
    auto moveDistanceX = 0.0f;
    auto moveDistanceY = 0.0f;
    std::vector<int> movementCase;
    movementCase.push_back(6.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); 

    auto shipXCord = myPlayer.getPlayer().getPosition().x;
    auto shipYCord = myPlayer.getPlayer().getPosition().y;
    auto sampleTime = -0.1f;
    auto moveDistance = 5.0f;

    auto landerMissiles = LanderMissiles(SCREENHEIGHT,SCREENWIDTH,MAPHEIGHT);
    landerMissiles.setMissiles(landers.getEnemiesVector());
    landerMissiles.launchMissiles(landers.getEnemiesVector());
    landerMissiles.samplingOperations(shipXCord,shipYCord,landers.getEnemiesVector());
    landerMissiles.calcTargetPos(int{0});
    landerMissiles.moveShortestPath(moveDistance, int{0});
    CHECK( landerMissiles.getMissilesVector()[0].getPosition() == sf::Vector2f(800.0f, 695.0f));
}

TEST_CASE("Lander missile moves to the left by 5 units if the ship is to right of the lander ") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{1000};
    auto yCord = int{450};
    auto spawnTime = float{0.0};
    auto xMax = xCord  + landerWidth/2;
    auto xMin = xCord  - landerWidth/2;
    auto yMax = yCord  + landerHeight/2;
    auto yMin = yCord  - landerHeight/2; 
    auto moveDistanceX = 0.0f;
    auto moveDistanceY = 0.0f;
    std::vector<int> movementCase;
    movementCase.push_back(6.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); 

    auto shipXCord = myPlayer.getPlayer().getPosition().x;
    auto shipYCord = myPlayer.getPlayer().getPosition().y;
    auto sampleTime = 0.0f;
    auto moveDistance = 5.0f;

    auto landerMissiles = LanderMissiles(SCREENHEIGHT,SCREENWIDTH,MAPHEIGHT);
    landerMissiles.setMissiles(landers.getEnemiesVector());
    landerMissiles.launchMissiles(landers.getEnemiesVector());
    landerMissiles.samplingOperations(shipXCord,shipYCord,landers.getEnemiesVector());
    landerMissiles.calcTargetPos(int{0});
    landerMissiles.moveShortestPath(moveDistance, int{0});
    CHECK(landerMissiles.getMissilesVector()[0].getPosition() == sf::Vector2(995.0f, 450.0f));
}

TEST_CASE("Lander missile moves diagonally towards the ship if the ship is 45 degrees above the lander ") {
    auto landerWidth = 54.0f;
    auto landerHeight = 48.0f;
    auto xCord = int{650};
    auto yCord = int{300};
    auto spawnTime = float{0.0};
    auto xMax = xCord  + landerWidth/2;
    auto xMin = xCord  - landerWidth/2;
    auto yMax = yCord  + landerHeight/2;
    auto yMin = yCord  - landerHeight/2; 
    auto moveDistanceX = 0.0f;
    auto moveDistanceY = 0.0f;
    std::vector<int> movementCase;
    movementCase.push_back(6.0f);

    auto landers = EnemyLanders{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, spawnTime);
    landers.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); 

    auto shipXCord = myPlayer.getPlayer().getPosition().x;
    auto shipYCord = myPlayer.getPlayer().getPosition().y;
    auto sampleTime = 0.0f;
    auto moveDistance = 5.0f;

    auto landerMissiles = LanderMissiles(SCREENHEIGHT,SCREENWIDTH,MAPHEIGHT);
    landerMissiles.setMissiles(landers.getEnemiesVector());
    landerMissiles.launchMissiles(landers.getEnemiesVector());
    landerMissiles.samplingOperations(shipXCord,shipYCord,landers.getEnemiesVector());
    landerMissiles.calcTargetPos(int{0});
    landerMissiles.moveShortestPath(moveDistance, int{0});

    CHECK(doctest::Approx(landerMissiles.getMissilesVector()[0].getPosition().x) == (650.0f + 5.0f*cos(3.14159/4)));
    CHECK(doctest::Approx(landerMissiles.getMissilesVector()[0].getPosition().y) == (300.0f + 5.0f*sin(3.14159/4)));
} 

TEST_CASE("Ground humanoids spawn in the specified location"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 5.0f;
    auto yCord = 5.0f;
    humanoids.placeHumanoids(xCord, yCord);

    CHECK(humanoids.getGroundHumanoidsVector()[0].getPosition().x == xCord);
    CHECK(humanoids.getGroundHumanoidsVector()[0].getPosition().y == yCord);
}

TEST_CASE("Ground humanoid hit boxes spawn in the specified location"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 5.0f;
    auto yCord = 5.0f;
    humanoids.placeHumanoids(xCord, yCord);
    humanoids.placeHumanoidHitBoxes();

    CHECK(humanoids.getHumanoidHitBoxVector()[0].getPosition().x == xCord);
    CHECK(humanoids.getHumanoidHitBoxVector()[0].getPosition().y == yCord);
}

TEST_CASE("Raising humanoids spawn in the specified location"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 5.0f;
    auto yCord = 5.0f;
    humanoids.spawnRaisingHumanoid(sf::Vector2f(xCord, yCord));

    CHECK(humanoids.getRaisingHumanoidsVector()[0].getPosition().x == xCord);
    CHECK(humanoids.getRaisingHumanoidsVector()[0].getPosition().y == yCord);
}

TEST_CASE("Falling humanoids spawn in the specified location"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 5.0f;
    auto yCord = 5.0f;
    humanoids.spawnFallingHumanoid(sf::Vector2f(xCord, yCord));

    CHECK(humanoids.getFallingHumanoidsVector()[0].getPosition().x == xCord);
    CHECK(humanoids.getFallingHumanoidsVector()[0].getPosition().y == yCord);
}

TEST_CASE("Ground humanoid and its hitbox spawn in the specified location when placed down"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 5.0f;
    auto yCord = 5.0f;
    humanoids.spawnGroundHumanoid(sf::Vector2f(xCord, yCord));

    CHECK(humanoids.getGroundHumanoidsVector()[0].getPosition().x == xCord);
    CHECK(humanoids.getGroundHumanoidsVector()[0].getPosition().y == yCord);
    CHECK(humanoids.getHumanoidHitBoxVector()[0].getPosition().x == xCord);
    CHECK(humanoids.getHumanoidHitBoxVector()[0].getPosition().y == yCord);
}

TEST_CASE("Ground humanoid hit boxes collide with landers"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 500.0f;
    auto yCord = 500.0f;
    humanoids.spawnGroundHumanoid(sf::Vector2f(xCord, yCord));

    auto landers = EnemyLanders(SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
    landers.initialiseEnemies();
    landers.spawnConditions(xCord, yCord, 0.0f);

    auto collisions = Collisions();

    std::tuple <bool, sf::Vector2f> humanoidHitBoxLanderCollision = collisions.checkHumanoidHitBox(humanoids.getHumanoidHitBoxVector(), landers.getEnemiesVector());

    CHECK(std::get<0>(humanoidHitBoxLanderCollision) == true);
    CHECK(std::get<1>(humanoidHitBoxLanderCollision) == sf::Vector2f(xCord, yCord));
}

TEST_CASE("Ground humanoids collide with landers"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 500.0f;
    auto yCord = 500.0f;
    humanoids.spawnGroundHumanoid(sf::Vector2f(xCord, yCord));

    auto kidnappers = KidnappingLanders(SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
    kidnappers.initialiseEnemies();
    kidnappers.spawnKidnapper(sf::Vector2f(xCord, yCord));

    auto collisions = Collisions();

    std::tuple <bool, sf::Vector2f> humanoidKidnapperCollision = collisions.checkHumanoid(kidnappers.getDownKidnappersVector(),humanoids.getGroundHumanoidsVector(), humanoids.getHumanoidHitBoxVector());

    CHECK(std::get<0>(humanoidKidnapperCollision) == true);
    CHECK(std::get<1>(humanoidKidnapperCollision) == sf::Vector2f(xCord, yCord));
}

TEST_CASE("Raising humanoids move up by the correct amount"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 500.0f;
    auto yCord = 500.0f;
    float raisingMoveDistance = 1.0f;
    humanoids.spawnRaisingHumanoid(sf::Vector2f(xCord, yCord));
    humanoids.moveRaisingHumanoids();

    CHECK(humanoids.getRaisingHumanoidsVector()[0].getPosition().y == yCord-raisingMoveDistance);
}

TEST_CASE("Falling humanoids move down by the correct amount"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 500.0f;
    auto yCord = 500.0f;
    float fallingMoveDistance = 2.0f;
    humanoids.spawnFallingHumanoid(sf::Vector2f(xCord, yCord));
    humanoids.moveFallingHumanoids();

    CHECK(humanoids.getFallingHumanoidsVector()[0].getPosition().y == yCord+fallingMoveDistance);
}

TEST_CASE("Falling humanoids can be shot"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 500.0f;
    auto yCord = 500.0f;
    float fallingMoveDistance = 2.0f;
    humanoids.spawnFallingHumanoid(sf::Vector2f(xCord, yCord));
    auto oldSize = humanoids.getFallingHumanoidsVector().size();

    auto myLaser = Laser(SCROLLABLE_SCREEN_WIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(true, false, xCord-1.0f, yCord);
    
    auto kidnappers = KidnappingLanders(SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
    kidnappers.spawnUpKidnapper(sf::Vector2f(xCord, yCord));

    auto collision = Collisions();
    bool laserFallingHumanoidCollisionRight =  collision.checkHumanoidLaser(humanoids.getFallingHumanoidsVector(), kidnappers.getUpKidnappersPasengersVector(), myLaser.getRightLaserVector(), myLaser.getRightLaserPosVector());

    CHECK(oldSize == 1);
    CHECK(humanoids.getFallingHumanoidsVector().size() == 0);
}

TEST_CASE("Raising humanoids can be shot"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 500.0f;
    auto yCord = 500.0f;
    humanoids.spawnRaisingHumanoid(sf::Vector2f(xCord, yCord));
    auto oldSize = humanoids.getRaisingHumanoidsVector().size();

    auto myLaser = Laser(SCROLLABLE_SCREEN_WIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(true, false, xCord-1.0f, yCord);
    
    auto kidnappers = KidnappingLanders(SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
    kidnappers.spawnUpKidnapper(sf::Vector2f(xCord, yCord));

    auto collision = Collisions();
    bool laserFallingHumanoidCollisionRight = collision.checkHumanoidLaser(humanoids.getRaisingHumanoidsVector(), kidnappers.getUpKidnappersPasengersVector(), myLaser.getRightLaserVector(), myLaser.getRightLaserPosVector());

    CHECK(oldSize == 1);
    CHECK(humanoids.getRaisingHumanoidsVector().size() == 0);
}

TEST_CASE("Raising humanoids are deleted after passing the upper map boundary"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    humanoids.initialiseHumanoidObjects();
    auto xCord = 500.0f;
    auto yCord = MAPHEIGHT;
    humanoids.spawnRaisingHumanoid(sf::Vector2f(xCord, yCord));
    auto oldSize = humanoids.getRaisingHumanoidsVector().size();
    humanoids.moveRaisingHumanoids();
    humanoids.moveRaisingHumanoids();

    CHECK(oldSize == 1);
    CHECK(humanoids.getRaisingHumanoidsVector().size() == 0);
}

TEST_CASE("Kidnappers spawn in the specified location"){
    auto kidnappers = KidnappingLanders(SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
    kidnappers.initialiseEnemies();
    auto xCord = 5.0f;
    auto yCord = 5.0f;
    kidnappers.spawnKidnapper(sf::Vector2f(xCord, yCord));

    CHECK(kidnappers.getDownKidnappersVector()[0].getPosition().x == xCord);
    CHECK(kidnappers.getDownKidnappersVector()[0].getPosition().y == yCord);
}

TEST_CASE("upKidnappers spawn in the specified location"){
    auto kidnappers = KidnappingLanders(SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
    kidnappers.initialiseEnemies();
    auto xCord = 5.0f;
    auto yCord = 5.0f;
    kidnappers.spawnUpKidnapper(sf::Vector2f(xCord, yCord));

    CHECK(kidnappers.getUpKidnappersVector()[0].getPosition().x == xCord);
    CHECK(kidnappers.getUpKidnappersVector()[0].getPosition().y == yCord);
}

TEST_CASE("Kidnappers move one moveDistance each time the move function is called"){
    auto kidnappers = KidnappingLanders(SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
    kidnappers.initialiseEnemies();
    auto xCord = 500.0f;
    auto yCord = 500.0f;
    auto moveDistance = 1.0f;
    kidnappers.spawnKidnapper(sf::Vector2f(xCord, yCord));
    kidnappers.moveDownKidnappers();

    CHECK(kidnappers.getDownKidnappersVector()[0].getPosition().x == xCord);
    CHECK(kidnappers.getDownKidnappersVector()[0].getPosition().y == yCord + moveDistance);
}

TEST_CASE("upKidnappers move one moveDistance each time the move function is called"){
    auto kidnappers = KidnappingLanders(SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
    kidnappers.initialiseEnemies();
    auto xCord = 500.0f;
    auto yCord = 500.0f;
    auto moveDistance = 1.0f;
    kidnappers.spawnUpKidnapper(sf::Vector2f(xCord, yCord));
    kidnappers.moveUpKidnappers();

    CHECK(kidnappers.getUpKidnappersVector()[0].getPosition().x == xCord);
    CHECK(kidnappers.getUpKidnappersVector()[0].getPosition().y == yCord - moveDistance);
}

TEST_CASE("Kidnappers collide with player spaceship"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    auto xCord = SCROLLABLE_SCREEN_WIDTH/2;
    auto yCord = SCREENHEIGHT/2;
    humanoids.spawnRaisingHumanoid(sf::Vector2f(xCord, yCord));

    auto kidnappers = KidnappingLanders(SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
    kidnappers.initialiseEnemies();
    kidnappers.spawnUpKidnapper(sf::Vector2f(xCord, yCord));
    auto oldSize = kidnappers.getUpKidnappersVector().size();

    auto myPlayer = Spaceship(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE); 
    myPlayer.initialiseShip();    

    auto collision = Collisions();
    std::tuple <bool, sf::Vector2f> upKidnapperSpaceshipCollision;
    upKidnapperSpaceshipCollision = collision.checkKidnappersObject(kidnappers.getUpKidnappersVector(), kidnappers.getUpKidnappersPasengersVector(), humanoids.getRaisingHumanoidsVector(), myPlayer.getPlayer());

    CHECK(std::get<0>(upKidnapperSpaceshipCollision) == true);
    CHECK(oldSize == 1);
    CHECK(kidnappers.getUpKidnappersVector().size() == 0);
}

 TEST_CASE("Pods spawn at the correctly generated coordinates") {
    auto xCord = int{3000};
    auto yCord = int{400};
    auto spawnTime = float{0.0};
    auto numberOfSwarmers = 0 ;

    auto pods = EnemyPods{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    pods.initialiseEnemies();
    pods.spawnConditionsPods(xCord, yCord, spawnTime, numberOfSwarmers);

    CHECK(pods.getEnemiesVector()[0].getPosition() == sf::Vector2f(3000.0f, 400.0f));
}   

 TEST_CASE("False check for pods spawn at the correctly generated coordinates") {
    auto xCord = int{3000};
    auto yCord = int{400};
    auto spawnTime = float{0.0};
    auto numberOfSwarmers = 0 ;

    auto pods = EnemyPods{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    pods.initialiseEnemies();
    pods.spawnConditionsPods(xCord, yCord, spawnTime, numberOfSwarmers);

    CHECK_FALSE(pods.getEnemiesVector()[0].getPosition() == sf::Vector2f(1000.0f, 400.0f));
}   

TEST_CASE("Pods move to the left by three pixels and down by one pixel") {
    auto podWidth = 60.0f;
    auto podHeight = 60.0f;
    auto xCord = int{300};
    auto yCord = int{300};
    auto spawnTime = float{0.0};
    auto xMax = 300.0f + podWidth/2;
    auto xMin = 300.0f  - podWidth/2;
    auto yMax = 300.0f  + podHeight/2;
    auto yMin = 300.0f  - podHeight/2; 
    auto moveDistanceX = 3.0f;
    auto moveDistanceY = 1.0f;
    std::vector<int> movementCase;
    movementCase.push_back(2.0f);

    auto pods = EnemyPods{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    pods.initialiseEnemies();
    pods.spawnConditions(xCord, yCord, spawnTime);
    pods.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);

    CHECK(pods.getEnemiesVector()[0].getPosition() == sf::Vector2f(297.0f, 301.0f));  
} 

TEST_CASE("All subtypes of the enemy class that inherit the movement functions from the base class cant move beyond the"
"map if the top of the enemy hits the boundary point. When they do hit the top boundary they move to the right of the game"
"screen whilst keeping a constant y coordinate") {
    auto podWidth = 60.0f;
    auto podHeight = 60.0f;
    auto spawnTime = float{0.0};
    auto xCord = int{300};
    auto yCord = int{237};
    auto xMax = xCord + podWidth/2;
    auto xMin = xCord - podWidth/2;
    auto yMax = yCord  + podHeight/2;
    auto yMin = yCord  - podHeight/2; 
    auto moveDistanceX = 1.0f;
    auto moveDistanceY = 7.0f;
    std::vector<int> movementCase;
    movementCase.push_back(7.0f);

    auto pods = EnemyPods{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    pods.initialiseEnemies();
    pods.spawnConditions(xCord, yCord, spawnTime);
    //move up twice and hit the top boundary twice resulting in the enemy moving to the right twice by 1 unit
    pods.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    pods.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);

    CHECK(pods.getEnemiesVector()[0].getPosition().x == 302.0f);
    CHECK(pods.getEnemiesVector()[0].getPosition().y == MAPHEIGHT+moveDistanceY +podHeight/2); //(200+7+30). Half the pod width is added since the origin of the enemy is at its center
} 

TEST_CASE("All subtypes of the enemy class that inherit the movement functions from the base class cant move beyond the"
"bottom of the screen if the bottom of the enemy hits the boundary point.") {
    auto podWidth = 60.0f;
    auto podHeight = 60.0f;
    auto spawnTime = float{0.0};
    auto xCord = int{300};
    auto yCord = int{869};
    auto xMax = xCord + podWidth/2;
    auto xMin = xCord - podWidth/2;
    auto yMax = yCord  + podHeight/2;
    auto yMin = yCord  - podHeight/2; 
    auto moveDistanceX = 1.0f;
    auto moveDistanceY = 1.0f;
    std::vector<int> movementCase;
    movementCase.push_back(8.0f);
    auto initialSwarmers =0;

    auto pods = EnemyPods{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    pods.initialiseEnemies();
    pods.spawnConditionsPods(xCord, yCord, spawnTime, initialSwarmers);
    //moves down 4 times and cant go past the border 
    for (int i = 0 ; i<4; i++){
        //bottom of the ship would be at a y value of 903 if there wasnt a boundary
        pods.enemyMovementConditions(int{0},xMax,xMin, yMax,yMin,moveDistanceX,moveDistanceY, movementCase);
    }
    CHECK(pods.getEnemiesVector()[0].getPosition().y == SCREENHEIGHT- moveDistanceY - podHeight/2); //(900-1-30)
} 

TEST_CASE("Three Swarmers spawn if a pod is destroyed") {
    auto xCord = int{860}; 
    auto yCord = int{450};
    auto spawnTime = float{0.0};
    auto initialSwarmers =0;

    auto pods = EnemyPods{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    auto swarmers = EnemySwarmers{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    pods.initialiseEnemies();
    swarmers.initialiseEnemies();
    pods.spawnConditionsPods(xCord, yCord, spawnTime, initialSwarmers);
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)

    auto collisionCheck = Collisions();
    auto collisionResult = collisionCheck.checkObject(pods.getEnemiesVector(),myPlayer.getPlayer());

    if (std::get<0>(collisionResult) == true){
        auto podCords =  std::get<1>(collisionResult);
        swarmers.swarmerSpawnConditions(podCords.x,podCords.y, myPlayer.getPlayer().getPosition().x,myPlayer.getPlayer().getPosition().y, spawnTime);
    }

    CHECK(swarmers.getEnemiesVector().size() == 3);
} 

TEST_CASE("Three Swarmers spawn to the right of the ship, at the correct points, when the pod is to the right of the ship") {
    auto xCord = int{860}; 
    auto yCord = int{450};
    auto swarmerWidth = 30.0f;
    auto swarmerHeight = 24.0f;
    auto spawnTime = float{0.0};
    auto initialSwarmers =0;

    auto pods = EnemyPods{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    auto swarmers = EnemySwarmers{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    pods.initialiseEnemies();
    swarmers.initialiseEnemies();
    pods.spawnConditionsPods(xCord, yCord, spawnTime, initialSwarmers);
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)

    auto collisionCheck = Collisions();
    auto collisionResult = collisionCheck.checkObject(pods.getEnemiesVector(),myPlayer.getPlayer());
    auto podCords = sf::Vector2f{};
    if (std::get<0>(collisionResult) == true){
        podCords =  std::get<1>(collisionResult);
        swarmers.swarmerSpawnConditions(podCords.x,podCords.y, myPlayer.getPlayer().getPosition().x,myPlayer.getPlayer().getPosition().y, spawnTime);
    }

    CHECK(swarmers.getEnemiesVector()[0].getPosition() == sf::Vector2f(podCords.x + 7*swarmerWidth,podCords.y));
    CHECK(swarmers.getEnemiesVector()[1].getPosition() == sf::Vector2f(podCords.x + 7*swarmerWidth,podCords.y + swarmerHeight));
    CHECK(swarmers.getEnemiesVector()[2].getPosition() == sf::Vector2f(podCords.x + 7*swarmerWidth,podCords.y - swarmerHeight)); 
} 

TEST_CASE("Swarmer moves to the right towards the player ship") {
    auto xCord = int{860}; 
    auto yCord = int{450};
    auto swarmerWidth = 30.0f;
    auto swarmerHeight = 24.0f;
    auto spawnTime = float{0.0};
    auto moveDistance = 6.0f;
    auto swarmers = EnemySwarmers{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    swarmers.initialiseEnemies();
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)

    swarmers.swarmerSpawnConditions(xCord,yCord, myPlayer.getPlayer().getPosition().x,myPlayer.getPlayer().getPosition().y, spawnTime);
    swarmers.samplingOperations(myPlayer.getPlayer().getPosition().x,myPlayer.getPlayer().getPosition().y);
    swarmers.calcTargetCords(int{0});
    swarmers.closestPath(moveDistance,int{0});

    CHECK(swarmers.getEnemiesVector()[0].getPosition() == sf::Vector2f(xCord + 7*swarmerWidth - moveDistance ,yCord));
} 

TEST_CASE("Swarmers take the shortest distance towards the ship") {
    auto xCord = int{4400}; 
    auto yCord = int{450};
    auto swarmerWidth = 30.0f;
    auto swarmerHeight = 24.0f;
    auto spawnTime = float{0.0};
    auto moveDistance = 6.0f;
    auto swarmers = EnemySwarmers{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    swarmers.initialiseEnemies();
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)

    swarmers.swarmerSpawnConditions(xCord,yCord, myPlayer.getPlayer().getPosition().x,myPlayer.getPlayer().getPosition().y, spawnTime);
    swarmers.samplingOperations(myPlayer.getPlayer().getPosition().x,myPlayer.getPlayer().getPosition().y);
    swarmers.calcTargetCords(int{0});
    swarmers.closestPath(moveDistance,int{0});

     // moves to the left towards the ship as there is a circular inifinte scrolling screen
    CHECK(swarmers.getEnemiesVector()[0].getPosition() == sf::Vector2f(xCord + 7*swarmerWidth + moveDistance ,yCord));
} 

TEST_CASE("Swarmers can infinitely scroll and move across the map when chasing the ship") {
    auto xCord = int{4600}; 
    auto yCord = int{450};
    auto swarmerWidth = 30.0f;
    auto swarmerHeight = 24.0f;
    auto spawnTime = float{0.0};
    auto moveDistance = 6.0f;
    auto swarmers = EnemySwarmers{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    swarmers.initialiseEnemies();
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (800,450)

    swarmers.swarmerSpawnConditions(xCord,yCord, myPlayer.getPlayer().getPosition().x,myPlayer.getPlayer().getPosition().y, spawnTime);
    swarmers.samplingOperations(myPlayer.getPlayer().getPosition().x,myPlayer.getPlayer().getPosition().y);
    swarmers.calcTargetCords(int{0});
    swarmers.closestPath(moveDistance,int{0});

     // moves to the left towards the ship as there is a circular inifinte scrolling screen
    CHECK(swarmers.getEnemiesVector()[0].getPosition() == sf::Vector2f(0.0f,yCord));
} 

TEST_CASE("Swarmers can infinitely scroll and move across the map when chasing the ship") {
    auto xCord = int{200}; 
    auto yCord = int{450};
    auto swarmerWidth = 30.0f;
    auto swarmerHeight = 24.0f;
    auto spawnTime = float{0.0};
    auto moveDistance = 6.0f;
    auto mapOverlapOffset = 18.0f;
    auto swarmers = EnemySwarmers{SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT};
    swarmers.initialiseEnemies();
    auto myPlayer = Spaceship(1.5*SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip(); //the ship is spawned at a center point of (3600,450)

    swarmers.swarmerSpawnConditions(xCord,yCord, myPlayer.getPlayer().getPosition().x,myPlayer.getPlayer().getPosition().y, spawnTime);
    swarmers.samplingOperations(myPlayer.getPlayer().getPosition().x,myPlayer.getPlayer().getPosition().y);
    swarmers.calcTargetCords(int{0});
    swarmers.closestPath(moveDistance,int{0});

     // moves to the left towards the ship as there is a circular inifinte scrolling screen
    CHECK(swarmers.getEnemiesVector()[0].getPosition() == sf::Vector2f(SCROLLABLE_SCREEN_WIDTH - mapOverlapOffset ,yCord));
} 

TEST_CASE("Spaceship wraps around the screen to the left")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    myPlayer.getPlayer().setPosition(sf::Vector2f(SPACESHIPWIDTH/2, SCREENHEIGHT/2));
    bool moveLeft = true;
    myPlayer.moveSpaceship(moveLeft, false, false, false);

    CHECK(myPlayer.getPlayer().getPosition().x == 4782.0f - SPACESHIPWIDTH/2);
}

TEST_CASE("Spaceship wraps around the screen to the right")
{
    auto myPlayer = Spaceship(SCREENWIDTH, SCREENHEIGHT, SPACESHIPWIDTH, SPACESHIPHEIGHT, MAPHEIGHT, MOVEDISTANCE);
    myPlayer.initialiseShip();
    myPlayer.getPlayer().setPosition(sf::Vector2f(4782 - SPACESHIPWIDTH/2, SCREENHEIGHT/2));
    bool moveRight = true;
    myPlayer.moveSpaceship(false, moveRight, false, false);

    CHECK(myPlayer.getPlayer().getPosition().x == 0.0f);
}

TEST_CASE("Laser wraps around the screen to the right")
{
    auto xCord = 4782.0f;
    auto yCord = SCREENHEIGHT/2; 
    auto myLaser = Laser(SCREENWIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(true, false, xCord, yCord);
    myLaser.moveLasers();
    auto laserSpeed = 15.0f;

    CHECK(myLaser.getRightLaserVector()[0].getPosition().x == laserSpeed);
}

TEST_CASE("Laser wraps around the screen to the left")
{
    auto xCord = 0.0f;
    auto yCord = SCREENHEIGHT/2; 
    auto myLaser = Laser(SCREENWIDTH, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    myLaser.initialiseLaser();
    myLaser.shoot(false, true, xCord, yCord);
    myLaser.moveLasers();
    auto laserSpeed = 15.0f;

    CHECK(myLaser.getLeftLaserVector()[0].getPosition().x == 4782 - laserSpeed);
}

TEST_CASE("Shield is destroyed when colliding with an enemy"){
    auto humanoids = Humanoids(SCROLLABLE_SCREEN_WIDTH, SCREENHEIGHT, MAPHEIGHT);
    auto xCord = SCROLLABLE_SCREEN_WIDTH/2;
    auto yCord = SCREENHEIGHT/2;
    humanoids.spawnRaisingHumanoid(sf::Vector2f(xCord, yCord));

    auto kidnappers = KidnappingLanders(SCREENHEIGHT,SCROLLABLE_SCREEN_WIDTH,MAPHEIGHT,SPACESHIPWIDTH,SPACESHIPHEIGHT);
    kidnappers.initialiseEnemies();
    kidnappers.spawnUpKidnapper(sf::Vector2f(xCord, yCord));

    auto shields = Shields(xCord, yCord, SPACESHIPWIDTH, SPACESHIPHEIGHT);
    shields.initialiseShieldObjects();
    shields.activateShield();

    auto collision = Collisions();
    std::tuple <bool, sf::Vector2f> upKidnapperSpaceshipCollision;
    upKidnapperSpaceshipCollision = collision.checkKidnappersObject(kidnappers.getUpKidnappersVector(), kidnappers.getUpKidnappersPasengersVector(), humanoids.getRaisingHumanoidsVector(), shields.getShield());

    if(std::get<0>(upKidnapperSpaceshipCollision) == true)
    {
        shields.destroyShield();
        shields.reducePlayerShields();
    }

    CHECK(Shields::availableShields == 2);
}