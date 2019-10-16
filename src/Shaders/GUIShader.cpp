#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <iostream>

#include "Shaders/ShaderProgram.h"
#include "Shaders/GUIShader.h"

namespace Shaders {
    GUIShader::GUIShader(const std::string & pathToVertexShader, const std::string & pathToFragmentShader) { // : ShaderProgram(pathToVertexShader, pathToFragmentShader)

        _programID = glCreateProgram();
        CreateVertexShader(pathToVertexShader);
        CreateFragmentShader(pathToFragmentShader);

        glAttachShader(_programID, _vertexID);
        glAttachShader(_programID, _fragmentID);
        glLinkProgram(_programID);
        glValidateProgram(_programID);

        int success;
        char infoLog[512];
        glGetProgramiv(_programID, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(_programID, 512, NULL, infoLog);
            std::cout << pathToVertexShader << " + " << pathToFragmentShader << std::endl;
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(_vertexID);
        glDeleteShader(_fragmentID);
    }
}
