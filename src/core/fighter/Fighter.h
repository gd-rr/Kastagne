/*******************************************************************************
 * @file Fighter.h
 * @brief Defines the Fighter class for a fighting game.
 ******************************************************************************/
#ifndef _FIGHTER_H
#define _FIGHTER_H

#include <iostream>
#include <fstream>
#include <memory>
#include <map>
#include <algorithm>
#include "StateMachine.h"
#include "../../utils/Vector2D.h"
#include "../../../lib/nlohmann/json.hpp"

/*******************************************************************************
 * @brief Struct representing a bounding box.
 ******************************************************************************/
struct BoundingBox {
    int posx; /**< X position of the bounding box. */
    int posy; /**< Y position of the bounding box. */
    int width; /**< Width of the bounding box. */
    int height; /**< Height of the bounding box. */
};

/*******************************************************************************
 * @brief Struct containing information about bounding boxes.
 ******************************************************************************/
struct BoundingBoxInfo {
    const BoundingBox& ownBox; /**< Bounding box of the fighter. */
    const BoundingBox& oppBox; /**< Bounding box of the opponent fighter. */
};

/*******************************************************************************
 * @brief Struct representing a rectangle from an atlas.
 ******************************************************************************/
struct RectangleFromAtlas
{
    BoundingBox atlas; /**< Bounding box from the atlas. */
    Vector2D  posCorrector; /**< Position corrector vector. */
    Vector2D  posCorrectorReverse; /**< Reverse position corrector vector. */
    u_int64_t spriteFrameTime; /**< Time for each sprite frame. */
    BoundingBox collideBox; /**< Collision bounding box. */
    BoundingBox hurtBox; /**< Hurt bounding box. */
    BoundingBox hitBox; /**< Hit bounding box. */
};

/*******************************************************************************
 * @class Fighter
 * @brief Represents a fighter in a fighting game.
 ******************************************************************************/
class Fighter
{
private:
    // Données membres liées à la description générale du combattant
    std::string m_name;
    Vector2D m_position;
    int m_direction;
    int m_scale;
    const char* m_imagePath;

    // Données membres liées aux mouvements et à l'état du combattant
    float m_velocity;
    StateMachine m_stateMachine;
    int m_keycode;
    bool m_reversed;
    bool m_hasCollideWithOpponent;

    // Données membres liées à la santé et aux dégâts du combattant
    int m_maxHealth;
    int m_currentHealth;
    int m_damage;

    // Données membres liées à l'animation et aux sprites
    std::unique_ptr<std::unordered_map<std::string, RectangleFromAtlas>> m_spritesSheet;
    mutable const RectangleFromAtlas* m_currentSpriteRect;
    std::string m_animationFrame;
    int m_currentFrame;
    int m_maxFrame;
    u_int64_t m_frameTime;
    bool m_isAnimationPlaying;

    // Données membres liées aux keybinds
    std::map<std::string, std::map<bool, std::pair<std::string, std::pair<int, std::pair<int, int>>>>> animationMap;
    bool m_playerId;

    Fighter* m_opponent;

    int m_screenBorder;
    int m_cameraPosition;
    int m_screenWidth;

    int m_stanceWidth;

    

public:
    /***************************************************************************
     * @brief Default constructor for the Fighter class.
     **************************************************************************/
    Fighter();

    /***************************************************************************
     * @brief Destructor for the Fighter class.
     **************************************************************************/
    ~Fighter();


    void init(std::string fighterName);
    void update(float deltaTime, bool playerId, std::string keycode);
    void updateStageContraints(float deltaTime);
    void initializeAnimationMap();
    void setAnimation(std::string keycode, bool playerId);
    void setPosition(int posx, int posy);
    void setVelocity(float vel);
    void setReversed(bool rev);
    void setOpponent(Fighter* opp);
    void setStageContraints(int border, int screenw);
    void setCameraPosition(int campos);
    void setScale(int scl);
    void setName(std::string fighterName);
    void setDirection(int dir);
    bool checkCollision(const BoundingBoxInfo& boxInfo) const;
    bool isCollidingWithOpponent() const;
    bool isHittingOpponent() const;
    bool isBeingHurtByOpponent() const;


    const RectangleFromAtlas& getSpriteRect() const;
    const BoundingBox& getCollideBox() const;
    const Vector2D& getPosition() const;
    const Vector2D& getCorrector() const;
    const std::string& getAnimationFrame() const;
    const int& getScale() const;
    const char* getAtlasPath() const;
    const int& getCurrentHealth() const;
    const int& getMaxHealth() const;
    const int& getStanceWidth() const;
    const int getWidth() const;
    const bool& getReversed() const;
    const std::string& getName() const;
    const float getVelocity() const;
    const int getDirection() const;
    void decreaseHealthBy(int dmg);

    /***************************************************************************
     * @brief Performs regression testing for the Fighter class.
     **************************************************************************/
    static void regressionTest();
};


#endif // !_FIGHTER_H
