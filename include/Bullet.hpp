#ifndef BULLET_HPP
#define BULLET_HPP

#include <vector>

#include "Entity.hpp"

// TODO: enum for bullet type

class Bullet: public Entity {
    public:
        // Constant bullet velocity
        static const int BULLET_VEL = 8;

        // Static list of bullets
        static std::vector<Bullet*> bulletList;

        // Constructor
        Bullet(int x, int y, double angle);

        // Renders bullet using FillRect
        void render(int camX, int camY, SDL_Renderer* renderer);

        // Moves the bullet at a constant velocity
        void move(int levelWidth, int levelHeight, std::vector<Entity*> entities);

    private:
        // X and Y velocity calculated from the angle
        double m_velX;
        double m_velY;

        // Velocity accumulators
        double m_accumX;
        double m_accumY;
};

#endif
