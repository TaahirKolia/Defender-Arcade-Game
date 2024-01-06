#include "EnemySwarmers.h"

EnemySwarmers::EnemySwarmers(float screenHeight, float scrollableScreenWidth, float mapHeight, float spaceshipWidth, float spaceshipHeight): 
    Enemies(screenHeight,scrollableScreenWidth,mapHeight,spaceshipWidth,spaceshipHeight){

    enemyWidth_ = 30.0f;
    enemyHeight_ = 24.0f;
    enemyTextureFile = "resources/Swarmer.png";
    concurrentEnemies = 3;
}

void EnemySwarmers::swarmerSpawnConditions(int podXCord, int podYCord, int shipYCord, int shipXCord ,float spawnTime){
    //make swarmers spawn away from ship
    auto podDirection = shipXCord - podXCord;
    float spawnOffset;


    if (podDirection <0){
        spawnOffset = 7*enemyWidth_;
    }
    else if(podDirection > 0){
        spawnOffset = -7*enemyWidth_;
    }
    if (spawnTimer.getElapsedTime().asSeconds() > spawnTime){
        enemy_.setPosition(podXCord + spawnOffset ,podYCord);
        enemies_.push_back(enemy_);
        enemy_.setPosition(podXCord + spawnOffset,podYCord + enemyHeight_);
        enemies_.push_back(enemy_);
        enemy_.setPosition(podXCord + spawnOffset ,podYCord - enemyHeight_);
        enemies_.push_back(enemy_);
    }
}

void EnemySwarmers::spawnSwarmers(float podXCord, float podYCord,  int shipYCord, int shipXCord){
    auto spawnTime = 1.0f;
    swarmerSpawnConditions(podXCord,podYCord,shipYCord,shipXCord,spawnTime);
    spawnTimer.restart();
}

void EnemySwarmers::swarmerMovement( float moveDistance){
    for(auto i = 0; i <enemies_.size(); i++){
        closestPath(moveDistance,i);
    }   
}

void EnemySwarmers::closestPath(float moveDistance, int i ){
        auto targetOne = targetXCord_[i] + scrollableScreenWidth_;
        auto targetTwo = targetXCord_[i] - scrollableScreenWidth_;
        auto scaleMovement = (i+1);
       
        if(abs(targetXCord_[i]) > abs(targetOne)){
            determineAngle(targetOne, moveDistance/scaleMovement, i);
        } 
        else if(abs(targetXCord_[i]) > abs(targetTwo)){
            determineAngle(targetTwo, moveDistance/scaleMovement, i);
        } 
        else if(abs(targetXCord_[i])<= abs(targetOne) ){
           determineAngle(targetXCord_[i], moveDistance/scaleMovement, i);
        } 
}

void EnemySwarmers::determineAngle(float target, float moveDistance,int index){
        angle = (atan2(targetYCord_[index], target));
        enemies_[index].move(moveDistance*cos(angle) , moveDistance*sin(angle));
        checkSwarmerBounds(index);
}

void EnemySwarmers::moveSwarmers(float shipXCord, float shipYCord){
    auto sampleTime = 0.1f;
    auto movementDistance = 6.0f;
    determineTargetPoisition(shipXCord,shipYCord,sampleTime);
    swarmerMovement(movementDistance);
}

void EnemySwarmers::determineTargetPoisition(float shipXCord, float shipYCord, float& sampleTime){

    if(sampleClock.getElapsedTime().asSeconds() >= sampleTime){
        samplingOperations(shipXCord,shipYCord);
    }
    for(auto i = 0; i <enemies_.size(); i++){
        calcTargetCords(i);
    }   
}

void EnemySwarmers::samplingOperations(float shipXCord, float shipYCord){
        targetXCord_.clear();
        targetYCord_.clear();
        xCord_ = shipXCord;
        yCord_ = shipYCord;
        sampleClock.restart();
}

void EnemySwarmers::calcTargetCords(int i){
    targetXCord_.push_back(xCord_ - enemies_[i].getPosition().x);
    targetYCord_.push_back(yCord_ - enemies_[i].getPosition().y);
}

void EnemySwarmers::checkSwarmerBounds(int index){
    
    if (enemies_[index].getPosition().x > scrollableScreenWidth_- 18.0f){
        auto yPos = enemies_[index].getPosition().y;
        enemies_[index].setPosition(0,yPos);
    }
    if (enemies_[index].getPosition().x < 0.0f){
        auto yPos = enemies_[index].getPosition().y;
        enemies_[index].setPosition(scrollableScreenWidth_ - 18.0f,yPos);
    }
    if (enemies_[index].getPosition().y > screenHeight_){
        auto xPos = enemies_[index].getPosition().x;
        enemies_[index].setPosition(xPos, screenHeight_- enemyHeight_/2);
    }
    if (enemies_[index].getPosition().y < mapHeight_){
        auto xPos = enemies_[index].getPosition().x;
        enemies_[index].setPosition(xPos,mapHeight_ + enemyHeight_/2);
    }
}

EnemySwarmers::~EnemySwarmers(){
} 