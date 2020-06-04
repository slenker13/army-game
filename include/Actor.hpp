#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "Entity.hpp"

#include <vector>

class Actor: public Entity {
    public:
        // Inits variables
        Actor(EntityType type);
        Actor(EntityType type, int x, int y);
        Actor(EntityType type, int x, int y, Expedition::Texture* texture);

        // Moves the actor
        void move(int levelWidth, int levelHeight, std::vector<Entity*> entities);

    protected:
        // Velocity of the actor
        double m_velX;
        double m_velY;

        // Velocity accumulators
        double m_accumX;
        double m_accumY;
};

#endif
