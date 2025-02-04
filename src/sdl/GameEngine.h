/*******************************************************************************
 * @file GameEngine.h
 * @brief Defines the GameEngine class for managing the game engine.
 ******************************************************************************/

#ifndef _GAME_ENGINE_H
#define _GAME_ENGINE_H

#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "SoundManager.h"
#include "../game/Game.h"
#include "../../lib/nlohmann/json.hpp"

/*******************************************************************************
 * @class GameEngine
 * @brief Manages the game engine.
 ******************************************************************************/
class GameEngine {
private:
    // SDL window and renderer
    SDL_Window*   m_window; /**< SDL window instance. */
    SDL_Renderer* m_renderer; /**< SDL renderer instance. */

    // Font
    TTF_Font* m_font; /**< Font used in the game engine. */

    // Flags
    bool m_isRunning; /**< Flag indicating if the game engine is running. */
    bool m_quit; /**< Flag indicating if the game engine should quit. */
    bool m_fullscreen; /**< Flag indicating if the game is in fullscreen mode. */
    bool m_inBattleScene; /**< Flag indicating if the game is in the battle scene. */

    // Event Manager
     bool quit; /**< Flag indicating if the game should quit. */
    std::string m_animationF1; /**< Animation for player 1. */
    std::string m_animationF2; /**< Animation for player 2. */
    std::map<unsigned int, std::string> m_keycodeSDL; /**< Map of SDL keycodes. */
    std::map<std::string, std::map<std::string, std::string>> m_keybinds; /**< Map of keybinds. */

    //Menu
    int m_keycodeMenu; /**< Keycode for menu interaction. */

    // Game objects
    Game m_game; /**< Game instance. */
    SoundManager m_soundManager; /**< Sound manager instance. */

    // Window properties
    int m_windowWidth; /**< Width of the window. */
    int m_windowHeight; /**< Height of the window. */
    int m_scaleFactor; /**< Scale factor of the window. */

    // Stage properties
    int m_stageFloor; /**< Floor of the stage. */

    // Player initialization
    std::vector<int> m_playerInitPosition; /**< Initial position of the player. */

    // Screen edges
    int m_screenLeftEdge; /**< Left edge of the screen. */
    int m_screenRightEdge; /**< Right edge of the screen. */

    const char* m_filePathMenu; /**< File path for the menu. */

public : 
    /***************************************************************************
     * @brief Default constructor for the GameEngine class.
     **************************************************************************/
    GameEngine();

    /***************************************************************************
     * @brief Destructor for the GameEngine class.
     **************************************************************************/
    ~GameEngine();

    /***************************************************************************
     * @brief Initializes the game engine.
     * @param title The title of the window.
     * @param xpos The x-coordinate of the window.
     * @param ypos The y-coordinate of the window.
     * @param width The width of the window.
     * @param height The height of the window.
     * @param fullscreen Flag indicating if the window is fullscreen.
     * @return True if initialization is successful, false otherwise.
     **************************************************************************/
    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    /***************************************************************************
     * @brief Cleans up the game engine.
     **************************************************************************/
    void cleanEngine();

    /***************************************************************************
     * @brief Handles events in the game loop.
     **************************************************************************/
    void handleEvents();

    /***************************************************************************
     * @brief Runs the game loop.
     **************************************************************************/
    void run();

    /***************************************************************************
     * @brief Runs the battle scene.
     **************************************************************************/
    void runBattleScene();

    /***************************************************************************
     * @brief Updates the game.
     * @param deltaTime The time elapsed since the last update.
     * @param m_keycodeF1 The keycode for player 1.
     * @param m_keycodeF2 The keycode for player 2.
     * @param m_keycodeMenu The keycode for menu interaction.
     **************************************************************************/
    void update(float deltaTime, std::string m_keycodeF1, std::string m_keycodeF2, int m_keycodeMenu);

    /***************************************************************************
     * @brief Runs the menu scene.
     **************************************************************************/
    void runMenu();

    /***************************************************************************
     * @brief Displays the menu.
     * @param items Vector of menu items.
     * @param index Index of the selected item.
     * @param filePath File path for the menu.
     **************************************************************************/
    void displayMenu(std::vector<std::string> items, int index, const char* filePath);

    /***************************************************************************
     * @brief Runs the fighter selection scene.
     **************************************************************************/
    void runSelectScene();

    /***************************************************************************
     * @brief Runs the loading scene.
     **************************************************************************/
    void runLoadingScene();

    /***************************************************************************
     * @brief Loads a font for rendering.
     * @param file Path to the font file.
     * @param size Size of the font.
     **************************************************************************/
    void loadFont(const char* file, int size);

    /***************************************************************************
     * @brief Renders black stripes.
     **************************************************************************/
    void renderBlackStripes();

    /***************************************************************************
     * @brief Renders the camera zone.
     * @param camera The camera object.
     **************************************************************************/
    void renderCameraZone(const Camera& camera);

    /***************************************************************************
     * @brief Loads a texture from a file path.
     * @param filePath The file path of the texture.
     * @return Pointer to the loaded texture.
     **************************************************************************/
    SDL_Texture* loadTexture(const char* filePath);

    
    /***************************************************************************
     * @brief Renders a copy of a texture to the rendering target.
     * @param texture The texture to render.
     * @param srcrect The source rectangle defining the portion of the texture to render.
     * @param dstrect The destination rectangle defining the position and size of the rendering on the target.
     * @param reverse Flag indicating whether to render the texture in reverse (flipped).
     * @return Returns 0 on success, or a negative error code on failure.
     **************************************************************************/
    int renderCopy(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect, bool reverse) const;


    //rendering functions
    /***************************************************************************
     * @brief Renders a texture with optional flipping.
     * @param texture The texture to render.
     * @param x The x-coordinate of the rendering position.
     * @param y The y-coordinate of the rendering position.
     * @param posX The x-coordinate of the position on the texture.
     * @param posY The y-coordinate of the position on the texture.
     * @param width The width of the rendered texture.
     * @param height The height of the rendered texture.
     * @param reverse Flag indicating if the texture should be flipped.
     **************************************************************************/
    void renderTexture(SDL_Texture* texture, int x, int y, int posX, int posY, int width, int height, bool reverse = false);

    /***************************************************************************
     * @brief Renders a texture for the selection scene.
     * @param texture The texture to render.
     * @param x The x-coordinate of the rendering position.
     * @param y The y-coordinate of the rendering position.
     * @param posX The x-coordinate of the position on the texture.
     * @param posY The y-coordinate of the position on the texture.
     * @param width The width of the rendered texture.
     * @param height The height of the rendered texture.
     * @param reverse Flag indicating if the texture should be flipped.
     **************************************************************************/
    void renderTextureSelectScene(SDL_Texture* texture, int x, int y, int posX, int posY, int width, int height, bool reverse = false);

    /***************************************************************************
     * @brief Renders a fighter icone texture for the selection scene.
     * @param texture The texture to render.
     * @param x The x-coordinate of the rendering position.
     * @param y The y-coordinate of the rendering position.
     * @param posX The x-coordinate of the position on the texture.
     * @param posY The y-coordinate of the position on the texture.
     * @param width The width of the rendered texture.
     * @param height The height of the rendered texture.
     * @param reverse Flag indicating if the texture should be flipped.
     **************************************************************************/
    void renderTextureSelectSceneMini(SDL_Texture* texture, int x, int y, int posX, int posY, int width, int height, bool reverse = false);

    /***************************************************************************
     * @brief Renders a fighter texture for the selection scene.
     * @param texture The texture to render.
     * @param x The x-coordinate of the rendering position.
     * @param y The y-coordinate of the rendering position.
     * @param posX The x-coordinate of the position on the texture.
     * @param posY The y-coordinate of the position on the texture.
     * @param width The width of the rendered texture.
     * @param height The height of the rendered texture.
     * @param reverse Flag indicating if the texture should be flipped.
     **************************************************************************/
    void renderTextureSelectSceneFighter(SDL_Texture* texture, int x, int y, int posX, int posY, int width, int height, bool reverse = false);

    /***************************************************************************
     * @brief Renders for the selection's box for the selection scene.
     * @param select The selection scene object.
     * @param texture The texture to render.
     * @param x The x-coordinate of the rendering position.
     * @param y The y-coordinate of the rendering position.
     * @param reverse Flag indicating if the texture should be flipped.
     **************************************************************************/
    void renderSelectSceneBox(const SelectScene& select,  SDL_Texture* texture,int x, int y, bool reverse);

    /***************************************************************************
     * @brief Renders a stage texture.
     * @param texture The texture to render.
     * @param x The x-coordinate of the rendering position.
     * @param y The y-coordinate of the rendering position.
     **************************************************************************/
    void renderStageTexture(SDL_Texture* texture, int x, int y);

    /***************************************************************************
     * @brief Renders the stage.
     * @param camera The camera object.
     * @param texture The texture to render.
     **************************************************************************/
    void renderStage(const Camera& camera, SDL_Texture* texture);

    /***************************************************************************
     * @brief Renders a fighter.
     * @param fighter The fighter object to render.
     * @param camera The camera object.
     * @param texture The texture to render.
     * @param reverse Flag indicating if the fighter should be flipped.
     **************************************************************************/
    void renderFighter(const Fighter& fighter, const Camera& camera, SDL_Texture* texture, bool reverse);

    /***************************************************************************
     * @brief Renders the hitbox of a fighter.
     * @param fighter The fighter object.
     * @param camera The camera object.
     **************************************************************************/
    void renderFighterHitbox(const Fighter& fighter, const Camera& camera);

    /***************************************************************************
     * @brief Renders player information.
     * @param texture The texture to render.
     * @param player The player whose information to render.
     * @param iconRect The rectangle for the icon.
     * @param nameRect The rectangle for the name.
     * @param iconX The x-coordinate of the icon.
     * @param iconY The y-coordinate of the icon.
     * @param nameX The x-coordinate of the name.
     * @param nameY The y-coordinate of the name.
     * @param iconWidth The width of the icon.
     * @param iconHeight The height of the icon.
     * @param reverse Flag indicating if the rendering should be reversed.
     **************************************************************************/
    void renderPlayerInfo(SDL_Texture* texture, const Fighter& player, const Rectangle& iconRect, const Rectangle& nameRect, int iconX, int iconY, int nameX, int nameY, int iconWidth, int iconHeight, bool reverse);

    /***************************************************************************
     * @brief Renders the health bar.
     * @param hud The HUD object.
     * @param texture The texture to render.
     * @param currentHealth1 The current health of player 1.
     * @param currentHealth2 The current health of player 2.
     **************************************************************************/
    void renderHealthBar(const Hud& hud, SDL_Texture* texture, int currentHealth1, int currentHealth2);

    /***************************************************************************
     * @brief Renders a health bar segment.
     * @param texture The texture to render.
     * @param rect The rectangle representing the segment.
     * @param x The x-coordinate of the segment.
     * @param y The y-coordinate of the segment.
     * @param width The width of the segment.
     * @param height The height of the segment.
     **************************************************************************/
    void renderHealthBarSegment(SDL_Texture* texture, const Rectangle& rect, int x, int y, int width, int height);

    /***************************************************************************
     * @brief Renders a texture without scaling.
     * @param texture The texture to render.
     * @param screenx The x-coordinate of the screen.
     * @param screeny The y-coordinate of the screen.
     * @param screenwidth The width of the screen.
     * @param screenheight The height of the screen.
     * @param posX The x-coordinate of the position on the texture.
     * @param posY The y-coordinate of the position on the texture.
     * @param width The width of the texture.
     * @param height The height of the texture.
     * @param reverse Flag indicating if the rendering should be reversed.
     **************************************************************************/
    void renderScalelessTexture(SDL_Texture* texture, int screenx, int screeny, int screenwidth, int screenheight, int posX, int posY, int width, int height, bool reverse);

    /***************************************************************************
     * @brief Renders an overlay.
     * @param hud The HUD object.
     * @param player1 The first player.
     * @param player2 The second player.
     * @param texture The texture to render.
     **************************************************************************/
    void renderOverlay(const Hud& hud, const Fighter& player1, const Fighter& player2, SDL_Texture* texture);

    /***************************************************************************
     * @brief Renders a timer.
     * @param rctLeft The rectangle for the left timer.
     * @param rctRight The rectangle for the right timer.
     * @param texture The texture to render.
     **************************************************************************/
    void renderTimer(const Rectangle& rctLeft, const Rectangle& rctRight, SDL_Texture* texture);

    /***************************************************************************
     * @brief Renders a general overlay.
     * @param hud The HUD object.
     * @param player1 The first player.
     * @param player2 The second player.
     * @param texture The texture to render.
     **************************************************************************/
    void renderGeneralOverlay(const Hud& hud, const Fighter& player1, const Fighter& player2, SDL_Texture* texture);

    /***************************************************************************
     * @brief Gets the quit status.
     * @return The quit status.
     **************************************************************************/
    bool getQuitStatus() const;

    /***************************************************************************
     * @brief Gets the width of a texture.
     * @param texture The texture.
     * @return The width of the texture.
     **************************************************************************/
    int getTextureWidth(SDL_Texture* texture);

    /***************************************************************************
     * @brief Gets the height of a texture.
     * @param texture The texture.
     * @return The height of the texture.
     **************************************************************************/
    int getTextureHeight(SDL_Texture* texture);

    /***************************************************************************
     * @brief Sets the window size.
     * @param width The width of the window.
     * @param height The height of the window.
     **************************************************************************/
    void setWindowSize(int width, int height);

    /***************************************************************************
     * @brief Sets the fullscreen mode.
     * @param fullscreen A flag indicating whether to enable fullscreen mode.
     **************************************************************************/
    void setFullscreen(bool fullscreen);

    /***************************************************************************
     * @brief Sets the boolean value for player 1.
     * @param b The boolean value to set.
     **************************************************************************/
    void setBoolP1(bool b);

    /***************************************************************************
     * @brief Checks if an event should trigger quitting.
     * @param event The SDL event.
     * @return True if the event should trigger quitting, false otherwise.
     **************************************************************************/
    bool shouldQuit(SDL_Event& event);

    /***************************************************************************
     * @brief Returns the action associated with a touch event.
     * @param event The SDL event.
     * @param name The name associated with the touch event.
     * @param action The action associated with the touch event.
     * @return The action associated with the touch event.
     **************************************************************************/
    std::string returnTouchAction(SDL_Event& event, const std::string& name, const std::string& action);

    /***************************************************************************
     * @brief Checks if a key is released.
     * @param event The SDL event.
     * @param key The SDL keycode.
     * @return True if the key is released, false otherwise.
     **************************************************************************/
    bool isKeyUp(SDL_Event& event, SDL_Keycode key);

    /***************************************************************************
     * @brief Checks if a key is pressed down.
     * @param event The SDL event.
     * @param key The SDL keycode.
     * @return True if the key is pressed down, false otherwise.
     **************************************************************************/
    bool isKeyDown(SDL_Event& event, SDL_Keycode key);

    /***************************************************************************
     * @brief Returns the SDL keycode associated with an action.
     * @param action The action.
     * @return The SDL keycode associated with the action.
     **************************************************************************/
    SDL_Keycode returnValueSDL(const std::string& action);
    
    
    
    /***************************************************************************
     * @brief Loads SDL keycodes from a file.
     * @param filename The name of the file to load.
     * @return True if the SDL keycodes are loaded successfully, false otherwise.
     **************************************************************************/
    bool loadKeycodeSDL(const std::string& filename);

    /***************************************************************************
     * @brief Loads keybinds from a file.
     * @param filename The name of the file to load.
     * @return True if the keybinds are loaded successfully, false otherwise.
     **************************************************************************/
    bool loadKeybinds(const std::string& filename);
    
    /***************************************************************************
     * @brief Handles keybinds for a player.
     * @param playerName The name of the player.
     * @param event The SDL event.
     **************************************************************************/
    void handleKeybinds(const std::string& playerName, SDL_Event& event);
    
    /***************************************************************************
     * @brief Sets the animation for a player.
     * @param playerName The name of the player.
     * @param keycode The keycode associated with the animation.
     **************************************************************************/
    void setAnimation(const std::string& playerName, const std::string& keycode);
    
    /***************************************************************************
     * @brief Resets the animation for a player.
     * @param playerName The name of the player.
     * @param keycode The keycode associated with the animation.
     **************************************************************************/
    void resetAnimation(const std::string& playerName, const std::string& keycode);
    
    /***************************************************************************
     * @brief Sets a keybind for a player.
     * @param playerName The name of the player.
     * @param action The action to bind.
     * @param newKey The new SDL keycode to bind to the action.
     **************************************************************************/
    void setKeybind(const std::string& playerName, const std::string& action, SDL_Keycode newKey);
    
    /***************************************************************************
     * @brief Writes keybinds to a file.
     **************************************************************************/
    void writeKeybindsToFile();

    /***************************************************************************
     * @brief Performs regression testing for the GameEngine class.
     **************************************************************************/
    static void regressionTest();
};

#endif