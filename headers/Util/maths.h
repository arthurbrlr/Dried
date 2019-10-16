#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <random>

/*
    Custom methods used for rendering, maths, reading files, etc...
*/

namespace Util {

    static glm::mat4 CreateTransformationMatrix (glm::vec2 translation, glm::vec2 scale) {
		glm::mat4 matrix = glm::mat4(1.0f);
		matrix = glm::translate(matrix, glm::vec3(translation.x, translation.y, 0.));
        matrix = glm::scale(matrix, glm::vec3(scale.x, scale.y, 0.));
        return matrix;
	}

    static glm::mat4 CreateTransformationMatrix (glm::vec3 translation, float rx, float ry, float rz, float scale) {
        glm::mat4 matrix = glm::mat4(1.0f);

        /* Translate */
        matrix = glm::translate(matrix, translation);

        /* Rotations */
        matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1.f, 0.f, 0.f));
        matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0.f, 1.f, 0.f));
        matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0.f, 0.f, 1.f));

        /* Scaling */
        matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));

        return matrix;
    }
/*
    static glm::mat4 CreateViewMatrix (Entities::Camera camera) {
        glm::mat4 matrix = glm::mat4(1.0f);

        // Rotation
        matrix = glm::rotate(matrix, glm::radians(camera.GetPitch()), glm::vec3(1.f, 0.f, 0.f));
        matrix = glm::rotate(matrix, glm::radians(camera.GetYaw()), glm::vec3(0.f, 1.f, 0.f));
        matrix = glm::rotate(matrix, glm::radians(camera.GetRoll()), glm::vec3(0.f, 0.f, 1.f));

        // Translate
        glm::vec3 cPos = camera.GetPosition();
        glm::vec3 negativeCameraPos = glm::vec3(-cPos.x, -cPos.y, -cPos.z);
        matrix = glm::translate(matrix, negativeCameraPos);

        return matrix;
    }
*/
    static void PrintMatrix4(glm::mat4 matrix, std::string nameOfMatrix) {
        std::cout << "Matrix printed : " << nameOfMatrix << std::endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                /* i and j are reversed because glm is column major */
                std::cout << matrix[j][i] << " ";
            }
            std::cout << std::endl;
        }
    }

    static int RandomInt (int min, int max) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> rand(min, max);

        return rand(rng);
    }

    class Files {
    public:
        Files(){};
        ~Files(){};

        static std::vector<std::string> Split(const std::string & line, char delimiter) {
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream tokenStream(line);
            while (std::getline(tokenStream, token, delimiter))
            {
                tokens.push_back(token);
            }
            return tokens;
        }
    };
}
