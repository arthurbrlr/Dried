#ifndef UTIL_H
#define UTIL_H

#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>
#include <random>
#include <string>
#include <sstream>

/*
    Random methods to print vectors in the console, split lines, etc...
*/

namespace Util {
    template <class T>
    static void PrintVector (std::vector<T> vect) {
        for (int i = 0; i < vect.size(); i++) {
            std::cout << vect[i] << " ";
        }
        std::cout << std::endl;
    }

    static void PrintVector (glm::vec2 vect) {
        std::cout << vect.x << " " << vect.y << std::endl;
    }

    static void PrintVector (glm::vec3 vect) {
        std::cout << vect.x << " " << vect.y << " " << vect.z << std::endl;
    }

    static int RandomInt (int min, int max) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> rand(min, max);

        return rand(rng);
    }

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
}

#endif
