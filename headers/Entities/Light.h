#ifndef LIGHT_H
#define LIGHT_H

#include <glm/gtc/type_ptr.hpp>

/*
    Light entity : define a point light in the game with:
        - a color
        - a position

    This class is not a child of the entity class 
    -> we don't need too much methods for the point light
*/

namespace Entities {
    class Light {
        private:
            glm::vec3 _position, _color;

        public:
            Light(){};
            Light(glm::vec3 pos, glm::vec3 color);
            ~Light(){};

            glm::vec3 GetPosition () const {return _position;}; 
            glm::vec3 GetColor () const {return _color;};

    };
}

#endif