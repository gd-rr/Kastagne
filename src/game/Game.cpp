#include "Game.h"

// Default constructor
Game::Game() : m_gameState(), m_battleScene(), m_fighterNames(2) {}

// Constructor taking an initial GameState as argument
Game::Game(GameState initialState) : m_gameState(initialState), m_battleScene(), m_fighterNames(2) {
    m_gameState = initialState;
    m_fighterNames[0] = "Alex";
    m_fighterNames[1] = "Alex";
}

// Destructor
Game::~Game() {}

// Method to update the game state based on the elapsed time and input
void Game::update(float deltaTime, std::string keycodeF1, std::string keycodeF2, int keycodeMenu) {
    // Update based on the current game state
    switch (m_gameState) {
        case GameState::LoadingScene:
            m_loadingScene.update(keycodeMenu);
            break;
        case GameState::MainMenu:
            m_menu.updateEvent(keycodeMenu);
            break;
        case GameState::CharacterSelection:
            m_select.updateEvent(keycodeMenu);
            break;
        case GameState::BattleScene:
            // Mettre à jour la scène de combat
            m_battleScene.update(deltaTime, keycodeF1,keycodeF2);
            break;
        case GameState::ExitGame:
            break;
    }
}

// Method to change the game state
void Game::changeState(GameState newState) {
    m_gameState = newState;

    switch (m_gameState) {
        case GameState::LoadingScene:
        case GameState::MainMenu:
            m_menu.initialize();
            break;
        case GameState::CharacterSelection:
            m_select.initialize();
        case GameState::BattleScene:
            m_battleScene.initialize(m_fighterNames[0], m_fighterNames[1]);
            break;
        case GameState::ExitGame:
            break;
    }
}

// Method to get the current game state
const GameState& Game::getCurrentGameState() const {
    return m_gameState;
}

// Method to get the battle scene object
BattleScene& Game::getBattleScene() {
    return m_battleScene;
}

// Method to get the menu object
Menu& Game::getMenu() {
    return m_menu;
}

// Method to get the select scene object
SelectScene& Game::getSelectScene(){
    return m_select;
}

// Method to get the loading scene object
LoadingScene& Game::getLoadingScene(){
    return m_loadingScene;
}

// Method to set the fighter names for player 1 and player 2
void Game::setFighterNames(std::string fighterName1, std::string fighterName2) {
    m_fighterNames[0] = fighterName1;
    m_fighterNames[1] = fighterName2;
}

void Game::regressionTest() {
    // Test default constructor
    Game gameDefaultConstructor;
    assert(gameDefaultConstructor.getCurrentGameState() == GameState::LoadingScene);

    // Test constructor with initial state
    Game gameWithInitialState(GameState::CharacterSelection);
    assert(gameWithInitialState.getCurrentGameState() == GameState::CharacterSelection);

    // Test changeState method
    gameDefaultConstructor.changeState(GameState::LoadingScene);
    assert(gameDefaultConstructor.getCurrentGameState() == GameState::LoadingScene);

    // Test getBattleScene method
    BattleScene& battleScene = gameDefaultConstructor.getBattleScene();
    assert(&battleScene == &gameDefaultConstructor.getBattleScene());

    // Test getMenu method
    Menu& menu = gameDefaultConstructor.getMenu();
    assert(&menu == &gameDefaultConstructor.getMenu());

    // Test getSelectScene method
    SelectScene& selectScene = gameDefaultConstructor.getSelectScene();
    assert(&selectScene == &gameDefaultConstructor.getSelectScene());

    // Test getLoadingScene method
    LoadingScene& loadingScene = gameDefaultConstructor.getLoadingScene();
    assert(&loadingScene == &gameDefaultConstructor.getLoadingScene());
}