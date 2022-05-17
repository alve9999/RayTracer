#include <SDL2/SDL.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool is_running = false;

int main(int argc, char* argv[])
{
    window = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    is_running = true;
    
    SDL_PumpEvents();
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
