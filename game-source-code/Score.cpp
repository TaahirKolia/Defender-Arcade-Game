#include "Score.h"

Score::Score(const std::string fontFile ):fontFile_{fontFile}{
    font.loadFromFile(fontFile_);
}

void Score::landerScoreTracker(bool laserRightCollision , bool laserLeftCollision){
    
    if (laserRightCollision == true || laserLeftCollision == true){
        score += landersScore;
        currentScoreString.clear();
    }
}

void Score::podScoreTracker(bool laserRightCollision, bool laserLeftCollision){
        if (laserRightCollision == true || laserLeftCollision == true){
        score += podsScore;
        currentScoreString.clear();
    }
}

void Score::swarmerScoreTracker(bool laserRightCollision, bool laserLeftCollision){
    if (laserRightCollision == true || laserLeftCollision == true){
        score += swarmersScore;
        currentScoreString.clear();
    }
}

void Score::humanoidSavedScoreTracker(bool laserRightCollision, bool laserLeftCollision){
    if (laserRightCollision == true  || laserLeftCollision == true){
        score += humanoidSavedScore;
        currentScoreString.clear();
    }
}

void Score::humanoidElimScoreTracker(int killedHumanoids){
    
    if (killedHumanoids > prevKilledHumanoids){
        score -= humanoidEliminatedScore;
        prevKilledHumanoids++;
        currentScoreString.clear();
    }
    if(score < 0)
    {
        score = 0;
    }
}

void Score::updateScore(){
    checkHighScore();
    currentScoreString = std::to_string(score);
    highScoreString = std::to_string(highScore);
    scoreText.setString("Current Score: " + currentScoreString +"\n\nHigh Score: "+highScoreString);
    scoreText.setFont(font);
    scoreText.setCharacterSize(15);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setStyle(sf::Text::Bold); 
    scoreText.setPosition(1250.0f, 75.0f);
}

void Score::checkHighScore(){
    if(score >= highScore ){
        highScore = score;
    }
}

void Score::resetScore(){
    score = 0;
    prevKilledHumanoids = 0;
}

sf::Text& Score::getScoreText(){
    return scoreText;
}

int Score::highScore = 0;
int Score::score = 0;
Score::~Score(){
}