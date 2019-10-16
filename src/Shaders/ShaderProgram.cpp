#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <iostream>

#include "Entities/Light.h"
#include "Shaders/ShaderProgram.h"

namespace Shaders {
    ShaderProgram::ShaderProgram (const std::string & pathToVertexShader, const std::string & pathToFragmentShader) {
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
    }

    void ShaderProgram::CreateVertexShader (const std::string & path) {

        std::string code = ReadShader(path);
        const char* src = code.c_str();

        _vertexID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(_vertexID, 1, &src, NULL);
        glCompileShader(_vertexID);

        int success;
        char infoLog[512];
        glGetShaderiv(_vertexID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(_vertexID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    void ShaderProgram::CreateFragmentShader (const std::string & path) {

        std::string code = ReadShader(path);
        const char* src = code.c_str();

        _fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(_fragmentID, 1, &src, NULL);
        glCompileShader(_fragmentID);

        int success;
        char infoLog[512];
        glGetShaderiv(_fragmentID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(_fragmentID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    std::string ShaderProgram::ReadShader (const std::string & path) {
        std::string shaderCode;
        std::string line;
        std::ifstream shaderFile(path);

        if (!shaderFile) {
            std::cout << "ERROR::SHADER::READING_FILE: " << path << std::endl;
        }

        while (getline(shaderFile, line)) {
            shaderCode += line;
            shaderCode += "\n";
        }
        shaderFile.close();
        return shaderCode;
    }

    void ShaderProgram::CleanUp() {
        glDetachShader(_programID, _vertexID); glDeleteShader(_vertexID);
        glDetachShader(_programID, _fragmentID); glDeleteShader(_fragmentID);
        glDeleteProgram(_programID);
        glUseProgram(0);
    }

    void ShaderProgram::SetInt (const std::string & name, const int & value) {
        glUniform1i(glGetUniformLocation(_programID, name.c_str()), value);
    }

    void ShaderProgram::SetBool (const std::string & name, const bool & value) {
        glUniform1i(glGetUniformLocation(_programID, name.c_str()), (int)value);
    }

    void ShaderProgram::SetFloat (const std::string & name, const float & value) {
        glUniform1f(glGetUniformLocation(_programID, name.c_str()), value);
    }

    void ShaderProgram::SetVec2 (const std::string & name, const glm::vec2 & value) {
        glUniform2f(glGetUniformLocation(_programID, name.c_str()), value.x, value.y);
    }

    void ShaderProgram::SetVec3 (const std::string & name, const glm::vec3 & value) {
        glUniform3f(glGetUniformLocation(_programID, name.c_str()), value.x, value.y, value.z);
    }

    void ShaderProgram::SetColor (const std::string & name, const glm::vec4 & value) {
        glUniform4f(glGetUniformLocation(_programID, name.c_str()), value.x, value.y, value.z, value.w);
    }

    void ShaderProgram::SetMatrix4 (const std::string & name, const glm::mat4 & value) {
        glUniformMatrix4fv(glGetUniformLocation(_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    void ShaderProgram::LoadTransformationMatrix (const glm::mat4 & value) {
        glUniformMatrix4fv(glGetUniformLocation(_programID, "transform"), 1, GL_FALSE, glm::value_ptr(value));
    }

    void ShaderProgram::LoadMainLight (const Entities::Light & light) {
        SetVec3("mainLightPosition", light.GetPosition());
        SetVec3("mainLightColor", light.GetColor());
    }
}
