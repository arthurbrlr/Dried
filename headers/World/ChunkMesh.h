#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

#include "BasicChunk.h"

namespace World {
    class ChunkMesh {
        private:
            BasicChunk _chunk;
            unsigned int _vaoID;
            unsigned int _vboIndicesID, _vboVerticesID, _vboTexCID, _vboNormalID, _vboColorID;

            std::vector<unsigned int> _meshIndices;
            std::vector<float> _meshVertices;
            std::vector<float> _meshTexCoord;
            std::vector<float> _meshNormals;
            std::vector<float> _meshColors;

        public:
            ChunkMesh(){};
            ChunkMesh(const BasicChunk & chunk);
            ~ChunkMesh(){};

            void BuildMesh ();
            void LoadMesh ();
            void UpdateMesh ();
            void RemoveBlockAt (const glm::vec3 & pos);

            void RenderMesh ();
            glm::vec3 GetChunkPosition () const {return _chunk.GetPosition();};
    };
}

#endif
