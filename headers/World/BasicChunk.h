#ifndef CHUNK_H
#define CHUNK_H

#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include <vector>

#include "Util/unorderedHash.h"

#include "Block/Block.h"
#include "Block/ChunkBlock.h"

namespace World {
    class BasicChunk {
        private:
            int _chunkID;
            bool _isEmpty;
            glm::vec3 _chunkPosition;
            std::unordered_map<glm::vec3, ChunkBlock> _chunkBlocks;

        public:
            BasicChunk(){};
            BasicChunk(glm::vec3 wPos, int id);
            ~BasicChunk(){};

            void UpdateChunkBlocks ();
            void RemoveBlockAt (const glm::vec3 & pos);

            int GetHeightAtPos (int x, int z);
            bool BlockAtPosExists (const glm::vec3 & pos);
            bool CheckFromNeighbour (const glm::vec3 & pos);

            std::unordered_map<glm::vec3, ChunkBlock> & GetChunkBlocks () {return _chunkBlocks;};
            glm::vec3 GetPosition () const {return _chunkPosition;};
            int GetBlockAt (const glm::vec3 & pos) const;
    };
}

namespace std {
    template <>
    struct hash<World::BasicChunk> {
        std::size_t operator () (const World::BasicChunk& chunk) const {
            size_t res = 17;
            res = res * 31 + std::hash<int>()( chunk.GetPosition().x );
            res = res * 31 + std::hash<int>()( chunk.GetPosition().y );
            res = res * 31 + std::hash<int>()( chunk.GetPosition().z );
            return res;
        }
    };
}

#endif
