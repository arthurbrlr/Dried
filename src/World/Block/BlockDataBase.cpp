#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>
#include <string>
#include <fstream>

#include "Util/util.h"

#include "Shaders/ShaderProgram.h"
#include "World/Block/Block.h"
#include "World/Block/BlockDataBase.h"

namespace World {

    void BlockDataBase::LoadBlockDataBase (const std::string & databasePath, Shaders::ShaderProgram* shader) {
        std::ifstream databaseFile;
        databaseFile.open(databasePath);
        BlockData newBdata(shader);
        bool readFiles = false;
        std::string path, ext;
        std::vector<std::string> files;

        if (!databaseFile.is_open()) {
            std::cout << "ERROR::BLOCKDATABASE::LOADING::FILE: Couldn't open " + databasePath << std::endl;
        } else {

            std::string line;

            while(!databaseFile.eof()) {
                std::getline(databaseFile, line);
                std::vector<std::string> lineSplited = Util::Split(line, ' ');

                if (line == "") continue;
                if (lineSplited[0] == "PATH") {
                    path = lineSplited[1];
                } else if (lineSplited[0] == "EXT") {
                    ext = lineSplited[1];
                } else if (lineSplited[0] == "BLOCKS") {
                    readFiles = true;
                    continue;
                }
                if (readFiles) files.push_back(path + line + ext);
            }

        }
        databaseFile.close();

        for (int i = 0; i < files.size(); i++) {
            AddBlockData(files[i], shader);
        }
    }

    void BlockDataBase::AddBlockData (const std::string & pathToBlockFile, Shaders::ShaderProgram* shader) {
        std::ifstream blockFile;
        blockFile.open(pathToBlockFile);
        BlockData newBdata(shader);

        if (!blockFile.is_open()) {
            std::cout << "ERROR::BLOCKDATABASE::LOADING::FILE: Couldn't open " + pathToBlockFile << std::endl;
        } else {

            std::string line;

            while(!blockFile.eof()) {
                std::getline(blockFile, line);
                std::vector<std::string> lineSplited = Util::Split(line, ' ');

                if (line != "" && lineSplited.size() > 0) {
                    if (lineSplited[0] == "NAME") {
                        newBdata._name = lineSplited[1];
                    } else if (lineSplited[0] == "ID") {
                        newBdata._blockID = std::stoi(lineSplited[1]);
                    } else if (lineSplited[0] == "TRANSPARENT") {
                        //std::cout << lineSplited[1] << std::endl;
                    } else if (lineSplited[0] == "ATLAS") {
                        //std::cout << lineSplited[1] << std::endl;
                    } else if (lineSplited[0] == "TOP") {
                        float x = std::stof(lineSplited[1])/16.f, y = std::stof(lineSplited[2])/16.f;
                        newBdata._topTextCoord = glm::vec2(x, y);
                    } else if (lineSplited[0] == "SIDE") {
                        float x = std::stof(lineSplited[1])/16.f, y = std::stof(lineSplited[2])/16.f;
                        newBdata._sideTextCoord = glm::vec2(x, y);
                    }  else if (lineSplited[0] == "BOTTOM") {
                        float x = std::stof(lineSplited[1])/16.f, y = std::stof(lineSplited[2])/16.f;
                        newBdata._bottomTextCoord = glm::vec2(x, y);
                    }  else if (lineSplited[0] == "SHADER") {
                        if (lineSplited[1] == "TERRAIN") {
                            //std::cout << lineSplited[1] << std::endl;
                        }
                    }
                }
            }
        }
        blockFile.close();
        _database.emplace(newBdata.GetID(), newBdata);
    }
}
