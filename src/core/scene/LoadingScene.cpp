#include "LoadingScene.h"

LoadingScene::LoadingScene() : m_quit(true), 
                               m_img1Path("data/images/loading/Chargement1.png"), 
                               m_img2Path("data/images/loading/Chargement2.png"),
                               m_img3Path("data/images/loading/Chargement3.png"),
                               m_img4Path("data/images/loading/Chargement4.png"),
                               m_img5Path("data/images/loading/Chargement5.png"),
                               m_img6Path("data/images/loading/Chargement6.png"),
                               m_img7Path("data/images/loading/Chargement7.png"),
                               m_img8Path("data/images/loading/Chargement8.png"){
}

LoadingScene::~LoadingScene() {

}

//update
void LoadingScene::update(int keycode){
    if(keycode == 3){
        m_quit = !m_quit;
    }
}

//getters
const char* LoadingScene::getImg1Path() const {
    return m_img1Path;
}

const char* LoadingScene::getImg2Path() const {
    return m_img2Path;
}

const char* LoadingScene::getImg3Path() const {
    return m_img3Path;
}

const char* LoadingScene::getImg4Path() const {
    return m_img4Path;
}

const char* LoadingScene::getImg5Path() const {
    return m_img5Path;
}

const char* LoadingScene::getImg6Path() const {
    return m_img6Path;
}
const char* LoadingScene::getImg7Path() const {
    return m_img7Path;
}

const char* LoadingScene::getImg8Path() const {
    return m_img8Path;
}

const bool& LoadingScene::getQuit() const{
    return m_quit;
}

// Test for the LoadingScene class
void LoadingScene::regressionTest(){
    // Initialize
    LoadingScene scene;

    // Test initialization
    assert(std::string(scene.getImg1Path()) == "data/images/loading/Chargement1.png");
    assert(std::string(scene.getImg2Path()) == "data/images/loading/Chargement2.png");
    assert(std::string(scene.getImg3Path()) == "data/images/loading/Chargement3.png");
    assert(std::string(scene.getImg4Path()) == "data/images/loading/Chargement4.png");
    assert(std::string(scene.getImg5Path()) == "data/images/loading/Chargement5.png");
    assert(std::string(scene.getImg6Path()) == "data/images/loading/Chargement6.png");
    assert(std::string(scene.getImg7Path()) == "data/images/loading/Chargement7.png");
    assert(std::string(scene.getImg8Path()) == "data/images/loading/Chargement8.png");
    assert(scene.getQuit() == true);

    // Test update
    // Simulate the user pressing enter to exit the loading scene
    scene.update(3);
    assert(scene.getQuit() == false);
}
