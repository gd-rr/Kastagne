#include "BattleScene.h"

// Constructor
BattleScene::BattleScene() : m_stage(), m_camera(), m_hud(), m_fighters(2) {
    m_endOfRound = false;
}

// Destructor
BattleScene::~BattleScene() {}

// Initializes the battle scene with the specified fighter names
void BattleScene::initialize(std::string fighterName1, 
                             std::string fighterName2) {

    // Initialize the first fighter
    m_fighters[0].init(fighterName1);
    m_fighters[0].setVelocity(0);
    m_fighters[0].setReversed(false);
    m_fighters[0].setDirection(1);

    // Initialize the second fighter
    m_fighters[1].init(fighterName2);
    m_fighters[1].setVelocity(0);
    m_fighters[1].setReversed(true);
    m_fighters[1].setDirection(-1);

    // Set opponents for each fighter
    m_fighters[0].setOpponent(&m_fighters[1]);
    m_fighters[1].setOpponent(&m_fighters[0]);
    
    // Set initial health values on the HUD
    m_hud.setPlayerHealth(0, m_fighters[0].getCurrentHealth());
    m_hud.setPlayerHealth(1, m_fighters[1].getCurrentHealth());

}

// Updates the battle scene
void BattleScene::update(float deltaTime, std::string keycodeF1,
                                          std::string keycodeF2) {
    // Variables to store positions of fighters
    int firstFighterPosition;
    int secondFighterPosition;

    // Calculate position of the first fighter based on its direction
    if(m_fighters[0].getDirection() == 1) 
        firstFighterPosition = 
            m_fighters[0].getPosition().x 
            + m_fighters[0].getSpriteRect().collideBox.posx*4;
    else firstFighterPosition = 
            m_fighters[0].getPosition().x + m_fighters[0].getStanceWidth() * 4;

    // Calculate position of the second fighter based on its direction
    if(m_fighters[1].getDirection() == 1) 
        secondFighterPosition = m_fighters[1].getPosition().x;
    else secondFighterPosition = 
        m_fighters[1].getPosition().x 
        + m_fighters[1].getStanceWidth() * 4 
        + m_fighters[1].getSpriteRect().posCorrectorReverse.x * 4 
        - m_fighters[1].getSpriteRect().collideBox.posx*4;

    // Update camera with fighter positions and velocities
    m_camera.setFighterPosition(0, firstFighterPosition);
    m_camera.setFighterVelocity(0, m_fighters[0].getVelocity());
    m_camera.setFighterDirection(0, m_fighters[0].getDirection());

    m_camera.setFighterPosition(1, secondFighterPosition);
    m_camera.setFighterVelocity(1, m_fighters[1].getVelocity());
    m_camera.setFighterDirection(1, m_fighters[1].getDirection());

    // Update camera position for both fighters
    m_fighters[0].setCameraPosition(m_camera.getPosition().x);
    m_fighters[1].setCameraPosition(m_camera.getPosition().x);

    // Update HUD healt bar with fighter health values
    for (unsigned int i = 0; i < 2; ++i) {
        int fighterHealth = m_fighters[i].getCurrentHealth();
        m_hud.updateHealthBar(i, fighterHealth);
    }

    // Check for end of battle condition
    if((m_fighters[0].getCurrentHealth() == 0 || 
        m_fighters[1].getCurrentHealth() == 0)) {
        m_endOfRound = true;
    }

    // Update timer on HUD
    m_hud.updateTimer(deltaTime);

    // Update both fighters
    m_fighters[0].update(deltaTime, true, keycodeF1);
    m_fighters[1].update(deltaTime, false, keycodeF2);

    // Update camera
    m_camera.update(deltaTime);
}

// Returns a reference to the fighter at the specified index
Fighter& BattleScene::getFighter(int index) {
    return m_fighters[index];
}

// Returns a reference to the stage of the battle scene
Stage& BattleScene::getStage() {
    return m_stage;
}

// Returns a reference to the HUD of the battle scene
Hud& BattleScene::getHud() {
    return m_hud;
}

// Returns a reference to the camera of the battle scene
Camera& BattleScene::getCamera() {
    return m_camera;
}

// Test for the BattleScene class
void BattleScene::regressionTest() {
    // Create an instance of the BattleScene class
    BattleScene battleScene;
    
    // Test 1: Initialize the battle scene with specified fighter names
    battleScene.initialize("Alex", "Alex");
    // Verify that fighters are initialized correctly
    assert(battleScene.getFighter(0).getName() == "Alex");
    assert(battleScene.getFighter(1).getName() == "Alex");

    // Test 2: Check end-of-battle condition
    // Simulate end of battle by setting one fighter's health to 0
    battleScene.getFighter(0).decreaseHealthBy(1000);
    battleScene.update(0.1f, "F1", "F2");
    // Verify that end of battle condition is detected
    assert(battleScene.m_endOfRound == true);
}