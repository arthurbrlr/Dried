#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <chrono>
#include <mutex>
#include <thread>

#include "Util/Config.h"

#include "Entities/Camera.h"
#include "World/ChunkMesh.h"
#include "RenderEngine/MeshBuilder.h"

namespace RenderEngine {

    void MeshBuilder::BuildNewMeshPerFrame () {
        glm::vec3 playerChunk = Entities::Camera::GetInstance().GetChunkPosition();
        
        if (_batch.size() > 0) {
            float minDist = 1000.;
            int index = 0;
            std::unique_lock<std::mutex> lck(_lock, std::defer_lock);
            if (!lck.try_lock()) return;

            for (int i = 0; i < _batch.size(); i++) {
                float distanceFromPlayer = std::abs(glm::length(_allMeshs[_batch[i]].mesh.GetChunkPosition() - playerChunk));
                if (distanceFromPlayer < minDist && distanceFromPlayer < RENDERDISTANCE) {
                    minDist = distanceFromPlayer;
                    index = i;
                }
            }

            _allMeshs[_batch[index]].mesh.BuildMesh();
            _allMeshs[_batch[index]].isBuilded = true;
            _batch.erase(_batch.begin() + index);
        }
    }


    void MeshBuilder::RenderWorld () {
        glm::vec3 playerChunk = Entities::Camera::GetInstance().GetChunkPosition();

        std::unique_lock<std::mutex> lck(_lock, std::defer_lock);
        bool locked = false;
        while (!locked) {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            locked = lck.try_lock();
        }

        for (int i = 0; i < _allMeshs.size(); i++) {
            if (!_allMeshs[i].isBuilded) continue;
            float distanceFromPlayer = std::abs(glm::length(_allMeshs[i].mesh.GetChunkPosition() - playerChunk));
            if (distanceFromPlayer < RENDERDISTANCE) {
                _allMeshs[i].mesh.RenderMesh();
            }
        }
    }


    void MeshBuilder::AddMeshToBatch (const World::BasicChunk & chunk, bool updatingMesh) {
        if (updatingMesh) {
            for (int i = 0; i < _allMeshs.size(); i++) {
                if (_allMeshs[i].mesh.GetChunkPosition() == chunk.GetPosition()) {
                        // the two lines below take some times to process
                    World::ChunkMesh mesh(chunk);
                    RenderData newRD(mesh);
                        // try to avoid doing this every frame (CD on mining for example)
                    _allMeshs[i] = newRD;
                    _batch.push_back(i);
                }
            }   
        } else {
            _allMeshs.push_back(RenderData(World::ChunkMesh(chunk)));
            _batch.push_back(_allMeshs.size() - 1);
        }
    }
}
