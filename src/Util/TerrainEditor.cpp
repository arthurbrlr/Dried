#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "World/WorldGenerator.h"

#include "Util/TerrainEditor.h"

namespace Util {

    void TerrainEditor::ExportToPNG () {

        std::cout << "Generating png" << std::endl;

        std::ofstream img(_filePath + ".pgm");
        img << "P3" << std::endl;

        img << 512 << " " << 512 << std::endl;

        img << 255 << std::endl;

        for (int i = 0; i < _pixels.size(); i++) {
            img << _pixels[i].r << " " << _pixels[i].g << " " << _pixels[i].b << std::endl;
        }

        img.close();

        std::string cmd;
        cmd = "convert " + _filePath + ".pgm " + _filePath + ".png";
        system(cmd.c_str());
        cmd = "rm " + _filePath + ".pgm";
        system(cmd.c_str());

        return;
    }


    void TerrainEditor::GenerateImage () {
        _pixels.clear();
        int maxV = 0;
        for (int i = -256; i < 256; i++) {
            for (int j = -256; j < 256; j++) {
                pixel p;
                /*
                int biome = World::WorldGenerator::GetInstance().GetBiomeAt(i, j).biomeID;
                if (biome == 1) {
                    p.r = 20;
                    p.g = 180;
                    p.b = 20;
                } else if (biome == 2) {
                    p.r = 255;
                    p.g = 255;
                    p.b = 20;
                } else if (biome == 3) {
                    p.r = 20;
                    p.g = 20;
                    p.b = 180;
                }*/
                float height = World::WorldGenerator::GetInstance().GetHeight(i, j);
                int pv = 255.f * height;
                p.r = pv;
                p.g = pv;
                p.b = pv;

                if (pv > maxV) maxV = pv;

                _pixels.push_back(p);
            }
        }

        std::cout << maxV << std::endl;

        ExportToPNG();
    }

}