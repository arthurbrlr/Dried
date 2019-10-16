#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include <string>

#include "ShaderProgram.h"

/*
    Terrain shader class

    Shader program used to render the world
*/

namespace Shaders {
    class TerrainShader : public ShaderProgram {

        public:
            TerrainShader(){};
            TerrainShader(const std::string & pathToVertexShader, const std::string & pathToFragmentShader);
            ~TerrainShader(){};
    };
}

#endif
