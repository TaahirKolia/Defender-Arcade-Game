#include "splash_screen.h"
#include <string>
#include <SFML/Graphics.hpp>

SplashScreen::SplashScreen(const std::string fontFile, const std::string backgroundFile, sf::Font& font, sf::Texture& texture ): fontFile_{fontFile}, backgroundFile_{backgroundFile}{

    texture.loadFromFile(backgroundFile_);
    if(!texture.loadFromFile(backgroundFile_)){
        throw cannotOpenBackgroundFile();
    } 

    font.loadFromFile(fontFile_);
    if(!font.loadFromFile(fontFile_)){
        throw cannotOpenFontFile();
    } 
}

void SplashScreen::loadSplashBackground(sf::Texture& texture){
    splashBackground.setTexture(texture);
}

void SplashScreen::loadTitle(sf::Font& font){
    title.setFont(font);
    title.setString("DEFENDER\n ");
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(405.0f, 120.0f); 

    titleBackdrop.setFont(font);
    titleBackdrop.setString("DEFENDER\n ");
    titleBackdrop.setCharacterSize(100);
    titleBackdrop.setFillColor(sf::Color::Red);
    titleBackdrop.setStyle(sf::Text::Bold);
    titleBackdrop.setPosition(400.0f, 125.0f);
}

void SplashScreen::loadInstructions(sf::Font& font){
    instructions.setFont(font);
    instructions.setString("\t   Controls: \n\n Move Up\t\t  : W\n Move Left\t\t: A\n Move Down\t\t: S\n Move Right\t   : D \n Shoot\t\t\t: J \n Activate Shield  : K");
    instructions.setCharacterSize(30);
    instructions.setFillColor(sf::Color::Red);
    instructions.setStyle(sf::Text::Bold); 
    instructions.setPosition(470.0f, 370.0f);
}

void SplashScreen::loadStartMessage(sf::Font& font){
    startMessage.setFont(font);
    startMessage.setString("Press \" Enter \" To Start The Game");
    startMessage.setCharacterSize(30);
    startMessage.setFillColor(sf::Color(100,181,226));
    startMessage.setStyle(sf::Text::Bold); 
    startMessage.setPosition(290.0f, 750.0f);
}

void SplashScreen::loadSpaceShip(){
    spaceShipTexture.loadFromFile(spaceShipRightFile_);
        
    if(!spaceShipTexture.loadFromFile(spaceShipRightFile_)){
        throw cannotOpenSpaceShipRightFile();
    } 
        
    spaceShip.setTexture(&spaceShipTexture);
    spaceShip.setPosition(450.0f,75.0f);  
}

void SplashScreen::loadSplashScreen(sf::Font& font, sf::Texture& texture ,sf::RenderWindow& window){
    SplashScreen::loadSplashBackground(texture);
    window.draw(splashBackground);
    SplashScreen::loadTitle(font);
    window.draw(titleBackdrop);
    window.draw(title);  
    SplashScreen::loadInstructions(font);
    window.draw(instructions);
    SplashScreen::loadStartMessage(font);
    window.draw(startMessage);
    SplashScreen::loadSpaceShip();
    window.draw(spaceShip);
}

SplashScreen::~SplashScreen(){
}