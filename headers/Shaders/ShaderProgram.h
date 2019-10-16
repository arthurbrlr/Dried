#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#include "Entities/Light.h"

/*
    Shader Program class

    Generic Shader class from which every simple shader program extend
    Use a vertex shader and a fragment shader
    Read them from a plain text file so it can be easily modified
*/

namespace Shaders {
    class ShaderProgram {
        protected:
            int _programID, _vertexID, _fragmentID;

            void CreateVertexShader (const std::string & path);
            void CreateFragmentShader (const std::string & path);
            std::string ReadShader (const std::string & path);

        public:
            ShaderProgram(){};
            ShaderProgram (const std::string & pathToVertexShader, const std::string & pathToFragmentShader);
            ~ShaderProgram(){};

                /* Utility */
            virtual void Start () {glUseProgram(_programID);};
            virtual void Stop (){glUseProgram(0);};
            void CleanUp ();

                /* Getter */
            int GetID () {return _programID;};

                /* Setters for uniforms */
            void SetInt (const std::string & name, const int & value);
            void SetBool (const std::string & name, const bool & value);
            void SetFloat (const std::string & name, const float & value);
            void SetVec2 (const std::string & name, const glm::vec2 & value);
            void SetVec3 (const std::string & name, const glm::vec3 & value);
            void SetColor (const std::string & name, const glm::vec4 & value);
            void SetMatrix4 (const std::string & name, const glm::mat4 & value);
            void LoadTransformationMatrix (const glm::mat4 & value);
            void LoadMainLight (const Entities::Light & light);
    };
}

#endif
