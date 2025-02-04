/*******************************************************************************
 * @file Hud.h
 * @brief Defines the Hud class for managing heads-up display elements.
 ******************************************************************************/
#ifndef _HUD_H
#define _HUD_H

#include <iostream>
#include <cassert>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <stdexcept> 
#include "../../utils/Vector2D.h"

/*******************************************************************************
 * @struct Rectangle
 * @brief Represents a rectangular region with position, size, and sprite 
 *        frame time.
 ******************************************************************************/
struct Rectangle {
    int posx; /**< The x-coordinate of the rectangle's position. */
    int posy; /**< The y-coordinate of the rectangle's position. */
    int width; /**< The width of the rectangle. */
    int height; /**< The height of the rectangle. */
    u_int64_t spriteFrameTime; /**< The sprite frame time of the rectangle. */
};

/*******************************************************************************
 * @class Hud
 * @brief Represents a heads-up display (HUD) for displaying game information.
 * 
 * The HUD class manages various elements of the heads-up display, including
 * health bars, timers, and sprites for displaying game information to the
 * players.
 ******************************************************************************/
class Hud
{
private:
    const char* m_overlayAltasPath;
    std::vector<int> m_playerHealth;
    std::unique_ptr<std::map<std::string, Rectangle>> m_spritesSheet;
    std::string m_timerFrame;
    int m_currentFrameLeft;
    int m_currentFrameRight;
    int m_maxFrame;
    mutable const Rectangle* m_currentTimerRectLeft;
    mutable const Rectangle* m_currentTimerRectRight;
    mutable const Rectangle* m_currentSpriteRect;
    u_int64_t m_frameTime;
    Vector2D m_position;

public:
    /***************************************************************************
     * @brief Default constructor for the Hud class.
     * 
     * Initializes member variables to default values.
     **************************************************************************/
    Hud();

    /***************************************************************************
     * @brief Destructor for the Hud class.
     * 
     * Cleans up any resources allocated by the Hud.
     **************************************************************************/
    ~Hud();

    /***************************************************************************
     * @brief Initializes the HUD elements.
     **************************************************************************/
    void init();

    /***************************************************************************
     * @brief Updates the timer display.
     * 
     * This method updates the timer animation based on the elapsed time since 
     * the last frame. It searches for the sprite information in the sprite 
     * sheet map, updates the frame time, and adjusts the current timer frame 
     * accordingly.
     * 
     * @param deltaTime The time elapsed since the last update.
     **************************************************************************/
    void updateTimer(float deltaTime);

    /***************************************************************************
     * @brief Updates the health bar for a player.
     * 
     * This method updates the health bar display for the specified player with 
     * the current health value.
     * 
     * @param playerIndex The index of the player.
     * @param currentHealth The current health of the player.
     **************************************************************************/
    void updateHealthBar(int playerIndex, int currentHealth);

    /***************************************************************************
     * @brief Gets the position of the HUD.
     * 
     * This method returns the position of the HUD on the screen.
     * 
     * @return The position of the HUD.
     **************************************************************************/
    const Vector2D& getPosition() const;

    /***************************************************************************
     * @brief Sets the health of a player.
     * 
     * This method sets the current health value of the specified player.
     * 
     * @param playerIndex The index of the player.
     * @param currentHealth The current health of the player.
     **************************************************************************/
    void setPlayerHealth(int playerIndex, int currentHealth);

    /***************************************************************************
     * @brief Gets the health of a player.
     * 
     * This method returns the current health value of the specified player.
     * 
     * @param playerIndex The index of the player (0 for player 1, 
     *        1 for player 2).
     * @return The current health of the player.
     **************************************************************************/
    const int& getPlayerHealth(int playerIndex) const;

    /***************************************************************************
     * @brief Gets the rectangle for the timer display.
     * 
     * This method returns the corresponding Recangle of a timer sprite.
     * 
     * @param index The index of the timer rectangle (0 left, 1 right).
     * @return The rectangle for the timer display.
     **************************************************************************/
    const Rectangle& getTimerRect(int index) const;

    /***************************************************************************
     * @brief Gets the rectangle for a sprite.
     * 
     * This method returns the corresponding Rectangle of a key passed in 
     * parameter.
     * 
     * @param k The key of the sprite.
     * @return The rectangle for the sprite.
     **************************************************************************/
    const Rectangle& getSpriteRect(std::string k) const;

    /***************************************************************************
     * @brief Gets the path to the overlay atlas.
     * 
     * This method retrieves the file path to the overlay atlas image used 
     * by the heads-up display (HUD) for rendering various graphical elements.
     * 
     * @return The path to the overlay atlas.
     **************************************************************************/
    const char* getOverlayAtlasPath() const;

    /***************************************************************************
     * @brief Performs regression testing for the Hud class.
     * 
     * This method performs regression testing for the Hud class to ensure
     * its functionality is consistent across different versions.
     **************************************************************************/
    static void regressionTest();
};

#endif // !_HUD_H