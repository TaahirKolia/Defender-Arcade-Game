#include "GameBackground.h"

GameBackground::GameBackground()
{}

void GameBackground::initialiseGameBackground()
{
    gameBackgroundTexture_.loadFromFile(gameBackgroundTexture_file);
    if(!gameBackgroundTexture_.loadFromFile(gameBackgroundTexture_file))
    {
        throw CannotOpenGameBackgroundTexture();
    }
    gameBackgroundImage_.setTexture(gameBackgroundTexture_);
}

sf::Sprite GameBackground::getGameBackground()
{
    return gameBackgroundImage_;
}