#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "Entity.hpp"

#include <vector>

class Actor: public Entity {
    public:
        // Inits variables
        Actor();
        Actor(int x, int y);
        Actor(int x, int y, Expedition::Texture* texture);

        // Moves the actor
        void move(int levelWidth, int levelHeight, std::vector<Entity*> entities);

    protected:
        // Velocity of the actor
        int m_velX;
        int m_velY;
};

#endif
