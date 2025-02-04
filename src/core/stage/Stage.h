/*******************************************************************************
 * @file Stage.h
 * 
 * @brief Defines the Stage class for managing background elements.
 ******************************************************************************/

#ifndef _STAGE_H
#define _STAGE_H

#include <iostream>
#include <cassert>

/**
 * @class Stage
 * 
 * @brief Manages background elements of the stage.
 * 
 * The Stage class handles background elements such as the background
 * image and foreground image of the stage.
 */
class Stage
{
private:
    const char* m_stagePathBack;  /**< The file path for the background image of 
				 					 the stage. */
    const char* m_stagePathFront; /**< The file path for the foreground image of 
				 					 the stage. */

public:
    /***************************************************************************
     * @brief Default constructor for the Stage class.
     * 
     * Initializes member variables to default values.
     **************************************************************************/
    Stage();

    /***************************************************************************
     * @brief Destructor for the Stage class.
     * 
     * Cleans up any resources allocated by the Hud.
     **************************************************************************/
    ~Stage();

    /***************************************************************************
     * @brief Updates the stage elements.
	 * 
	 * This method updates the stage elements based on the elapsed time.
     * 
     * @param deltaTime The time elapsed since the last update.
     **************************************************************************/
    void update(float deltaTime);

    /***************************************************************************
     * @brief Gets the file path for the foreground image of the stage.
     * 
     * This method returns the file path for the foreground image
     * of the stage.
	 * 
     * @return The file path for the foreground image of the stage.
     **************************************************************************/
    const char* getStageFrontPath() const;

    /***************************************************************************
     * @brief Gets the file path for the background image of the stage.
     * 
     * This method returns the file path for the background image
     * of the stage.
	 * 
     * @return The file path for the background image of the stage.
     **************************************************************************/
    const char* getStageBackPath() const;

    /***************************************************************************
     * @brief Performs regression testing for the Stage class.
     * 
     * This method performs regression testing for the Stage class to ensure
     * its functionality is consistent across different versions.
     **************************************************************************/
    static void regressionTest();
};

#endif // !_STAGE_H
