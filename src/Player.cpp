#include "Player.hpp"

Player::Player() {}

Player::Player(int x, int y) : Actor(x, y) {}

Player::Player(int x, int y, std::string texturePath, SDL_Renderer* renderer) : Actor(x, y, texturePath, renderer) {}

void Player::handleEvent(SDL_Event& e) {
    // Key pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym)  {
            case SDLK_UP: m_velY -= PLAYER_VEL; break;
            case SDLK_DOWN: m_velY += PLAYER_VEL; break;
            case SDLK_LEFT: m_velX -= PLAYER_VEL; break;
            case SDLK_RIGHT: m_velX += PLAYER_VEL; break;
        }
    }
    // Key released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: m_velY += PLAYER_VEL; break;
            case SDLK_DOWN: m_velY -= PLAYER_VEL; break;
            case SDLK_LEFT: m_velX += PLAYER_VEL; break;
            case SDLK_RIGHT: m_velX -= PLAYER_VEL; break;
        }
    }
}
