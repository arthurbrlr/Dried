#ifndef STATE_MAINMENU_H
#define STATE_MAINMENU_H

#include "RenderEngine/GUIRenderer.h"
#include "Shaders/ShaderProgram.h"

#include "State.h"
#include "StateMachine.h"

/*
    State : Main Menu class

    Used to handle the main menu state of the application (which is just an image right now)
*/

namespace States {
    class State_MainMenu : public State {
        private:
            RenderEngine::GUIRenderer _gui;
            Shaders::ShaderProgram _guiShader;

        public:
            State_MainMenu () : State(MAIN_MENU) {};

            void StartState ();
            void UpdateState ();
            void EndState ();
    };
}


#endif
