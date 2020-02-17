#ifndef EXPEDITION_TEXTURE_HPP
#define EXPEDITION_TEXTURE_HPP

#include <SDL2/SDL_render.h>

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
#include <SDL2/SDL_ttf.h>
#endif

#include <stdint.h>
#include <string>

namespace Expedition {
    // Texture wrapper class
    class Texture {
        public:
            // Init variables
            Texture();

            // Deallocates memory
            ~Texture();

            // Loads image file at path
            bool loadFromFile(std::string path, SDL_Renderer* renderer);

            #if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
            // Creates texture from text string
            bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer);
            #endif

            // Renders texture at point
            void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

            // Deallocates texture
            void free();

            // Set color modulation
            void setColor(uint8_t r, uint8_t g, uint8_t b);

            // Set blending
            void setBlendMode(SDL_BlendMode blending);

            // Set alpha modulation
            void setAlpha(uint8_t a);

            // Image dimension getters
            int getWidth();
            int getHeight();

        private:
            // SDL texture
            SDL_Texture* m_texture;

            // Renderer associated with texture
            SDL_Renderer* m_renderer;

            // Image dimensions
            int m_width;
            int m_height;
    };
}

#endif
