#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <thread>
#include <math.h>

#include "RenderEngine/Loader.h"
#include "RenderEngine/GUIRenderer.h"
#include "RenderEngine/DisplayManager.h"
#include "RenderEngine/MeshBuilder.h"

#include "Interactions/Raycast.h"

#include "GraphicInterface/DebugInterface.h"

#include "Shaders/GUIShader.h"
#include "Shaders/TerrainShader.h"

#include "Entities/Light.h"
#include "Entities/Camera.h"

#include "Util/Config.h"

#include "Textures/TextureAtlas.h"

#include "World/Block/BlockDataBase.h"
#include "World/BasicChunk.h"
#include "World/ChunkMesh.h"
#include "World/WorldGenerator.h"
#include "World/World.h"

#include "States/State.h"
#include "States/StateMachine.h"


namespace States {

    void State_Game::StartState () {

        World::WorldGenerator::GetInstance().SetSeed(10);
        World::World::GetInstance().BuildWorld();

        std::string vPath = "res/shaders/normal.vs", fPath = "res/shaders/normal.fs";
        _terrainShader = Shaders::TerrainShader(vPath, fPath);
        Entities::Light sun(glm::vec3(0.f, 1000.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
        _terrainShader.LoadMainLight(sun);

        std::string uiVPath = "res/shaders/gui.vs", uiFPath = "res/shaders/gui.fs";
        _guiShader = Shaders::GUIShader(uiVPath, uiFPath);
        _gui = RenderEngine::GUIRenderer(&_guiShader);
        _gui.AddElement(GraphicInterface::GUIElement(RenderEngine::Loader::GetInstance().LoadTexture("res/textures/cursor.png", true), glm::vec2(0, 0), glm::vec2(0.015, RenderEngine::DisplayManager::GetInstance().GetAspect() * 0.015)));

        World::BlockDataBase::GetInstance().LoadBlockDataBase("res/blocks/blockdb.db", &_terrainShader);
        Entities::Camera::GetInstance().Init(glm::vec3(-3.f, 10.f, 0.f));

        _ray = Interactions::Raycast(RenderEngine::DisplayManager::GetInstance().GetProjectionMatrix());
    }

    void State_Game::UpdateState () {
        _terrainShader.Start();
        Entities::Light sun(glm::vec3(0.f, 1000.f, 0.f), glm::vec3(1.f, 1.f, 1.f));
        _terrainShader.LoadMainLight(sun);

        RenderEngine::DisplayManager::GetInstance().StartFrame();
        Entities::Camera::GetInstance().ProcessInputs(RenderEngine::DisplayManager::GetInstance().GetWindow());

        glm::vec3 camPos = Entities::Camera::GetInstance().GetPosition();
        int camChunkX = std::floor(camPos.x / (CHUNKSIZE + 1));
        int camChunkY = std::floor(camPos.y / (CHUNKSIZE + 1));
        int camChunkZ = std::floor(camPos.z / (CHUNKSIZE + 1));

        _ray.Update();

        _terrainShader.SetMatrix4("cameraView", Entities::Camera::GetInstance().GetViewMatrix());
        _terrainShader.SetMatrix4("projection", RenderEngine::DisplayManager::GetInstance().GetProjectionMatrix());

        if (World::World::GetInstance().IsGenerated()) {
            RenderEngine::MeshBuilder::GetInstance().BuildNewMeshPerFrame();
            RenderEngine::MeshBuilder::GetInstance().RenderWorld();
        }

        _gui.Render();


        GraphicInterface::DebugInterface::GetInstance().Update();
        RenderEngine::DisplayManager::GetInstance().EndFrame();
        //_terrainShader.Stop();
    }

    void State_Game::EndState () {

        World::World::GetInstance().CloseWorld();
        _terrainShader.Stop();
        _terrainShader.CleanUp();
    }
}
