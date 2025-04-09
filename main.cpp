#define SDL_MAIN_HANDLED

#include<iostream>
#include"window.cpp"

#include"Colision.cpp"
#include"Sound.cpp"

Window window;

int main(){
    window.WindowInit();
    while(window.running){
        window.endrund = false;
        window.FrameStart = SDL_GetTicks();
        window.Events();
        window.Render();
        window.FrameOptymalisation();
    }
    window.DestroyWindow();
    return 0;
}