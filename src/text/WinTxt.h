/*******************************************************************************
 * @file wintxt.h
 * @brief Defines the WinTxt class for managing the text-based game.
 ******************************************************************************/

#ifndef WINTXT_H
#define WINTXT_H

#include <cassert>

/*******************************************************************************
 * @class WinTxt
 * @brief Version of the game in the terminal.
 ******************************************************************************/
struct Player {
    char p; /**< Player identifier. */
    int x; /**< Index of the player on the ground. */
    int y; /**< Index of the player on the air. */
    int h; /**< Health points of the player. */
};

class WinTxt {
private:
    char m_terrain_jump[70]; /**< Representation of the air. */
    char m_terrain_ground[70]; /**< Representation of the ground. */

    Player m_player1; /**< Player 1 instance. */
    Player m_player2; /**< Player 2 instance. */
    int m_time; /**< Current time in the round. */
    int m_round; /**< Current round in the game. */

public:
    /***************************************************************************
     * @brief Default constructor for the WinTxt class.
     **************************************************************************/
    WinTxt();

    /***************************************************************************
     * @brief Destructor for the WinTxt class.
     **************************************************************************/
    ~WinTxt();

    // Movements
    /***************************************************************************
     * @brief Moves a player to the right.
     * @param p a player.
     **************************************************************************/
    void moveRight(Player& p);

    /***************************************************************************
     * @brief Moves a player to the left.
     * @param p a player.
     **************************************************************************/
    void moveLeft(Player& p);

    /***************************************************************************
     * @brief Moves a player to the air.
     * @param p a player.
     **************************************************************************/
    void jumpUp(Player& p);

    /***************************************************************************
     * @brief Moves a player to the ground.
     * @param p a player.
     **************************************************************************/
    void jumpDown(Player& p);

    /***************************************************************************
     * @brief Identifier of a player become o.
     * @param p a player.
     **************************************************************************/
    void crouch(Player& p);
    
    /***************************************************************************
     * @brief Identifier of a player become P.
     * @param p a player.
     **************************************************************************/
    void punch(Player& p);

    /***************************************************************************
     * @brief Identifier of a player become K.
     * @param p a player.
     **************************************************************************/
    void kick(Player& p);

    /***************************************************************************
     * @brief Identifier of a player become O.
     * @param p a player.
     **************************************************************************/
    void reset(Player& p);

    // Tests position/health
    /***************************************************************************
     * @brief Tests player 1's position.
     * @return true if player 2 is near player 1.
     **************************************************************************/
    bool testPositionP1();

    /***************************************************************************
     * @brief Tests player 2's position.
     * @return true if player 1 is near player 2.
     **************************************************************************/
    bool testPositionP2();

    /***************************************************************************
     * @brief Tests players' health.
     * @return true if player 1 health is 0 or if player 2 health is 0.
     **************************************************************************/
    bool testHealth();

    // Updates
    /***************************************************************************
     * @brief Updates player 1's health.
     **************************************************************************/
    void updateHealthP1(); 
    
    /***************************************************************************
     * @brief Updates player 2's health.
     **************************************************************************/
    void updateHealthP2();

    /***************************************************************************
     * @brief Updates the round.
     **************************************************************************/
    void updateRound(); 

    // Display
    /***************************************************************************
     * @brief  Displays the game.
     **************************************************************************/
    void afficher();

    // Events
    /***************************************************************************
     * @brief Handles game events
     **************************************************************************/
    void event();

    // Run
    /***************************************************************************
     * @brief Runs the text-based game.
     **************************************************************************/
    void runTxt();

    /***************************************************************************
     * @brief Performs regression testing for the WinTxt class.
     **************************************************************************/
    static void regressionTest();
};

#endif
