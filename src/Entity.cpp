#include "Entity.hpp"

#include <SDL2/SDL_render.h>

Entity::Entity() : m_posX(0), m_posY(0), m_width(0), m_height(0) {}

Entity::Entity(int x, int y) : m_posX(x), m_posY(y), m_width(0), m_height(0) {}

Entity::Entity(int x, int y, Expedition::Texture* texture) : m_posX(x), m_posY(y), m_texture(texture) {
    m_width = texture->getWidth();
    m_height = texture->getHeight();
}

void Entity::setTexture(Expedition::Texture* texture) {
    m_texture = texture;
    m_width = texture->getWidth();
    m_height = texture->getHeight();
}

void Entity::render(int camX, int camY, double angle) {
    m_texture->render(m_posX - camX, m_posY - camY, nullptr, angle, nullptr, SDL_FLIP_NONE);
}

int Entity::getPosX() { return m_posX; }
int Entity::getPosY() {return m_posY; }
int Entity::getWidth() { return m_width; }
int Entity::getHeight() {return m_height; }
