/*******************************************************************************
 * @file GameState.h
 * @brief Defines the GameState enum for representing different states 
 *        of the game.
 ******************************************************************************/
#ifndef _GAME_STATE_H
#define _GAME_STATE_H

/*******************************************************************************
 * @enum GameState
 * @brief Represents the possible states of the game.
 * 
 * The GameState enum represents the different states that the game can be in.
 * These states include loading scene, main menu, character selection, battle
 * scene, and exiting the game.
 ******************************************************************************/
enum class GameState {
    LoadingScene, /**< Loading scene state. */
    MainMenu, /**< Main menu state. */
    CharacterSelection, /**< Character selection state. */
    BattleScene, /**< Battle scene state. */
    ExitGame /**< Exit game state. */
};
#endif // !_GAME_STATE_H