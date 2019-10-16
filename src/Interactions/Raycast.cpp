#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <chrono>

#include "Util/util.h"
#include "World/World.h"
#include "RenderEngine/DisplayManager.h"
#include "Entities/Camera.h"
#include "Interactions/Raycast.h"

namespace Interactions {

    void Raycast::Update () {
        _viewMatrix = Entities::Camera::GetInstance().GetViewMatrix();
        _ray = CalculateRay();
        //World::World::GetInstance().GetBlockAtPos(_ray);
        _frameUntilMining--;
        if (glfwGetKey(RenderEngine::DisplayManager::GetInstance().GetWindow(), GLFW_KEY_R) && _frameUntilMining < 0) {
            World::World::GetInstance().RemoveBlockAtPos(_ray);
            _frameUntilMining = 5;
        }
    }


    glm::vec3 Raycast::CalculateRay () {
        float yaw = glm::radians(Entities::Camera::GetInstance().GetRotation().y);
        float pitch = glm::radians(Entities::Camera::GetInstance().GetRotation().x);
        glm::vec3 camPos = Entities::Camera::GetInstance().GetPosition();
        glm::vec3 worldRay;

        for (int i = 0; i < 7; i++) {
            worldRay = camPos;
            worldRay.x += std::clamp(glm::cos(yaw)  , -1.f, 1.f) * 6.f * (float)i / 7.f;
            worldRay.z += std::clamp(glm::sin(yaw)  , -1.f, 1.f) * 6.f * (float)i / 7.f;
            worldRay.y += std::clamp(glm::tan(pitch), -1.f, 1.f) * 6.f * (float)i / 7.f;
            glm::vec3 worldIntRay = glm::vec3(std::floor(worldRay.x), std::floor(worldRay.y), std::floor(worldRay.z));
            
            auto start = std::chrono::system_clock::now();
            if (i == 6 || World::World::GetInstance().BlockAtPosExists(worldIntRay)) {
                return worldIntRay;
            }
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            //std::cout << "--- [Raycast Iteration] Block at pos exists time: " << elapsed_seconds.count() << std::endl;
        }
    }


    glm::vec2 Raycast::MouseToNormalizedCoords (const float & mouseX, const float & mouseY) {
        float x = (2.f * mouseX) / RenderEngine::DisplayManager::GetInstance().GetWidth() - 1.f;
        float y = (2.f * mouseY) / RenderEngine::DisplayManager::GetInstance().GetHeight() - 1.f;

        return glm::vec2(x, -y);
    }


    glm::vec4 Raycast::ToEyeCoords (const glm::vec4 & clipCoords) {
        glm::mat4 invertViewMatrix = glm::inverse(_viewMatrix);
        glm::vec4 eyeCoords = invertViewMatrix * clipCoords;

        return glm::vec4(eyeCoords.x, eyeCoords.y, -1.f, 0.f);
    }

    glm::vec3 Raycast::ToWorldCoords (const glm::vec4 & eyeCoords) {
        glm::mat4 invertProjMatrix = glm::inverse(_projectionMatrix);
        glm::vec4 rayWorld = invertProjMatrix * eyeCoords;
        glm::vec3 ray = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
        
        return glm::normalize(ray);
    }


}