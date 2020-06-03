#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>

#include "Expedition/Expedition.hpp"

#include "Player.hpp"
#include "Wall.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

// Screen dimension constants
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;
const int LEVEL_WIDTH = 1920;
const int LEVEL_HEIGHT = 1440;

// Fixed delta time (60 FPS)
const double dt = 1 / 120.0;

// Loads media from file
bool loadMedia();

void close();

// Game window
Expedition::Window g_window;

// Scene textues
Expedition::Texture g_bgTexture;

void close() {
    // Destroy window (destroys renderer)
    g_window.free();

    // Free background texture
    g_bgTexture.free();

    // Close engine (closes SDL)
    Expedition::close();
}

bool loadMedia() {
    bool success = true;

    // Load level grid
    if (!g_bgTexture.loadFromFile("data/background.png", g_window.getRenderer())) {
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
        if (!g_window.init("Game Window", SCREEN_WIDTH, SCREEN_HEIGHT, false, true)) {
            printf("ERROR: Window initialization failed.\n");
        } else {
            if (!loadMedia()) {
                printf("ERROR: Failed to load media.\n");
            } else {
                // Main loop flag
                bool quit = false;

                // Event handler
                SDL_Event e;

                // Initialize texture cache
                Expedition::TextureCache g_textureCache(g_window.getRenderer());

                // Camera
                Expedition::Camera2D camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_WIDTH, LEVEL_HEIGHT);
                int camX = camera.getCameraRect()->x;
                int camY = camera.getCameraRect()->y;

                // Entity vector
                std::vector<Entity*> entityList;

                // Timestep timer
                Expedition::Timer stepTimer;
                double accumulator = 0.0;

                // Player
                Player player(LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2, g_textureCache.getTexture("data/player.png"));
                entityList.push_back(&player);

                // Walls
                SDL_Color black = {0x00, 0x00, 0x00, 0xFF};
                Wall wall1(600, 300, 40, 400, black);
                entityList.push_back(&wall1);
                Wall wall2(1200, 300, 40, 400, black);
                entityList.push_back(&wall2);

                Enemy* enemy = new Enemy(player.getPosX(), player.getPosY() - 100, g_textureCache.getTexture("data/enemy.png"));
                entityList.push_back(enemy);

                // GAME LOOP
                while (!quit) {
                    // Get timestep
                    float timestep = stepTimer.getTicks() / 1000.0f;
                    accumulator += timestep;
                    // Restart timer
                    stepTimer.start();

                    // Print FPS
                    // if (timestep != 0) {
                    //     printf("FPS: %f\n", 1.0f / timestep);
                    // }

                    /******** UPDATE ********/
                    while (accumulator >= dt) {
                        // Handle events on queue
                        while (SDL_PollEvent(&e) != 0) {
                            // Close window
                            if (e.type == SDL_QUIT) {
                                quit = true;
                            }

                            g_window.handleEvent(e);
                            player.handleEvent(e);
                        }

                        // Player update
                        player.move(LEVEL_WIDTH, LEVEL_HEIGHT, entityList);
                        player.shoot();
                        camera.updatePosition((player.getPosX() + player.getWidth() / 2) - SCREEN_WIDTH / 2, (player.getPosY() + player.getHeight() / 2) - SCREEN_HEIGHT / 2);
                        camX = camera.getCameraRect()->x;
                        camY = camera.getCameraRect()->y;

                        // Calculate rotation angle
                        player.calculateAngle(camX, camY);
                        
                        // Move bullets
                        for (Bullet* bullet : Bullet::bulletList) {
                            bullet->move(LEVEL_WIDTH, LEVEL_HEIGHT, entityList);
                        }

                        // Move enemies
                        for (Entity* entity : entityList) {
                            if (entity->getType() == EntityType::enemy) {
                                static_cast<Enemy*>(entity)->move(LEVEL_WIDTH, LEVEL_HEIGHT, entityList);
                            }
                        }   

                        // Remove entities
                        std::vector<Entity*>::iterator entityIt = entityList.begin();
                        while (entityIt != entityList.end()) {
                            Entity* entity = *entityIt;
                            if (entity->isRemoved()) {
                                entityIt = entityList.erase(entityIt);
                                delete entity;
                            } else {
                                entityIt++;
                            }
                        }
                        
                        // Remove bullets
                        std::vector<Bullet*>::iterator bulletIt = Bullet::bulletList.begin();
                        while (bulletIt != Bullet::bulletList.end()) {
                            Bullet* bullet = *bulletIt;
                            if (bullet->isRemoved()) {
                                bulletIt = Bullet::bulletList.erase(bulletIt);
                                delete bullet;
                            } else {
                                bulletIt++;
                            }
                        }

                        // Decrease accumulator
                        accumulator -= dt;
                    }
                    /****************/

                    /******** RENDER ********/
                    // Clear screen
                    g_window.clearScreen();

                    // Render scene
                    g_bgTexture.render(0, 0, camera.getCameraRect());

                    // Render entities
                    for (Entity* entity : entityList) {
                        switch (entity->getType()) {
                            case EntityType::player:
                                static_cast<Player*>(entity)->render(camX, camY);
                                break;
                            case EntityType::wall:
                                static_cast<Wall*>(entity)->render(camX, camY, g_window.getRenderer());
                                break;
                            case EntityType::enemy:
                                static_cast<Enemy*>(entity)->render(camX, camY);
                                break;
                            case EntityType::bullet:
                                // Do nothing
                                break;
                        }
                    }

                    // Render bullets
                    for (Bullet* bullet : Bullet::bulletList) {
                        bullet->render(camX, camY, g_window.getRenderer());
                    }

                    // Update screen
                    g_window.render();
                    /****************/
                }
            }
        }
    }
    close();

    return 0;
}
