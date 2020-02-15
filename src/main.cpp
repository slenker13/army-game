#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>

#include "Expedition.hpp"


// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Loads media from file
bool loadMedia();

void close();

// Game window
Expedition::Window g_window;

// Scene textures
Expedition::Texture g_texture;

void close() {
    // Destroy window (destroys renderer)
    g_window.free();

    // Free textures
    g_texture.free();

    Expedition::close();
}

bool loadMedia() {
    bool success = true;

    if (!g_texture.loadFromFile("data/smile.png", g_window.getRenderer())) {
        printf("ERROR: Failed to load texture.\n");
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
            printf("ERROR: Window initialization failed.");
        } else {
            if (!loadMedia()) {
                printf("ERROR: Failed to load media.\n");
            } else {
                // Main look flag
                bool quit = false;

                // Event handler
                SDL_Event e;

                // GAME LOOP
                while (!quit) {
                    // Handle events on queue
                    while (SDL_PollEvent(&e) != 0) {
                        // Close window
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }

                        g_window.handleEvent(e);
                    }

                    // Only draw if window is not minimized
                    if (!g_window.isMinimized()) {
                        // Clear screen
                        g_window.clearScreen();

                        // Render scene
                        g_texture.render((g_window.getWidth() - g_texture.getWidth()) / 2, (g_window.getHeight() - g_texture.getHeight()) / 2);

                        // Update screen
                        g_window.render();
                    }
                }
            }
        }
    }

    return 0;
}
