#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include <vector>
#include <mutex>
#include <unordered_map>
#include <string>

#include "lua/lua.hpp"

#include "Util/util.h"
#include "Util/OpenSimplexNoise.h"

#include "World/Block/ChunkBlock.h"

namespace World {
    struct BiomeGenerationData {
        int biomeID;
        float offsetX, offsetZ, frequencyX, frequencyZ;
        int heightOffset, preprocessingFunction;
        float multiplier;
        int topBlockID, underBlockID;
    };

    class WorldGenerator {
        private:
            int _seed;
            float _biomeFX = 200.f, _biomeFZ = 205.f;
            OpenSimplexNoise _noise, _moistureNoise;
            std::unordered_map<std::string, BiomeGenerationData> _biomes;
            std::vector<std::string> _biomeNames;

            bool CheckLua (lua_State* L, int r);

            static WorldGenerator* instance;
            WorldGenerator();
            ~WorldGenerator(){};

        public:
            WorldGenerator(WorldGenerator const&) = delete;
            void operator=(WorldGenerator const&) = delete;
            static WorldGenerator& GetInstance () {
                static WorldGenerator instance;
                return instance;
            };

            std::mutex _lock;

            void SetSeed (int seed = 0) {_seed = seed; _noise = OpenSimplexNoise(_seed); _moistureNoise = OpenSimplexNoise(_seed + Util::RandomInt(-1000, 1111));};

            float GetBiomeAt (const int & block_X, const int & block_Z);
            int GetBlockAt (const int & block_X, const int & block_Y, const int & block_Z);
            float GetHeight (const float & block_X, const float & block_Z);
            int GetHeight (const float & block_X, const float & block_Z, const BiomeGenerationData & biome);
            std::vector<int> GetHeights (const int & chunk_X, const int & chunk_Z);

            void SetBiomeFX (const float & nBFX) {_biomeFX = nBFX;};
            void SetBiomeFZ (const float & nBFZ) {_biomeFZ = nBFZ;};
    };

}

namespace std {
    template <>
    struct hash<World::BiomeGenerationData> {
        std::size_t operator () (const World::BiomeGenerationData & data) const {
            size_t res = 17;
            res = res * 31 + std::hash<int>()( data.biomeID );
            res = res * 31 + std::hash<float>()( data.offsetX );
            res = res * 31 + std::hash<float>()( data.offsetZ);
            res = res * 31 + std::hash<float>()( data.multiplier);
            res = res * 31 + std::hash<float>()( data.frequencyX);
            res = res * 31 + std::hash<float>()( data.frequencyZ);
            return res;
        }
    };
}

#endif