#include "GameManager.h"


GameManager::GameManager(){
}

void GameManager::declarations(){

    myBackground.initialiseGameBackground();
    backgroundImage = myBackground.getGameBackground();
    graphics.initialiseBackgrounds();
    myLaser.initialiseLaser();
    playerLives.initialiseLifeBar();
    humanoids.initialiseHumanoidObjects();
    kidnappers.initialiseEnemies();
    shield.initialiseShieldObjects();
    srand(time(NULL));
}

void GameManager::pollEvents(){

    sf::Event evnt;
    while(window.pollEvent(evnt))
    {
        if(evnt.type == evnt.Closed)
        {
            window.close();
        }
    }
}

void GameManager::startScreenOperations(){

    window.clear();
    splashScreen.loadSplashScreen(font,splashScreenTexture, window); 
    window.display();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
        gameHasStarted = true;
        landers.initialiseEnemies();
        myFuel.initialiseFuel();
        myPlayer->initialiseShip();
        pods.initialiseEnemies();
        graphics.initialiseViews();
        swarmers.initialiseEnemies();
        kidnappers.initialiseEnemies();
    }
}

void GameManager::defaultCollisionStates(){

    landerCollision = bool{false};
    landerMissileCollision = bool{false};
    laserRightCollisionLander = bool{false};
    laserLeftCollisionLander = bool{false};
    fuelCollision = bool{false};
    laserLeftCollisionPods = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
    laserRightCollisionPods = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f)); 
    podCollision = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f)); 
    laserRightCollisionSwarmer= bool{false};
    laserLeftCollisionSwarmer = bool{false};
    swarmerCollision = bool{false};
    humanoidHitBoxLanderCollision = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f)); 
    humanoidKidnapperCollision = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f)); 
    upKidnapperLaserCollisionRight= std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
    upKidnapperLaserCollisionLeft = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
    upKidnapperSpaceshipCollision = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
    upKidnapperShieldCollision = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
    laserRaisingHumanoidCollisionRight = false;
    laserRaisingHumanoidCollisionLeft = false;
    laserFallingHumanoidCollisionRight = false;
    laserFallingHumanoidCollisionLeft = false;
    shipHumanoidCollision = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
    downKidnapperSpaceshipCollision = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
    downKidnapperShieldCollision = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
    shieldLanderCollision = false;
    shieldLanderMissileCollision = false;
    shieldPodCollision = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
    shieldSwarmerCollision = bool{false};
}

void GameManager::collisionOperations(){

    defaultCollisionStates();
    humanoidCollisions();
    landerCollision = std::get<0>(Collision.checkObject(landers.getEnemiesVector(), myPlayer->getPlayer()));
    landerMissileCollision = Collision.checkEnemyMissiles(landerMissiles.getMissilesVector(),landerMissiles,myPlayer->getPlayer());
    laserRightCollisionLander = std::get<0>(Collision.checkLaser(landers.getEnemiesVector(), myLaser.getRightLaserVector(), myLaser.getRightLaserPosVector()));
    laserLeftCollisionLander = std::get<0>(Collision.checkLaser(landers.getEnemiesVector(), myLaser.getLeftLaserVector(), myLaser.getLeftLaserPosVector()));
    fuelCollision = std::get<0>(Collision.checkObject(myFuel.getFuelcanVect(), myPlayer->getPlayer()));
    laserRightCollisionPods = (Collision.checkLaser(pods.getEnemiesVector(), myLaser.getRightLaserVector(), myLaser.getRightLaserPosVector()));
    laserLeftCollisionPods = (Collision.checkLaser(pods.getEnemiesVector(), myLaser.getLeftLaserVector(), myLaser.getLeftLaserPosVector()));
    podCollision = Collision.checkObject(pods.getEnemiesVector(), myPlayer->getPlayer());
    laserLeftCollisionSwarmer = std::get<0>(Collision.checkLaser(swarmers.getEnemiesVector(), myLaser.getLeftLaserVector(), myLaser.getLeftLaserPosVector()));
    laserRightCollisionSwarmer = std::get<0>(Collision.checkLaser(swarmers.getEnemiesVector(), myLaser.getRightLaserVector(), myLaser.getRightLaserPosVector()));
    swarmerCollision = std::get<0>(Collision.checkObject(swarmers.getEnemiesVector(), myPlayer->getPlayer()));
    shieldLanderCollision = std::get<0>(Collision.checkObject(landers.getEnemiesVector(), shield.getShield()));
    shieldLanderMissileCollision = Collision.checkEnemyMissiles(landerMissiles.getMissilesVector(),landerMissiles,shield.getShield());
    shieldPodCollision = Collision.checkObject(pods.getEnemiesVector(), shield.getShield());
    shieldSwarmerCollision = std::get<0>(Collision.checkObject(swarmers.getEnemiesVector(), shield.getShield()));

    if(fuelCollision == true)
    {
        myFuel.addFuel();
    }
    
    if(collisionClock.getElapsedTime().asSeconds() > 0.5f){
        
        if(landerCollision == true || landerMissileCollision == true || std::get<0>(podCollision) == true || swarmerCollision == true || std::get<0>(upKidnapperSpaceshipCollision) == true || std::get<0>(downKidnapperSpaceshipCollision) == true ){
            playerLives.checkPlayerLives(collisionClock);
        }
    }

    if(laserLeftCollisionLander == true || laserRightCollisionLander == true || landerCollision == true){
        landers.incrementLandersDestroyed();
    }

    if(shieldLanderCollision || shieldLanderMissileCollision || shieldSwarmerCollision || std::get<0>(shieldPodCollision) || std::get<0>(downKidnapperShieldCollision) || std::get<0>(upKidnapperShieldCollision))
    {
        shield.destroyShield();
    }
}
void GameManager::humanoidCollisions()
{
    humanoidHitBoxLanderCollision = Collision.checkHumanoidHitBox(humanoids.getHumanoidHitBoxVector(), landers.getEnemiesVector());
    if(std::get<0>(humanoidHitBoxLanderCollision) == true)
    {
        kidnappers.spawnKidnapper(std::get<1>(humanoidHitBoxLanderCollision));
        landers.incrementLandersDestroyed();
    }

    humanoidKidnapperCollision = Collision.checkHumanoid(kidnappers.getDownKidnappersVector(),humanoids.getGroundHumanoidsVector(), humanoids.getHumanoidHitBoxVector());
    if(std::get<0>(humanoidKidnapperCollision) == true)
    {
        kidnappers.spawnUpKidnapper(std::get<1>(humanoidKidnapperCollision));
        sf::Vector2f raisingHumanoidSpawnPoint (std::get<1>(humanoidKidnapperCollision).x, std::get<1>(humanoidKidnapperCollision).y + humanoids.humanoidHeight);
        humanoids.spawnRaisingHumanoid(raisingHumanoidSpawnPoint);
    }

    upKidnapperLaserCollisionRight = Collision.checkKidnappersLaser(kidnappers.getUpKidnappersVector(), kidnappers.getUpKidnappersPasengersVector(), humanoids.getRaisingHumanoidsVector(), myLaser.getRightLaserVector(), myLaser.getRightLaserPosVector());
    upKidnapperLaserCollisionLeft = Collision.checkKidnappersLaser(kidnappers.getUpKidnappersVector(), kidnappers.getUpKidnappersPasengersVector(), humanoids.getRaisingHumanoidsVector(), myLaser.getLeftLaserVector(), myLaser.getLeftLaserPosVector());
    upKidnapperSpaceshipCollision = Collision.checkKidnappersObject(kidnappers.getUpKidnappersVector(), kidnappers.getUpKidnappersPasengersVector(), humanoids.getRaisingHumanoidsVector(), myPlayer->getPlayer());
    upKidnapperShieldCollision = Collision.checkKidnappersObject(kidnappers.getUpKidnappersVector(), kidnappers.getUpKidnappersPasengersVector(), humanoids.getRaisingHumanoidsVector(), shield.getShield());
    if(std::get<0>(upKidnapperLaserCollisionRight) == true)
    {
        humanoids.spawnFallingHumanoid(std::get<1>(upKidnapperLaserCollisionRight));
    }
    if(std::get<0>(upKidnapperLaserCollisionLeft) == true)
    {
        humanoids.spawnFallingHumanoid(std::get<1>(upKidnapperLaserCollisionLeft));
    }
    if(std::get<0>(upKidnapperSpaceshipCollision) == true)
    {
        humanoids.spawnFallingHumanoid(std::get<1>(upKidnapperSpaceshipCollision));
    }
    if(std::get<0>(upKidnapperShieldCollision) == true)
    {
        humanoids.spawnFallingHumanoid(std::get<1>(upKidnapperShieldCollision));
    }

    laserRaisingHumanoidCollisionRight =  Collision.checkHumanoidLaser(humanoids.getRaisingHumanoidsVector(), kidnappers.getUpKidnappersPasengersVector(), myLaser.getRightLaserVector(), myLaser.getRightLaserPosVector());
    laserRaisingHumanoidCollisionLeft =  Collision.checkHumanoidLaser(humanoids.getRaisingHumanoidsVector(), kidnappers.getUpKidnappersPasengersVector(), myLaser.getLeftLaserVector(), myLaser.getLeftLaserPosVector());
    laserFallingHumanoidCollisionRight =  Collision.checkHumanoidLaser(humanoids.getFallingHumanoidsVector(), kidnappers.getUpKidnappersPasengersVector(), myLaser.getRightLaserVector(), myLaser.getRightLaserPosVector());
    laserFallingHumanoidCollisionLeft =  Collision.checkHumanoidLaser(humanoids.getFallingHumanoidsVector(), kidnappers.getUpKidnappersPasengersVector(), myLaser.getLeftLaserVector(), myLaser.getLeftLaserPosVector());

    if(laserRaisingHumanoidCollisionRight || laserRaisingHumanoidCollisionLeft || laserFallingHumanoidCollisionRight || laserFallingHumanoidCollisionLeft)
    {
        humanoids.incrementKilledHumanoids();
    }

    if(myPlayer->hasPassenger == false)
    {
        shipHumanoidCollision = Collision.checkObject(humanoids.getFallingHumanoidsVector(), myPlayer->getPlayer());
    }

    if(std::get<0>(shipHumanoidCollision) == true)
    {
        myPlayer->hasPassenger = true;
        shipHumanoidCollision = std::make_tuple(false, sf::Vector2f(0.0f, 0.0f));
    }

    if(myPlayer->getPlayer().getPosition().y == SCREENHEIGHT-SPACESHIPHEIGHT/2 && myPlayer->hasPassenger)
    {
        humanoids.spawnGroundHumanoid(myPlayer->getPlayer().getPosition());
        myPlayer->hasPassenger = false;
    }

    downKidnapperSpaceshipCollision = Collision.checkObject(kidnappers.getDownKidnappersVector(), myPlayer->getPlayer());
    downKidnapperShieldCollision = Collision.checkObject(kidnappers.getDownKidnappersVector(), shield.getShield());
}

void GameManager::updateGameScore(){
    gameScore.podScoreTracker( std::get<0>(laserRightCollisionPods), std::get<0>(laserLeftCollisionPods));
    gameScore.landerScoreTracker( laserRightCollisionLander,  laserLeftCollisionLander);
    gameScore.swarmerScoreTracker( laserRightCollisionSwarmer,  laserLeftCollisionSwarmer);
    gameScore.humanoidSavedScoreTracker(std::get<0>(upKidnapperLaserCollisionLeft), std::get<0>(upKidnapperLaserCollisionRight));
    gameScore.humanoidElimScoreTracker(Humanoids::killedHumanoids);
    gameScore.updateScore();
}

void GameManager::gameMechanics(){

    std::tuple <bool, bool, bool, bool, bool> movementInputs;
    movementInputs = std::make_tuple(false, false, false, false, false);
    movementInputs = myPlayer->getMovementInputs(movementInputs);
    bool moveLeft = std::get<0>(movementInputs);
    bool moveRight = std::get<1>(movementInputs);
    bool moveUp = std::get<2>(movementInputs);
    bool moveDown = std::get<3>(movementInputs);
    bool spaceshipIsMoving = std::get<4>(movementInputs);

    std::tuple <bool, bool> shootingInputs;
    shootingInputs = std::make_tuple(false, false);
    shootingInputs = myLaser.getMovementInputs(shootingInputs, myPlayer->spaceshipDirection);
    bool shootRight = std::get<0>(shootingInputs);
    bool shootLeft = std::get<1>(shootingInputs);
    auto shipXCord = myPlayer->getPlayer().getPosition().x;
    auto shipYCord = myPlayer->getPlayer().getPosition().y;

    landers.spawnEnemies(shipXCord, shipYCord);
    landers.moveEnemies();
    landerMissiles.start(landers.getEnemiesVector(),shipXCord, shipYCord);

    if (std::get<0>(laserLeftCollisionPods) == true){
        auto podCords =  std::get<1>(laserLeftCollisionPods);
        swarmers.spawnSwarmers(podCords.x,podCords.y, shipYCord,shipXCord);
    }
    if (std::get<0>(laserRightCollisionPods) == true){
        auto podCords =  std::get<1>(laserRightCollisionPods);
        swarmers.spawnSwarmers(podCords.x,podCords.y,shipYCord,shipXCord);
    }
    if (std::get<0>(podCollision) == true){
        auto podCords =  std::get<1>(podCollision);
        swarmers.spawnSwarmers(podCords.x,podCords.y,shipYCord,shipXCord);
    }
    if (std::get<0>(shieldPodCollision) == true){
        auto podCords =  std::get<1>(shieldPodCollision);
        swarmers.spawnSwarmers(podCords.x,podCords.y,shipYCord,shipXCord);
    }
    
    swarmers.moveSwarmers(shipXCord, shipYCord);

    pods.spawnPods(shipXCord, shipYCord, swarmers.getEnemiesVector().size());
    pods.moveEnemies();

    myLaser.shoot(shootRight, shootLeft, myPlayer->getPlayer().getPosition().x, myPlayer->getPlayer().getPosition().y);
    myLaser.moveLasers();
    
    bool shipHasFuel = myFuel.checkFuelLevel();
    myPlayer->checkSpaceshipMovement(moveLeft, moveRight, moveUp, moveDown, shipHasFuel);
    myFuel.doFuelOperations(spaceshipIsMoving);
    humanoids.doHumanoidOperations();
    kidnappers.moveKidnappers();
    shield.checkShieldInput();
    shield.moveShield(myPlayer->getPlayer().getPosition().x, myPlayer->getPlayer().getPosition().y);
}

void GameManager::gameOperations(){

    gameMechanics();
    collisionOperations(); 
    updateGameScore();
    endGameChecks();

    window.clear();
    graphics.gameScrolling(window,landers,pods, landerMissiles,*myPlayer, myLaser,myFuel,swarmers,kidnappers,humanoids,shield);
    graphics.minimap(window,landers,pods, landerMissiles,*myPlayer, myLaser,myFuel,swarmers,kidnappers,humanoids,shield);
    graphics.HUD(window,myFuel,playerLives,gameScore,shield);
    window.display();    
    window.setView(window.getDefaultView()); 
}

void GameManager::gameStates(){
    if (gameHasStarted == false && gameHasEnded == false){
        startScreenOperations();
    }
    if(gameHasStarted == true && gameHasEnded == false){
        gameOperations();
    }
    if(gameHasStarted == true && gameHasEnded == true){
        endScreenOperations();
    } 
}

void GameManager::play(){
    declarations();
    window.setFramerateLimit(60);
     while (window.isOpen())
    {
        pollEvents();
        gameStates();
    } 
}
GameManager::~GameManager(){
}

void GameManager::endGameChecks(){

    if (EnemyLanders::landersDestroyed== 20){
        resetParameters();
        gameHasEnded = true;
        gameWon = true;
    } 
        
    if(playerLives.getPlayerLives() == 0 || (myPlayer->getPlayer().getPosition().y == SCREENHEIGHT-SPACESHIPHEIGHT/2 && myFuel.checkFuelLevel() == false )){
        gameHasEnded = true;
        gameWon = false; 
        resetParameters();
    }

    if(humanoids.getKilledHumanoids() == humanoids.maxHumanoidCount)
    {
        gameHasEnded = true;
        gameWon = false;
        resetParameters();
    }
}

void GameManager::resetParameters(){
    landers.resetEnemies();
    landerMissiles.resetMissiles();
    swarmers.resetEnemies();
    pods.resetEnemies();
    playerLives.reset();
    numOfLives = 3;
    myFuel.resetFuel();
    myLaser.resetLasers();
    myPlayer->spaceshipDirection = true;
    myPlayer->hasPassenger = false;
    humanoids.reset();
    kidnappers.resetEnemies();
    shield.reset();
}

void GameManager::endScreenOperations(){
    window.clear();
    endScreen.endGameScreen(window,gameWon, Score::score, Score::highScore);
    window.display();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        gameHasEnded = false;
        gameHasStarted = false;
        gameWon = false;
        gameScore.resetScore();
    }
}