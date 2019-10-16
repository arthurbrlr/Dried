#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include <vector>

#include "Shaders/ShaderProgram.h"
#include "GraphicInterface/GUIElement.h"

/*
    GUI Renderer class

    Used to render every GUI element
*/

namespace RenderEngine {
    class GUIRenderer {
        private:
            std::vector<GraphicInterface::GUIElement> _elements;
            Shaders::ShaderProgram* _shader;
            int _vaoID;

            std::vector<float> quad = {-1., 1., -1., -1., 1., 1., 1., -1.};

        public:
            GUIRenderer (){};
            GUIRenderer (Shaders::ShaderProgram* shader);
            ~GUIRenderer(){};

            void Render ();
            void CleanUp ();
            void AddElement (GraphicInterface::GUIElement element);
            void DeleteElements ();
    };
}

#endif
