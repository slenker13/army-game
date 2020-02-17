#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>

#include "Expedition/Expedition.hpp"

#include "Player.hpp"

// Screen dimension constants
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;
const int LEVEL_WIDTH = 1920;
const int LEVEL_HEIGHT = 1440;

// Loads media from file
bool loadMedia();

void close();

// Game window
Expedition::Window g_window;

// Scene textues
Expedition::Texture g_levelGrid;

void close() {
    // Destroy window (destroys renderer)
    g_window.free();

    Expedition::close();
}

bool loadMedia() {
    bool success = true;

    // Load level grid
    if (!g_levelGrid.loadFromFile("data/level-grid.png", g_window.getRenderer())) {
        printf("ERROR: Unable to render level grid texture. SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

int main (int argc, char* args[]) {
    // Start up SDL and create window
    if (!Expedition::init()) {
        printf("ERROR: Failed to initialize.\n");
    } else {
        if (!g_window.init("Game Window", SCREEN_WIDTH, SCREEN_HEIGHT, false)) {
            printf("ERROR: Window initialization failed.\n");
        } else {
            if (!loadMedia()) {
                printf("ERROR: Failed to load media.\n");
            } else {
                // Main look flag
                bool quit = false;

                // Event handler
                SDL_Event e;

                // Camera
                Expedition::Camera2D camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT);

                // Player
                Player player(0, 0, "data/smile.png", g_window.getRenderer());

                // GAME LOOP
                while (!quit) {
                    // Handle events on queue
                    while (SDL_PollEvent(&e) != 0) {
                        // Close window
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }

                        g_window.handleEvent(e);
                        player.handleEvent(e);
                    }

                    // Only draw if window is not minimized
                    if (!g_window.isMinimized()) {
                        // Clear screen
                        g_window.clearScreen();

                        // Render background
                        g_levelGrid.render(0, 0);

                        // Update
                        player.move(LEVEL_WIDTH, LEVEL_HEIGHT);
                        camera.updatePosition((player.getPosX() + player.getWidth() / 2) - SCREEN_WIDTH / 2, (player.getPosY() + player.getHeight() / 2) - SCREEN_HEIGHT / 2);

                        // Render
                        player.render(camera.getCameraRect().x, camera.getCameraRect().y);

                        // Update screen
                        g_window.render();
                    }
                }
            }
        }
    }

    return 0;
}
