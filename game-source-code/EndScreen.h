#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <SFML/Graphics.hpp>

/** \class EndScreen
 * @brief Displays end game screens for when the game is won or when the game is lost
 * 
 */
class EndScreen{

    public:
    /**
     * @brief Construct a new End Screen object
     * 
         * @param fontFile String comprising of the file directory to load the correct font. 
     */
        EndScreen(const std::string fontFile);
        /**
         * @brief Displays a screen which indicates to the player that they have won. Additionally, it shows the game scores and prompts the user to play again 
         * 
         * @param currentScore The score obtained from the current game
         * @param highScore     The highest score obtained throughout the game session 
         */
        void setWonScreen(int currentScore, int highScore);
         /**
         * @brief Displays a screen which indicates to the player that they have lost. Additionally, it shows the game scores and prompts the user to play again 
         * 
         * @param currentScore The score obtained from the current game
         * @param highScore     The highest score obtained throughout the game session 
         */
        void setLostScreen(int currentScore, int highScore);
        /**
         * @brief Chooses to display either game lost or game won screen depending on the gameWon boolean
         * 
         * @param window Window that the end game screen is displayed on
         * @param gameWon Boolean which indicates wheter the game is won 
         * @param currentScore The score obtained from the current game
         * @param highScore     The highest score obtained throughout the game session 
         */
        void endGameScreen(sf::RenderWindow& window, bool gameWon,int currentScore, int highScore);
        /**
         * @brief Destroy the End Screen object
         * 
         */
        ~EndScreen();
        
    private:
        sf::Font font;
        sf::Text gameLostText;
        sf::Text gameWonText;
        std::string fontFile_;
};

#endif