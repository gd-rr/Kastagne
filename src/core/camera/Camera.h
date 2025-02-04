/*******************************************************************************
 * @file Camera.h
 * @brief Defines the Camera class, which represents the player’s evolution 
 * space
 ******************************************************************************/
#ifndef _CAMERA_H
#define _CAMERA_H

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include "../../utils/Vector2D.h" 

/*******************************************************************************
 * @class Camera
 * 
 * @brief Representing the players' playing space.
 * 
 * The Camera class handles the position of the camera within the game's world,
 * ensuring that the player's characters remain visible on the screen as they 
 * move through the game environment.
 ******************************************************************************/
class Camera
{
private:
    Vector2D m_position; /**< The position of the camera. */
    
    int m_screenWidth; /**< The width of the screen. */
    int m_screenHeight; /**< The height of the screen. */
    int m_stageLeftEdge; /**< The left edge of the stage. */
    int m_stageWidth; /**< The width of the stage. */
    int m_cameraZone; /**< The camera zone. */

    std::vector<int>    m_fighterPosition; /**< The positions of fighters. */
    std::vector<float>  m_fighterVelocity; /**< The velocities of fighters. */
    std::vector<int>    m_fighterDirection; /**< The directions of fighters. */

public:
    /***************************************************************************
     * @brief Default constructor for the Camera class.
     * 
     * Initializes member variables to default values.
     **************************************************************************/
    Camera();

    /***************************************************************************
     * @brief Destructor for the Camera class.
     * 
     * Cleans up any resources allocated by the Camera.
     **************************************************************************/
    ~Camera();

    /***************************************************************************
     * @brief Updates the camera position.
     * 
     * This method calculates the new position of the camera based on the 
     * positions and velocities of the fighters, ensuring that they remain 
     * visible on the screen.
     * 
     * @param deltaTime The time elapsed since the last update.
     **************************************************************************/
    void update(float deltaTime);

    /***************************************************************************
     * @brief Centers the camera on the stage.
     * 
     * This method centers the camera on the stage.
     * 
     * @param stageWidth The width of the stage.
     * @param stageHeight The height of the stage.
     **************************************************************************/
    void centerOnStage(int stageWidth, int stageHeight);

    /***************************************************************************
     * @brief Sets the position of the fighter at the specified index.
     * 
     * This method sets the position of the fighter at the specified index.
     * 
     * @param index The index of the fighter.
     * @param pos The position to set.
     **************************************************************************/
    void setFighterPosition(int index, int pos);
    /***************************************************************************
     * @brief Sets the velocity of the fighter at the specified index.
     * 
     * This method sets the velocity of the fighter at the specified index.
     * 
     * @param index The index of the fighter.
     * @param vel The velocity to set.
     **************************************************************************/
    void setFighterVelocity(int index, float vel);

    /***************************************************************************
     * @brief Sets the direction of the fighter at the specified index.
     * 
     * This method sets the direction of the fighter at the specified index.
     * 
     * @param index The index of the fighter.
     * @param dir The direction to set.
     **************************************************************************/
    void setFighterDirection(int index, int dir);

    /***************************************************************************
     * @brief Sets the screen dimensions.
     * 
     * This method sets the width and height of the screen.
     * 
     * @param width The width of the screen.
     * @param height The height of the screen.
     **************************************************************************/
    void setScreenDimension(int width, int height);

    /***************************************************************************
     * @brief Sets the position of the camera.
     * 
     * This method sets the position of the camera.
     * 
     * @param pos The position to set.
     **************************************************************************/
    void setPosition(const Vector2D& pos);

    /***************************************************************************
     * @brief Sets the left edge of the stage.
     * 
     * This method sets the left edge of the stage.
     * 
     * @param leftEdge The left edge to set.
     **************************************************************************/
    void setStageEdge(int leftEdge);

    /***************************************************************************
     * @brief Gets the position of the camera.
     * 
     * This method retrieves the current position of the camera.
     * 
     * @return The position of the camera.
     **************************************************************************/
    const Vector2D& getPosition() const;

    /***************************************************************************
     * @brief Gets the camera zone.
     * 
     * This method retrieves the camera zone.
     * 
     * @note This method is intended for use by the renderer.
     * @return The camera zone.
     **************************************************************************/
    const int getCameraZone() const;

    /***************************************************************************
     * @brief Performs regression testing for the Camera class.
     * 
     * This method performs regression testing for the Camera class to  ensure 
     * its functionality is consistent across different versions.
     **************************************************************************/
    static void regressionTest();
};

#endif // !_CAMERA_H
