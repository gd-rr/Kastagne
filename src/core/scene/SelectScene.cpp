#include "SelectScene.h"
#include <iostream>

SelectScene::SelectScene() : m_currentAnimationName("SelectedSquare-"), 
                             m_currentFrame(0),
                             m_frameTime(0), 
                             m_p1(true), 
                             m_p2(false), 
                             m_dudley(true), 
                             m_alex(false), 
                             m_p1Choose(false), 
                             m_p2Choose(false), 
                             m_quit(true) {

}

SelectScene::~SelectScene(){
    m_atlas = nullptr;
    m_backGround = nullptr;
}

//initialize
void SelectScene::initialize(){
    m_atlas = "data/images/selection/Atlas_CharacterSelection.png";
    m_backGround = "data/images/selection/BackGround_CharacterSelection.png";
    m_sceneElement = (std::unordered_map<std::string, frameData>{
        {"SelectedSquare-0", { { {1201, 36}, 108, 108 }, 70} },
        {"SelectedSquare-1", { { {1199, 169}, 108, 108}, 70} },
        {"SelectedSquare-2", { { {1200, 301}, 108, 108}, 70} }
    });
}

//updates
void SelectScene::update(float deltaTime){
    std::string key = m_currentAnimationName + std::to_string(m_currentFrame);
    auto it = m_sceneElement.find(key);
    if (it != m_sceneElement.end()) {
       m_currentFrameData = &(it->second);
    }
    m_frameTime += deltaTime;
    if (m_frameTime >= m_currentFrameData->atlasFrameTime) {
        if (m_currentFrame >= 3 - 1) {
            m_currentFrame = 0;
        }
        else {
            ++m_currentFrame;
        }
        m_frameTime -= m_currentFrameData->atlasFrameTime;
    } 
}

void SelectScene::updateEvent(int keycode){
    if(m_p2Choose == false){
        if(keycode == 2 && m_dudley ==  true){
            m_dudley = !m_dudley;
            m_alex = !m_alex;
            return;
        }
        if(keycode == 1 && m_alex == true){
            m_dudley = !m_dudley;
            m_alex = !m_alex;
            return;
        }
    }

    if(keycode == 3){
        if(m_p1Choose == true && m_p2Choose == true){
            m_quit = !m_quit;
            return;
        }
        if(m_p2 == true){
            m_p2Choose = !m_p2Choose;
            return;
        }
        if(m_p1 == true){
            m_p1Choose = !m_p1Choose;
            m_p2 = !m_p2;
            return;
        }
    }
}


//getters
const char* SelectScene::getAtlasPath(){
    return m_atlas;
}

const char* SelectScene::getBackGroundPath(){
    return m_backGround;
}

const frameData& SelectScene::getFrameData() const{
    std::string key = m_currentAnimationName + std::to_string(m_currentFrame);
    auto it = m_sceneElement.find(key);
    if (it != m_sceneElement.end()) {
        m_currentFrameData = &(it->second);
        return *m_currentFrameData;
    }
    else {
        static frameData defaultRect;
        return defaultRect;
    }
}

const std::string& SelectScene::getCurrentAnimationName() const{
    return m_currentAnimationName;
}

const bool& SelectScene::getBoolDudley() const{
    return m_dudley;
}

const bool& SelectScene::getBoolAlex() const{
    return m_alex;
}

const bool& SelectScene::getBoolP1() const{
    return m_p1;
}

const bool& SelectScene::getBoolP2() const{
    return m_p2;
}

const bool& SelectScene::getBoolP1Choose() const{
    return m_p1Choose;
}

const bool& SelectScene::getBoolP2Choose() const{
    return m_p2Choose;
}

const bool& SelectScene::getQuitSelect() const{
    return m_quit;
}

// Test for the SelectScene class
void SelectScene::regressionTest(){
    // Initialize
    SelectScene scene;

    scene.initialize();

    // Test initialization
    assert(scene.getCurrentAnimationName() == "SelectedSquare-");
    assert(scene.m_currentFrame == 0);
    assert(scene.m_frameTime == 0);
    assert(scene.getBoolP1() == true);
    assert(scene.getBoolP2() == false);
    assert(scene.getBoolDudley() == true);
    assert(scene.getBoolAlex() == false);
    assert(scene.getBoolP1Choose() == false);
    assert(scene.getBoolP2Choose() == false);
    assert(scene.getQuitSelect() == true);

    // Test getters of paths
    assert(std::string(scene.getAtlasPath()) == "data/images/selection/Atlas_CharacterSelection.png");
    assert(std::string(scene.getBackGroundPath()) == "data/images/selection/BackGround_CharacterSelection.png");

    // Test update
    scene.update(1.0); // Simulate a small time step
    assert(scene.m_currentFrame == 0);
    assert(scene.m_frameTime == 1);

    // Test updateEvent
    // Simulate player 1 go down
    scene.updateEvent(2);
    assert(scene.getBoolDudley() == false);
    assert(scene.getBoolAlex() == true);

    // Simulate player 1 selecting Alex
    scene.updateEvent(3);
    assert(scene.getBoolP1Choose() == true);
    assert(scene.getBoolP2Choose() == false);
    assert(scene.getBoolP1() == true);
    assert(scene.getBoolP2() == true);

    // Simulate player 1 go up
    scene.updateEvent(1);
    assert(scene.getBoolDudley() == true);
    assert(scene.getBoolAlex() == false);

    // Simulate player 2 selecting Dudley
    scene.updateEvent(3);
    assert(scene.getBoolP2Choose() == true);
    assert(scene.getQuitSelect() == true);

    scene.updateEvent(3);
    assert(scene.getBoolP1Choose() == true);
    assert(scene.getBoolP2Choose() == true);
    assert(scene.getQuitSelect() == false);
}