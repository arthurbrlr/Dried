#ifndef GUISHADER_H
#define GUISHADER_H

#include <string>

#include "ShaderProgram.h"

/*
    GUI Shader class 
    
    Shader program used to render GUI elements on screen
*/

namespace Shaders {
    class GUIShader : public ShaderProgram {
        
        public:
            GUIShader(){};
            GUIShader(const std::string & pathToVertexShader, const std::string & pathToFragmentShader);
            ~GUIShader(){};
    };
}

#endif
