/*******************************************************************************
 * @file StateMachine.h
 * @brief Defines the StateMachine class for managing states and transitions
 *        of a player.
 ******************************************************************************/
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <iostream>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

using string = std::string;

template<typename T>
using unorderedSet = std::unordered_set<T>;

template<typename T1, typename T2>
using unorderedMap = std::unordered_map<T1, T2>;

using transitionMap = unorderedMap<string, unorderedSet<string>>;

/*******************************************************************************
 * @class StateMachine
 * 
 * @brief Represents a state machine for managing states and transitions.
 * 
 * This class provides functionality for managing states and transitions of
 * a player in a game. It allows defining states and transitions between
 * these states, and provides methods for checking transition validity and
 * setting the current state.
 ******************************************************************************/
class StateMachine {
private:
    string m_currentState;
    transitionMap m_transitions;

public:
    /***************************************************************************
     * @brief Default constructor for the StateMachine class.
     * 
     * Initializes member variables to default values.
     **************************************************************************/
    StateMachine();

    /***************************************************************************
     * @brief Destructor for the StateMachine class.
     * 
     * Cleans up any resources allocated by the StateMachine.
     **************************************************************************/
    ~StateMachine();
    
    /***************************************************************************
     * @brief Checks if a transition to a new state is allowed.
     * 
     * This method checks if transitioning to the specified new state is
     * allowed based on the current state and defined transitions.
     * 
     * @param newState The state to transition to.
     * @return True if the transition is allowed, false otherwise.
     **************************************************************************/
    bool isTransitionAllowed(const std::string& newState) const;

    /***************************************************************************
     * @brief Sets the current state of the state machine.
     * 
     * This method sets the current state of the state machine to the specified
     * state, if the transition is allowed.
     * 
     * @param state The state to set as the current state.
     **************************************************************************/
    void setCurrentState(std::string& state);

    /***************************************************************************
     * @brief Performs regression testing for the StateMachine class.
     * 
     * This method performs regression testing for the StateMachine class to 
     * ensure its functionality is consistent across different versions.
     **************************************************************************/
    static void regressionTest();
};

#endif // STATE_MACHINE_H
