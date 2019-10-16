#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <vector>

#include "Util/util.h"
#include "Util/Config.h"

#include "Entities/Camera.h"
#include "RenderEngine/DisplayManager.h"
#include "GraphicInterface/DebugInterface.h"
#include "World/WorldGenerator.h"
#include "World/BasicChunk.h"
#include "World/World.h"

namespace GraphicInterface {
    void DebugInterface::Init () {
        // Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();
        ImGui_ImplGlfw_InitForOpenGL(RenderEngine::DisplayManager::GetInstance().GetWindow(), true);
        const char* glsl_version = "#version 410";
        ImGui_ImplOpenGL3_Init(glsl_version);

                /* Set the input callback */
        /*
        auto keyboard_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            DebugInterface::GetInstance().AddInput(std::to_string(key));
        };
        glfwSetKeyCallback(RenderEngine::DisplayManager::GetInstance().GetWindow(), keyboard_callback);*/
    }

    void DebugInterface::Update () {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (!_show) return;

        float deltaTime = RenderEngine::DisplayManager::GetInstance().DeltaTime() * 1000;

        if (deltaTime > _maxFrameTime) _maxFrameTime = deltaTime;

        _frameDurationVector.push_back(deltaTime);
        if (_frameDurationVector.size() > 240) {
            _frameDurationVector.erase(_frameDurationVector.begin());
        }

        ImGui::Begin("Debug Window", &_show);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Run Time: %.3f s", RenderEngine::DisplayManager::GetInstance().GetTime());
        ImGui::Text("Frame Time: %.2f ms", deltaTime);
        ImGui::SameLine();
        ImGui::Text("%.2f fps", 1000.f / deltaTime);
        ImGui::Text("Maximum: %.2f ms", _maxFrameTime);
        ImGui::PlotLines("Frame Times", &_frameDurationVector[0], _frameDurationVector.size());
        double mPosX, mPosY;
        glfwGetCursorPos(RenderEngine::DisplayManager::GetInstance().GetWindow(), &mPosX, &mPosY);
        ImGui::Text("mouse_x %d", (int)mPosX);
        ImGui::SameLine();
        ImGui::Text("mouse_y %d", (int)mPosY);
        ImGui::Checkbox("Wireframe Rendering", &_lines);

        if (_lines) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        glm::vec3 camPos = Entities::Camera::GetInstance().GetPosition();
        _posX = camPos.x; _posY = camPos.y; _posZ = camPos.z;
        ImGui::Text("Camera Position: ", _posX);
        ImGui::Text("x: %.1f /", _posX);
        ImGui::SameLine();
        ImGui::Text("y: %.1f /", _posY);
        ImGui::SameLine();
        ImGui::Text("z: %.1f", _posZ);

        //_terrainHeight = World::World::GetInstance().GetHeightAtPos(camPos.x, camPos.z);
        //ImGui::Text("Terrain Height: %d", _terrainHeight);

        int chunkX = std::floor(_posX / (CHUNKSIZE + 1));
        int chunkZ = std::floor(_posZ / (CHUNKSIZE + 1));
        ImGui::Text("In chunk x: %d", chunkX);
        ImGui::SameLine();
        ImGui::Text("z: %d", chunkZ);
        ImGui::End();


        if (_displayTerrainEditorWindow) TerrainEditorWindow();
        //ImGui::ShowDemoWindow(&_show);
    }

    void DebugInterface::TerrainEditorWindow ()  {
        ImGui::Begin("Debug Window", &_displayTerrainEditorWindow);

        ImGui::SliderFloat2("Biome Frequencies", bfs, 1.f, 1000.f, "%.1f");
        World::WorldGenerator::GetInstance().SetBiomeFX(bfs[0]);
        World::WorldGenerator::GetInstance().SetBiomeFZ(bfs[1]);
        if (ImGui::Button("Regenerate Image")) {
            _updateTerrainEditor = true;
        }
        ImGui::End();
    }

    void DebugInterface::Render () {
        ImGui::Render();
        ImGui::UpdatePlatformWindows();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void DebugInterface::Clear () {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
