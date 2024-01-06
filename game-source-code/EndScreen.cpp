#include "EndScreen.h"


EndScreen::EndScreen(const std::string fontFile ):fontFile_{fontFile}{

    font.loadFromFile(fontFile_);
}

void EndScreen::setLostScreen(int currentScore, int highScore){
    auto currentScoreString = std::to_string(currentScore);
    auto highScoreString = std::to_string(highScore);
    gameLostText.setFont(font);
    gameLostText.setString("\t\t\t  GAME LOST \n\n\n\t  Current Game Score :" + currentScoreString + " \n\t  Current High Score :" + highScoreString + " \n\n\n\tPress the spacebar to return\n\t     to the main menu");
    gameLostText.setCharacterSize(30);
    gameLostText.setFillColor(sf::Color::Red);
    gameLostText.setStyle(sf::Text::Bold); 
    gameLostText.setPosition(280.0f, 270.0f);
}

void EndScreen::endGameScreen(sf::RenderWindow& window, bool gameWon, int currentScore, int highScore){

    if (gameWon == true){
        setWonScreen(currentScore,highScore);
        window.draw(gameWonText);
    }
    else{
        setLostScreen(currentScore,highScore);
        window.draw(gameLostText);
    }
}

void EndScreen::setWonScreen(int currentScore, int highScore){
    auto currentScoreString = std::to_string(currentScore);
    auto highScoreString = std::to_string(highScore);
    gameWonText.setFont(font);
    gameWonText.setString("\t\t\t GAME WON \n\n\n\t  Current Game Score :" + currentScoreString + " \n\t  Current High Score :" + highScoreString + " \n\n\n\tPress the spacebar to return\n\t     to the main menu");
    gameLostText.setCharacterSize(30);
    gameWonText.setCharacterSize(30);
    gameWonText.setFillColor(sf::Color::Green);
    gameWonText.setStyle(sf::Text::Bold); 
    gameWonText.setPosition(280.0f, 270.0f);
}

EndScreen::~EndScreen(){
}