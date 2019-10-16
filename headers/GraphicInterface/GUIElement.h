#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <glm/gtc/type_ptr.hpp>

/*
    GUI element class

    Represent a simple textured quad drawn above the game
*/

namespace GraphicInterface {
    struct GUIElement {
        glm::vec2 _position, _scale;
        unsigned int _textureID;

        GUIElement (unsigned int textureID, glm::vec2 pos, glm::vec2 scale) : _textureID(textureID), _position(pos), _scale(scale) {};
    };
}

#endif
