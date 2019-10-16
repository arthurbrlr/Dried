#ifndef MESHBUILDER_H
#define MESHBUILDER_H

#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <mutex>

#include "World/ChunkMesh.h"

/*
    MeshBuilder singleton

    Singleton responsible for building and updating chunk meshes
*/

namespace RenderEngine {

        // Struct used to keep track of which chunk has a mesh or not
    struct RenderData {
        World::ChunkMesh mesh;
        bool isBuilded;

        RenderData (const World::ChunkMesh & m) : mesh(m), isBuilded(false) {};
    };

    class MeshBuilder {
        private:
            std::vector<int> _batch;
            std::vector<RenderData> _allMeshs;

            static MeshBuilder* instance;
            MeshBuilder(){};

        public:
            MeshBuilder(MeshBuilder const&) = delete;
            void operator=(MeshBuilder const&) = delete;
            static MeshBuilder& GetInstance () {
                static MeshBuilder instance;
                return instance;
            };

            std::mutex _lock;

            void BuildNewMeshPerFrame ();
            void RenderWorld ();
            void AddMeshToBatch (const World::BasicChunk & chunk, bool updating);
    };
}

#endif
