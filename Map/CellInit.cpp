#pragma once

#include<iostream>
#include"../SDL/include/SDL2/SDL.h"
#include<vector>
#include"MazeSize.hpp"

/*to do -> Change The Maze Generating Algorythm -> makes some breakes
1)Run THe Algoryhm and then break some walls
2)change the algorythm z
----------------------*/


struct Wall{SDL_Rect rect;};

class Cell{
    public:
        SDL_Rect rect;

        std::vector<SDL_Rect>Wall;

        /*Each of the Cell have index, to easyli locale them*/
        int index;
        
        /*Every Cell have the center of it, it helps in Spawning Weapons, and Playrs after Deads :D*/
        struct Point{float x;float y;};
        Point center;

        bool visited;
        /*check which way current cell have gone 
        [0] - up
        [1] - right
        [2] - down
        [3] - left */
        bool Path[3];

        /*Dimensions, 
        [0] - x position, 
        [1] - y position */
        int top_left[2];
        int top_right[2];
        int botton_right[2];
        int botton_left[2];

        void CellMake();
        /*Create a SDL_Rect for every Wall which is not destroyed*/
        void WallMake();
        void CellDraw(SDL_Renderer *renderer);
        void CellColide(int X[4],int Y[4]);
        bool CellWallColide(SDL_Rect wallrect,SDL_Rect objrect);
        int corners[2][2];

        //list o neibors
        std::vector<int>N;

    private:

    
};

void Cell::WallMake(){

    if(!Path[0]){
    Wall.push_back({corners[0][0],corners[0][1],CELL_SIZE,CELL_WALL_THICKNESS});
    }
    if(!Path[1]){
    Wall.push_back({corners[0][0]+CELL_SIZE,corners[0][1],CELL_WALL_THICKNESS,CELL_SIZE+CELL_WALL_THICKNESS});
    }
    if(!Path[2]){
    Wall.push_back({corners[0][0],corners[0][1]+CELL_SIZE,CELL_SIZE+CELL_WALL_THICKNESS,CELL_WALL_THICKNESS});
    }
    if(!Path[3]){
    Wall.push_back({corners[0][0],corners[0][1],CELL_WALL_THICKNESS,CELL_SIZE});
    }
}

/*Here we "positioning a cell "*/
void Cell::CellMake(){

    //top left
    corners[0][0] = rect.x;
    corners[0][1] = rect.y;

    for(int i=0;i<4;i++){
        Path[i] = false;
    }

    rect.h = CELL_SIZE;
    rect.w = CELL_SIZE;

    center.x = rect.x + rect.w/2;
    center.y = rect.y + rect.h/2;

    visited = false;
}

void Cell::CellDraw(SDL_Renderer *renderer){

    SDL_SetRenderDrawColor(renderer,130,130,130,255);

    if(!Path[0]){
    rect = {corners[0][0],corners[0][1],CELL_SIZE,CELL_WALL_THICKNESS};
    SDL_RenderFillRect(renderer,&rect);
    }
    if(!Path[1]){
    rect = {corners[0][0]+CELL_SIZE,corners[0][1],CELL_WALL_THICKNESS,CELL_SIZE+CELL_WALL_THICKNESS};
    SDL_RenderFillRect(renderer,&rect);
    }
  
    if(!Path[2]){
    rect = {corners[0][0],corners[0][1]+CELL_SIZE,CELL_SIZE+CELL_WALL_THICKNESS,CELL_WALL_THICKNESS};
    SDL_RenderFillRect(renderer,&rect);
    }

    if(!Path[3]){
    rect = {corners[0][0],corners[0][1],CELL_WALL_THICKNESS,CELL_SIZE};
    SDL_RenderFillRect(renderer,&rect);
    }
    
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
}