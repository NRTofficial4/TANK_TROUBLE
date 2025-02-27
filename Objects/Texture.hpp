#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

SDL_Texture* TextureLoad(const char *filename,SDL_Renderer *renderer){
    SDL_Surface *surface = IMG_Load(filename);
    if(surface == nullptr){
        std::cout << "Could not found the picture !\n";
    }
    SDL_Texture *ImTexture = SDL_CreateTextureFromSurface(renderer,surface);
    if(ImTexture == nullptr){
        std::cout << "ImTexture not initialized !\n";
    }
    SDL_FreeSurface(surface);

    return ImTexture;
}