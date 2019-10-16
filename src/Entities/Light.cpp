#include <glm/gtc/type_ptr.hpp>

#include "Entities/Light.h"

namespace Entities {
    Light::Light (glm::vec3 pos, glm::vec3 col) {
        _position = pos;
        _color = col;
    }
}