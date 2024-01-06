#include "GraphicsManager.h"

Graphics::Graphics(float screenHeight, float windowWidth,float scrollableScreenWidth, float mapHeight):
    screenHeight_{screenHeight},windowWidth_{windowWidth}, scrollableScreenWidth_{scrollableScreenWidth}, mapHeight_{mapHeight}{
}

void Graphics::enemyObjects(sf::RenderWindow& window, EnemyLanders& landers, EnemyPods& pods, LanderMissiles& landerMissiles, EnemySwarmers& swarmers, KidnappingLanders& kidnappers, Humanoids& humanoids){

        draw.printObject(window, landers.getEnemiesVector());
        draw.printObject(window,landerMissiles.getMissilesVector());
        draw.printObject(window,pods.getEnemiesVector());
        draw.printObject(window,humanoids.getHumanoidHitBoxVector());
        draw.printObject(window,humanoids.getGroundHumanoidsVector());
        draw.printObject(window,humanoids.getRaisingHumanoidsVector());
        draw.printObject(window,humanoids.getFallingHumanoidsVector());
        draw.printObject(window,kidnappers.getDownKidnappersVector());
        draw.printObject(window,kidnappers.getUpKidnappersVector());
        draw.printObject(window,swarmers.getEnemiesVector());
}

void Graphics::initialiseBackgrounds(){
        myBackground.initialiseGameBackground();
        backgroundImage = myBackground.getGameBackground();
}

void Graphics::shipObjects(sf::RenderWindow& window, Spaceship& myPlayer, Laser& lasers, Fuel& fuel, Shields& shield){

        draw.printRectObject(window,myPlayer.getPlayer());
        draw.printObject(window,lasers.getLeftLaserVector());
        draw.printObject(window, lasers.getRightLaserVector());
        draw.printRectObject(window,shield.getShield());
        draw.printObject(window,fuel.getFuelcanVect());
}

void Graphics::HUD(sf::RenderWindow& window, Fuel& fuel, PlayerLives& playerLives, Score& gameScore, Shields& shield){
    hudView.setCenter(windowWidth_/2,screenHeight_/2);
    window.setView(hudView);
    mapSeparationLine.setSize(sf::Vector2f(windowWidth_, mapSeparationLineThickness));
    mapSeparationLine.setPosition(0,mapHeight_-mapSeparationLineThickness);
    mapLeftSeparationLine.setSize(sf::Vector2f(mapSeparationLineThickness, mapHeight_));
    mapLeftSeparationLine.setPosition(mapLeftSeparationLinePos, 0);
    mapRightSeparationLine.setSize(sf::Vector2f(mapSeparationLineThickness, mapHeight_));
    mapRightSeparationLine.setPosition(mapRightSeparationLinePos, 0);

    draw.printRectObject(window,mapLeftSeparationLine);
    draw.printRectObject(window,mapSeparationLine);
    draw.printRectObject(window,mapRightSeparationLine);
    draw.printObject(window,playerLives.getLivesBar());
    draw.printText(window,gameScore.getScoreText());  
    draw.printObject(window,fuel.getFuelBar());
    draw.printObject(window, shield.getShieldBar());
}

void Graphics::initialiseViews(){

    gameView1.reset(sf::FloatRect(0,mapHeight_, windowWidth_, screenHeight_));
    gameView1.setViewport(sf::FloatRect(0,0,1.0f, 1.0f));
    hudView.reset(sf::FloatRect(0,0, windowWidth_, screenHeight_));
    hudView.setViewport(sf::FloatRect(0,0, 1.0f, 1.0f));
    gameView2.reset(sf::FloatRect(0.0f,200.0f, windowWidth_, screenHeight_));
    gameView2.setViewport(sf::FloatRect(0.4935f,0, 1.0f, 1.0f)); 
    mapView.reset(sf::FloatRect(0,200.0f, scrollableScreenWidth_, screenHeight_));
    mapView.setViewport(sf::FloatRect(0.25f,-0.06f, 0.5f, 0.275f));
    mapView.setCenter(4800/2,(screenHeight_/2));

}

void Graphics::gameScrolling(sf::RenderWindow& window, EnemyLanders& landers, EnemyPods& pods, LanderMissiles& landerMissiles,
Spaceship& myPlayer, Laser& lasers, Fuel& fuel, EnemySwarmers& swarmers, KidnappingLanders& kidnappers, Humanoids& humanoids, Shields& shield){

    gameView1.setCenter(screenPosition);

    if(myPlayer.getPlayer().getPosition().x > windowWidth_/2 && myPlayer.getPlayer().getPosition().x < 4000.0f ){
        screenPosition.x = myPlayer.getPlayer().getPosition().x;
        window.setView(gameView1); 
        window.draw(backgroundImage);   
        shipObjects(window, myPlayer,lasers,fuel,shield);
        enemyObjects(window,landers,pods,landerMissiles,swarmers,kidnappers,humanoids);
    }   
     else if(myPlayer.getPlayer().getPosition().x >= 4000.0f && myPlayer.getPlayer().getPosition().x <= 4800.0f)
    {
        gameView2.setViewport(sf::FloatRect(0.4935f,0, 1.0f, 1.0f)); 
        screenPosition.x = myPlayer.getPlayer().getPosition().x;
        gameView2.setCenter(myPlayer.getPlayer().getPosition().x -4001.0f  ,screenHeight_/2);
        window.setView(gameView2);
        window.draw(backgroundImage);   
        shipObjects(window, myPlayer,lasers,fuel,shield); 
        enemyObjects(window,landers,pods,landerMissiles,swarmers,kidnappers,humanoids);

        window.setView(gameView1);
        window.draw(backgroundImage);   
        shipObjects(window, myPlayer,lasers,fuel,shield);
        enemyObjects(window,landers,pods,landerMissiles,swarmers,kidnappers,humanoids);
        } 
    else if(myPlayer.getPlayer().getPosition().x >= 0.0f && myPlayer.getPlayer().getPosition().x <= 800.0f)
    {
        screenPosition.x = myPlayer.getPlayer().getPosition().x;
        gameView2.setCenter(4000.0f + myPlayer.getPlayer().getPosition().x ,screenHeight_/2);
        gameView2.setViewport(sf::FloatRect(-0.494f,0, 1.0f, 1.0f));
        window.setView(gameView2);
        window.draw(backgroundImage);   
        shipObjects(window, myPlayer,lasers,fuel,shield);
        enemyObjects(window,landers,pods,landerMissiles,swarmers,kidnappers,humanoids);

        window.setView(gameView1); 
        window.draw(backgroundImage);   
        shipObjects(window, myPlayer,lasers,fuel,shield);
        enemyObjects(window,landers,pods,landerMissiles,swarmers,kidnappers,humanoids);
    }   
}

void Graphics::minimap(sf::RenderWindow& window, EnemyLanders& landers, EnemyPods& pods, LanderMissiles& landerMissiles,
Spaceship& myPlayer, Laser& lasers, Fuel& fuel, EnemySwarmers& swarmers, KidnappingLanders& kidnappers, Humanoids& humanoids, Shields& shield){

    window.setView(mapView);  
    window.draw(backgroundImage);   
    shipObjects(window, myPlayer,lasers,fuel,shield);
    enemyObjects(window,landers,pods,landerMissiles,swarmers,kidnappers,humanoids);
    minimapPositionBars(window,myPlayer);
}

void Graphics::minimapPositionBars(sf::RenderWindow& window,Spaceship& myPlayer){

    auto minimapBarRight = sf::RectangleShape{};
    auto minimapBarLeft= sf::RectangleShape{};
    
    if(myPlayer.getPlayer().getPosition().x > scrollableScreenWidth_ - windowWidth_/2){
        shipXPosRight = 0.0f - scrollableScreenWidth_ + windowWidth_/2 + myPlayer.getPlayer().getPosition().x;
    }
    else{
        shipXPosRight = myPlayer.getPlayer().getPosition().x + windowWidth_/2;
    }
    if(myPlayer.getPlayer().getPosition().x > 0 && myPlayer.getPlayer().getPosition().x < windowWidth_/2){
        shipXPosLeft = scrollableScreenWidth_ - windowWidth_/2 + myPlayer.getPlayer().getPosition().x;
    }
    else{
    shipXPosLeft = myPlayer.getPlayer().getPosition().x - windowWidth_/2;
    }

    minimapBarLeft.setSize(sf::Vector2f(10.0f, screenHeight_ - mapHeight_ ));
    minimapBarLeft.setPosition(shipXPosLeft,mapHeight_-mapSeparationLineThickness);
    minimapBarLeft.setFillColor(sf::Color::Red);
    minimapBarRight.setSize(sf::Vector2f(10.0f, screenHeight_ - mapHeight_ ));
    minimapBarRight.setPosition(shipXPosRight ,mapHeight_-mapSeparationLineThickness);
    minimapBarRight.setFillColor(sf::Color(100,181,226));

    window.draw(minimapBarLeft);
    window.draw(minimapBarRight);
}
