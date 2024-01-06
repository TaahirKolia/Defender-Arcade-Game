#include "EnemyPods.h"

EnemyPods::EnemyPods(float screenHeight, float scrollableScreenWidth, float mapHeight, float spaceshipWidth, float spaceshipHeight):
 Enemies(screenHeight,scrollableScreenWidth,mapHeight,spaceshipWidth,spaceshipHeight){

    enemyWidth_ = 60.0f;
    enemyHeight_ = 60.0f;
    enemyTextureFile = "resources/Pod.png";
    concurrentEnemies = 1;
    total = 3;
}

void EnemyPods::spawnConditionsPods(int generatedXCord, int generatedYCord, float spawnTime, int numOfSwarmers){
    numOfEnemies = enemies_.size();
   if (spawnTimer.getElapsedTime().asSeconds() >= spawnTime && numOfEnemies < concurrentEnemies &&  totalEnemies< total && numOfSwarmers == 0){
        enemy_.setPosition(generatedXCord,generatedYCord);
        enemies_.push_back(enemy_);
        spawnTimer.restart(); 
        totalEnemies++;
    }
}

void EnemyPods::spawnPods(float shipXCord, float shipYCord, int numOfSwarmers){
    Enemies::spawnBounds(shipXCord, shipYCord);
    auto spawnTime = 4.0f;
    EnemyPods::spawnConditionsPods(xCord,yCord,spawnTime,numOfSwarmers);
}

 void EnemyPods::declareMovements(int enemyIndex){

        auto maxEnemyXCord = enemies_[enemyIndex].getPosition().x + enemyWidth_/2;
        auto minEnemyXCord = enemies_[enemyIndex].getPosition().x - enemyWidth_/2;
        auto maxEnemyYCord = enemies_[enemyIndex].getPosition().y + enemyHeight_/2;
        auto minEnemyYCord = enemies_[enemyIndex].getPosition().y - enemyHeight_/2; 
        auto moveDistanceX = 3.0f;
        auto moveDistanceY = 1.0f;     

        if(caseClock.getElapsedTime().asSeconds() > 1.0f && !movementCase.empty()){
            movementCase.erase(movementCase.begin(), movementCase.begin()+concurrentEnemies );
            caseClock.restart();
        }

        if(movementCase.size() <= concurrentEnemies ){
            generateMovementCases();
        }

        Enemies::enemyMovementConditions( enemyIndex,  maxEnemyXCord, minEnemyXCord ,  maxEnemyYCord ,  minEnemyYCord,  moveDistanceX,  moveDistanceY,  movementCase);
        movementTime.restart();
}

void EnemyPods::moveEnemies(){
    auto moveThresholdTime = 0.01f;
    if ( movementTime.getElapsedTime().asSeconds() > moveThresholdTime){
        for (int  i = 0 ; i <enemies_.size(); i++){
            EnemyPods::declareMovements(i);
        }
    }
}  
  
EnemyPods::~EnemyPods()
{
}