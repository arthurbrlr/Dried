    /* OpenGL */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "RenderEngine/DisplayManager.h"
#include "RenderEngine/GUIRenderer.h"
#include "RenderEngine/Loader.h"

#include "Shaders/GUIShader.h"

#include "Util/TerrainEditor.h"

#include "GraphicInterface/GUIElement.h"
#include "GraphicInterface/DebugInterface.h"

#include "States/State.h"
#include "States/State_Terrain.h"

namespace States {
    void State_Terrain::StartState () {
        std::string vPath = "res/shaders/gui.vs", fPath = "res/shaders/gui.fs";
        _guiShader = Shaders::GUIShader(vPath, fPath);

        Util::TerrainEditor::GetInstance().GenerateImage();
        _gui = RenderEngine::GUIRenderer(&_guiShader);
        _gui.AddElement(GraphicInterface::GUIElement(RenderEngine::Loader::GetInstance().LoadTexture(Util::TerrainEditor::GetInstance().ImgPath(), false), glm::vec2(0, 0), glm::vec2(1., 1.)));
        glfwSetInputMode(RenderEngine::DisplayManager::GetInstance().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        GraphicInterface::DebugInterface::GetInstance().DisplayTerrainEditor(true);
    }


    void State_Terrain::UpdateState () {
        RenderEngine::DisplayManager::GetInstance().StartFrame();
        _gui.Render();
        GraphicInterface::DebugInterface::GetInstance().Update();

        if (GraphicInterface::DebugInterface::GetInstance().UpdateTerrainEditor()) {
            Util::TerrainEditor::GetInstance().GenerateImage();
            _gui.DeleteElements();
            _gui.AddElement(GraphicInterface::GUIElement(RenderEngine::Loader::GetInstance().LoadTexture(Util::TerrainEditor::GetInstance().ImgPath(), false), glm::vec2(0, 0), glm::vec2(1., 1.)));
        }

        RenderEngine::DisplayManager::GetInstance().EndFrame();
    }


    void State_Terrain::EndState () {
        GraphicInterface::DebugInterface::GetInstance().DisplayTerrainEditor(false);
        _guiShader.CleanUp();
    }
}
