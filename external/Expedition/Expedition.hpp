#ifndef EXPEDITION_HPP
#define EXPEDITION_HPP

// Expedition Engine headers
#include "Texture.hpp"
#include "Timer.hpp"
#include "Window.hpp"
#include "Camera2D.hpp"
#include "TextureCache.hpp"

namespace Expedition {
    // Initializes SDL systems
    bool init();

    // Quits SDL systems
    void close();
}

#endif
