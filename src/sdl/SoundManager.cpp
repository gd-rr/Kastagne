#include "SoundManager.h"

// Default values for audio settings
const int DEFAULT_FREQUENCY = 44100;
const Uint16 DEFAULT_FORMAT = MIX_DEFAULT_FORMAT;
const int DEFAULT_CHANNELS = 2; // Mono: 1, Stereo: 2.
const int DEFAULT_CHUNKSIZE = 2048;

// Constructor
SoundManager::SoundManager() : m_initialized(false) {}

// Destructor
SoundManager::~SoundManager() {
    close(); // Ensure proper cleanup upon destruction
}

// Initialize SDL_mixer and audio settings
bool SoundManager::initialize() {
    // Attempt to initialize SDL_mixer
    if (Mix_OpenAudio(DEFAULT_FREQUENCY, 
                      DEFAULT_FORMAT, 
                      DEFAULT_CHANNELS, 
                      DEFAULT_CHUNKSIZE) < 0) {
        // Print error message if initialization fails
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " 
            << Mix_GetError() << std::endl;
        return false;
    }

    // Mark SoundManager as initialized
    m_initialized = true;
    return true;
}

// Close SDL_mixer and release resources
void SoundManager::close() {
    // Libérer toutes les instances de musique chargées
    for (Mix_Music* music : m_loadedMusic) {
        Mix_FreeMusic(music);
    }
    m_loadedMusic.clear(); // Vider le vecteur

    // Si SoundManager est initialisé, fermez SDL_mixer
    if (m_initialized) {
        Mix_CloseAudio();
        m_initialized = false;
    }
}

// Load music from file
Mix_Music* SoundManager::loadMusic(const char* filePath) {
    // Check if SoundManager is initialized
    if (!m_initialized) {
        std::cerr << "SoundManager not initialized!" << std::endl;
        return nullptr;
    }

    // Load music file
    Mix_Music* music = Mix_LoadMUS(filePath);
    if (music == nullptr) {
        // Print error message if loading fails
        std::cerr << "Failed to load music! SDL_mixer Error: " 
            << Mix_GetError() << std::endl;
    } else {
        // Ajouter la musique chargée au vecteur
        m_loadedMusic.push_back(music);
    }

    return music;
}

// Play music
void SoundManager::playMusic(const char* filePath, int loops) {
    // Load music from file
    Mix_Music* music = loadMusic(filePath);
    if (music != nullptr) {
        // Play the loaded music
        Mix_PlayMusic(music, loops);
    }
}

// Fade in music
void SoundManager::fadeInMusic(const char* filePath, int loops, int fadeTime) {
    // Load music from file
    Mix_Music* music = loadMusic(filePath);
    if (music != nullptr) {
        // Fade in and play the loaded music
        Mix_FadeInMusic(music, loops, fadeTime);
    }
}

// Play sound effect
void SoundManager::playSound(const char* filePath) {
    // Check if SoundManager is initialized
    if (!m_initialized) {
        std::cerr << "SoundManager not initialized!" << std::endl;
        return;
    }

    // Load sound effect from file
    Mix_Chunk* sound = Mix_LoadWAV(filePath);
    if (sound == nullptr) {
        // Print error message if loading fails
        std::cerr << "Failed to load sound effect! SDL_mixer Error: " 
            << Mix_GetError() << std::endl;
        return;
    }

    // Play the loaded sound effect
    Mix_PlayChannel(-1, sound, 0);
}

// Fade out music
void SoundManager::fadeOutMusic(int fadeTime) {
    // Check if SoundManager is initialized
    if (!m_initialized) {
        std::cerr << "SoundManager not initialized!" << std::endl;
        return;
    }

    // Fade out the currently playing music
    Mix_FadeOutMusic(fadeTime);
}

// Set volume level
void SoundManager::setVolume(int volume) { // Value between 0 and 128
    // Set volume for all channels
    Mix_Volume(-1, volume);
}

// Test for the SoundManager class
void SoundManager::regressionTest() {
    // Create an instance of the SoundManager class
    SoundManager soundManager;

    // Test 1: Initialize SDL_mixer
    assert(soundManager.initialize() == true);

    // Test 2: Load and play music
    soundManager.playMusic("data/music/introTheme.ogg", 0); // Play once

    // Test 4: Fade in music
    soundManager.fadeInMusic("data/music/introTheme.ogg", 0, 1000); // Fade in over 1 second

    // Test 5: Set volume level
    soundManager.setVolume(100); // Set volume to 100 (half of maximum)

    // Test 6: Fade out music
    soundManager.fadeOutMusic(1000); // Fade out over 1 second

    // Test 7: Close SDL_mixer
    soundManager.close();
}
