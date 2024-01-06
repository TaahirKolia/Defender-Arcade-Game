#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <string>

/** \class Score
 * @brief Updates the game score based on when enemies are eliminated, or when humanoids are saved or abducted
 * 
 */

class Score{

    public:
    /**
     * @brief Construct a new Score object
     * 
    * @param fontFile String comprising of the file directory to load the correct font. 
     */
    Score(const std::string fontFile);
    /**
     * @brief Increments the score if a lander is destroyed  
     * 
     * @param laserRightCollision Boolen which indicates whether a right missile has collided with a lander
     * @param laserLeftCollision Boolen which indicates whether a left missile has collided with a lander
     */
    void landerScoreTracker(bool laserRightCollision , bool laserLeftCollision);
    /**
     * @brief Increments the score if a pods is destroyed  
     * 
     * @param laserRightCollision Boolen which indicates whether a right missile has collided with a pod
     * @param laserLeftCollision Boolen which indicates whether a left missile has collided with a pod
     */
    void podScoreTracker(bool laserRightCollision , bool laserLeftCollision);
    /**
     * @brief Increments the score if a swarmer is destroyed  
     * 
     * @param laserRightCollision Boolen which indicates whether a right missile has collided with a swarnmer
     * @param laserLeftCollision Boolen which indicates whether a left missile has collided with a swarnmer
     */
    void swarmerScoreTracker(bool laserRightCollision , bool laserLeftCollision);
    /**
     * @brief Increments the score if a humanoid is saved 
     * 
      * @param laserRightCollision Boolen which indicates whether a right missile has collided with a kidnapping lander
     * @param laserLeftCollision Boolen which indicates whether a left missile has collided with a kidnapping lander
     */
    void humanoidSavedScoreTracker(bool laserRightCollision, bool laserLeftCollision);
    /**
     * @brief Reduces the score if a humanoid is eliminated or abducted
     * 
     * @param killedHumanoids The total number of humanoids that have been killed 
     */
    void humanoidElimScoreTracker(int killedHumanoids);
    /**
     * @brief Updates the score after an enemy or humanoid is eliminated
     * 
     */
    void updateScore();
    /**
     * @brief Resets the game score 
     * 
     */
    void resetScore();
    /**
     * @brief Checks if the current game score is more than the high score
     * 
     */
    void checkHighScore();
    /**
     * @brief Gets the Score Text object
     * 
     * @return returns a sf::Text& which contains the game score 
     */
    sf::Text& getScoreText();
    /**
     * @brief Destroy the Score object
     * 
     */
    ~Score();

    public:
    static int score;
    static int highScore;
    private:
    sf::Font font;
    std::string fontFile_;
    int landersScore = int{150};
    int podsScore = int{1000};
    int swarmersScore = int{200};
    int humanoidSavedScore = int{500};
    int humanoidEliminatedScore = int{1000};
    int prevKilledHumanoids = int{0};
    std::string currentScoreString; 
    std::string highScoreString; 
    sf::Text scoreText;
    
};

#endif