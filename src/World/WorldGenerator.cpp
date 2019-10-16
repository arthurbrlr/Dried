#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "lua/lua.hpp"

#include "Util/Config.h"
#include "Util/util.h"

#include "World/Block/ChunkBlock.h"
#include "World/WorldGenerator.h"

namespace World {

    WorldGenerator::WorldGenerator () {
        
        int biomeNb = 0;

        lua_State* L = luaL_newstate();
        luaL_openlibs(L);

        int r = luaL_dofile(L, "res/world/biomeData.lua");
        if (CheckLua(L, r)) {
            lua_getglobal(L, "GetBiomeNumber");

            if (lua_isfunction(L, -1)) {
                if (CheckLua(L, lua_pcall(L, 0, 1, 0))) {
                    biomeNb = lua_tonumber(L, -1);
                    lua_pop(L, 1);
                }
            }

            for (int i = 0; i < biomeNb; i++) {

                BiomeGenerationData biomeData;
                std::string biomeName;

                lua_getglobal(L, "GetBiome");

                if (lua_isfunction(L, -1)) {
                    lua_pushinteger(L, i+1);
                    if (CheckLua(L, lua_pcall(L, 1, 1, 0))) {
                        if (lua_istable(L, -1)) {
                            lua_pushstring(L, "biomeName");
                            lua_gettable(L, -2);
                            biomeName = lua_tostring(L, -1);
                            lua_pop(L, 1);

                            lua_pushstring(L, "biomeID");
                            lua_gettable(L, -2);
                            biomeData.biomeID = (int)lua_tonumber(L, -1);
                            lua_pop(L, 1);

                            lua_pushstring(L, "offsetX");
                            lua_gettable(L, -2);
                            biomeData.offsetX = (float)lua_tonumber(L, -1);
                            lua_pop(L, 1);

                            lua_pushstring(L, "offsetZ");
                            lua_gettable(L, -2);
                            biomeData.offsetZ = (float)lua_tonumber(L, -1);
                            lua_pop(L, 1);

                            lua_pushstring(L, "frequencyX");
                            lua_gettable(L, -2);
                            biomeData.frequencyX = (float)lua_tonumber(L, -1);
                            lua_pop(L, 1);

                            lua_pushstring(L, "frequencyZ");
                            lua_gettable(L, -2);
                            biomeData.frequencyZ = (float)lua_tonumber(L, -1);
                            lua_pop(L, 1);

                            lua_pushstring(L, "heightOffset");
                            lua_gettable(L, -2);
                            biomeData.heightOffset = (int)lua_tonumber(L, -1);
                            lua_pop(L, 1);

                            lua_pushstring(L, "multiplier");
                            lua_gettable(L, -2);
                            biomeData.multiplier = (float)lua_tonumber(L, -1);
                            lua_pop(L, 1);

                            lua_pushstring(L, "preprocessing");
                            lua_gettable(L, -2);
                            biomeData.preprocessingFunction = (int)lua_tonumber(L, -1);
                            lua_pop(L, 1);

                            lua_pushstring(L, "topBlockID");
                            lua_gettable(L, -2);
                            biomeData.topBlockID = (int)lua_tonumber(L, -1);
                            lua_pop(L, 1);

                            lua_pushstring(L, "underBlockID");
                            lua_gettable(L, -2);
                            biomeData.underBlockID = (int)lua_tonumber(L, -1);
                            lua_pop(L, 1);
                        }
                    }
                }
                _biomeNames.push_back(biomeName);
                _biomes.emplace(biomeName, biomeData);
            }
        }

        lua_close(L);
    }


        // REDO ALL THE WORLD GENERATION SO IT CAN BE MORE NATURAL

        // https://www.redblobgames.com/maps/terrain-from-noise/
        // http://parzivail.com/procedural-terrain-generaion/
        

    int WorldGenerator::GetBlockAt (const int & block_X, const int & block_Y, const int & block_Z) {

        //BiomeGenerationData biome = GetBiomeAt(block_X, block_Z);
        float biome = GetBiomeAt(block_X, block_Z);
        int top = std::ceil( GetHeight(block_X, block_Z) * 168 - 40 );
        float cave = _noise.Evaluate(block_X/15.f, block_Y/15.f, block_Z/15.f);
        BiomeGenerationData bgd;

        if (top < 0.f) bgd = _biomes["ocean"];
        else if (top < 40.f) {
            if (biome < 0.f) {
                bgd = _biomes["desert"];
            } else {
                bgd = _biomes["plain"];
            }
        } else if (top < 100.f) {
            bgd = _biomes["mountain"];
        }


        if (block_Y > top || cave < -0.57f) return 0;

        if (block_Y <= top - 4) {
            if (_noise.Evaluate(block_X, block_Y, block_Z) < -0.5f) return 4;
            else return 3;
        } else if (block_Y >= top - 3 && block_Y <= top - 1) {
            return bgd.underBlockID;
        } else if (block_Y == top) {
            return bgd.topBlockID;
        }

        return 0.;
    }

        /* Use LUA for those functions depending on the biome type */

    float WorldGenerator::GetBiomeAt (const int & block_X, const int & block_Z) {
        float moisture = _moistureNoise.Evaluate(0.5f * block_X / BIOMEF, 0.5f * block_Z / BIOMEF, 1.f, 0.f);
        return moisture;
    }

    float WorldGenerator::GetHeight (const float & block_X, const float & block_Z) {
        float height = 0;
        height += (_noise.Evaluate( 1.f * block_X / BIOMEF, 1.f * block_Z / BIOMEF, 1.0f, 0.0f) / 2.f + 0.7f) * 0.75f; 
        height += (_noise.Evaluate( 2.f * block_X / BIOMEF, 2.f * block_Z / BIOMEF, 1.0f, 0.0f) / 2.f + 0.7f) * 0.35f; 
        height += (_noise.Evaluate( 4.f * block_X / BIOMEF, 4.f * block_Z / BIOMEF, 1.0f, 0.0f) / 2.f + 0.7f) * 0.10f; 
        height += (_noise.Evaluate( 8.f * block_X / BIOMEF, 8.f * block_Z / BIOMEF, 1.0f, 0.0f) / 2.f + 0.7f) * 0.05f; 
        height += (_noise.Evaluate( 16.f * block_X / BIOMEF, 16.f * block_Z / BIOMEF, 1.0f, 0.0f) / 2.f + 0.7f) * 0.05f; 

        height /= 1.3f;

        if (height > 1.f) height = 0.9f;

        return std::pow(height, 3);

        /*
        BiomeGenerationData nBiomes[4] = {
            GetBiomeAt(block_X+1, block_Z-1),
            GetBiomeAt(block_X+1, block_Z+1),
            GetBiomeAt(block_X-1, block_Z-1),
            GetBiomeAt(block_X-1, block_Z+1)
        };

        int nHeights[4] = {
            GetHeight(block_X+1, block_Z-1, nBiomes[0]),
            GetHeight(block_X+1, block_Z+1, nBiomes[1]),
            GetHeight(block_X-1, block_Z-1, nBiomes[2]),
            GetHeight(block_X-1, block_Z+1, nBiomes[3])
        };

        int height = std::ceil(  ( (nHeights[0] + nHeights[1] ) / 2.f + (nHeights[2] + nHeights[3]) / 2.f ) / 2.f );

        BiomeGenerationData biome = GetBiomeAt(block_X, block_Z);
        height += GetHeight(block_X, block_Z, biome); 
        return height / 2;*/
    }


    int WorldGenerator::GetHeight (const float & block_X, const float & block_Z, const BiomeGenerationData & biome) {
        float noiseEval = _noise.Evaluate(biome.offsetX + block_X / biome.frequencyX, biome.offsetZ + block_Z / biome.frequencyZ); // Between -1 and 1
        float processNoiseEval = 0;
        if (biome.preprocessingFunction == 1) {
            processNoiseEval = std::exp(std::tan(noiseEval));
        } else if (biome.preprocessingFunction == 2) {
            processNoiseEval = std::abs(noiseEval);
        } else if (biome.preprocessingFunction == 3) {

        }

        return std::ceil( processNoiseEval * biome.multiplier + biome.heightOffset);
    }

    
    std::vector<int> WorldGenerator::GetHeights (const int & chunk_X, const int & chunk_Z) {
        std::vector<int> heightMap;
        for (int i = 0; i < CHUNKSIZE + 1; i++) {
            for (int j = 0; j < CHUNKSIZE + 1; j++) {
                int height = GetHeight((i + chunk_X * (CHUNKSIZE+1) ) / 100.f, (i + chunk_Z * (CHUNKSIZE+1) ) / 100.f);
                heightMap.push_back(height);
            }
        }
        return heightMap;
    }


    bool WorldGenerator::CheckLua (lua_State* L, int r) {
        if (r != LUA_OK) {
            std::cout << lua_tostring(L, -1) << std::endl;
            return false;
        }
        return true;
    }
}