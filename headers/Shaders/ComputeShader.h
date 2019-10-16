#ifndef COMPUTE_SHADER_H
#define COMPUTE_SHADER_H

#include <string>

#include "ShaderProgram.h"

/*
    Compute Shader Class

    I tried to implement compute shaders in order to
    calculate the world generation on the GPU but
    unfortunately CS are not supported on macOS's OpenGL

    So this class is useless
*/

namespace Shaders {
    class ComputeShader {
        private:
            int _programID, _computeID;
            unsigned int _textID;

            static ComputeShader* instance;
            ComputeShader(){};

        public:
            ComputeShader(ComputeShader const&) = delete;
            void operator=(ComputeShader const&) = delete;
            static ComputeShader& GetInstance () {
                static ComputeShader instance;
                return instance;
            };

            void Load (const std::string & path);

            void Start ();
            void Stop ();
            void CleanUp ();

            void CreateTexture ();
            void InititializeWorkGroup ();
            void LoadComputeShader (const std::string & path);

            unsigned int GetTexture () const {return _textID;};

    };
}


#endif