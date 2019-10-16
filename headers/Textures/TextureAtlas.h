#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <string>

/*
    Texture Atlas Singleton

    Stores every textures used in the gamew
*/

namespace Textures {
    class Texture;

    class TextureAtlas {
        private:
            unsigned int _atlasID;

            static TextureAtlas* instance;
            TextureAtlas(){};

        public:
            TextureAtlas(TextureAtlas const&) = delete;
            void operator=(TextureAtlas const&) = delete;
            static TextureAtlas& GetInstance () {
                static TextureAtlas instance;
                return instance;
            };

            void Init (const std::string & path);
            void UseAtlas (const int & index);
            int GetID () const {return _atlasID;};
    };
}

#endif
