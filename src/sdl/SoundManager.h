/*******************************************************************************
 * @file SoundManager.h
 * @brief Defines the SoundManager class for managing audio in the game.
 ******************************************************************************/

#ifndef _SOUND_MANAGER_H
#define _SOUND_MANAGER_H

#include <iostream>
#include <cassert>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/*******************************************************************************
 * @class SoundManager
 * @brief Manages audio playback in the game.
 *
 * The SoundManager class provides functionality to manage audio playback in 
 * the game. It handles loading and playing music and sound effects, as well 
 * as controlling volume levels and performing fade-in and fade-out effects.
 ******************************************************************************/
class SoundManager {
private:
    std::vector<Mix_Music*> m_loadedMusic;
    bool m_initialized; /**< Flag indicating whether the SoundManager 
                             is initialized. */
                             
public:
    /***************************************************************************
     * @brief Default constructor for the SoundManager class.
     * 
     * Initializes member variables to default values.
     **************************************************************************/
    SoundManager();

    /***************************************************************************
     * @brief Destructor for the SoundManager class.
     * 
     * Cleans up any resources allocated by the SoundManager.
     **************************************************************************/
    ~SoundManager();

    /***************************************************************************
     * @brief Initializes SDL_mixer and audio settings.
     * 
     * Attempts to initialize SDL_mixer with the default audio settings.
     * 
     * @return True if initialization succeeds, false otherwise.
     **************************************************************************/
    bool initialize();

    /***************************************************************************
     * @brief Closes the SoundManager and frees resources.
     * 
     * Closes SDL_mixer and releases any resources acquired during 
     * initialization.
     **************************************************************************/
    void close();

    /***************************************************************************
     * @brief Loads music from a file.
     * 
     * Loads music from the specified file path.
     * 
     * @param filePath The path to the music file.
     * @return A pointer to the loaded music.
     **************************************************************************/
    Mix_Music* loadMusic(const char* filePath);

    /***************************************************************************
     * @brief Plays music from a file.
     * 
     * Loads and plays music from the specified file path.
     * 
     * @param filePath The path to the music file.
     * @param loops The number of times to loop the music 
     *              (-1 for infinite loop).
     **************************************************************************/
    void playMusic(const char* filePath, int loops = -1);

    /***************************************************************************
     * @brief Plays a sound effect from a file.
     * 
     * Loads and plays a sound effect from the specified file path.
     * 
     * @param filePath The path to the sound effect file.
     **************************************************************************/
    void playSound(const char* filePath);

    /***************************************************************************
     * @brief Fades in music from a file.
     * 
     * Loads and fades in music from the specified file path.
     * 
     * @param filePath The path to the music file.
     * @param loops The number of times to loop the music 
     *              (-1 for infinite loop).
     * @param fadeTime The duration of the fade-in effect in milliseconds.
     **************************************************************************/
    void fadeInMusic(const char* filePath, int loops, int fadeTime);

    /***************************************************************************
     * @brief Fades out the currently playing music.
     * 
     * Fades out the currently playing music over the specified duration.
     * 
     * @param fadeTime The duration of the fade-out effect in milliseconds.
     **************************************************************************/
    void fadeOutMusic(int fadeTime);

    /***************************************************************************
     * @brief Sets the volume of the sound manager.
     * 
     * Sets the volume level for all channels.
     * 
     * @param volume The volume level (0-128).
     **************************************************************************/
    void setVolume(int volume);

    /***************************************************************************
     * @brief Performs regression testing for the SoundManager class.
     * 
     * This method performs regression testing for the SoundManager class to 
     * ensure its functionality is consistent across different versions.
     **************************************************************************/
    static void regressionTest();
};

#endif // _SOUND_MANAGER_H
