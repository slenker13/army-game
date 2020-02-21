#include "Player.hpp"

#include <math.h>

Player::Player() {}

Player::Player(int x, int y) : Actor(x, y) {}

Player::Player(int x, int y, Expedition::Texture* texture) : Actor(x, y, texture) {}

void Player::handleEvent(SDL_Event& e) {
    // Key pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym)  {
            case SDLK_w: m_velY -= PLAYER_VEL; break;
            case SDLK_s: m_velY += PLAYER_VEL; break;
            case SDLK_a: m_velX -= PLAYER_VEL; break;
            case SDLK_d: m_velX += PLAYER_VEL; break;
        }
    }
    // Key released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w: m_velY += PLAYER_VEL; break;
            case SDLK_s: m_velY -= PLAYER_VEL; break;
            case SDLK_a: m_velX += PLAYER_VEL; break;
            case SDLK_d: m_velX -= PLAYER_VEL; break;
        }
    }
}
