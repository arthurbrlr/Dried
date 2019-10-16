    /* OpenGL */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

#include "Util/maths.h"

#include "GraphicInterface/GUIElement.h"
#include "RenderEngine/Loader.h"

#include "RenderEngine/GUIRenderer.h"

namespace RenderEngine {
    GUIRenderer::GUIRenderer (Shaders::ShaderProgram* shader)  : _shader(shader) {
        _vaoID = Loader::GetInstance().LoadToVAO(quad);
    }

    void GUIRenderer::Render () {
        _shader->Start();
        glBindVertexArray(_vaoID);
        glEnableVertexAttribArray(0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for (int i = 0; i < _elements.size(); i++) {
            glActiveTexture(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, _elements[i]._textureID);
            _shader->LoadTransformationMatrix(Util::CreateTransformationMatrix(_elements[i]._position, _elements[i]._scale));
            glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.size()/2);
        }
        glDisable(GL_BLEND);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
        _shader->Stop();
    }

    void GUIRenderer::CleanUp () {
        _shader->CleanUp();
        DeleteElements();
    }

    void GUIRenderer::AddElement (GraphicInterface::GUIElement element) {
        _elements.push_back(element);
    }

    void GUIRenderer::DeleteElements () {
        _elements.clear();
    }
}
