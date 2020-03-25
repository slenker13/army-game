#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL_events.h>

#include "Expedition/Timer.hpp"

#include "Actor.hpp"

class Player: public Actor {
    public:
        // Maximum axis velocity of the player
        static const int PLAYER_VEL = 3;

        // Initialize player
        Player();
        Player(int x, int y);
        Player(int x, int y, Expedition::Texture* texture);

        // Calulate rotation angle based on the mouse position
        void calculateAngle(int camX, int camY);

        // Calls Entity render function with member angle
        void render(int camX, int camY);

        // Shoot gun
        void shoot();

        // Handle input events
        void handleEvent(SDL_Event& e);

    private:
        // Rotation angle
        double m_angle;
};

#endif
