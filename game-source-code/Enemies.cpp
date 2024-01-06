#include "Enemies.h"

Enemies::Enemies(float screenHeight, float scrollableScreenWidth, float mapHeight, float spaceshipWidth, float spaceshipHeight):
    screenHeight_{screenHeight}, scrollableScreenWidth_{scrollableScreenWidth}, mapHeight_{mapHeight}, spaceshipWidth_{spaceshipWidth}, spaceshipHeight_{spaceshipHeight}{
}

void Enemies::initialiseEnemies(){
    enemyTexture.loadFromFile(enemyTextureFile);
    enemy_.setSize(sf::Vector2f(enemyWidth_,enemyHeight_));
    enemy_.setTexture(&enemyTexture);
    enemy_.setOrigin(enemyWidth_/2 , enemyHeight_/2);
    enemies_.clear();
    enemies_.reserve(concurrentEnemies);
    spawnTimer.restart();
    numOfEnemies = 0 ;
}

void Enemies::spawnCoordinates(){
    xRange = scrollableScreenWidth_-  enemyWidth_ -18.0f;
    yRange = screenHeight_ - mapHeight_ -  enemyHeight_; 
    xCord = rand() % xRange + enemyWidth_/2 +18.0f;
    yCord = rand() % yRange + mapHeight_ + enemyHeight_/2;
} 

void Enemies::spawnBounds(float shipXCord, float shipYCord){
    spawnCoordinates();
    while(xCord < shipXCord + 2*spaceshipWidth_ && xCord > shipXCord - 2*spaceshipWidth_&& yCord < shipYCord + 2*spaceshipHeight_ && yCord > shipYCord - 2*spaceshipHeight_){
        spawnCoordinates();
    }
}

void Enemies::spawnConditions(int generatedXCord, int generatedYCord, float spawnTime){
    numOfEnemies = enemies_.size();
   if (spawnTimer.getElapsedTime().asSeconds() >= spawnTime && numOfEnemies < concurrentEnemies &&  totalEnemies< total ){
        enemy_.setPosition(generatedXCord,generatedYCord);
        enemies_.push_back(enemy_);
        spawnTimer.restart(); 
        totalEnemies++;
    }
}

void Enemies::spawnEnemies(float shipXCord, float shipYCord){
    Enemies::spawnBounds(shipXCord, shipYCord);
    auto spawnTime = 4.0f;
    Enemies::spawnConditions(xCord,yCord,spawnTime);
}

void Enemies::declareMovements(int enemyIndex){

        auto maxEnemyXCord = enemies_[enemyIndex].getPosition().x + enemyWidth_/2;
        auto minEnemyXCord = enemies_[enemyIndex].getPosition().x - enemyWidth_/2;
        auto maxEnemyYCord = enemies_[enemyIndex].getPosition().y + enemyHeight_/2;
        auto minEnemyYCord = enemies_[enemyIndex].getPosition().y - enemyHeight_/2; 
        auto moveDistanceX = 1.0f;
        auto moveDistanceY = 1.0f;      

        if(caseClock.getElapsedTime().asSeconds() > 1.0f && !movementCase.empty()){
            movementCase.erase(movementCase.begin(), movementCase.begin() + concurrentEnemies-1);
            caseClock.restart();
        }

        if(movementCase.size() <= concurrentEnemies ){
            generateMovementCases();
        }
        Enemies::enemyMovementConditions( enemyIndex,  maxEnemyXCord, minEnemyXCord ,  maxEnemyYCord ,  minEnemyYCord,  moveDistanceX,  moveDistanceY,  movementCase);
        movementTime.restart();
}

void Enemies::generateMovementCases(){

    for (auto i = 0; i < 2*(concurrentEnemies+1); i++){
        movementCase.push_back((rand()%int{8})+1);
    }
}

// moves landers at a specified time interval if the generated coordinates are valid  
void Enemies::moveEnemies(){
    auto moveThresholdTime = 0.01f;
    if ( movementTime.getElapsedTime().asSeconds() > moveThresholdTime){
        for (int  i = 0 ; i <enemies_.size(); i++){
            Enemies::declareMovements(i);
        }
    }
}
void Enemies::enemyMovementConditions(int enemyIndex, float maxEnemyXCord, float minEnemyXCord, float maxEnemyYCord , float minEnemyYCord, int moveDistanceX, int moveDistanceY, std::vector<int> movementCase){
         
        if (movementCase[enemyIndex] == 1 && maxEnemyXCord <= scrollableScreenWidth_ -3*enemyWidth_ - moveDistanceX && maxEnemyYCord <= screenHeight_ - moveDistanceY ){
            enemies_[enemyIndex].move(sf::Vector2f(moveDistanceX,moveDistanceY)); 
        }
        else if (movementCase[enemyIndex]  == 2 && minEnemyXCord > moveDistanceX && maxEnemyYCord  <= screenHeight_ - moveDistanceY ){
            enemies_[enemyIndex].move(sf::Vector2f(-moveDistanceX,moveDistanceY)); 
        }
        else if (movementCase[enemyIndex]  == 3 &&  minEnemyXCord > + moveDistanceX && minEnemyYCord > mapHeight_ + moveDistanceY){
            enemies_[enemyIndex].move(sf::Vector2f(-moveDistanceX,-moveDistanceY)); 
        }
        else if (movementCase[enemyIndex]  == 4 && maxEnemyXCord <= scrollableScreenWidth_ - 3*enemyWidth_- moveDistanceX && minEnemyYCord > mapHeight_ + moveDistanceY){
            enemies_[enemyIndex].move(sf::Vector2f(moveDistanceX, -moveDistanceY)); 
        }
        else if (movementCase[enemyIndex]  == 5 && maxEnemyXCord <= scrollableScreenWidth_- moveDistanceX &&  minEnemyXCord > moveDistanceX){
            enemies_[enemyIndex].move(sf::Vector2f(moveDistanceX, 0.0f)); 
        }
        else if (movementCase[enemyIndex]  == 6 && maxEnemyXCord <= (screenHeight_ - moveDistanceY) && minEnemyXCord > moveDistanceX){
            enemies_[enemyIndex].move(sf::Vector2f(-moveDistanceX, 0.0f)); 
        }
        else if (movementCase[enemyIndex]  == 7 && maxEnemyYCord < (screenHeight_ - moveDistanceY) && minEnemyYCord > (mapHeight_ + moveDistanceY)){
            enemies_[enemyIndex].move(sf::Vector2f(0.0f, -moveDistanceY)); 
        }
        else if (movementCase[enemyIndex]  == 8 && maxEnemyYCord < (screenHeight_ - moveDistanceY) && minEnemyYCord > (mapHeight_ + moveDistanceY)){
            enemies_[enemyIndex].move(sf::Vector2f(0.0f, moveDistanceY)); 
        } 
        else if (maxEnemyYCord == screenHeight_ - moveDistanceY && maxEnemyXCord <= scrollableScreenWidth_ -3*enemyWidth_ - moveDistanceX && minEnemyXCord > moveDistanceX){
            enemies_[enemyIndex].move(sf::Vector2f(moveDistanceX, 0.0f)); 
        }  
        else if ( minEnemyYCord == (mapHeight_ + moveDistanceY) && maxEnemyXCord <= (scrollableScreenWidth_ -3*enemyWidth_ - moveDistanceX )&& minEnemyXCord > moveDistanceX){
            enemies_[enemyIndex].move(sf::Vector2f(moveDistanceX,0.0f)); 
        } 
}

void Enemies::resetEnemies(){
    numOfEnemies = 0;
    totalEnemies = 0;
    enemies_.clear();
    enemies_.reserve(concurrentEnemies);
}


std::vector<sf::RectangleShape>& Enemies::getEnemiesVector(){
    return enemies_;
}

sf::RectangleShape& Enemies::getEnemy(){
    return enemy_;
}

Enemies::~Enemies(){
}