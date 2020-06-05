#include "Enemy.hpp"

#include "Bullet.hpp"

Enemy::Enemy() : Actor(EntityType::enemy) {}

Enemy::Enemy(int x, int y) : Actor(EntityType::enemy, x, y) {}

Enemy::Enemy(int x, int y, Expedition::Texture* texture) : Actor(EntityType::enemy, x, y, texture) {}

void Enemy::move(int levelWidth, int levelHeight, std::vector<Entity*> entities) {
    // Get player coords
    Entity* player = entities.at(0);
    int playerX = player->getPosX() + player->getWidth() / 2;
    int playerY = player->getPosY() + player->getHeight() / 2;

    // Get enemy center coordinates
    int centerX = m_posX + m_width / 2;
    int centerY = m_posY + m_height / 2;

    // Get angle to player and calulate velocities
    double angle = atan2(playerY - centerY, playerX - centerX);
    m_velX = (double)ENEMY_VEL * cos(angle);
    m_velY = (double)ENEMY_VEL * sin(angle);

    // Move left or right
    int xMove = floor(m_velX);
    double oldAccumX = m_accumX;
    m_accumX += m_velX - xMove;
    if (m_accumX >= 1.0) {
        xMove += floor(m_accumX);
        m_accumX -= floor(m_accumX);
    }
    m_posX += xMove;
    m_collider.x = m_posX;

    // Keep in bounds
    if (m_posX < 0 || m_posX + m_width > levelWidth) {
        m_posX -= xMove;
        m_collider.x = m_posX;
        m_accumX = oldAccumX;
    }
    // Check collision
    for (Entity* other : entities) {
        if (other != this && Entity::checkCollision(other)) {
            switch (other->getType()) {
                case EntityType::player:
                    other->remove();
                    break;
                case EntityType::wall:
                    m_posX -= xMove;
                    m_collider.x = m_posX;
                    m_accumX = oldAccumX;
                    break;
                case EntityType::enemy:
                    m_posX -= xMove;
                    m_collider.x = m_posX;
                    m_accumX = oldAccumX;
                    break;
                case EntityType::bullet:
                    break;
            }
        }
    }

    // Move up or down
    int yMove = floor(m_velY);
    double oldAccumY = m_accumY;
    m_accumY += m_velY - yMove;
    if (m_accumY >= 1.0) {
        yMove += floor(m_accumY);
        m_accumY -= floor(m_accumY);
    }
    m_posY += yMove;
    m_collider.y = m_posY;

    // Keep in bounds
    if (m_posY < 0 || m_posY + m_height > levelHeight) {
        m_posY -= yMove;
        m_collider.y = m_posY;
        m_accumY = oldAccumY;
    }
    // Check collision
    for (Entity* other : entities) {
        if (other != this && Entity::checkCollision(other)) {
            switch (other->getType()) {
                case EntityType::player:
                    other->remove();
                    break;
                case EntityType::wall:
                    m_posY -= yMove;
                    m_collider.y= m_posY;
                    m_accumY = oldAccumY;
                    break;
                case EntityType::enemy:
                    m_posY -= yMove;
                    m_collider.y = m_posY;
                    m_accumY = oldAccumY;
                    break;
                case EntityType::bullet:
                    break;
            }
        }
    }

    // Check for bullet hit
    for (Bullet* bullet : Bullet::bulletList) {
        if (Entity::checkCollision(bullet)) {
            m_remove = true;
        }
    }
}
