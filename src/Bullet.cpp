#include "Bullet.hpp"

#include <math.h>
#include <vector>

// Define static variables
std::vector<Bullet*> Bullet::bulletList;

Bullet::Bullet(int x, int y, double angle) : Entity(x, y, 4, 4), m_remove(false) {
    // Calculate X and Y velocities from angle
    double angleRads = angle * M_PI / 180.0;
    m_velX = (double)BULLET_VEL * cos(angleRads);
    m_velY = (double)BULLET_VEL * sin(angleRads);
}

void Bullet::render(int camX, int camY, SDL_Renderer* renderer) {
    // Draw bullet using FillRect
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_Rect renderRect = {m_posX - camX, m_posY - camY, m_width, m_height};
    SDL_RenderFillRect(renderer, &renderRect);
}

void Bullet::move(int levelWidth, int levelHeight, std::vector<Entity*> entities) {
    // Move left or right
    m_posX = round(m_posX + m_velX);
    m_collider.x = m_posX;

    // Keep in bounds
    if (m_posX < 0 || m_posX + m_width > levelWidth) {
        m_remove = true;
    }
    // Check collision (skip player at pos 0)
    for (int i = 1; i < entities.size(); i++) {
        if (entities.at(i) != this && Entity::checkCollision(entities.at(i))) {
            m_remove = true;
        }
    }

    // Move the dot up or down
    m_posY += m_velY;
    m_collider.y = m_posY;

    // Keep in bounds
    if (m_posY < 0 || m_posY + m_height > levelHeight) {
        m_remove = true;
    }
    // Check collision (skip player at pos 0)
    for (int i = 1; i < entities.size(); i++) {
        if (entities.at(i) != this && Entity::checkCollision(entities.at(i))) {
            m_remove = true;
        }
    }
}

bool Bullet::isRemoved() {
    return m_remove;
}
