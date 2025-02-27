/*Digital enemy - Additional object that will go through the map till infinity
when Colided with player -> explode -> Player Dead
Movement Explained:
1) Spawn in Random cell (we got all the cell center x,y position)
2) mark cell as visited (in DFS algorythm should end with all cells marked as unvisited)
3) check random path that is true (random number from 0 to 3)
4) define cell to go to next by the number in step 3)
5) go to the next cell, if position ni center of the cell, look for another cell and update the "to follow" point as center of the next cell*/


#include<iostream>
#include<stdbool.h>
#include"../Texture.hpp"

class DigitalEnemy{
    public:
        SDL_Rect rect;
        SDL_Texture *text;

        // vector of dx,dy -> determine how and in which direction should x,y values of Enemy increase/dexrease;
        int dx,dy;
        int x;
        int y;

        void Load(SDL_Renderer *renderer,const char *filename);

        void Render(SDL_Renderer *renderer, int xC, int yC);
        
    private:

        //xC, yC - x,y position of a cell that was selected
        void MoveToNextCell(int xC, int yC);
};

void DigitalEnemy::Load(SDL_Renderer *renderer,const char *filename){
    text = TextureLoad(filename,renderer);
    rect.w = 100;
    rect.h = 100;
}

void DigitalEnemy::Render(SDL_Renderer *renderer, int xC, int yC){
    MoveToNextCell(xC,yC);
    SDL_RenderCopy(renderer,text,NULL,&rect);
}

void DigitalEnemy::MoveToNextCell(int xC, int yC){

    int step = 1;

    if(x > xC) x-=step;
    if(x < xC) x+=step;
    if(y > yC) y-=step;
    if(y < yC) y+=step;

    rect.x = x - rect.w/2;
    rect.y = y - rect.h/2;
}