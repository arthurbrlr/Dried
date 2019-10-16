/* Image Reader */
#define STB_IMAGE_IMPLEMENTATION
#include "Util/stb_image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>

#include "RenderEngine/Loader.h"

namespace RenderEngine {
    unsigned int Loader::CreateVAO () {
        unsigned int vao; glGenVertexArrays(1, &vao);
        _vaos.push_back(vao);
        BindVAO(vao);
        return vao;
    }

    void Loader::BindVAO (unsigned int vaoID) {
        glBindVertexArray(vaoID);
    }

    unsigned int Loader::BindIndicesBuffer (const std::vector<unsigned int> & indices, GLenum mode) {
        unsigned int vbo; glGenVertexArrays(1, &vbo);
        _vbos.push_back(vbo);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], mode);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        return vbo;
    }

    unsigned int Loader::StoreDataInAttributeList (int                        attributeNumber,
                                                   int                        coordinateSize,
                                                   GLenum                     mode,
                                                   const std::vector<float> & data) {
        unsigned int vbo; glGenVertexArrays(1, &vbo);
        _vbos.push_back(vbo);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], mode);
        glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, coordinateSize * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return vbo;
    }

    void Loader::UnbindVAO () {
        glBindVertexArray(0);
    }

    unsigned int Loader::LoadToVAO (const std::vector<float> & vertices) {
        unsigned int vao = CreateVAO();
        StoreDataInAttributeList(0, 2, GL_STATIC_DRAW, vertices);
        UnbindVAO();
        return vao;
    }


    std::vector<unsigned int> Loader::LoadToBuffers (const std::vector<unsigned int> & indices,
                                                     const std::vector<float>        & vertices,
                                                     const std::vector<float>        & textureCoord,
                                                     const std::vector<float>        & normals,
                                                     const std::vector<float>        & colors,
                                                     GLenum                          indicesMode,
                                                     GLenum                          verticesMode) {
        std::vector<unsigned int> buffersIndices;
        buffersIndices.reserve(6);
        buffersIndices[0] = CreateVAO();
        buffersIndices[1] = BindIndicesBuffer(indices, indicesMode);
        buffersIndices[2] = StoreDataInAttributeList(0, 3, verticesMode, vertices);
        buffersIndices[3] = StoreDataInAttributeList(1, 2, GL_STATIC_DRAW, textureCoord);
        buffersIndices[4] = StoreDataInAttributeList(2, 3, GL_STATIC_DRAW, normals);
        buffersIndices[5] = StoreDataInAttributeList(3, 4, GL_STATIC_DRAW, colors);
        UnbindVAO();
        return buffersIndices;
    }

    void Loader::ChangeIndicesBuffer (const std::vector<unsigned int> & newIndices,
                                      unsigned int vaoToChange,
                                      unsigned int vboToChange) {
        BindVAO(vaoToChange);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboToChange);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, newIndices.size() * sizeof(unsigned int), &newIndices[0], GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        UnbindVAO();
    }

    void Loader::ChangeDataInAttributeList (const std::vector<float> & data,
                                            int attributeNumber,
                                            int coordinateSize,
                                            unsigned int vaoToChange,
                                            unsigned int vboToChange) {
        BindVAO(vaoToChange);
        glBindBuffer(GL_ARRAY_BUFFER, vboToChange);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_DYNAMIC_DRAW);
        glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, coordinateSize * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        UnbindVAO();
    }

    void Loader::BindVertexAttributes () {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
    }

    void Loader::UnbindVertexAttributes () {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glBindVertexArray(0);
    }

    void Loader::CleanUp () {
        for (unsigned int i : _vaos) {
            glDeleteVertexArrays(1, &i);
        }

        for (unsigned int i : _vbos) {
            glDeleteBuffers(1, &i);
        }
    }

    unsigned int Loader::LoadTexture (const std::string & path, bool isTransparent) {
            /* Texture binding */
        unsigned int texture;
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

            /* Texture loading */
        int nrChannels, width, height;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);
        //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        if (data) {
            if (isTransparent) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        } else {
            std::cout << "ERROR::TEXTURE::LOADING: Couldn't load " << path << std::endl;
        }
        stbi_image_free(data);

        return texture;
    }
}
