#ifndef RAYCAST_H
#define RAYCAST_H

#include <glm/gtc/type_ptr.hpp>

#include "Entities/Camera.h"

/*
    Raycast class

    Custom raycast used to interact with the world
    In this example, it also handles the "mining cooldown" (5 frames) to avoid
    updating meshes every frame
*/

namespace Interactions {

    class Raycast {
        private:
            glm::vec3 _ray;
            glm::mat4 _projectionMatrix, _viewMatrix;
            int _frameUntilMining = 5;

            glm::vec3 CalculateRay ();
            glm::vec2 MouseToNormalizedCoords (const float & mouseX, const float & mouseY);
            glm::vec4 ToEyeCoords (const glm::vec4 & clipCoords); 
            glm::vec3 ToWorldCoords (const glm::vec4 & eyeCoords);

        public:
            Raycast () {};
            Raycast (const glm::mat4 & pMat) : _projectionMatrix(pMat) {
                _viewMatrix = Entities::Camera::GetInstance().GetViewMatrix();
            };
            ~Raycast () {};

            void Update ();

            glm::vec3 GetRay () const {return _ray;};

    };
}

#endif