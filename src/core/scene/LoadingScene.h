/*******************************************************************************
 * @file LoadingScene.h
 * @brief Defines the LoadingScene class for managing loading scenes.
 ******************************************************************************/

#ifndef _LOADINGSCENE_H
#define _LOADINGSCENE_H

#include <iostream>
#include <cassert>

/*******************************************************************************
 * @class LoadingScene
 * @brief Manages loading scenes.
 ******************************************************************************/
class LoadingScene {
private:
    const char* m_img1Path; /**< Path of image 1. */
    const char* m_img2Path; /**< Path of image 2. */
    const char* m_img3Path; /**< Path of image 3. */
    const char* m_img4Path; /**< Path of image 4. */
    const char* m_img5Path; /**< Path of image 5. */
    const char* m_img6Path; /**< Path of image 6. */
    const char* m_img7Path; /**< Path of image 7. */
    const char* m_img8Path; /**< Path of image 8. */
    bool m_quit; /**< Flag indicating if the loading scene should quit. */

public:
    /***************************************************************************
     * @brief Default constructor for the LoadingScene class.
     **************************************************************************/
    LoadingScene();

    /***************************************************************************
     * @brief Destructor for the LoadingScene class.
     **************************************************************************/
    ~LoadingScene();

    // Update
    /***************************************************************************
     * @brief Updates the loading scene.
     * @param keycode The keycode for input handling.
     **************************************************************************/
    void update(int keycode);

    // Getters
    /***************************************************************************
     * @brief Gets the path of image 1.
     * @return The path of image 1.
     **************************************************************************/
    const char* getImg1Path() const;
    
    /***************************************************************************
     * @brief Gets the path of image 2.
     * @return The path of image 2.
     **************************************************************************/
    const char* getImg2Path() const;
    
    /***************************************************************************
     * @brief Gets the path of image 3.
     * @return The path of image 3.
     **************************************************************************/
    const char* getImg3Path() const;
    
    /***************************************************************************
     * @brief Gets the path of image 4.
     * @return The path of image 4.
     **************************************************************************/
    const char* getImg4Path() const;
    
    /***************************************************************************
     * @brief Gets the path of image 5.
     * @return The path of image 5.
     **************************************************************************/
    const char* getImg5Path() const;
    
    /***************************************************************************
     * @brief Gets the path of image 6.
     * @return The path of image 6.
     **************************************************************************/
    const char* getImg6Path() const;
    
    /***************************************************************************
     * @brief Gets the path of image 7.
     * @return The path of image 7.
     **************************************************************************/
    const char* getImg7Path() const;
    
    /***************************************************************************
     * @brief Gets the path of image 8.
     * @return The path of image 8.
     **************************************************************************/
    const char* getImg8Path() const;
    
    /***************************************************************************
     * @brief Gets the quit flag.
     * @return The quit flag.
     **************************************************************************/
    const bool& getQuit() const;

    // Tests
    /***************************************************************************
     * @brief Performs regression testing for the LoadingScene class.
     **************************************************************************/
    static void regressionTest();

};

#endif
