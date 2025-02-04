#include "StateMachine.h"

StateMachine::StateMachine() {
        m_currentState = "Stance";
        // Initialisation des transitions
        m_transitions["Stance"] = {
            "Stance",
            "Crouch",
            "JumpBackward",
            "JumpForward",
            "JumpUpward",
            "DashBackward",
            "DashForward",
            "WalkBackward",
            "WalkForward",
            "Taunt",
            "StandingFarHK",
            "StandingFarHP",
            "StandingFarLK",
            "StandingFarLP",
            "StandingFarMK",
            "StandingFarMP",
            "StandingCloseLP",
            "StandingCloseMK",
            "JumpUpwardHK",
            "JumpUpwardHP",
            "JumpUpwardLK",
            "JumpUpwardLP",
            "JumpUpwardMK",
            "JumpUpwardMP",
            "JumpDiagonalHK",
            "JumpDiagonalHP",
            "JumpDiagonalLK",
            "JumpDiagonalLP",
            "JumpDiagonalMK",
            "JumpDiagonalMP",
            "CrouchHK",
            "CrouchHP",
            "CrouchLK",
            "CrouchLP",
            "CrouchMK",
            "CrouchMP"
        };

        m_transitions["Crouch"] = {
            "Stance",
            "Crouch",
            "Taunt",
            "CrouchHK",
            "CrouchHP",
            "CrouchLK",
            "CrouchLP",
            "CrouchMK",
            "CrouchMP"
            };
            
        m_transitions["JumpBackward"] = {"Stance"};

        m_transitions["JumpForward"]  = {
            "Stance",
            "JumpDiagonalHK",
            "JumpDiagonalHP",
            "JumpDiagonalLK",
            "JumpDiagonalLP",
            "JumpDiagonalMK",
            "JumpDiagonalMP",
        };

        m_transitions["JumpUpward"]   = {
            "Stance",
            "JumpUpwardHK",
            "JumpUpwardHP",
            "JumpUpwardLK",
            "JumpUpwardLP",
            "JumpUpwardMK",
            "JumpUpwardMP",
        };

        m_transitions["WalkBackward"] = {
            "Stance",
            "Crouch",
            "JumpBackward",
            "JumpForward",
            "JumpUpward",
            "DashBackward",
            "DashForward",
            "WalkBackward",
            "WalkForward",
            "Taunt",
            "StandingFarHK",
            "StandingFarHP",
            "StandingFarLK",
            "StandingFarLP",
            "StandingFarMK",
            "StandingFarMP",
            "StandingCloseLP",
            "StandingCloseMK",
        };

        m_transitions["WalkForward"] = m_transitions["WalkBackward"];

        m_transitions["DashForward"] = {"Stance"};

        m_transitions["DashBackward"] = {"Stance"};

        m_transitions["Taunt"] = {"Stance"};

        m_transitions["StandingFarHK"]   = {"Stance"};
        m_transitions["StandingFarHP"]   = {"Stance"};
        m_transitions["StandingFarLK"]   = {"Stance"};
        m_transitions["StandingFarLP"]   = {"Stance"};
        m_transitions["StandingFarMK"]   = {"Stance"};
        m_transitions["StandingFarMP"]   = {"Stance"};
        m_transitions["StandingCloseLP"] = {"Stance"};
        m_transitions["StandingCloseMK"] = {"Stance"};
        //m_transitions["JumpUpwardHK"]    = {"Stance"};
        //m_transitions["JumpUpwardHP"]    = {"Stance"};
        //m_transitions["JumpUpwardLK"]    = {"Stance"};
        //m_transitions["JumpUpwardLP"]    = {"Stance"};
        //m_transitions["JumpUpwardMK"]    = {"Stance"};
        //m_transitions["JumpUpwardMP"]    = {"Stance"};
        //m_transitions["JumpDiagonalHK"]  = {"Stance"};
        //m_transitions["JumpDiagonalHP"]  = {"Stance"};
        //m_transitions["JumpDiagonalLK"]  = {"Stance"};
        //m_transitions["JumpDiagonalLP"]  = {"Stance"};
        //m_transitions["JumpDiagonalMK"]  = {"Stance"};
        //m_transitions["JumpDiagonalMP"]  = {"Stance"};
        m_transitions["CrouchHK"]        = {"Crouch"};
        m_transitions["CrouchHP"]        = {"Crouch"};
        m_transitions["CrouchLK"]        = {"Crouch"};
        m_transitions["CrouchLP"]        = {"Crouch"};
        m_transitions["CrouchMK"]        = {"Crouch"};
        m_transitions["CrouchMP"]        = {"Crouch"};

        /*
        Ko
        Timeout
        Entrance
        Block
        BlockHigh
        BlockLow
        Parry
        ParryLow
        Win1
        Win2
        Win3
        HitStanding
        HitCrouch
        */

}

StateMachine::~StateMachine() {}

bool StateMachine::isTransitionAllowed(const string& newState) const {
    auto it = m_transitions.find(m_currentState);
    if (it != m_transitions.end() && it->second.count(newState) > 0) {
        return true;
    }
    return false;
}

void StateMachine::setCurrentState(string& state) {
    m_currentState = state;
}

// Test for the StateMachine class
void StateMachine::regressionTest() {
    // Create an instance of the StateMachine class
    StateMachine stateMachine;

    // Test 1: Check transition from initial state to "Stance"
    assert(stateMachine.isTransitionAllowed("Stance") == true);

    // Test 2: Try setting current state to "Stance"
    string newState = "Stance";
    stateMachine.setCurrentState(newState);
    assert(stateMachine.m_currentState == "Stance");

    // Test 3: Try setting current state to "Crouch" from "Stance"
    newState = "Crouch";
    stateMachine.setCurrentState(newState);
    assert(stateMachine.m_currentState == "Crouch");

    // Test 4: Try setting current state to "JumpBackward" from "Crouch"
    newState = "JumpBackward";
    stateMachine.setCurrentState(newState);
    // Also, isTransitionAllowed should return false for this transition
    assert(stateMachine.isTransitionAllowed(newState) == false);
}