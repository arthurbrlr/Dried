#include <glm/gtc/type_ptr.hpp>

#include "Entities/Entity.h"

namespace Entities {
    glm::mat4 Entity::GetTransformationMatrix () const {
        glm::mat4 tMatrix = glm::mat4(1.0f);

        /* Translate */
        tMatrix = glm::translate(tMatrix, _position);

        /* Rotations */
        tMatrix = glm::rotate(tMatrix, glm::radians(_rotX), glm::vec3(1.f, 0.f, 0.f));
        tMatrix = glm::rotate(tMatrix, glm::radians(_rotY), glm::vec3(0.f, 1.f, 0.f));
        tMatrix = glm::rotate(tMatrix, glm::radians(_rotZ), glm::vec3(0.f, 0.f, 1.f));

        /* Scaling */
        tMatrix = glm::scale(tMatrix, glm::vec3(_scale, _scale, _scale));

        return tMatrix;
    }
}
