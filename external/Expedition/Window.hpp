#ifndef EXPEDITION_WINDOW_HPP
#define EXPEDITION_WINDOW_HPP

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>

#include <string>

namespace Expedition {
    // Wrapper class for SDL_Window
    class Window {
        public:
            // Init variables
            Window();

            // Create window
            bool init(std::string name, int width, int height, bool resizable, bool vsync);

            // Delete window
            void free();

            // Handle window events
            void handleEvent(SDL_Event& e);

            // Get renderer
            SDL_Renderer* getRenderer();

            // Focus on the window
            void focus();

            // Clear window contents
            void clearScreen();

            // Draw window contents
            void render();

            // Window dimensions
            int getWidth();
            int getHeight();

            //  Window focii
            bool hasMouseFocus();
            bool hasKeyboardFocus();
            bool isFullscreen();
            bool isMinimized();
            bool isShown();

        private:
            // Window data
            SDL_Window* m_window;
            SDL_Renderer* m_renderer;

            // Window dimensions
            int m_width;
            int m_height;

            // Window focus
            bool m_mouseFocus;
            bool m_keyboardFocus;
            bool m_fullScreen;
            bool m_minimized;
            bool m_shown;
    };
}

#endif
