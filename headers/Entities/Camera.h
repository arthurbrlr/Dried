#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "Entities/Entity.h"

/*
    Camera singleton

    Used to control the view of the world
    In this program, the camera IS the player (there's no player entity yet)
*/

namespace Entities {

    class Camera : public Entity {
        private:
            glm::mat4 _viewMatrix;
            glm::vec3 _cameraFront, _cameraUp;

            float _moveSpeed = 0.15f, _sensitivity = 0.15f;
            bool _firstMouse = true, _freezed = false;
            float _lastX = 400, _lastY = 300;
            double _mFreezedX, _mFreezedY;

            static Camera* instance;
            Camera(){};

            void CreateViewMatrix ();

        public:
            Camera(Camera const&) = delete;
            void operator=(Camera const&) = delete;
            static Camera& GetInstance () {
                static Camera instance;
                return instance;
            };

            void Init (const glm::vec3 & initialPosition);
            void ProcessInputs (GLFWwindow* window);

                /* Getters */
            glm::mat4 GetViewMatrix () const {return _viewMatrix;};
            glm::vec3 GetChunkPosition ();
    };
}

#endif
