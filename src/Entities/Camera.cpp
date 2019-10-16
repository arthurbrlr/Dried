#define CAMERA_SPEED 2

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Util/Config.h"

#include "RenderEngine/DisplayManager.h"
#include "Entities/Camera.h"

namespace Entities {
    void Camera::Init (const glm::vec3 & initialPosition) {
        _position = initialPosition;
        _cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        _viewMatrix = glm::mat4(1.0f);
    }


    glm::vec3 Camera::GetChunkPosition () {
        int camChunkX = std::floor(_position.x / (CHUNKSIZE + 1));
        int camChunkY = std::floor(_position.y / (CHUNKSIZE + 1));
        int camChunkZ = std::floor(_position.z / (CHUNKSIZE + 1));

        return glm::vec3(camChunkX, camChunkY, camChunkZ);
    }

    void Camera::ProcessInputs (GLFWwindow* window) {

        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !_freezed) {
            glfwGetCursorPos(window, &_mFreezedX, &_mFreezedY);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            _freezed = true;
        }

        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && _freezed) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            _freezed = false;
            glfwSetCursorPos(window, _mFreezedX, _mFreezedY);
        }

        if (_freezed) return;

        float dt = RenderEngine::DisplayManager::GetInstance().DeltaTime();

            /* Movement due to the keyboard input (translations in the world) */
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS) _position += _moveSpeed * _cameraFront;
        else if (glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) _position -= _moveSpeed * _cameraFront;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS) _position -= _moveSpeed * glm::normalize(glm::cross(_cameraFront, _cameraUp));
        else if (glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) _position += _moveSpeed * glm::normalize(glm::cross(_cameraFront, _cameraUp));

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS) _position += _moveSpeed *  _cameraUp;
        else if (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) _position -= _moveSpeed * _cameraUp;

            /* Movement due to the mouse input (rotations in the world) */

        double mPosX, mPosY;
        glfwGetCursorPos(RenderEngine::DisplayManager::GetInstance().GetWindow(), &mPosX, &mPosY);

        if(_firstMouse) {
            _lastX = mPosX;
            _lastY = mPosY;
            _firstMouse = false;
        }

        float xoffset = mPosX - _lastX;
        float yoffset = _lastY - mPosY;
        _lastX = mPosX;
        _lastY = mPosY;

        _rotY += xoffset * _sensitivity;
        _rotX += yoffset * _sensitivity;

        if(_rotX > 89.0f) _rotX = 89.0f;
        if(_rotX < -89.0f) _rotX = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(_rotY)) * cos(glm::radians(_rotX));
        front.y = sin(glm::radians(_rotX));
        front.z = sin(glm::radians(_rotY)) * cos(glm::radians(_rotX));
        _cameraFront = glm::normalize(front);

        //_position.y = 0;

        _viewMatrix = glm::lookAt(_position, _position + _cameraFront, _cameraUp);
    }

    void Camera::CreateViewMatrix () {
         _viewMatrix = glm::mat4(1.0f);

        /* Rotation */
        _viewMatrix = glm::rotate(_viewMatrix, glm::radians(_rotX), glm::vec3(1.f, 0.f, 0.f));
        _viewMatrix = glm::rotate(_viewMatrix, glm::radians(_rotY), glm::vec3(0.f, 1.f, 0.f));
        _viewMatrix = glm::rotate(_viewMatrix, glm::radians(_rotZ), glm::vec3(0.f, 0.f, 1.f));

        /* Translate */
        glm::vec3 negativeCameraPos = glm::vec3(-_position.x, -_position.y, -_position.z);
        _viewMatrix = glm::translate(_viewMatrix, negativeCameraPos);
    }
}
