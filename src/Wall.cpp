#include "Wall.hpp"

Wall::Wall(int x, int y, int width, int height, SDL_Color color) : Entity(x, y, width, height), m_color(color) {
    m_renderRect.x = x;
    m_renderRect.y = y;
    m_renderRect.w = width;
    m_renderRect.h = height;
}

void Wall::render(int camX, int camY, SDL_Renderer* renderer) {
    // Draw wall using FillRect
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    m_renderRect.x = m_posX - camX;
    m_renderRect.y = m_posY - camY;
    SDL_RenderFillRect(renderer, &m_renderRect);
}
