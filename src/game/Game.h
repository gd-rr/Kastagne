/*******************************************************************************
 * @file game.h
 * @brief Defines the Game class for managing the game state and scenes.
 ******************************************************************************/
#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <vector>
#include <cassert>
#include "GameState.h"
#include "../core/menu/Menu.h"
#include "../core/scene/LoadingScene.h"
#include "../core/scene/SelectScene.h"
#include "../core/scene/BattleScene.h"

/*******************************************************************************
 * @class Game
 * @brief Represents the main game controller managing game state and scenes.
 * 
 * The Game class represents the main controller of the game, responsible for
 * managing the game state and scenes such as the main menu, character selection,
 * battle scene, and loading scene.
 ******************************************************************************/
class Game {
private:
    GameState m_gameState;
    BattleScene m_battleScene;
    Menu m_menu;
    SelectScene m_select;
    LoadingScene m_loadingScene;
    std::vector<std::string> m_fighterNames;

public:
    /***************************************************************************
     * @brief Default constructor for the Game class.
     * 
     * Initializes member variables to default values.
     **************************************************************************/
    Game();

    /***************************************************************************
     * @brief Constructor for the Game class with an initial game state.
     * 
     * Initializes member variables to default values with an initial game
     * state.
     * 
     * @param initialState The initial state of the game.
     **************************************************************************/
    Game(GameState initialState);

    /***************************************************************************
     * @brief Destructor for the Game class.
     * 
     * Cleans up any resources allocated by the Game.
     **************************************************************************/
    ~Game();

    /***************************************************************************
     * @brief Updates the game based on the elapsed time and input.
     * 
     * This method updates the game state based on the elapsed time and player 
     * input. It delegates the update to the appropriate scene based on the 
     * current game state.
     * 
     * @param deltaTime The time elapsed since the last update.
     * @param keycodeF1 The keycode for player 1.
     * @param keycodeF2 The keycode for player 2.
     **************************************************************************/
    void update(float deltaTime, std::string keycodeF1, std::string keycodeF2, int keycodeMenu);

    /***************************************************************************
     * @brief Changes the game state to a new state.
     * 
     * This method changes the game state to the specified new state.
     * It also initializes scenes as needed when transitioning to certain 
     * states.
     * 
     * @param newState The new state of the game.
     **************************************************************************/
    void changeState(GameState newState);

    /***************************************************************************
     * @brief Gets the current game state.
     * 
     * This method returns the current game state.
     * 
     * @return The current game state.
     **************************************************************************/
    const GameState& getCurrentGameState() const;

    /***************************************************************************
     * @brief Gets the battle scene.
     * 
     * This method returns a reference to the battle scene object.
     * 
     * @return Reference to the battle scene.
     **************************************************************************/
    BattleScene& getBattleScene();

    /***************************************************************************
     * @brief Gets the menu.
     * 
     * This method returns a reference to the menu object.
     * 
     * @return Reference to the menu.
     **************************************************************************/
    Menu& getMenu();

    /***************************************************************************
     * @brief Gets the fighter selection scene.
     * 
     * This method returns a reference to the select scene object.
     * 
     * @return Reference to the fighter selection scene.
     **************************************************************************/
    SelectScene& getSelectScene();

    /***************************************************************************
     * @brief Gets the loading scene.
     * 
     * This method returns a reference to the loading scene object.
     * 
     * @return Reference to the loading scene.
     **************************************************************************/
    LoadingScene& getLoadingScene();

    /***************************************************************************
     * @brief Sets the names of fighters participating in the battle.
     * 
     * This method sets the names of the fighters participating in the battle.
     * 
     * @param fighterName1 The name of fighter 1.
     * @param fighterName2 The name of fighter 2.
     **************************************************************************/
    void setFighterNames(std::string fighterName1, std::string fighterName2);

    /***************************************************************************
     * @brief Performs regression testing for the Game class.
     * 
     * This method performs regression testing for the Game class to ensure
     * its functionality is consistent across different versions.
     **************************************************************************/
    static void regressionTest();
};

#endif