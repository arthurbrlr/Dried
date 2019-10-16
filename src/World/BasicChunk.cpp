#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Util/Config.h"

#include "World/World.h"
#include "World/WorldGenerator.h"
#include "World/Block/ChunkBlock.h"
#include "World/BasicChunk.h"

namespace World {
    BasicChunk::BasicChunk (glm::vec3 wPos, int id) : _chunkPosition(wPos), _chunkID(id) {

        int c = 0;
        
        for (int i = 0; i < CHUNKSIZE+1; i++)
        for (int j = 0; j < CHUNKSIZE+1; j++)
        for (int k = 0; k < CHUNKSIZE+1; k++) {

            glm::vec3 bPos = glm::vec3(i, k, j) + glm::vec3(_chunkPosition.x * (CHUNKSIZE+1), _chunkPosition.y * (CHUNKSIZE+1), _chunkPosition.z * (CHUNKSIZE+1));
            int blockID = WorldGenerator::GetInstance().GetBlockAt(bPos.x, bPos.y, bPos.z);
            if (blockID == 0) continue;

            ChunkBlock newBlock(blockID, c);
            _chunkBlocks.emplace(bPos, newBlock);

            c++;
        }

        if (c == 0) _isEmpty = true;
        else _isEmpty = false;
    }


    void BasicChunk::UpdateChunkBlocks () {
        for (auto & it : _chunkBlocks) {
            glm::vec3 pos = it.first;
            bool front  = BlockAtPosExists(glm::vec3(pos.x, pos.y, pos.z-1)),
                 back   = BlockAtPosExists(glm::vec3(pos.x, pos.y, pos.z+1)),
                 left   = BlockAtPosExists(glm::vec3(pos.x+1, pos.y, pos.z)),
                 right  = BlockAtPosExists(glm::vec3(pos.x-1, pos.y, pos.z)),
                 top    = BlockAtPosExists(glm::vec3(pos.x, pos.y+1, pos.z)),
                 bottom = BlockAtPosExists(glm::vec3(pos.x, pos.y-1, pos.z));
             it.second.SetBooleans(front, back, left, right, top, bottom);
        }
    }


    bool BasicChunk::BlockAtPosExists (const glm::vec3 & pos) {
        std::unordered_map<glm::vec3, ChunkBlock>::const_iterator it = _chunkBlocks.find(pos);
        if (it != _chunkBlocks.end()) {
            return true;
        } else {
            return false;
        }
    }


    bool BasicChunk::CheckFromNeighbour (const glm::vec3 & pos) {
        std::unordered_map<glm::vec3, ChunkBlock>::const_iterator it = _chunkBlocks.find(pos);
        if (it == _chunkBlocks.end()) {
            return false;
        } else {
            return true;
        }
    }


    int BasicChunk::GetBlockAt (const glm::vec3 & pos) const {
        std::unordered_map<glm::vec3, ChunkBlock>::const_iterator it = _chunkBlocks.find(pos);
        return it->second.GetID();
    }


    void BasicChunk::RemoveBlockAt (const glm::vec3 & pos) {
        std::unordered_map<glm::vec3, ChunkBlock>::const_iterator it = _chunkBlocks.find(pos);
        if (it != _chunkBlocks.end()) {
            _chunkBlocks.erase(it);
        }
    }

    int BasicChunk::GetHeightAtPos (int x, int z) {
        for (int y = CHUNKSIZE; y > -1; y--) {
            for (auto & it : _chunkBlocks) {
                if (it.first == glm::vec3(x, y, z)) {
                    return y + 1;
                }
            }
        }
        return 0.;
    }
}
