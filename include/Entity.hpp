#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

#include "Expedition/Texture.hpp"

// Enum for entity type
enum class EntityType {
    player,
    enemy,
    wall,
    bullet
};

class Entity {
    public:
        // Init entity
        Entity(EntityType type);
        Entity(EntityType type, int x, int y);
        Entity(EntityType type, int x, int y, int width, int height);
        Entity(EntityType type, int x, int y, Expedition::Texture* texture);

        // Loads texture
        void setTexture(Expedition::Texture* texture);

        // Renders the entity relative to the camera
        void render(int camX, int camY, double angle = 0.0);

        // Checks the collision between this and another entity
        bool checkCollision(Entity* other);

        // Sets remove flag
        void remove();

        // Getters
        int getPosX();
        int getPosY();
        int getWidth();
        int getHeight();
        EntityType getType();
        bool isRemoved();

    protected:
        // Entity type
        EntityType m_type;

        // Entity offsets
        int m_posX;
        int m_posY;

        // Entity dimensions
        int m_width;
        int m_height;

        // Collision box
        SDL_Rect m_collider;

        // Entity texture
        Expedition::Texture* m_texture;

        // Deletion flag
        bool m_remove;
};

#endif
