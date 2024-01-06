#ifndef GAME_BACKGROUND
#define GAME_BACKGROUND

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * \class CannotOpenGameBackgroundTexture
 * @brief Exception that is thrown when the game background texture file cannot be opened
 * 
 */
class CannotOpenGameBackgroundTexture{};

/**
 * \class GameBackground
 * @brief Loads the game background and allows it to be displayed on the game window
 * 
 */
class GameBackground{
public:
    /**
     * @brief Construct a new Game Background object
     * 
     */
    GameBackground();
    /**
     * @brief Loads and sets the texture for the game background
     * 
     */
    void initialiseGameBackground();
    /**
     * @brief Get the Game Background object
     * 
     * @return sf::Sprite of the game background with its texture
     */
    sf::Sprite getGameBackground();

private:
    sf::Sprite gameBackgroundImage_;
    sf::Texture gameBackgroundTexture_;
    std::string gameBackgroundTexture_file = ("resources/scrollable_Background.png");

};

#endif