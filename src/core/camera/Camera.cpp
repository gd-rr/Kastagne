#include "Camera.h"

// Constructor
Camera::Camera() :  m_fighterPosition(2), 
                    m_fighterVelocity(2), 
                    m_fighterDirection(2) {
    // Initialize member variables
    m_position.x    = 0;
    m_position.y    = 0;
    m_cameraZone    = 375;
    m_screenWidth   = 0;
    m_screenHeight  = 0;
    m_stageLeftEdge = 0;
    m_stageWidth    = 0;
    m_fighterPosition   = {0, 0};
    m_fighterVelocity   = {0, 0};
    m_fighterDirection  = {0, 0};
}

// Destructor
Camera::~Camera() {}

// Updates the camera based on fighter positions and other parameters
void Camera::update(float deltaTime) {
    // Camera limits
    const int leftCameraLimit = -m_stageLeftEdge;
    const int rightCameraLimit = 
        m_stageWidth + m_stageLeftEdge - m_screenWidth - m_cameraZone;

    // Current camera zone limits
    const int currentLeftZoneLimit  = 
        m_position.x + m_cameraZone + m_stageLeftEdge;
    const int currentRightZoneLimit = 
        m_position.x + m_screenWidth - m_cameraZone - m_stageLeftEdge;

    // Neutral zone
    const int neutralZone = 
        m_screenWidth - (m_cameraZone << 1) - (m_stageLeftEdge << 1);

    // Calculate minimum and maximum fighter positions
    const int minPositionX = 
        std::min(m_fighterPosition[0], m_fighterPosition[1]);
    const int maxPositionX = 
        std::max(m_fighterPosition[0], m_fighterPosition[1]);

    // Updating the camera based on fighter position
    if ((maxPositionX - minPositionX) > neutralZone) {
        const int middlePosition = ((maxPositionX - minPositionX) >> 1);
        m_position.x = minPositionX + middlePosition - (m_screenWidth >> 1);
    } else {
        // If fighter exceeds the current camera zone, move the camera
        for (int i = 0; i < 2; ++i) {
            if ((m_fighterPosition[i] < currentLeftZoneLimit && 
                (m_fighterVelocity[i] * m_fighterDirection[i]) < 0) || 
                (m_fighterPosition[i] > currentRightZoneLimit && 
                (m_fighterVelocity[i] * m_fighterDirection[i]) > 0)) {
                m_position.x += 
                    m_fighterVelocity[i] * m_fighterDirection[i] * deltaTime;
            }
        }
    }
    // Ensure camera does not exceed its limits
    if (m_position.x < leftCameraLimit) 
        m_position.x = leftCameraLimit;
    if (m_position.x > rightCameraLimit) 
        m_position.x = rightCameraLimit;
}

// Centers the camera on the stage
void Camera::centerOnStage(int stageWidth, int stageHeight) {
    m_stageWidth = stageWidth;
    m_position.x = (stageWidth>>1) - (m_screenWidth>>1);
    m_position.y = stageHeight - m_screenHeight;
}

// Sets the position of the specified fighter
void Camera::setFighterPosition(int index, int pos) {
    m_fighterPosition[index] = pos;
}

// Sets the velocity of the specified fighter
void Camera::setFighterVelocity(int index, float vel) {
    m_fighterVelocity[index] = vel;
}

// Sets the direction of the specified fighter
void Camera::setFighterDirection(int index, int dir) {
    m_fighterDirection[index] = dir;
}

// Returns the position of the camera
const Vector2D& Camera::getPosition() const {
    return m_position;
}

// Sets the dimensions of the screen
void Camera::setScreenDimension(int width, int height) {
    m_screenWidth = width;
    m_screenHeight = height;    
}

// Sets the position of the camera
void Camera::setPosition(const Vector2D& pos) {
    m_position = pos;
}

// Sets the left edge of the stage
void Camera::setStageEdge(int leftEdge) {
    m_stageLeftEdge = leftEdge;
}

// Returns the camera zone
const int Camera::getCameraZone() const {
    return m_cameraZone;
}

// Test for the Camera class
void Camera::regressionTest() {
    // Create an instance of the Camera class
    Camera camera;

    // Test 1: setFighterPosition method
    camera.setFighterPosition(0, 100);
    assert(camera.m_fighterPosition[0] == 100);

    // Test 2: setFighterVelocity method
    camera.setFighterVelocity(0, 2.5f);
    assert(camera.m_fighterVelocity[0] == 2.5f);

    // Test 3: setFighterDirection method
    camera.setFighterDirection(0, 1);
    assert(camera.m_fighterDirection[0] == 1);

    // Test 4: setScreenDimension method
    camera.setScreenDimension(800, 600);
    assert(camera.m_screenWidth == 800);
    assert(camera.m_screenHeight == 600);

    // Test 5: setPosition method
    Vector2D newPosition = {50, 50};
    camera.setPosition(newPosition);
    assert(camera.getPosition().x == 50);
    assert(camera.getPosition().y == 50);

    // Test 6: setStageDimension method
    camera.setStageEdge(140);
    assert(camera.m_stageLeftEdge == 140);

    // Test 7: centerOnStage method
    camera.centerOnStage(1024, 768);
    assert(camera.m_stageWidth == 1024);
    assert(camera.m_position.x == 112);
    assert(camera.m_position.y == 168);

    // Test 8: getCameraZone method
    camera.m_cameraZone = 50;
    assert(camera.getCameraZone() == 50);

    // Test 9: update method
    // update method - Case 1
    camera.setScreenDimension(800, 600);
    camera.m_cameraZone = 50; // Assuming camera zone is 50
    camera.setStageEdge(100);
    camera.centerOnStage(1240, 780);
    camera.setFighterPosition(0, 400);
    camera.setFighterPosition(1, 700); // Assuming fighter positions
    camera.setFighterVelocity(0, 2.0f);
    camera.setFighterVelocity(1, -1.5f);
    camera.setFighterDirection(0, 1);
    camera.setFighterDirection(1, -1);
    camera.update(0.1f);
    // Assert expected camera position after update
    assert(camera.getPosition().x == 220); // Expected camera position

    // Test update method - Case 2
    camera.setPosition({0, 0});
    camera.setFighterPosition(0, 100);
    camera.setFighterVelocity(0, -2.0f);
    camera.setFighterDirection(0, -1);
    camera.update(10.0f);
    // Assert expected camera position after update
    assert(camera.getPosition().x == 0); // Expected camera position

    // Test update method - Case 3
    camera.setPosition({700, 0});
    camera.setFighterPosition(0, 700);
    camera.setFighterVelocity(0, 2.0f);
    camera.setFighterDirection(0, 1);
    camera.update(5.0f);
    // Assert expected camera position after update
    assert(camera.getPosition().x == 490); // Expected camera position

    // Test update method - Case 4
    camera.setPosition({50, 0});
    camera.setFighterPosition(0, 100);
    camera.setFighterVelocity(0, 1.0f);
    camera.setFighterDirection(0, 1);
    camera.update(0.1f);
    // Assert expected camera position after update
    assert(camera.getPosition().x == 0); // Expected camera position
}