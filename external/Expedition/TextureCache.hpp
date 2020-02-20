#ifndef TEXTURECACHE_HPP
#define TEXTURECACHE_HPP

#include <string>
#include <map>

#include <SDL2/SDL_render.h>

#include "Texture.hpp"

namespace Expedition {
    // Manages textures
    class TextureCache {
        public:
            TextureCache();
            TextureCache(SDL_Renderer* renderer);

            ~TextureCache();

            // Initializes renderer
            void setRenderer(SDL_Renderer* renderer);

            // Returns texture at path. If not already in the map, it adds it.
            Texture* getTexture(std::string texturePath);

        private:
            // Map to hold all texture objects
            std::map<std::string, Texture*> m_textureMap;

            SDL_Renderer* m_renderer;
    };
}

#endif
