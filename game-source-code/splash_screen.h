#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <SFML/Graphics.hpp>

/**
 * @brief Exception that is thrown when the font file cannot load.
 */
class cannotOpenFontFile{};
/**
 * @brief Exception that is thrown when the background texture file cannot load.
 */
class cannotOpenBackgroundFile{};
/**
 * @brief Exception that is thrown when the spaceship texture file cannot load.
 */
class cannotOpenSpaceShipRightFile{};

/**
 * \class SplashScreen
 * @brief The Splash Screen Class is responsible for displaying a start up screen consisting of a sprite background and text that informs
 * the user how to play and start the game.     
 */
class SplashScreen{

    public:
        /**
         * @brief Construct a new Splash Screen object
         * 
         * @param fontFile String comprising of the file directory to load the correct font. 
         * @param backgroundFile String comprising of the file directory to load the correct font. 
         * @param font Font variable that is initialised with the font found in the font file.
         * @param texture Texture varaible that is initialised with the texture loaded from the background file
         */
        SplashScreen(const std::string fontFile, const std::string backgroundFile, sf::Font& font, sf::Texture& texture);
        /**
         * @brief Responsible for setting the correct texture to the splash screeen background 
         * 
         * @param texture Texture that is applied to the splash screen background.
         */
        void loadSplashBackground(sf::Texture& texture);
        /**
         * @brief Sets the properties such as the position, size, font, and colour of the text associated with the game title.
         * 
         * @param font Font that is applied to text on the splash screen.
         */
        void loadTitle(sf::Font& font);
        /**
         * @brief Sets the properties such as the position, size, font, and colour of the text associated with the game instructions.
         * 
         * @param font Font that is applied to text on the splash screen.
         */
        void loadInstructions(sf::Font& font);
        /**
         * @brief Sets the properties such as the position, size, font, and colour of the text to start the game.
         * 
         * @param font Font that is applied to text on the splash screen.
         */
        void loadStartMessage(sf::Font& font);
        /**
         * @brief Sets the position of the sf::RectangleShape and loads and sets the texture to be player's spaceship .
         */
        void loadSpaceShip();
        /**
         * @brief Calls the other SplashScreen functions so that the different start screen segements are drawn together to the window.  
         * 
         * @param font Font that is applied to text on the splash screen.
         * @param texture Texture that is applied to the splash screen background.
         * @param window The display window that the function draws to.
         */
        void loadSplashScreen(sf::Font& font, sf::Texture& texture ,sf::RenderWindow& window);
        /**
         * @brief Destroy the Splash Screen object
         */
        ~SplashScreen();

    private:

        std::string fontFile_;
        std::string backgroundFile_;
        sf::Sprite splashBackground;
        sf::Text title;
        sf::Text titleBackdrop;
        sf::Text instructions;
        sf::Text startMessage;
        sf::Texture spaceShipTexture;
        std::string spaceShipRightFile_{"resources\\Spaceship_right.png"};
        sf::RectangleShape spaceShip{sf::Vector2f(102.0f,36.0f)};

};
#endif