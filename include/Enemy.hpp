#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Actor.hpp"

class Enemy : public Actor {
    public:
        // Maximum axis velocity of the enemy
        static const int ENEMY_VEL = 2;

        // Initialize enemy
        Enemy();
        Enemy(int x, int y);
        Enemy(int x, int y, Expedition::Texture* texture);

        // Calculates the enemies movement
        void move(int levelWidth, int levelHeight, std::vector<Entity*> entities);
};

#endif
