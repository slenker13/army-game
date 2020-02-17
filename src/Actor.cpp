#include "Actor.hpp"

Actor::Actor() : m_velX(0), m_velY(0) {}

Actor::Actor(int x, int y) : Entity(x, y), m_velX(0), m_velY(0) {}

Actor::Actor(int x, int y, std::string texturePath, SDL_Renderer* renderer) : 
    Entity(x, y, texturePath, renderer), m_velX(0), m_velY(0) {}

void Actor::move(int levelWidth, int levelHeight) {
    // Move left or right
    m_posX += m_velX;

    // Keep in bounds
    if (m_posX < 0 || m_posX + m_width > levelWidth) {
        m_posX -= m_velX;
    }

    // Move the dot up or down
    m_posY += m_velY;

    // Keep in bounds
    if (m_posY < 0 || m_posY + m_height > levelHeight) {
        m_posY -= m_velY;
    }
}
