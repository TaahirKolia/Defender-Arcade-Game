#include "Collisions.h"

Collisions::Collisions(){
}

void Collisions::NextPosition(sf::RectangleShape& spaceShip){

    nextPos = spaceShip.getGlobalBounds();
    nextPos.left += MOVEDISTANCE;
    nextPos.top += MOVEDISTANCE;

}

std::tuple<bool, sf::Vector2f> Collisions::checkObject(std::vector<sf::RectangleShape>& Object, sf::RectangleShape& spaceShip){

    NextPosition(spaceShip);
    for (auto i = 0 ; i < Object.size(); i ++){

        auto objectPosition = Object[i].getGlobalBounds();
        auto objectCords= Object[i].getPosition();
        if(objectPosition.intersects(spaceShip.getGlobalBounds())){
            Object.erase(Object.begin()+i);
            return std::make_tuple(true, objectCords);
        }
    }
    return std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
} 


bool Collisions::checkEnemyMissiles(std::vector<sf::RectangleShape>& EnemyMissile, LanderMissiles& landerMissile , sf::RectangleShape& spaceShip){

    NextPosition(spaceShip);
    for (auto i = 0 ; i < EnemyMissile.size(); i ++){
        
        if(EnemyMissile[i].getGlobalBounds().intersects(spaceShip.getGlobalBounds())){
            landerMissile.deleteMissileInfo(i);
            return true;
        }
    }
    return false;
} 

std::tuple<bool, sf::Vector2f> Collisions::checkLaser(std::vector<sf::RectangleShape>& Enemy, std::vector<sf::RectangleShape>& Laser, std::vector<float>& laserPos){

    for (auto j= 0; j< Laser.size(); j++){

        auto laserPosition = Laser[j].getGlobalBounds();
        for (auto i = 0 ; i < Enemy.size(); i ++){
            auto enemyPosition = Enemy[i].getGlobalBounds();
            
            if(enemyPosition.intersects(laserPosition)){
                auto enemyCoords = Enemy[i].getPosition();
                Enemy.erase(Enemy.begin()+i);
                Laser.erase(Laser.begin()+j);
                laserPos.erase(laserPos.begin()+j);
                return std::make_tuple(true, enemyCoords);
            }
        }
    }
    return std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
}

std::tuple<bool, sf::Vector2f> Collisions::checkHumanoidHitBox(std::vector<sf::RectangleShape>& hitbox, std::vector<sf::RectangleShape>& lander){

    for (auto j= 0; j< lander.size(); j++){

        auto landerPosition = lander[j].getGlobalBounds();
        auto landerCoords = lander[j].getPosition();
        
        for (auto i = 0 ; i < hitbox.size(); i ++)
        {
            auto objectPosition = hitbox[i].getGlobalBounds();
            if(objectPosition.intersects(landerPosition))
            {
                lander.erase(lander.begin()+j);
                hitbox[i].setScale(-1.0f,-1.0f);
                return std::make_tuple(true, landerCoords);
            }
        }
    }
    return std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
} 

std::tuple<bool, sf::Vector2f> Collisions::checkHumanoid(std::vector<sf::RectangleShape>& lander, std::vector<sf::RectangleShape>& humanoid, std::vector<sf::RectangleShape>& hitBox){

    for (auto j= 0; j< lander.size(); j++){

        auto landerPosition = lander[j].getGlobalBounds();
        auto landerCoords = lander[j].getPosition();
        
        for (auto i = 0 ; i < humanoid.size(); i ++)
        {
            auto objectPosition = humanoid[i].getGlobalBounds();
            if(objectPosition.intersects(landerPosition))
            {
                lander.erase(lander.begin()+j);
                humanoid.erase(humanoid.begin()+i);
                hitBox.erase(hitBox.begin()+i);
                return std::make_tuple(true, landerCoords);
            }
        }
    }
    return std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
} 

std::tuple<bool, sf::Vector2f> Collisions::checkKidnappersLaser(std::vector<sf::RectangleShape>& lander, std::vector<bool>& passenger, std::vector<sf::RectangleShape>& human, std::vector<sf::RectangleShape>& laser, std::vector<float>& laserPos){

    for (auto j= 0; j< lander.size(); j++){

        auto landerPosition = lander[j].getGlobalBounds();
        auto landerCoords = lander[j].getPosition();
        
        for (auto i = 0 ; i < laser.size(); i ++)
        {
            auto objectPosition = laser[i].getGlobalBounds();
            if(objectPosition.intersects(landerPosition) && passenger[j] == true)
            {
                lander.erase(lander.begin()+j);
                human.erase(human.begin()+j);
                passenger.erase(passenger.begin()+j);
                laser.erase(laser.begin()+i);
                laserPos.erase(laserPos.begin()+i);
                return std::make_tuple(true, landerCoords);
            }
            else if(objectPosition.intersects(landerPosition) && passenger[j] == false)
            {
                lander.erase(lander.begin()+j);
                passenger.erase(passenger.begin()+j);
                laser.erase(laser.begin()+i);
                laserPos.erase(laserPos.begin()+i);
                return std::make_tuple(false, landerCoords);
            }
        }
    }
    return std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
} 

std::tuple<bool, sf::Vector2f> Collisions::checkKidnappersObject(std::vector<sf::RectangleShape>& lander, std::vector<bool>& passenger, std::vector<sf::RectangleShape>& human, sf::RectangleShape& object){

    NextPosition(object);
    for (auto i = 0 ; i < lander.size(); i ++){

        auto objectPosition = lander[i].getGlobalBounds();
        auto landerCoords = lander[i].getPosition();
        if(objectPosition.intersects(object.getGlobalBounds()) && passenger[i] == true){
            lander.erase(lander.begin()+i);
            human.erase(human.begin()+i);
            passenger.erase(passenger.begin()+i);

            return std::make_tuple(true, landerCoords);
        }
        else if(objectPosition.intersects(object.getGlobalBounds()) && passenger[i] == false)
        {
            lander.erase(lander.begin()+i);
            passenger.erase(passenger.begin()+i);

            return std::make_tuple(false, landerCoords);
        }
    }
    return std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
} 

bool Collisions::checkHumanoidLaser(std::vector<sf::RectangleShape>& Enemy,std::vector<bool>& Passengers, std::vector<sf::RectangleShape>& Laser, std::vector<float>& laserPos){

    for (auto j= 0; j< Laser.size(); j++){

        auto laserPosition = Laser[j].getGlobalBounds();
        for (auto i = 0 ; i < Enemy.size(); i ++){
           
            auto objectPosition = Enemy[i].getGlobalBounds();
            if(objectPosition.intersects(laserPosition)){
                Enemy.erase(Enemy.begin()+i);
                Passengers[i] = false;
                Laser.erase(Laser.begin()+j);
                laserPos.erase(laserPos.begin()+j);

                return true;
            }
        }
    }
    return false;
} 

Collisions::~Collisions(){
};