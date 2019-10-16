/* OpenGL */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "RenderEngine/Loader.h"
#include "Textures/TextureAtlas.h"

namespace Textures {
    void TextureAtlas::Init (const std::string & path) {
        _atlasID = RenderEngine::Loader::GetInstance().LoadTexture(path, false);
    }

    void TextureAtlas::UseAtlas (const int & index) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _atlasID);
    }
}
