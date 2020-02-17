#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "Entity.hpp"

class Actor: public Entity {
    public:
        // Inits variables
        Actor();
        Actor(int x, int y);
        Actor(int x, int y, std::string texturePath, SDL_Renderer* renderer);

        // Moves the actor
        void move(int levelWidth, int levelHeight);

        // Collision with another entity
        bool checkCollision(Entity e);

    protected:
        // Velocity of the actor
        int m_velX;
        int m_velY;
};

#endif
