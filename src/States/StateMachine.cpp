#include <thread>
#include <chrono>
#include <iostream>

#include "States/State_Terrain.h"
#include "States/State_MainMenu.h"
#include "States/State_Game.h"
#include "States/StateMachine.h"

namespace States {
    void StateMachine::Init (State* initState) {
        _currentState = initState;
        _currentState->StartState();
    }

    void StateMachine::Update () {
        _currentState->UpdateState();
    }

    void StateMachine::Clear () {
        _currentState->EndState();
    }

    void StateMachine::TransitionToNewState (State* nextState) {

        float fadeInValue = 1.f;
        /*
        while (fadeInValue > 0.) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "." << std::flush;
            fadeInValue -= 0.1f;
        }
        std::cout << std::endl;
        */

        _currentState->EndState();
        _currentState = nextState;
        _currentState->StartState();
    }
}
