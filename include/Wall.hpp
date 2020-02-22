#ifndef WALL_HPP
#define WALL_HPP

#include "Entity.hpp"

class Wall: public Entity {
    public:
        // Set variables
        Wall(int x, int y, int width, int height, SDL_Color color);

        // Renders wall using FillRect
        void render(int camX, int camY, SDL_Renderer* renderer);

    private:
        // Color of the wall
        SDL_Color m_color;

        // Rect used to render
        SDL_Rect m_renderRect;
};

#endif
