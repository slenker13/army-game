#include "Entity.hpp"

#include <SDL2/SDL_render.h>

Entity::Entity(EntityType type) : m_type(type), m_posX(0), m_posY(0), m_width(0), m_height(0), m_remove(false) {
    m_collider = {0, 0, 0, 0};
}

Entity::Entity(EntityType type, int x, int y) : m_type(type), m_posX(x), m_posY(y), m_width(0), m_height(0), m_remove(false) {
    m_collider = {x, y, 0, 0};
}

Entity::Entity(EntityType type, int x, int y, int width, int height) : m_type(type), m_posX(x), m_posY(y), m_width(width), m_height(height), m_remove(false) {
    m_collider = {x, y, width, height};
}

Entity::Entity(EntityType type, int x, int y, Expedition::Texture* texture) : m_type(type), m_posX(x), m_posY(y), m_texture(texture), m_remove(false) {
    m_width = texture->getWidth();
    m_height = texture->getHeight();
    m_collider = {x, y, m_width, m_height};
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
    left = m_collider.x;
    right = m_collider.x + m_collider.w;
    top = m_collider.y;
    bottom = m_collider.y + m_collider.h;

    // Calculate other's sides
    otherLeft = other->m_collider.x;
    otherRight = other->m_collider.x + other->m_collider.w;
    otherTop = other->m_collider.y;
    otherBottom = other->m_collider.y + other->m_collider.h;

    // Check if any sides are outside
    if (bottom <= otherTop) return false;
    if (top >= otherBottom) return false;
    if (right <= otherLeft) return false;
    if (left >= otherRight) return false;

    // Intersection
    return true;
}

void Entity::remove() {
    m_remove = true;
}

int Entity::getPosX() { return m_posX; }
int Entity::getPosY() { return m_posY; }
int Entity::getWidth() { return m_width; }
int Entity::getHeight() { return m_height; }
EntityType Entity::getType() { return m_type; }
bool Entity::isRemoved() { return m_remove; }
