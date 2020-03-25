#include "Bullet.hpp"

#include <math.h>
#include <vector>

// Define static variables
std::vector<Bullet*> Bullet::bulletList;

Bullet::Bullet(int x, int y, double angle) : Entity(x, y, 4, 4) {
    // Calculate X and Y velocities from angle
    double angleRads = angle * M_PI / 180.0;
    m_velX = BULLET_VEL * cos(angleRads);
    m_velY = BULLET_VEL * sin(angleRads);
}

void Bullet::render(int camX, int camY, SDL_Renderer* renderer) {
    // Draw bullet using FillRect
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_Rect renderRect = {m_posX - camX, m_posY - camY, m_width, m_height};
    SDL_RenderFillRect(renderer, &renderRect);
}

void Bullet::move(int levelWidth, int levelHeight, std::vector<Entity*> entities) {
    // Move left or right
    m_posX += m_velX;
    m_collider.x = m_posX;

    // Keep in bounds
    if (m_posX < 0 || m_posX + m_width > levelWidth) {

    }
    // Check collision
    for (Entity* other : entities) {
        if (other != this && Entity::checkCollision(other)) {

        }
    }

    // Move the dot up or down
    m_posY += m_velY;
    m_collider.y = m_posY;

    // Keep in bounds
    if (m_posY < 0 || m_posY + m_height > levelHeight) {

    }
    // Check collision
    for (Entity* other : entities) {
        if (other != this && Entity::checkCollision(other)) {

        }
    }
}
