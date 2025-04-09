#define SDL_MAIN_HANDLED
#include "include/SDL2/SDL.h"
#include <iostream>

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow(
        "Simple SDL2 Window",            // Window title
        SDL_WINDOWPOS_CENTERED,          // Initial x position
        SDL_WINDOWPOS_CENTERED,          // Initial y position
        800,                             // Width, in pixels
        600,                             // Height, in pixels
        SDL_WINDOW_SHOWN                 // Flags
    );

    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Main loop flag
    bool quit = false;
    SDL_Event event;

    // Main event loop
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        // We can add rendering code here later if needed
    }

    // Clean up and quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}