#ifndef ENTITY_H
#define ENTITY_H

#include <glm/gtc/type_ptr.hpp>

/*
    Entity class, base class for every entity in the game (no shit sherlock)

    Define some basic behaviour of entities like:
        - Set/Get position
        - Set/Get rotation
        - Set/Get scale
        - Calculate the transformation matrix of the entity
*/

namespace Entities {
    
    class Entity {
        protected:
            glm::vec3 _position;
            float _rotX = 0.f, _rotY = 0.f, _rotZ = 0.f, _scale = 1.f;

        public:
            Entity() : _position(glm::vec3(0.f, 0.f, 0.f)) {};
            Entity(glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
                : _position(position), _rotX(rotX), _rotY(rotY), _rotZ(rotZ), _scale(scale) {};
            ~Entity(){};

                /* Setters */
            void SetPosition (const glm::vec3 & position) {_position = position;};
            void SetRX (const float & rx) {_rotX = rx;};
            void SetRY (const float & ry) {_rotY = ry;};
            void SetRZ (const float & rz) {_rotZ = rz;};
            void SetScale (const float & scale) {_scale = scale;};

                /* Getters */
            glm::vec3 GetPosition () const {return _position;};
            glm::mat4 GetTransformationMatrix () const;
            glm::vec3 GetRotation () {return glm::vec3(_rotX, _rotY, _rotZ);};
            float GetScale () const {return _scale;}; 
    };
}

#endif
