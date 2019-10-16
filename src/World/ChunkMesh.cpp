#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <vector>
#include <iostream>
#include <chrono>

#include "Util/unorderedHash.h"
#include "Util/util.h"

#include "Shaders/ShaderProgram.h"
#include "Textures/TextureAtlas.h"
#include "RenderEngine/Loader.h"
#include "World/Block/BlockDataBase.h"
#include "World/Block/Block.h"
#include "World/Block/ChunkBlock.h"
#include "World/BasicChunk.h"
#include "World/ChunkMesh.h"

namespace World {

    ChunkMesh::ChunkMesh (const BasicChunk & chunk) {
        _chunk = chunk;
        _chunk.UpdateChunkBlocks();
        //BuildMesh();
    }


    void ChunkMesh::BuildMesh () {
        glm::vec3 chunkPosition = _chunk.GetPosition();
        int c = 0;

        for (auto & it : _chunk.GetChunkBlocks()) {
            if (it.second.IsVisible()) {
                std::vector<bool> booleans = it.second.GetBooleans();
                glm::vec3 blockPos = it.first;
                Block::GetInstance().AddFacesToMesh(blockPos, it.second.GetID(), c, booleans, _meshVertices, _meshTexCoord, _meshNormals, _meshColors);
            }
        }

        for (int i = 0; i < c; i++) {
            _meshIndices.push_back(i);
        }

        LoadMesh();
    }

    void ChunkMesh::LoadMesh () {
        std::vector<unsigned int> buffersIndices;
        buffersIndices = RenderEngine::Loader::GetInstance().LoadToBuffers(_meshIndices,
                                                                           _meshVertices,
                                                                           _meshTexCoord,
                                                                           _meshNormals,
                                                                           _meshColors,
                                                                           GL_DYNAMIC_DRAW,
                                                                           GL_DYNAMIC_DRAW);
        _vaoID = buffersIndices[0];
        _vboIndicesID = buffersIndices[1];
        _vboVerticesID = buffersIndices[2];
        _vboTexCID = buffersIndices[3];
        _vboNormalID = buffersIndices[4];
        _vboColorID = buffersIndices[5];
    }

    void ChunkMesh::RenderMesh () {
        glm::mat4 transform = glm::mat4(1.0f);
        BlockDataBase::GetInstance().GetBlockDataWithId(1).GetShader()->Start(); // Ne fonctionne pas ??
        BlockDataBase::GetInstance().GetBlockDataWithId(1).GetShader()->LoadTransformationMatrix(transform);
        Textures::TextureAtlas::GetInstance().UseAtlas(0);

        glBindVertexArray(_vaoID);
        RenderEngine::Loader::GetInstance().BindVertexAttributes();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboIndicesID);
        glDrawElements(GL_TRIANGLES, _meshIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        RenderEngine::Loader::GetInstance().UnbindVertexAttributes();
    }

    void ChunkMesh::UpdateMesh () {
        _meshIndices.clear();
        _meshVertices.clear();
        _meshTexCoord.clear();
        _meshNormals.clear();
        _meshColors.clear();

        _chunk.UpdateChunkBlocks();
        glm::vec3 chunkPosition = _chunk.GetPosition();
        int c = 0;

        for (auto & it : _chunk.GetChunkBlocks()) {
            if (it.second.IsVisible()) {
                std::vector<bool> booleans = it.second.GetBooleans();
                glm::vec3 blockPos = it.first;
                Block::GetInstance().AddFacesToMesh(blockPos, it.second.GetID(), c, booleans, _meshVertices, _meshTexCoord, _meshNormals, _meshColors);
            }
        }

        for (int i = 0; i < c; i++) {
            _meshIndices.push_back(i);
        }

        glDeleteVertexArrays(1, &_vaoID);
        glDeleteBuffers(1, &_vboIndicesID);
        glDeleteBuffers(1, &_vboVerticesID);
        glDeleteBuffers(1, &_vboTexCID);
        glDeleteBuffers(1, &_vboNormalID);
        glDeleteBuffers(1, &_vboColorID);

        LoadMesh();
    }

    void ChunkMesh::RemoveBlockAt (const glm::vec3 & pos) {
        _chunk.RemoveBlockAt(pos);
        UpdateMesh();
    }
}
