#ifndef STATE_TERRAIN_H
#define STATE_TERRAIN_H

#include "Shaders/ShaderProgram.h"
#include "RenderEngine/GUIRenderer.h"

#include "StateMachine.h"
#include "State.h"

/*
    State : Terrain Editor class

    Used to handle the "terrain editor" state of the application (shows a top map of the world)
*/

namespace States {
    class State_Terrain : public State {
        private:
            Shaders::ShaderProgram _guiShader;
            RenderEngine::GUIRenderer _gui;

        public:
            State_Terrain () : State(EDITOR) {};

            void StartState ();
            void UpdateState ();
            void EndState ();
    };
}


#endif
