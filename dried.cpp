    /* OpenGL */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

    /* Maths */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

    /* Legacy */
#include <iostream>
#include <string>
#include <vector>
#include <thread>

    /* Engine */
#include "Util/OpenSimplexNoise.h"

#include "States/StateMachine.h"
#include "RenderEngine/Loader.h"
#include "RenderEngine/DisplayManager.h"
#include "GraphicInterface/DebugInterface.h"
#include "Textures/TextureAtlas.h"


int main(void) {
    
    std::string cmd("clear");
    system(cmd.c_str());

    if (RenderEngine::DisplayManager::GetInstance().Init() == -1) return -1;
    GraphicInterface::DebugInterface::GetInstance().Init();
    Textures::TextureAtlas::GetInstance().Init("res/textures/texture-atlas.png");

    /* State machine */
    States::State_MainMenu s_menu;
    States::State_Game s_game;
    States::State_Terrain s_terrain;
    States::StateMachine::GetInstance().Init(&s_menu);

    while(!glfwWindowShouldClose(RenderEngine::DisplayManager::GetInstance().GetWindow())) {
        if (glfwGetKey(RenderEngine::DisplayManager::GetInstance().GetWindow(), GLFW_KEY_G) == GLFW_PRESS) {
            States::StateMachine::GetInstance().TransitionToNewState(&s_game);
            glfwSetInputMode(RenderEngine::DisplayManager::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else if (glfwGetKey(RenderEngine::DisplayManager::GetInstance().GetWindow(), GLFW_KEY_H) == GLFW_PRESS) {
            States::StateMachine::GetInstance().TransitionToNewState(&s_menu);
            glfwSetInputMode(RenderEngine::DisplayManager::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        States::StateMachine::GetInstance().Update();
    }

    States::StateMachine::GetInstance().Clear();
    RenderEngine::Loader::GetInstance().CleanUp();
    RenderEngine::DisplayManager::GetInstance().Clear();
    GraphicInterface::DebugInterface::GetInstance().Clear();

    return 0;
}
