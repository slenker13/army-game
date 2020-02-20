#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL_events.h>

#include "Actor.hpp"

class Player: public Actor {
    public:
        // Maximum axis velocity of the player
        static const int PLAYER_VEL = 5;

        // Initialize player
        Player();
        Player(int x, int y);
        Player(int x, int y, Expedition::Texture* texture);

        // Handle input events
        void handleEvent(SDL_Event& e);
};

#endif
