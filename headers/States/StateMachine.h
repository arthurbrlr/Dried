#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "State.h"
#include "State_Terrain.h"
#include "State_MainMenu.h"
#include "State_Game.h"

/*
    State machine singleton

    Handle every states of the application and the transition between them
*/

namespace States {

    class State;
    class State_MainMenu;
    class State_Game;

    class StateMachine {
        private:
            State* _currentState;

            static StateMachine* instance;
            StateMachine(){};

        public:
            StateMachine(StateMachine const&) = delete;
            void operator=(StateMachine const&) = delete;
            static StateMachine& GetInstance () {
                static StateMachine instance;
                return instance;
            };

            void Init (State* initState);
            void TransitionToNewState (State* nextState);
            void Update ();
            void Clear ();

            GameState GetCurrentState () {return _currentState->GState();};
    };
}

#endif
