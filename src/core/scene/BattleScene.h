/*******************************************************************************
 * @file BattleScene.h
 * @brief Represents the scene where player-vs-player battles occur.
 ******************************************************************************/
#ifndef _BATTLE_SCENE_H
#define _BATTLE_SCENE_H

#include <vector>
#include "../stage/Stage.h"
#include "../camera/Camera.h"
#include "../hud/Hud.h"
#include "../fighter/Fighter.h"

/*******************************************************************************
 * @class BattleScene
 * 
 * @brief Represents the scene where player-vs-player battles occur.
 * 
 * The BattleScene class represents the scene where player-vs-player battles 
 * take place. It manages the stage, camera, HUD, and fighters involved in the 
 * battle.
 ******************************************************************************/
class BattleScene {
private:
    Stage   m_stage;
    Camera  m_camera;
    Hud     m_hud;
    std::vector<Fighter> m_fighters;
    bool m_endOfRound;

public:
    /***************************************************************************
     * @brief Constructs a new BattleScene object.
     * 
     * Initializes member variables to default values.
     **************************************************************************/
    BattleScene();

    /***************************************************************************
     * @brief Destroys the BattleScene object.
     * 
     * Cleans up any resources allocated by the BattleScene.
     **************************************************************************/
    ~BattleScene();

    /***************************************************************************
     * @brief Initializes the battle scene with the specified fighter names.
     * 
     * This method initializes the battle scene with the specified fighter 
     * names. It initializes the fighters, sets their opponents, and sets 
     * initial health values on the HUD.
     * 
     * @param fighterName1 The name of the first fighter.
     * @param fighterName2 The name of the second fighter.
     **************************************************************************/
    void initialize(std::string fighterName1, std::string fighterName2);

    /***************************************************************************
     * @brief Updates the battle scene.
     * 
     * This method updates the battle scene, including the fighters, camera, 
     * HUD, and checks for end of battle condition.
     * 
     * @param deltaTime The time elapsed since the last update.
     * @param keycodeF1 The key code for controlling the first fighter.
     * @param keycodeF2 The key code for controlling the second fighter.
     **************************************************************************/
    void update(float deltaTime, std::string keycodeF1, std::string keycodeF2);

    /***************************************************************************
     * @brief Gets the fighter at the specified index.
     * 
     * This method returns a reference to the fighter at the specified index.
     * 
     * @param index The index of the fighter to retrieve.
     * @return Reference to the fighter at the specified index.
     **************************************************************************/
    Fighter& getFighter(int index);

    /***************************************************************************
     * @brief Gets the stage of the battle scene.
     * 
     * This method returns a reference to the stage object of the battle scene. 
     *
     * @return Reference to the stage object.
     **************************************************************************/
    Stage& getStage();

    /***************************************************************************
     * @brief Gets the heads-up display of the battle scene.
     * 
     * This method returns a reference to the heads-up display (HUD) object of 
     * the battle scene.
     * 
     * @return Reference to the HUD object.
     **************************************************************************/
    Hud& getHud();

    /***************************************************************************
     * @brief Gets the camera of the battle scene.
     * 
     * This method returns a reference to the camera object of the battle scene.
     * 
     * @return Reference to the camera object.
     **************************************************************************/
    Camera& getCamera();

    /***************************************************************************
     * @brief Performs regression testing for the BattleScene class.
     * 
     * This method performs regression testing for the BattleScene class to ensure
     * its functionality is consistent across different versions.
     **************************************************************************/
    static void regressionTest();
}; 

#endif // !_BATTLE_SCENE_H
