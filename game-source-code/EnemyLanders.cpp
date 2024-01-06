#include "EnemyLanders.h"

EnemyLanders::EnemyLanders(float screenHeight, float scrollableScreenWidth, float mapHeight, float spaceshipWidth, float spaceshipHeight): 
    Enemies(screenHeight,scrollableScreenWidth,mapHeight,spaceshipWidth,spaceshipHeight){
    enemyWidth_ = 54.0f;
    enemyHeight_ = 48.0f;
    enemyTextureFile = "resources/Lander.png";
    concurrentEnemies = 8;
    total = 20;
}

void EnemyLanders::spawnEnemies(float shipXCord, float shipYCord){
    Enemies::spawnBounds(shipXCord, shipYCord);
    auto spawnTime = 0.5f;
    Enemies::spawnConditions(xCord,yCord,spawnTime);
}

void EnemyLanders::resetEnemies(){
    landersDestroyed = 0; 
    Enemies::resetEnemies();
} 

void EnemyLanders::incrementLandersDestroyed(){
    landersDestroyed++;
}

int EnemyLanders::landersDestroyed = 0;


 EnemyLanders::~EnemyLanders(){
 }