#ifndef WORLD_H
#define WORLD_H

#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

#include <thread>
#include <mutex>

#include "Util/Config.h"
#include "Util/util.h"
#include "Util/unorderedHash.h"

#include "BasicChunk.h"

namespace World {
    class World {
        private:
            bool _isGenerated = false, _isRunning = false;

                // chunks that are builded
            std::unordered_map<glm::vec3, BasicChunk> _worldChunks;
                // columns already existing
            std::unordered_map<glm::vec3, int> _columns;
            std::mutex _mutex;
                // threads responsible for building the world
            std::vector<std::thread> _loadingWorldThreads;
                // arrays used to load the chunks around the player in a spiral
            std::vector<int> _neighX, _neighZ;

                // #singleton patern (1/2)
            static World* instance;
            World(){};
            ~World(){};
                // #singleton patern

            void BuildSpiral ();
            //std::vector<int> CalculateColumnHeights (int x, int z);
            std::unordered_map<glm::vec3, BasicChunk>::const_iterator ChunkAt (glm::vec3 chunkPos);
            std::unordered_map<glm::vec3, BasicChunk>::iterator ChunkAtNC (glm::vec3 chunkPos);
            bool ColumnAtPosExists (const glm::vec3 & pos);

        public:
                // #singleton patern (2/2)
            World(World const&) = delete;
            void operator=(World const&) = delete;
            static World& GetInstance () {
                static World instance;
                return instance;
            };
                // #singleton patern

            void BuildWorld ();
            void BuildChunkColumn (int x, int z);
            void BuildAroundPlayer ();
            void CloseWorld ();

            int GetHeightAtPos (int x, int z);
            bool IsGenerated () const {return _isGenerated;};

            std::unordered_map<glm::vec3, BasicChunk> & GetChunks () {return _worldChunks;};
            //BlockData GetBlockAtPos (const glm::vec3 & blockPos);
            bool BlockAtPosExists (const glm::vec3 & blockWorldPos);
            void GetBlockAtPos (const glm::vec3 & blockWorldPos);
            void RemoveBlockAtPos (const glm::vec3 & blockWorldPos);
    };
}



#endif
