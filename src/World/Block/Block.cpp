#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Util/util.h"

#include "RenderEngine/Loader.h"
#include "World/Block/BlockDataBase.h"
#include "World/Block/Block.h"

namespace World {
     void Block::AddFacesToMesh (glm::vec3 position,
                                int blockID,
                                int & triangleCount,
                                std::vector<bool> & booleans,
                                std::vector<float> & vertices,
                                std::vector<float> & texCoord,
                                std::vector<float> & normals,
                                std::vector<float> & colors) {
        if (!booleans[0]) AddFace(_frontFaceVertices, _frontTextCoord, _frontNormal, position, blockID, 1, triangleCount, vertices, texCoord, normals, colors);
        if (!booleans[1]) AddFace(_backFaceVertices, _backTextCoord, _backNormal, position, blockID, 1, triangleCount, vertices, texCoord, normals, colors);
        if (!booleans[2]) AddFace(_leftFaceVertices, _leftTextCoord, _leftNormal, position, blockID, 1, triangleCount, vertices, texCoord, normals, colors);
        if (!booleans[3]) AddFace(_rightFaceVertices, _rightTextCoord, _rightNormal, position, blockID, 1, triangleCount, vertices, texCoord, normals, colors);
        if (!booleans[4]) AddFace(_topFaceVertices, _topTextCoord, _topNormal, position, blockID, 0, triangleCount, vertices, texCoord, normals, colors);
        if (!booleans[5]) AddFace(_bottomFaceVertices, _bottomTextCoord, _bottomNormal, position, blockID, 2, triangleCount, vertices, texCoord, normals, colors);
    }

    void Block::AddFace (const std::vector<float> & faceVertices,
                         const std::vector<float> & faceText,
                         const std::vector<float> & faceNormal,
                         const glm::vec3 & position,
                         const int & id,
                         const int & faceID, // 0 for top, 1 for side, 2 for bottom
                         int & triangleCount,
                         std::vector<float> & vertices,
                         std::vector<float> & texCoord,
                         std::vector<float> & normals,
                         std::vector<float> & colors) {
        std::vector<float> nVertices = {
            faceVertices[0] + position.x, faceVertices[1] + position.y, faceVertices[2] + position.z,
            faceVertices[3] + position.x, faceVertices[4] + position.y, faceVertices[5] + position.z,
            faceVertices[6] + position.x, faceVertices[7] + position.y, faceVertices[8] + position.z,

            faceVertices[9] + position.x, faceVertices[10] + position.y, faceVertices[11] + position.z,
            faceVertices[12] + position.x, faceVertices[13] + position.y, faceVertices[14] + position.z,
            faceVertices[15] + position.x, faceVertices[16] + position.y, faceVertices[17] + position.z
        };

        glm::vec2 atlasCoord;
        if (faceID == 0) atlasCoord = BlockDataBase::GetInstance().GetBlockDataWithId(id).GetTopTextCoord();
        if (faceID == 1) atlasCoord = BlockDataBase::GetInstance().GetBlockDataWithId(id).GetSideTextCoord();
        if (faceID == 2) atlasCoord = BlockDataBase::GetInstance().GetBlockDataWithId(id).GetBottomTextCoord();

        std::vector<float> nTextCoord = {
            atlasCoord.x + faceText[0] / 16.f, atlasCoord.y + faceText[1] / 16.f,
            atlasCoord.x + faceText[2] / 16.f, atlasCoord.y + faceText[3] / 16.f,
            atlasCoord.x + faceText[4] / 16.f, atlasCoord.y + faceText[5] / 16.f,
            atlasCoord.x + faceText[6] / 16.f, atlasCoord.y + faceText[7] / 16.f,
            atlasCoord.x + faceText[8] / 16.f, atlasCoord.y + faceText[9] / 16.f,
            atlasCoord.x + faceText[10] / 16.f, atlasCoord.y + faceText[11] / 16.f,
        };

        vertices.insert(vertices.end(), nVertices.begin(), nVertices.end());
        texCoord.insert(texCoord.end(), nTextCoord.begin(), nTextCoord.end());

        for (int i = 0; i < 6; i++) {
            normals.insert(normals.end(), faceNormal.begin(), faceNormal.end());
        }

        colors.insert(colors.end(), _col.begin(), _col.end());
        
        triangleCount+=6;
    }
}
