#ifndef TERRAIN_EDITOR_H
#define TERRAIN_EDITOR_H

#include <string>
#include <vector>

/*
    Terrain Editor Singleton

    Used to show a top map of the world, colored by biome type (WIP)
*/

namespace Util {

    struct pixel {
        int r, g, b;
    };

    class TerrainEditor {
        private:
            std::string _filePath = "res/terrain";
            std::vector<pixel> _pixels;

            static TerrainEditor* instance;
            TerrainEditor(){};
            ~TerrainEditor(){};

        public:
            TerrainEditor(TerrainEditor const&) = delete;
            void operator=(TerrainEditor const&) = delete;
            static TerrainEditor& GetInstance () {
                static TerrainEditor instance;
                return instance;
            };

            void ExportToPNG ();
            void GenerateImage ();

            std::string ImgPath () const {return _filePath + ".png";};


    };

}

#endif