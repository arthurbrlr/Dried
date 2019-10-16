#ifndef CHUNK_BLOCK_H
#define CHUNK_BLOCK_H

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "BlockDataBase.h"

/*
    Chunk Block class

    Represent a block in a chunk
    Used to store the visibility, type, id of a block, etc...
*/

namespace World {
    class ChunkBlock {
        private:
            int _blockID, _blockIndex;
            bool _front, _back, _left, _right, _top, _bottom;
            int _lightLevel;

        public:
            ChunkBlock(){};
            ChunkBlock(const int & id, const int & index);
            ~ChunkBlock(){};

            void PrintMesg ();
                /* Setters */
            void SetBooleans (bool front, bool back, bool left, bool right, bool top, bool bottom);
                /* Getters */
                // return true if the block has to be hidden
            bool IsVisible () const {return !(_front && _back && _bottom && _top && _left && _right);};
            int GetID () const {return _blockID;};
            int GetIndex () const {return _blockIndex;};
            std::vector<bool> GetBooleans () const {return {_front, _back, _left, _right, _top, _bottom};};
    };
}

namespace std {
    template <>
    struct hash<World::ChunkBlock> {
        std::size_t operator () (const World::ChunkBlock& cBlock) const {
            size_t res = 17;
            res = res * 31 + std::hash<int>()( cBlock.GetIndex() );
            return res;
        }
    };
}

#endif
