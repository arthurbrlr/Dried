#ifndef LOADER_H
#define LOADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

/*
    Loader singleton

    Used to load complex meshes in VAOs (chunk meshes, entities [not yet...])
*/

namespace RenderEngine {
    class Loader {
        private:
            std::vector<unsigned int> _vaos, _vbos;

            static Loader* instance;
            Loader(){};

            unsigned int CreateVAO ();
            void BindVAO (unsigned int vaoID);
            unsigned int BindIndicesBuffer (const std::vector<unsigned int> & indices, GLenum mode);
            unsigned int StoreDataInAttributeList (int attributeNumber,
                                                   int coordinateSize,
                                                   GLenum mode,
                                                   const std::vector<float> & data);
            void UnbindVAO();

        public:
            Loader(Loader const&) = delete;
            void operator=(Loader const&) = delete;
            static Loader& GetInstance () {
                static Loader instance;
                return instance;
            };

            unsigned int LoadToVAO (const std::vector<float> & vertices);
            std::vector<unsigned int> LoadToBuffers (const std::vector<unsigned int> & indices,
                                                     const std::vector<float> & vertices,
                                                     const std::vector<float> & textureCoord,
                                                     const std::vector<float> & normals,
                                                     const std::vector<float> & colors,
                                                     GLenum indicesMode,
                                                     GLenum verticesMode);
            void ChangeIndicesBuffer (const std::vector<unsigned int> & newIndices,
                                      unsigned int vaoToChange,
                                      unsigned int vboToChange);
            void ChangeDataInAttributeList (const std::vector<float> & data,
                                            int attributeNumber,
                                            int coordinateSize,
                                            unsigned int vaoToChange,
                                            unsigned int vboToChange);
            void BindVertexAttributes();
            void UnbindVertexAttributes();
            void CleanUp ();
            unsigned int LoadTexture (const std::string & path, bool isTransparent);
    };
}



#endif
