#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include "Expedition/Texture.hpp"

class Entity {
    public:
        // Init entity
        Entity();
        Entity(int x, int y);
        Entity(int x, int y, Expedition::Texture* texture);

        // Loads texture
        void setTexture(Expedition::Texture* texture);

        // Renders the entity relative to the camera
        void render(int camX, int camY, double angle = 0.0);

        // Getters
        int getPosX();
        int getPosY();
        int getWidth();
        int getHeight();

    protected:
        // Entity offsets
        int m_posX;
        int m_posY;

        // Entity dimensions
        int m_width;
        int m_height;

        // Entity texture
        Expedition::Texture* m_texture;
};

#endif
