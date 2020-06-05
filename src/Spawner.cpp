#include "Spawner.hpp"

Spawner::Spawner() {}

bool Spawner::spawn() {
    bool spawn = false;
    int spawnInterval;

    if (!m_gameTimer.isStarted()) m_gameTimer.start();

    if (m_gameTimer.getTicks() < 1000 * 30) {   // 30 seconds
        spawnInterval = 3000;   // 3 seconds
    } else if (m_gameTimer.getTicks() < 1000 * 60) {    // 60 seconds
        spawnInterval = 1000;   // 1 second
    } else {
        spawnInterval = 500;    // .5 seconds
    }

    if (!m_spawnTimer.isStarted() || m_spawnTimer.getTicks() > spawnInterval) {
        // Create enemy
        spawn = true;
        m_spawnTimer.start();
    }

    return spawn;
}
