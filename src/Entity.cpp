#include "Entity.hpp"

#include <SDL2/SDL_render.h>

Entity::Entity() : m_posX(0), m_posY(0), m_width(0), m_height(0) {
    m_collider.w = 0;
    m_collider.h = 0;
}

Entity::Entity(int x, int y) : m_posX(x), m_posY(y), m_width(0), m_height(0) {
    m_collider.w = 0;
    m_collider.h = 0;
}

Entity::Entity(int x, int y, int width, int height) : m_posX(x), m_posY(y), m_width(width), m_height(height) {
    m_collider.w = width;
    m_collider.h = height;
}

Entity::Entity(int x, int y, Expedition::Texture* texture) : m_posX(x), m_posY(y), m_texture(texture) {
    m_width = texture->getWidth();
    m_height = texture->getHeight();
    m_collider.w = m_width;
    m_collider.h = m_height;
}

void Entity::setTexture(Expedition::Texture* texture) {
    m_texture = texture;
    m_width = texture->getWidth();
    m_height = texture->getHeight();
    m_collider.w = m_width;
    m_collider.h = m_height;
}

void Entity::render(int camX, int camY, double angle) {
    m_texture->render(m_posX - camX, m_posY - camY, nullptr, angle, nullptr, SDL_FLIP_NONE);
}

bool Entity::checkCollision(Entity* other) {
    // Sides of each rect
    int left, otherLeft;
    int right, otherRight;
    int top, otherTop;
    int bottom, otherBottom;

    // Calculate sides
    left = m_posX;
    right = m_posX + m_width;
    top = m_posY;
    bottom = m_posY + m_height;

    // Calculate other's sides
    otherLeft = other->getPosX();
    otherRight = other->getPosX() + other->getWidth();
    otherTop = other->getPosY();
    otherBottom = other->getPosY() + other->getHeight();

    // Check if any sides are outside
    if (bottom <= otherTop) return false;
    if (top >= otherBottom) return false;
    if (right <= otherLeft) return false;
    if (left >= otherRight) return false;

    // Intersection
    return true;
}

int Entity::getPosX() { return m_posX; }
int Entity::getPosY() {return m_posY; }
int Entity::getWidth() { return m_width; }
int Entity::getHeight() {return m_height; }
