#include "Entity.hpp"

#include <SDL2/SDL_render.h>

Entity::Entity() : m_posX(0), m_posY(0), m_width(0), m_height(0) {}

Entity::Entity(int x, int y) : m_posX(x), m_posY(y), m_width(0), m_height(0) {}

Entity::Entity(int x, int y, std::string texturePath, SDL_Renderer* renderer) : m_posX(x), m_posY(y), m_width(0), m_height(0) {
    initTexture(texturePath, renderer);
}

Entity::~Entity() {
    m_texture.free();
}

bool Entity::initTexture(std::string texturePath, SDL_Renderer* renderer) {
    // Success flag
    bool success = true;

    if (!m_texture.loadFromFile(texturePath, renderer)) {
        printf("ERROR: Failed to load texture entity from %s.\n", texturePath.c_str());
        success = false;
    } else {
        m_width = m_texture.getWidth();
        m_height = m_texture.getHeight();
    }

    return success;
}

void Entity::render(int camX, int camY) {
    m_texture.render(m_posX - camX, m_posY - camY);
}

int Entity::getPosX() { return m_posX; }
int Entity::getPosY() {return m_posY; }
int Entity::getWidth() { return m_width; }
int Entity::getHeight() {return m_height; }
