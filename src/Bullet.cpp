#include "Bullet.hpp"

#include <math.h>
#include <vector>

// Define static variables
std::vector<Bullet*> Bullet::bulletList;

Bullet::Bullet(int x, int y, double angle) : Entity(EntityType::bullet, x, y, 5, 5), m_accumX(0.0), m_accumY(0.0) {
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
    int xMove = floor(m_velX);
    m_accumX += m_velX - xMove;
    if (m_accumX >= 1.0) {
        xMove += floor(m_accumX);
        m_accumX -= floor(m_accumX);
    }
    m_posX += xMove;
    m_collider.x = m_posX;

    // Keep in bounds
    if (m_posX < 0 || m_posX + m_width > levelWidth) {
        m_remove = true;
    }

    // Move the dot up or down
    int yMove = floor(m_velY);
    m_accumY += m_velY - yMove;
    if (m_accumY >= 1.0) {
        yMove += floor(m_accumY);
        m_accumY -= floor(m_accumY);
    }
    m_posY += yMove;
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
