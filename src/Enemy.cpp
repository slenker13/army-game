#include "Enemy.hpp"

#include "Bullet.hpp"

Enemy::Enemy() : Actor(EntityType::enemy) {}

Enemy::Enemy(int x, int y) : Actor(EntityType::enemy, x, y) {}

Enemy::Enemy(int x, int y, Expedition::Texture* texture) : Actor(EntityType::enemy, x, y, texture) {}

void Enemy::move(int levelWidth, int levelHeight, std::vector<Entity*> entities) {
    // m_velX = 2;
    // m_velY = 2;

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
            switch (other->getType()) {
                case EntityType::player:
                    
                    break;
                case EntityType::wall:
                    m_posX -= m_velX;
                    m_collider.x = m_posX;
                    break;
                case EntityType::enemy:
                    m_posX -= m_velX;
                    m_collider.x = m_posX;
                    break;
                case EntityType::bullet:
                    break;
            }
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
            switch (other->getType()) {
                case EntityType::player:
                    printf("PLAYER COLLISION\n");
                    break;
                case EntityType::wall:
                    m_posY -= m_velY;
                    m_collider.y= m_posY;
                    break;
                case EntityType::enemy:
                    m_posY -= m_velY;
                    m_collider.y = m_posY;
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
