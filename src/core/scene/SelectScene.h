/*******************************************************************************
 * @file SelectScene.h
 * @brief Defines the SelectScene class for managing the select scene.
 ******************************************************************************/

#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include <iostream>
#include "../../utils/Vector2D.h"
#include <map>
#include <memory>
#include <unordered_map>
#include <cassert>

struct Rect {
    Vector2D position; /**< Position of the rectangle. */
    int width, height; /**< Width and height of the rectangle. */
}; 

struct frameData {
    Rect atlasData; /**< Data of the atlas. */
    int atlasFrameTime; /**< Time for each frame in the atlas. */
};

/*******************************************************************************
 * @class SelectScene
 * @brief Manages the select scene.
 ******************************************************************************/
class SelectScene {
private:
    const char* m_atlas; /**< Path of the atlas. */
    const char* m_backGround; /**< Path of the background. */
    std::unordered_map<std::string, frameData> m_sceneElement; /**< Map of scene elements. */
    std::string m_currentAnimationName; /**< Current animation name. */
    int m_currentFrame; /**< Current frame in the animation. */
    mutable const frameData* m_currentFrameData; /**< Current frame data. */
    int m_frameTime; /**< Time for each frame. */
 
    bool m_p2; /**< Flag indicating if player 2 is selected. */
    bool m_dudley; /**< Flag indicating if Dudley is selected. */
    bool m_alex; /**< Flag indicating if Alex is selected. */
    bool m_p1Choose; /**< Flag indicating if player 1 has chosen. */
    bool m_p2Choose; /**< Flag indicating if player 2 has chosen. */
    bool m_quit; /**< Flag indicating if the select scene should quit. */

public:
    bool m_p1; /**< Flag indicating if player 1 is selected. */

    /***************************************************************************
     * @brief Default constructor for the SelectScene class.
     **************************************************************************/
    SelectScene();

    /***************************************************************************
     * @brief Destructor for the SelectScene class.
     **************************************************************************/
    ~SelectScene(); 

    // Initialize
    /***************************************************************************
     * @brief Initializes the select scene.
     **************************************************************************/
    void initialize();

    // Updates
    /***************************************************************************
     * @brief Updates the select scene.
     * @param deltaTime The time elapsed since the last update.
     **************************************************************************/
    void update(float deltaTime);
    
    /***************************************************************************
     * @brief Updates the select scene based on events.
     * @param keycode The keycode for input handling.
     **************************************************************************/
    void updateEvent(int keycode);

    // Getters
    /***************************************************************************
     * @brief Gets the path of the atlas.
     * @return The path of the atlas.
     **************************************************************************/
    const char* getAtlasPath();
    
    /***************************************************************************
     * @brief Gets the path of the background.
     * @return The path of the background.
     **************************************************************************/
    const char* getBackGroundPath();
    
    /***************************************************************************
     * @brief Gets the frame data.
     * @return The frame data.
     **************************************************************************/
    const frameData& getFrameData() const;
    
    /***************************************************************************
     * @brief Gets the current animation name.
     * @return The current animation name.
     **************************************************************************/
    const std::string& getCurrentAnimationName() const;
    
    /***************************************************************************
     * @brief Gets the Dudley flag.
     * @return The Dudley flag.
     **************************************************************************/
    const bool& getBoolDudley() const;
    
    /***************************************************************************
     * @brief Gets the Alex flag.
     * @return The Alex flag.
     **************************************************************************/
    const bool& getBoolAlex() const;
    
    /***************************************************************************
     * @brief Gets the player 1 flag.
     * @return The player 1 flag.
     **************************************************************************/
    const bool& getBoolP1() const;
    
    /***************************************************************************
     * @brief Gets the player 2 flag.
     * @return The player 2 flag.
     **************************************************************************/
    const bool& getBoolP2() const;
    
    /***************************************************************************
     * @brief Gets the player 1 choose flag.
     * @return The player 1 choose flag.
     **************************************************************************/
    const bool& getBoolP1Choose() const;
    
    /***************************************************************************
     * @brief Gets the player 2 choose flag.
     * @return The player 2 choose flag.
     **************************************************************************/
    const bool& getBoolP2Choose() const;
    
    /***************************************************************************
     * @brief Gets the quit select flag.
     * @return The quit select flag.
     **************************************************************************/
    const bool& getQuitSelect() const;

    /***************************************************************************
     * @brief Performs regression testing for the SelectScene class.
     **************************************************************************/
    static void regressionTest();

};

#endif