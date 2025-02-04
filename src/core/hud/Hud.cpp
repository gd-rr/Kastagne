#include "Hud.h"

// Constructor definition for the Hud class
Hud::Hud() : m_playerHealth(2) {
    init(); // Calls the init() method to initialize the object.
}

// Destructor definition for the Hud class
Hud::~Hud() {
    m_overlayAltasPath = nullptr;
}

// Method to initialize the member variables of the Hud class
void Hud::init() {
    // Setting the path for the overlay atlas image.
    m_overlayAltasPath = "data/images/overlay/overlay.png";

    // Initializing the animation data.
    m_timerFrame = "time-";
    m_currentFrameLeft  = 9;
    m_currentFrameRight = 9;
    m_maxFrame = 9;
    m_frameTime = 0;
    
    // Initializing the spritesSheet map with sprite information
    m_spritesSheet =
    std::make_unique<std::map<std::string, Rectangle>>(std::map<std::string, Rectangle>{
        // Entries for timer digits
        { "time-0", {291, 184, 17, 26, 664} }, // 0
        { "time-1", {223, 157, 17, 26, 664} }, // 1
        { "time-2", {240, 157, 17, 26, 664} }, // 2
        { "time-3", {257, 157, 17, 26, 664} }, // 3
        { "time-4", {274, 157, 17, 26, 664} }, // 4
        { "time-5", {291, 157, 17, 26, 664} }, // 5
        { "time-6", {223, 184, 17, 26, 664} }, // 6
        { "time-7", {240, 184, 17, 26, 664} }, // 7
        { "time-8", {257, 184, 17, 26, 664} }, // 8
        { "time-9", {274, 184, 17, 26, 664} }, // 9

        // Entries for urgent timer digits
        { "timeUrgent-0", {153, 184, 17, 26, 700} }, // 0
        { "timeUrgent-1", {0  , 157, 17, 26, 700} }, // 1
        { "timeUrgent-2", {17 , 216, 17, 26, 700} }, // 2
        { "timeUrgent-3", {34 , 216, 17, 26, 700} }, // 3
        { "timeUrgent-4", {51 , 216, 17, 26, 700} }, // 4
        { "timeUrgent-5", {68 , 216, 17, 26, 700} }, // 5
        { "timeUrgent-6", {85 , 216, 17, 26, 700} }, // 6
        { "timeUrgent-7", {102, 216, 17, 26, 700} }, // 7
        { "timeUrgent-8", {119, 216, 17, 26, 700} }, // 8
        { "timeUrgent-9", {136, 216, 17, 26, 700} }, // 9

        // Entries for alternate urgent timer digits
        { "timeUrgentAlt-0", {324, 216, 17, 26, 700} }, // 0
        { "timeUrgentAlt-1", {171, 216, 17, 26, 700} }, // 1
        { "timeUrgentAlt-2", {188, 216, 17, 26, 700} }, // 2
        { "timeUrgentAlt-3", {205, 216, 17, 26, 700} }, // 3
        { "timeUrgentAlt-4", {222, 216, 17, 26, 700} }, // 4
        { "timeUrgentAlt-5", {239, 216, 17, 26, 700} }, // 5
        { "timeUrgentAlt-6", {256, 216, 17, 26, 700} }, // 6
        { "timeUrgentAlt-7", {273, 216, 17, 26, 700} }, // 7
        { "timeUrgentAlt-8", {290, 216, 17, 26, 700} }, // 8
        { "timeUrgentAlt-9", {307, 216, 17, 26, 700} }, // 9

        // Entries for statut overlay
        { "statutBar", {8, 246, 170, 31} },
        { "timerBack", {164, 159, 48, 24} },

        // Entries for health
        { "currentHealth" , {79, 24, 3, 5} },
        { "maxHealth"     , {84, 24, 3, 5} },

        // Entries for round icon
        { "roundRemainingIcon" , {134, 21, 6, 4} },
        { "roundVictoryIcon" , {143, 20, 12, 7} },
        { "roundPerfectIcon" , {158, 20, 12, 7} },
        { "roundCloseIcon"   , {173, 20, 12, 7} },
        { "roundSuperIcon"   , {188, 20, 12, 7} },

        // Entries for fighter
        { "alexIcon"   , {40, 45, 30, 20} },
        { "alexName"   , {40, 67, 29, 7} },
        { "dudleyIcon"   , {193, 45, 31, 20} },
        { "dudleyName"   , {188, 67, 40, 7} },
        
    });
}

// Method to update the timer animation based on the elapsed time
void Hud::updateTimer(float deltaTime) { // Refactor possible with lambda func??

    // Searching for the sprite information in the spritesSheet map
    std::string keyLeft = m_timerFrame + std::to_string(m_currentFrameLeft);    
    auto it1 = m_spritesSheet->find(keyLeft);
    if (it1 != m_spritesSheet->end()) {
        m_currentTimerRectLeft = &(it1->second);
    } else {
        // If the sprite information is not found, throw an exception
        throw std::runtime_error("Sprite information for timer not found");
    }

    std::string keyRight = m_timerFrame + std::to_string(m_currentFrameRight);
    auto it2 = m_spritesSheet->find(keyRight);
    if (it2 != m_spritesSheet->end()) {
        m_currentTimerRectRight = &(it2->second);
    } else {
        throw std::runtime_error("Sprite information for timer not found");
    }

    // Logic for timer animation
    m_frameTime += deltaTime;
    if (m_frameTime >= m_currentTimerRectRight->spriteFrameTime) {
        if (m_currentFrameRight <= 0) {
            if (m_currentFrameLeft <= 0) {
                // Timer has reached "00", handle accordingly (e.g., end game)
            } else {
                m_currentFrameRight = m_maxFrame;
                --m_currentFrameLeft;
            }
        } else {
            --m_currentFrameRight;
        }
        m_frameTime -= m_currentTimerRectRight->spriteFrameTime;
    }
}

// Method to update the health bar of a player
void Hud::updateHealthBar(int playerIndex, int currentHealth) {
    setPlayerHealth(playerIndex, currentHealth);
}

// Method to get the position of the HUD
const Vector2D& Hud::getPosition() const {
    return m_position;
}

// Method to set the health of a player
void Hud::setPlayerHealth(int playerIndex, int currentHealth) {
    m_playerHealth[playerIndex] = currentHealth;
}

// Method to get the health of a player
const int& Hud::getPlayerHealth(int playerIndex) const {
    return m_playerHealth[playerIndex];
}

// Method to get the rectangle representing the timer for the specified index
const Rectangle& Hud::getTimerRect(int index) const {
     // Determine which currentFrame to use based on the index
    int currentFrame = (index == 0) ? m_currentFrameLeft : m_currentFrameRight;

     // Searching for the sprite information in the spritesSheet map
    std::string key = m_timerFrame + std::to_string(currentFrame);
    auto it = m_spritesSheet->find(key);
    if (it != m_spritesSheet->end()) {
        if (index == 0) {
            m_currentTimerRectLeft = &(it->second);
            return *m_currentTimerRectLeft;
        } else {
            m_currentTimerRectRight = &(it->second);
            return *m_currentTimerRectRight;
        }
    } else {
        // If the sprite information is not found, throw an exception
        throw std::runtime_error("Sprite information for timer not found");
    }
}

// Method to get the rectangle representing the sprite with the specified key
const Rectangle& Hud::getSpriteRect(std::string key) const {
     // Searching for the sprite information in the spritesSheet map
    auto it = m_spritesSheet->find(key);
    if (it != m_spritesSheet->end()) {
        m_currentSpriteRect = &(it->second);
        return *m_currentSpriteRect;
    }
    else {
        // If the sprite information is not found, throw an exception
        throw std::runtime_error("Sprite information not found");
    }
}

// Method to get the path of the overlay atlas
const char* Hud::getOverlayAtlasPath() const {
    return m_overlayAltasPath;
}

// Test for the StateMachine class
void Hud::regressionTest() {
    // Create an instance of the StateMachine class
    Hud hud;

    // Test 1: Check initial state
    assert(hud.m_overlayAltasPath = "data/images/overlay/overlay.png");
    assert(hud.m_timerFrame == "time-");
    assert(hud.m_currentFrameLeft == 9);
    assert(hud.m_currentFrameRight == 9);
    assert(hud.m_maxFrame == 9);
    assert(hud.m_frameTime == 0);

    assert(hud.getSpriteRect("time-0").posx == 291);
    assert(hud.getSpriteRect("time-0").posy == 184);
    assert(hud.getSpriteRect("time-0").width == 17);
    assert(hud.getSpriteRect("time-0").height == 26);
    assert(hud.getSpriteRect("time-0").spriteFrameTime == 664);

    // Test 2: updateTimer method
    hud.updateTimer(700.0f);
    assert(hud.m_currentFrameLeft == 9);
    assert(hud.m_currentFrameRight == 8);
    
    assert(hud.getTimerRect(0).posx == 274);
    assert(hud.getTimerRect(0).posy == 184);
    assert(hud.getTimerRect(0).width == 17);
    assert(hud.getTimerRect(0).height == 26);
    assert(hud.getTimerRect(0).spriteFrameTime == 664);

    assert(hud.getTimerRect(1).posx == 257);
    assert(hud.getTimerRect(1).posy == 184);
    assert(hud.getTimerRect(1).width == 17);
    assert(hud.getTimerRect(1).height == 26);
    assert(hud.getTimerRect(1).spriteFrameTime == 664);

    // Test 3: setPlayerHealth method
    hud.m_playerHealth[0] = 0;
    hud.m_playerHealth[1] = 0;

    hud.setPlayerHealth(0, 300);
    hud.setPlayerHealth(1, 500);

    // Test 4: getPlayerHealth method
    assert(hud.getPlayerHealth(0) == 300);
    assert(hud.getPlayerHealth(1) == 500);

    // Test 5: updateHealthBar method
    hud.setPlayerHealth(0, 240);
    hud.setPlayerHealth(1, 115);

    hud.updateHealthBar(0, hud.getPlayerHealth(0));
    hud.updateHealthBar(1, hud.getPlayerHealth(1));

    assert(hud.getPlayerHealth(0) == 240);
    assert(hud.getPlayerHealth(1) == 115);

    // Test 6: getPosition method
    hud.m_position.x = 45;
    hud.m_position.y = 180;
    
    assert(hud.getPosition().x == 45);
    assert(hud.getPosition().y == 180);

    // Test 9: getOverlayAtlasPath method
    const char* test = "test";
    hud.m_overlayAltasPath = test;
    assert(hud.getOverlayAtlasPath() == test);
}