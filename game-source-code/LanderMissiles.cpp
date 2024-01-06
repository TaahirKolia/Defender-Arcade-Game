 #include "LanderMissiles.h"

LanderMissiles::LanderMissiles(float screenHeight, float scrollableScreenWidth, float mapHeight ):screenHeight_{screenHeight}, scrollableScreenWidth_{scrollableScreenWidth}, mapHeight_{mapHeight}{
}

void LanderMissiles::setMissiles(std::vector<sf::RectangleShape> landers_){
    
    missile.setFillColor(sf::Color::White);
    missile.setSize(sf::Vector2f(10.f,10.f));
    missile.setOrigin(5.0f,5.0f);

    if(missileClock.getElapsedTime().asSeconds()>5.0f){
        launchMissiles(landers_);
        missileClock.restart();
    }
}

void LanderMissiles::moveMissiles(float moveDistance){
            
    for(auto i = 0; i <missiles.size(); i++){
        moveShortestPath(moveDistance,i);
        checkMissileBounds(i);
    }   
}

void LanderMissiles::determineTargetPoisition(float& shipXCord, float& shipYCord, std::vector<sf::RectangleShape> landers_, float& sampleTime){

    if(missileClock.getElapsedTime().asSeconds() >= sampleTime){
        samplingOperations(shipXCord,shipYCord,landers_);
    }

    for(auto i = 0; i <missiles.size(); i++){
        calcTargetPos(i);
    }   
}

void LanderMissiles::samplingOperations(float& shipXCord, float& shipYCord, std::vector<sf::RectangleShape> landers_){
        missiles.clear();
        landerCenter.clear();
        landerCoordinates.clear();
        targetXCord_.clear();
        targetYCord_.clear();
        xCord_ = shipXCord;
        yCord_ = shipYCord;
        samplePositions(landers_);
}

void LanderMissiles::moveShortestPath(float moveDistance, int i){

        auto opposingEndTargetOne = targetXCord_[i]+scrollableScreenWidth_;     // when the lander is between 0.0f and 800.0f and the ship is between 4000.0f and 4800.0f
        auto opposingEndTargetTwo = targetXCord_[i]-scrollableScreenWidth_;     // when the lander is between 4000.0f and 4800.0f and the ship is between 0.0f and 800.0f
       
        if(abs(targetXCord_[i]) >= abs(opposingEndTargetOne)){
            angle = (atan2(targetYCord_[i], opposingEndTargetOne));
            missiles[i].move(moveDistance*cos(angle) , moveDistance*sin(angle));

        } 
        else if(abs(targetXCord_[i]) >= abs(opposingEndTargetTwo)){
            angle = (atan2(targetYCord_[i], opposingEndTargetTwo));
            missiles[i].move(moveDistance*cos(angle) , moveDistance*sin(angle));
        } 

        else if(abs(targetXCord_[i])<= abs(opposingEndTargetOne) ){
            angle = (atan2(targetYCord_[i], targetXCord_[i]));
            missiles[i].move(moveDistance*cos(angle) , moveDistance*sin(angle));
        } 
}

void LanderMissiles::calcTargetPos(int index){
        targetXCord_.push_back(xCord_ - landerCoordinates[index].x);
        targetYCord_.push_back(yCord_ - landerCoordinates[index].y);
}

void LanderMissiles::samplePositions(std::vector<sf::RectangleShape> landers_){
    
    landerCoordinates.reserve(totalMissiles);
    for (auto i = 0 ; i < landers_.size(); i++){
        landerCoordinates.push_back(sf::Vector2f(landers_[i].getPosition().x, landers_[i].getPosition().y));
    }
}

void LanderMissiles::launchMissiles(std::vector<sf::RectangleShape> landers_){
    
    for(auto i = 0; i<landers_.size(); i++){
        landerCenter.push_back(sf::Vector2f(landers_[i].getPosition().x, landers_[i].getPosition().y));
        missile.setPosition(landerCenter[i]);
        missiles.push_back(missile);
    }
}

void LanderMissiles::checkMissileBounds(int index){
    
    if (missiles[index].getPosition().x > scrollableScreenWidth_- 18.0f){
        auto yPos = missiles[index].getPosition().y;
        missiles[index].setPosition(0,yPos);
    }
    if (missiles[index].getPosition().x < 0.0f){
        auto yPos = missiles[index].getPosition().y;
        missiles[index].setPosition(scrollableScreenWidth_ - 18.0f,yPos);
    }
    if (missiles[index].getPosition().y > screenHeight_){
        missiles.erase(missiles.begin()+index);
        landerCoordinates.erase(landerCoordinates.begin()+index);
        targetXCord_.erase(targetXCord_.begin()+index);
        targetYCord_.erase(targetYCord_.begin()+index);
    }
    if (missiles[index].getPosition().y < mapHeight_){
        missiles.erase(missiles.begin()+index);
        landerCoordinates.erase(landerCoordinates.begin()+index);
        targetXCord_.erase(targetXCord_.begin()+index);
        targetYCord_.erase(targetYCord_.begin()+index);
    }
}

void LanderMissiles::start(std::vector<sf::RectangleShape> landers_, float shipXCord, float shipYCord){
    auto sampleTime = 4.4f;
    auto movementDistance = 3.0f;
    setMissiles(landers_);
    determineTargetPoisition(shipXCord,shipYCord,landers_,sampleTime);
    moveMissiles(movementDistance);
}

void LanderMissiles::resetMissiles(){
    missiles.clear();
}

std::vector<sf::RectangleShape>& LanderMissiles::getMissilesVector(){
    return missiles; 
}

std::vector<sf::Vector2f> & LanderMissiles::getCoordinatesVector(){
    return landerCoordinates;
}

void LanderMissiles::deleteMissileInfo(int missileIndex){
    landerCoordinates.erase(landerCoordinates.begin()+missileIndex);
    targetXCord_.erase(targetXCord_.begin()+missileIndex);
    targetYCord_.erase(targetYCord_.begin()+missileIndex);
    missiles.erase(missiles.begin()+ missileIndex);
    landerCenter.erase(landerCenter.begin()+missileIndex);
}

LanderMissiles::~LanderMissiles(){
}