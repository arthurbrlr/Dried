    /* OpenGL */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>

#include "Shaders/ComputeShader.h"

namespace Shaders {
    void ComputeShader::Load (const std::string & path) {
        _programID = glCreateProgram();
        CreateTexture();
        InititializeWorkGroup();
        LoadComputeShader(path);
    }

    
    void ComputeShader::Start () {
        glUseProgram(_programID);
        std::cout << "Dispatch compute" << std::endl;
        glDispatchCompute((unsigned int)512, (unsigned int)512, 1);
        std::cout << "Waiting" << std::endl;
        glMemoryBarrier(GL_ALL_BARRIER_BITS);
        std::cout << "Shader finished" << std::endl;
    }

    void ComputeShader::Stop () {
        glUseProgram(0);
    }

    void ComputeShader::CleanUp () {
        glDetachShader(_programID, _computeID); glDeleteShader(_computeID);
        glDeleteProgram(_programID);
        glUseProgram(0);
    }


    void ComputeShader::CreateTexture () {
        std::cout << "Creating texture" << std::endl;
        int tex_w = 512, tex_h = 512;
        glGenTextures(1, &_textID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _textID);
        std::cout << "Parameters" << std::endl;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        std::cout << "TexImage2D" << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, tex_w, tex_h, 0, GL_RGBA, GL_FLOAT, NULL);
        //glTexStorage2D(GL_TEXTURE_2D, 1,GL_RGBA32F, tex_w, tex_h);
        std::cout << "Binding texture" << std::endl;
        glBindImageTexture(0, _textID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        std::cout << "Texture created" << std::endl;
    }


    void ComputeShader::LoadComputeShader (const std::string & path) {

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

        const char* src = shaderCode.c_str();
        int success;
        char infoLog[512];

        _computeID = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(_computeID, 1, &src, NULL);
        glCompileShader(_computeID);
        glGetShaderiv(_computeID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(_computeID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPUTE::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        glAttachShader(_programID, _computeID);
        glLinkProgram(_programID);
        glValidateProgram(_programID);
        glGetProgramiv(_programID, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(_programID, 512, NULL, infoLog);
            std::cout << path << std::endl;
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }


    void ComputeShader::InititializeWorkGroup () {
        std::cout << "Initializing work group" << std::endl;

        int work_grp_cnt[3];
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);
        std::cout << "max global (total) work group size x: " << work_grp_cnt[0] << " y: " << work_grp_cnt[1] << " z: " << work_grp_cnt[2] << std::endl;


        int work_grp_size[3];
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);
        std::cout << "max local (in one shader) work group sizes x: " << work_grp_size[0] << " y: " << work_grp_size[1] << " z: " << work_grp_size[2] << std::endl;

        int work_grp_inv;
        glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
        std::cout << "max local work group invocations " << work_grp_inv << std::endl;
    }
}