#include "Actor.hpp"

Actor::Actor(EntityType type) : Entity(type), m_velX(0.0), m_velY(0.0), m_accumX(0.0), m_accumY(0.0) {}

Actor::Actor(EntityType type, int x, int y) : Entity(type, x, y), m_velX(0.0), m_velY(0.0), m_accumX(0.0), m_accumY(0.0) {}

Actor::Actor(EntityType type, int x, int y, Expedition::Texture* texture) : 
    Entity(type, x, y, texture), m_velX(0.0), m_velY(0.0), m_accumX(0.0), m_accumY(0.0) {}

// UNUSED
void Actor::move(int levelWidth, int levelHeight, std::vector<Entity*> entities) {
    // Move left or right
    m_posX += m_velX;
    m_collider.x = m_posX;

    // Keep in bounds
    if (m_posX < 0 || m_posX + m_width > levelWidth) {
        m_posX -= m_velX;
        m_collider.x = m_posX;
    }
    // Check collision
    for (Entity* other : entities) {
        if (other != this && Entity::checkCollision(other)) {
            m_posX -= m_velX;
            m_collider.x = m_posX;
        }
    }

    // Move up or down
    m_posY += m_velY;
    m_collider.y = m_posY;

    // Keep in bounds
    if (m_posY < 0 || m_posY + m_height > levelHeight) {
        m_posY -= m_velY;
        m_collider.y = m_posY;
    }
    // Check collision
    for (Entity* other : entities) {
        if (other != this && Entity::checkCollision(other)) {
            m_posY -= m_velY;
            m_collider.y = m_posY;
        }
    }
}
