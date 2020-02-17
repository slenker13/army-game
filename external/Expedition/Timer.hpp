#ifndef EXPEDITION_TIMER_HPP
#define EXPEDITION_TIMER_HPP

#include <stdint.h>

namespace Expedition {
    // Timer management class
    class Timer {
        public:
            // Init variables
            Timer();

            // Clock actions
            void start();
            void stop();
            void pause();
            void unpause();

            // Get timer time
            uint32_t getTicks();

            // Check status
            bool isStarted();
            bool isPaused();

        private:
            // Ticks when the timer was started
            uint32_t m_startTicks;

            // Ticks when the time was paused
            uint32_t m_pausedTicks;

            // Timer status
            bool m_paused;
            bool m_started;
    };
}

#endif
