#include <glm/gtc/type_ptr.hpp>

#include "World/Block/ChunkBlock.h"

namespace World {
    ChunkBlock::ChunkBlock (const int & id, const int & index) {
        _blockID = id;
        _blockIndex = index;
    }

    void ChunkBlock::SetBooleans (bool front, bool back, bool left, bool right, bool top, bool bottom) {
        _front = front;
        _back = back;
        _left = left;
        _right = right;
        _top = top;
        _bottom = bottom;
    }

    void ChunkBlock::PrintMesg () {
        std::cout << "ChunkBlock at :" << _blockIndex << std::endl;
        std::cout << _front << " " << _back << " " << _left << " " << _right << " " << _top << " " << _bottom << std::endl;
        std::cout << "Visibility: " << !IsVisible() << std::endl;
    }
}
