    /* OpenGL */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "RenderEngine/DisplayManager.h"
#include "RenderEngine/GUIRenderer.h"
#include "RenderEngine/Loader.h"

#include "Shaders/GUIShader.h"
#include "Shaders/ComputeShader.h"

#include "GraphicInterface/GUIElement.h"
#include "GraphicInterface/DebugInterface.h"

#include "States/State.h"
#include "States/State_MainMenu.h"

namespace States {
    void State_MainMenu::StartState () {
        std::string vPath = "res/shaders/gui.vs", fPath = "res/shaders/gui.fs";
        _guiShader = Shaders::GUIShader(vPath, fPath);
        _gui = RenderEngine::GUIRenderer(&_guiShader);
        //Shaders::ComputeShader::GetInstance().Load("res/world/test.cshader");
        std::cout << "Adding element" << std::endl;
        _gui.AddElement(GraphicInterface::GUIElement(RenderEngine::Loader::GetInstance().LoadTexture("res/textures/menu_bg.png", false), glm::vec2(0, 0), glm::vec2(1., 1.)));
        //_gui.AddElement(GraphicInterface::GUIElement(Shaders::ComputeShader::GetInstance().GetTexture(), glm::vec2(0, 0), glm::vec2(1., 1.)));
    }


    void State_MainMenu::UpdateState () {
        glfwSetInputMode(RenderEngine::DisplayManager::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        RenderEngine::DisplayManager::GetInstance().StartFrame();
        //Shaders::ComputeShader::GetInstance().Start();
        _gui.Render();
        GraphicInterface::DebugInterface::GetInstance().Update();
        RenderEngine::DisplayManager::GetInstance().EndFrame();
    }


    void State_MainMenu::EndState () {
        _guiShader.CleanUp();
        //Shaders::ComputeShader::GetInstance().CleanUp();
    }
}
