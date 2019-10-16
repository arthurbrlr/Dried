#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <iostream>
#include <vector>

#include <thread>
#include <chrono>
#include <mutex>

#include "Entities/Camera.h"

#include "Util/unorderedHash.h"
#include "Util/Config.h"
#include "Util/util.h"

#include "RenderEngine/MeshBuilder.h"

#include "World/WorldGenerator.h"
#include "World/BasicChunk.h"
#include "World/World.h"

namespace World {


    /*
        BuildWorld ()

        Build a randomly generated world when launching the game
    */

    void World::BuildWorld () {

        _isRunning = true; // Game is running

            // Calculate a spiral around the player in order to load the chunks in a spiral shape
        BuildSpiral();

        std::cout << "Building world" << std::endl;

            /* 
                Initial build of the world in a square shape
                (the player is not yet instanced in the world so the order doesn't matter)
            */
        auto start = std::chrono::system_clock::now();
        for (int i = -RENDERDISTANCE; i < RENDERDISTANCE + 1; i++) {
            for (int j = -RENDERDISTANCE; j < RENDERDISTANCE + 1; j++) {
                BuildChunkColumn(i, j);
                float per = ( (i + RENDERDISTANCE) * RENDERDISTANCE + j );
                std::cout << per << std::endl;
            }
        }

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Initial world buidling time: " << elapsed_seconds.count() << "s" << std::endl;

            // Start the thread responsible for building chunks around the player while playing
        _loadingWorldThreads.emplace_back([](){return World::World::GetInstance().BuildAroundPlayer();});

        _isGenerated = true; // Wolrd is generated
    }



    /*
        BuildChunkColumn (x, z)
            @x: x coordinate of the chunk column
            @z: z coordinate of the chunk column

        Build a column of 16 chunks (16 x 16 x 16 blocks)
    */

    void World::BuildChunkColumn (int x, int z) {

            // Loop over the height
        for (int k = 0; k < 16; k++) {


                /*
                    Check if the mutex associated with the World instance is locked (used by another method),

                    locked : try again in 1 millisecond
                    not locked : lock it and do the rest
                */
            std::unique_lock<std::mutex> lck(_mutex, std::defer_lock);
            bool locked = false;
            while (!locked) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                locked = lck.try_lock();
            }

            glm::vec3 chunkPos(x, k-8, z); // chunk position in the world
            int chunkID = x * 43 + z * 37 + 13 * k;
                // add a new chunk to the hash map using position as key
            _worldChunks.emplace(chunkPos, BasicChunk(chunkPos, chunkID));


                /*
                    Check if the mutex associated with the MeshBuilder instance is locked

                    locked : try again in 1 millisecond
                    not locked : lock it and do the rest
                */
            std::unique_lock<std::mutex> lck2(RenderEngine::MeshBuilder::GetInstance()._lock, std::defer_lock);
            locked = false;
            while (!locked) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                locked = lck2.try_lock();
            }
                // add the new chunk to the batch in order to build the mesh associated with it
            RenderEngine::MeshBuilder::GetInstance().AddMeshToBatch(_worldChunks.find(chunkPos)->second, false);
        }

            // add the column position in a hash map to keep track of which column has been built
        _columns.emplace(glm::vec3(x, 0, z), 1);
    }



    /*
        BuildAroundPlayer ()

        This function run on its own thread to build chunk around the player
        without causing lags
    */

    void World::BuildAroundPlayer () {

            // the method run as long as the game state is enable
        while (_isRunning) {
            bool newChunkBuilded = false; // used to build one column per iteration of the while loop

                // get the chunk of the player
            int centerX = Entities::Camera::GetInstance().GetPosition().x / (CHUNKSIZE+1);
            int centerZ = Entities::Camera::GetInstance().GetPosition().z / (CHUNKSIZE+1);

                // loop in a spiral around the player
            for (int i = 0; i < _neighX.size(); i++) {
                    // build a chunk column if it does not exist at the specified position
                if (!ColumnAtPosExists(glm::vec3(centerX + _neighX[i], 0, centerZ + _neighZ[i])) && !newChunkBuilded) {
                    BuildChunkColumn(centerX + _neighX[i], centerZ + _neighZ[i]);
                    newChunkBuilded = true;
                }
            }
        }
    }



    /*
        CloseWorld ()

        Stop building the world when leaving the game state
    */

    void World::CloseWorld () {
        _isRunning = false;
            // wait for the thread used to build the world around the player
        for (auto & t : _loadingWorldThreads) {
            t.join();
        }
    }



    /*
        ColumnAtPosExists (pos)
            @pos: position of the chunk column (could be vec2)

        Check if a chunk column already exist at the specified position
    */

    bool World::ColumnAtPosExists (const glm::vec3 & pos) {
        std::unordered_map<glm::vec3, int>::const_iterator it = _columns.find(pos);
        if (_columns.find(pos) != _columns.end()) {
            return true;
        } else {
            return false;
        }
    }

    

    /*
        BuildSpiral ()

        Build two arrays : _neighX and _neighY
            _neighX is the X coordinate of the chunks in the spiral, relative to the player
            _neighY is the Y coordinate of the chunks in the spiral, relative to the player
        These arrays are used to build chunks in a spiral around the player at runtime       
    */

    void World::BuildSpiral () {
        int x, z, dx, dz;
        x = z = dx = 0;
        dz = -1;
        int t = 2 * RENDERDISTANCE;
        int maxI = t * t;
        for(int i =0; i < maxI; i++){
            if ((-RENDERDISTANCE <= x) && (x <= RENDERDISTANCE) && (-RENDERDISTANCE <= z) && (z <= RENDERDISTANCE)) {
                _neighX.push_back(x);
                _neighZ.push_back(z);
            }

            if( (x == z) || ((x < 0) && (x == -z)) || ((x > 0) && (x == 1 - z))) {
                t = dx;
                dx = -dz;
                dz = t;
            }

            x += dx;
            z += dz;
        }
    }
        


    /*
        ChunkAt (chunkPos)
            @chunkPos: chunk position

        Return a const_iterator of the _worldChunks hashmap 
        Used to check if there is a chunk at the specified position
    */

    std::unordered_map<glm::vec3, BasicChunk>::const_iterator World::ChunkAt (glm::vec3 chunkPos) {
        std::unordered_map<glm::vec3, BasicChunk>::const_iterator it = _worldChunks.find(chunkPos);
        return _worldChunks.find(chunkPos);
    }



    /*
        ChunkAtNC (chunkPos)
            @chunkPos: chunk position

        Return an iterator (non constant) of the _worldChunks hashmap
        Used to check if there is a chunk at the specified position
    */

    std::unordered_map<glm::vec3, BasicChunk>::iterator World::ChunkAtNC (glm::vec3 chunkPos) {
        std::unordered_map<glm::vec3, BasicChunk>::iterator it = _worldChunks.find(chunkPos);
        return _worldChunks.find(chunkPos);
    }



    /*
        BlockAtPosExists (blockWorldPos)
            @blockWorldPos: world position of the block to check

        Return true if there's a block at the specified position
    */

    bool World::BlockAtPosExists (const glm::vec3 & blockWorldPos) {

            // First find the chunk where the block should be
        glm::vec3 chunkPos(std::floor(blockWorldPos.x / (CHUNKSIZE + 1)),
                           std::floor(blockWorldPos.y / (CHUNKSIZE + 1)),
                           std::floor(blockWorldPos.z / (CHUNKSIZE + 1)));
        std::unordered_map<glm::vec3, BasicChunk>::const_iterator it = ChunkAt(chunkPos);
        auto end = std::chrono::system_clock::now();

            // if the chunk exist, search in it - else return false
        if (it != _worldChunks.end()) {
            BasicChunk chunk = it->second;
            return(chunk.BlockAtPosExists(blockWorldPos));
        } else {
            return false;
        }
    }



    /*
            ## Should return a BlockData to display on GUI for example
            ## Here the method only displays the block type in the console

        GetBlockAtPos (blockWordlPos)
            @blockWorldPos: world position of the block to get

        Display the type of the block at the specified position
    */

    void World::GetBlockAtPos (const glm::vec3 & blockWorldPos) {

/*      
        // ???
        std::unique_lock<std::mutex> lck2(RenderEngine::MeshBuilder::GetInstance()._lock, std::defer_lock);
        bool locked = false;
        while (!locked) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            locked = lck2.try_lock();
        }
*/


        if (BlockAtPosExists(blockWorldPos)) {
            glm::vec3 chunkPos(std::floor(blockWorldPos.x / (CHUNKSIZE + 1)),
                               std::floor(blockWorldPos.y / (CHUNKSIZE + 1)),
                               std::floor(blockWorldPos.z / (CHUNKSIZE + 1)));
            std::unordered_map<glm::vec3, BasicChunk>::iterator it = ChunkAtNC(chunkPos);
            int bId = it->second.GetBlockAt(blockWorldPos);
            std::cout << "Block exist and is type: " << bId << std::endl;
        } else {
            std::cout << "No block found" << std::endl;
        }
    }



    /*
        RemoveBlockAtPos (blockWorldPos)
            @blockWorldPos: world position of the block to remove

        Remove a block in the world at the specified position
    */

    void World::RemoveBlockAtPos (const glm::vec3 & blockWorldPos) {
        
            // try to lock the _lock mutex of the MeshBuilder (to update the chunk mesh)
        std::unique_lock<std::mutex> lck2(RenderEngine::MeshBuilder::GetInstance()._lock, std::defer_lock);
        bool locked = false;
        while (!locked) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            locked = lck2.try_lock();
        }
        
        if (BlockAtPosExists(blockWorldPos)) {
            glm::vec3 chunkPos(std::floor(blockWorldPos.x / (CHUNKSIZE + 1)), 
                               std::floor(blockWorldPos.y / (CHUNKSIZE + 1)),
                               std::floor(blockWorldPos.z / (CHUNKSIZE + 1)));
            std::unordered_map<glm::vec3, BasicChunk>::iterator it = ChunkAtNC(chunkPos);
            it->second.RemoveBlockAt(blockWorldPos);
            it->second.UpdateChunkBlocks();
            RenderEngine::MeshBuilder::GetInstance().AddMeshToBatch(_worldChunks.find(chunkPos)->second, true);
        }
    }
}
