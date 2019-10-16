#ifndef STATE_INGAME_H
#define STATE_INGAME_H

#include <vector>

#include "Interactions/Raycast.h"
#include "Shaders/ShaderProgram.h"
#include "RenderEngine/GUIRenderer.h"

#include "StateMachine.h"
#include "State.h"

/*
    State : Game class

    Used to handle the gaming state of the application
*/

namespace States {
    class State_Game : public State {
        private:
            Shaders::ShaderProgram _terrainShader, _guiShader;
            RenderEngine::GUIRenderer _gui;
            Interactions::Raycast _ray;

        public:
            State_Game () : State(GAME) {};

            void StartState ();
            void UpdateState ();
            void EndState ();
    };
}


#endif
