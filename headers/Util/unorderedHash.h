#ifndef UNORDERED_HASH_H
#define UNORDERED_HASH_H

#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include <iostream>

/*
    Hash functions for glm::vec3 (needed to use unordered_maps)
*/

namespace std {

    template <>
    struct hash<glm::vec3> {
        std::size_t operator () (const glm::vec3& vector) const {
            size_t res = 17;
            res = res * 31 + std::hash<float>()( vector.x );
            res = res * 31 + std::hash<float>()( vector.y );
            res = res * 31 + std::hash<float>()( vector.z );
            return res;
        }
    };
}

#endif
