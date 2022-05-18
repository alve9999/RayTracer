#include <SDL2/SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <array>
#include "shader.h"

SDL_Window* window;
SDL_Renderer* renderer;
bool is_running;
std::array<std::array<glm::vec3,1080>,1920> image;


int main(int argc, char* argv[]){
    window = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    is_running = true;
    while(is_running){
        //SDL_PumpEvents();
        //SDL_Event event;
        //
        //SDL_PollEvent(&event);
        //switch (event.type){
        //    case SDL_QUIT:
        //        is_running = false;
        //    default:
        //        ;
        //}
        //SDL_RenderClear(renderer);
        shader(image);
        //for(int i = 0; i < image.size(); i++){
        //    for(int j = 0; j < image[i].size(); j++){
        //        SDL_SetRenderDrawColor(renderer, image[i][j].x, image[i][j].y, image[i][j].z, 255);
        //        SDL_RenderDrawPoint(renderer, i, j);
        //    }
        //}
        //SDL_RenderPresent(renderer);
        //SDL_Delay(10000);
    }
    return 0;
}