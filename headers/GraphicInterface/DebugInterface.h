#ifndef DEBUG_INTERFACE_H
#define DEBUG_INTERFACE_H
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

/*
    DebugInterface singleton : GUI using imgui 
    display debug informations on the screen

    examples: 
        - time per frame
        - graph of the time / frame for the last 10 seconds
*/

namespace GraphicInterface {
    class DebugInterface {
        private:
            bool _show = true;
            bool _lines = false;
            int _shaderUsed = 0, _texCUsed = 0;
            std::vector<float> _frameDurationVector;
            float _posX = 0, _posY = 0, _posZ = 0, _maxFrameTime = 0;
            int _terrainHeight = 0;


                /* Terrain Editor */
            bool _updateTerrainEditor = false;
            bool _displayTerrainEditorWindow = true;
            float bfs[2] = {200.f, 205.f};

            static DebugInterface* instance;
            DebugInterface(){};

        public:
            DebugInterface(DebugInterface const&) = delete;
            void operator=(DebugInterface const&) = delete;
            static DebugInterface& GetInstance () {
                static DebugInterface instance;
                return instance;
            };

            void Init ();
            void Update ();
            void Render ();
            void Clear ();

            void TerrainEditorWindow ();

                /* Setters */
            void SetVisibility (const bool & vis) {_show = vis;};
            void DisplayTerrainEditor (const bool & b) {_displayTerrainEditorWindow = b;};


                /* Getters */
            int GetShaderUsed () const {return _shaderUsed;};
            int GetSliderValue () const {return _texCUsed;};
            bool UpdateTerrainEditor () {
                if (_updateTerrainEditor) {
                    _updateTerrainEditor = false;
                    return true;
                }
                return _updateTerrainEditor;
            };
    };
}

#endif
