#ifndef BLOCK_DATABASE_H
#define BLOCK_DATABASE_H

#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <string>
#include <vector>

#include "Shaders/ShaderProgram.h"
#include "Block.h"

/*
    Block Database singleton

    Used to store the data about all the blocks in the game (block data struct)
    All BlockDatas can be found in the /res/blocks folder
*/

namespace World {
    struct BlockData {
        std::string _name;
        int _blockID;
        glm::vec2 _topTextCoord, _sideTextCoord, _bottomTextCoord;
        std::vector<int> _loots;
        Shaders::ShaderProgram* _shader = 0;

        BlockData(){};
        BlockData(Shaders::ShaderProgram* shader) : _shader(shader) {};
        ~BlockData(){};

        Shaders::ShaderProgram* GetShader () const {return _shader;};
        int GetID () const {return _blockID;};
            // the following methods return the texture coordinates of a face in the texture atlas  
        glm::vec2 GetTopTextCoord () const {return _topTextCoord;};
        glm::vec2 GetSideTextCoord () const {return _sideTextCoord;};
        glm::vec2 GetBottomTextCoord () const {return _bottomTextCoord;};
    };

    class BlockDataBase {
        private:
            std::unordered_map<int, BlockData> _database;

            static BlockDataBase* instance;
            BlockDataBase(){};

            void AddBlockData (const std::string & pathToBlockFile, Shaders::ShaderProgram* shader);

        public:
            BlockDataBase(BlockDataBase const&) = delete;
            void operator=(BlockDataBase const&) = delete;
            static BlockDataBase& GetInstance () {
                static BlockDataBase instance;
                return instance;
            };

            void LoadBlockDataBase (const std::string & databasePath, Shaders::ShaderProgram* shader);

            BlockData GetBlockDataWithId (int blockID) {return _database[blockID];};
    };
}

namespace std {
    template <>
    struct hash<World::BlockData> {
        std::size_t operator () (const World::BlockData& bdata) const {
            size_t res = 17;
            res = res * 31 + std::hash<int>()( bdata._blockID );
            return res;
        }
    };
}

#endif
