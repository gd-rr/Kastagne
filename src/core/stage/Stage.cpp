#include "Stage.h"

Stage::Stage() : m_stagePathBack("data/images/backgrounds/background1_back.png"), m_stagePathFront("data/images/backgrounds/background1_front.png") {}

Stage::~Stage() {}

void Stage::update(float deltaTime) {
    
}

const char* Stage::getStageFrontPath() const {
    return m_stagePathFront;
}

const char* Stage::getStageBackPath() const {
    return m_stagePathBack;
}

// Test for the Stage class
void Stage::regressionTest() {
    // Create an instance of the Stage class
    Stage stage;

    // Test 1: Check stage background paths
    assert(std::string(stage.getStageFrontPath()) == "data/images/backgrounds/background1_front.png");
    assert(std::string(stage.getStageBackPath()) == "data/images/backgrounds/background1_back.png");
}
