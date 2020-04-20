#include "Player.hpp"

#include <math.h>

#include "Bullet.hpp"

Player::Player() : m_angle(0.0) {}

Player::Player(int x, int y) : Actor(x, y), m_angle(0.0) {}

Player::Player(int x, int y, Expedition::Texture* texture) : Actor(x, y, texture), m_angle(0.0) {}

void Player::calculateAngle(int camX, int camY) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    int centerX = m_posX - camX + (m_width / 2);
    int centerY = m_posY - camY + (m_height / 2);
    m_angle = atan2(y - centerY, x - centerX) * 180.0 / M_PI;
}

void Player::render(int camX, int camY) {
    Entity::render(camX, camY, m_angle + 90);
}

void Player::shoot() {
    if (m_shooting && (!m_shootTimer.isStarted() || m_shootTimer.getTicks() > 400)) {
        // Calculate muzzle position
        // Center coordinates
        int x = m_posX + m_width / 2 - 2;
        int y = m_posY + m_height / 2 - 2;
        // Move towards mouse
        int distance = m_width / 2;
        double angleRads = m_angle * M_PI / 180.0;
        x += distance * cos(angleRads);
        y += distance * sin(angleRads);
        
        // Create new bullet and add it to the list
        Bullet::bulletList.push_back(new Bullet(x, y, m_angle));

        // Restart timer
        m_shootTimer.start();
    }
}

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

    // Mouse click
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        m_shooting = true;
    }
    if (e.type == SDL_MOUSEBUTTONUP) {
        m_shooting = false;
        m_shootTimer.stop();
    }
}
