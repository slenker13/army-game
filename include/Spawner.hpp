#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include "Expedition/Timer.hpp"

class Spawner {
    public:
        // Initialize spawner
        Spawner();

        // Returns true if enemy is ready to be spawned
        bool spawn();

    private:
        // Spawning timer
        Expedition::Timer m_spawnTimer;

        // Game timer
        Expedition::Timer m_gameTimer;
};

#endif
