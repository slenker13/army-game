#ifndef CAMERA2D_HPP
#define CAMERA2D_HPP

#include <SDL2/SDL_rect.h>

namespace Expedition {
    class Camera2D {
        public:
            // Init variables
            Camera2D(int x, int y, int screenWidth, int screenHeight, int levelWidth, int levelHeight);

            // Updates camera position in bounds
            void updatePosition(int x, int y);

            // Getter
            SDL_Rect getCameraRect();
        
        private:
            // Camera area
            SDL_Rect m_cameraRect;

            // Level Dimension
            int m_levelWidth;
            int m_levelHeight;
    };
}

#endif
