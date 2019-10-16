#ifndef BLOCK_H
#define BLOCK_H

#include <glm/gtc/type_ptr.hpp>

#include <vector>

/*
    Block singleton

    Describe the mesh of a simple cube, used to add
    cube faces to a chunk mesh
*/

namespace World {
    class Block {
        private:
           std::vector<float> _frontFaceVertices = {-0.5f, -0.5f, -0.5f, 0.5f,  0.5f, -0.5f, 0.5f, -0.5f, -0.5f,
                                                    0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f},
                              _backFaceVertices = {-0.5f, -0.5f,  0.5f, 0.5f, -0.5f,  0.5f, 0.5f,  0.5f,  0.5f,
                                                   0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f},
                              _rightFaceVertices = {-0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
                                                    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f},
                              _leftFaceVertices = { 0.5f,  0.5f,  0.5f, 0.5f, -0.5f, -0.5f, 0.5f,  0.5f, -0.5f,
                                                    0.5f, -0.5f, -0.5f, 0.5f,  0.5f,  0.5f, 0.5f, -0.5f,  0.5f},
                              _bottomFaceVertices = {-0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f,  0.5f,
                                                     0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f},
                              _topFaceVertices = {-0.5f,  0.5f, -0.5f, 0.5f,  0.5f,  0.5f, 0.5f,  0.5f, -0.5f,
                                                   0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f};

           std::vector<float> _frontTextCoord = {0.f, 0.f, 1.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f},
                              _backTextCoord = {1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, 1.f, 1.f, 0.f},
                              _rightTextCoord = {0.f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f},
                              _leftTextCoord = {1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0.f},
                              _bottomTextCoord = {0.f, 0.f, 1.f, 0.f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f, 0.f, 0.f},
                              _topTextCoord = {0.f, 0.f, 1.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f};

            std::vector<float> _frontNormal = {0.f,  0.f, -1.f,},
                               _backNormal = {0.f, 0.f, 1.f},
                               _rightNormal = {-1.f, 0.f, 0.f},
                               _leftNormal = {1.f, 0.f, 0.f},
                               _bottomNormal = {0.f, -1.f, 0.f},
                               _topNormal = {0.f, 1.f, 0.f};

            std::vector<float> _col = {1.f, 0.f, 0.f, 1.f};


            static Block* instance;
            Block(){};

            void AddFace (const std::vector<float> & faceVertices,
                          const std::vector<float> & faceText,
                          const std::vector<float> & faceNormal,
                          const glm::vec3 & position,
                          const int & id,
                          const int & faceID,
                          int & triangleCount,
                          std::vector<float> & vertices,
                          std::vector<float> & texCoord,
                          std::vector<float> & normals,
                          std::vector<float> & colors);

        public:
            Block(Block const&) = delete;
            void operator=(Block const&) = delete;
            static Block& GetInstance () {
                static Block instance;
                return instance;
            };

            unsigned int Init ();
            void RenderFull ();
            void RenderFace (const std::vector<bool> & booleans, unsigned int vao);
            void Clear ();

            void AddFacesToMesh (glm::vec3 position,
                                int blockID,
                                int & triangleCount,
                                std::vector<bool> & booleans,
                                std::vector<float> & vertices,
                                std::vector<float> & texCoord,
                                std::vector<float> & normals,
                                std::vector<float> & colors);

            void SetTextureOffset(){};
    };
}


#endif
