/*TO DO:
New Algorythm :
1 Chose Random Cell
2 In Random direction remove one or 2  walls with respect to neibors of the Cell 
3 repeat till  all Cells are visited ------------------*/

#pragma once

#include<iostream>
#include<vector>
#include"SDL/include/SDL2/SDL.h"
#include<random>

#include"CellInit.cpp"
#include"MazeSize.hpp"

//random direction 
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<>distrib(0,3);

//Make Some changes to Maze ----*we do a "little" trolling-----
//random direction 
std::uniform_int_distribution<>RandomPathGenerator(0,10);
std::uniform_int_distribution<>RandomWall(0,3);

//SmallAdjustment :/
int IterAdjust(int x);

class Maze{

    public:

    Cell cell_obj;
    std::vector<Cell>cell;
    std::vector<Cell>Current_cell;

    //iterator for switching to athother Cell;
    int iter;
    //value to check "step" to another cell and operate on it
    int step ;

    /*iterators to check the previous iter to destroy wall*/
    int iter2;
    int iter1;

    int RandomIter,IterLeft;

    /*number to random select a path*/
    int m;

    /*Apply some Changes*/
    void MazeMakeWall(int x);
    
    //Create Maze
    void MazeCellInitialize();
    void MazeMake();

    //How Algorythms Work:
    void MazeInit();
    //destroy the wall betwen current and last checked cell
    void MazeDestroyWall();

    //select random direction 
    void MazeDirection();

    void MazeDraw(SDL_Renderer *renderer);

    bool MazeColide(SDL_Rect rect);
    
    private:

     //funtion that select every 1 in 15 cells and remove all walls to make some space:))
    void MakeSpace();

};


void Maze::MakeSpace(){
    for(int j=1;j < cell.size()-1;j+=2){

        for(int i=0;i++;i<=3){
            cell[j].Path[i]=true;
        }
        std::cout << j << "iter:"<< " workinghere\n";

         cell[j+1].Path[3] = true;

        if(j >1) cell[j-1].Path[1] = true;

        if(j+CELL_NUMBER_WIDTH < cell.size()) cell[j+CELL_NUMBER_WIDTH].Path[2] = true;
    
        if(j > CELL_NUMBER_WIDTH ) cell[j-CELL_NUMBER_WIDTH].Path[0] = true;
        if(j > 60) break;
    
}
}



void Maze::MazeCellInitialize(){

int index = 0;
    /*placing Cell in corect order and place*/
    for(int y=0;y<WINDOW_HEIGH-CELL_SIZE;y += CELL_SIZE){
        for(int x=0;x<WINDOW_WIDTH-CELL_SIZE;x += CELL_SIZE){
        
        cell_obj.rect.x = x;
        cell_obj.rect.y = y;
        cell_obj.index = index;

        for(int index =0;index < 4;index++){
            cell_obj.Path[index] = false;
        }

        cell_obj.CellMake();

        cell.emplace_back(cell_obj);

        index++;
        }
    }
    MazeMake();
}

/*We can just build a walls easili here ----- *_* ----*/
/*ok so Walls are overlapping, but some no, becouse there is no neibor (fr cell on edges) ,so
solution 1 -> check which wall is overlapping and remove it -> too hard, nah not worth it ----------------------
solution 2 -> build more walls for the cells in neibor -> nice easy solution, we get this ----------------------*/

void Maze::MazeMake(){
    /*generate index list of neiborhood of every Cell*/
    for(int index = 0; index < MAZE_CELL_NUMBER; index++){
        // std::cout << "index : " << index << "\n";
    
    bool checked = false;

    //top left
    if(index == CELL_TOP_LEFT && !checked) {
        cell[index].N.push_back(index + 1);
        cell[index].N.push_back(index + CELL_NUMBER_WIDTH); 
        cell[index].Wall.push_back({cell[index].corners[0][0],cell[index].corners[0][1],CELL_SIZE,CELL_WALL_THICKNESS});
        cell[index].Wall.push_back({cell[index].corners[0][0],cell[index].corners[0][1],CELL_WALL_THICKNESS,CELL_SIZE});
        checked = true;
    }

    //top rigth
    if(index == CELL_TOP_RIGHT && !checked) {
        cell[index].N.push_back(index - 1);
        cell[index].N.push_back(index + CELL_NUMBER_WIDTH);
        cell[index].Wall.push_back({cell[index].corners[0][0],cell[index].corners[0][1],CELL_SIZE,CELL_WALL_THICKNESS});
        cell[index].Wall.push_back({cell[index].corners[0][0]+CELL_SIZE,cell[index].corners[0][1],CELL_WALL_THICKNESS,CELL_SIZE+CELL_WALL_THICKNESS});
        checked = true;
    };

    //botton left
    if(index == CELL_BOTTON_LEFT && !checked) {
        cell[index].N.push_back(index + 1);
        cell[index].N.push_back(index - CELL_NUMBER_WIDTH);
        cell[index].Wall.push_back({cell[index].corners[0][0],cell[index].corners[0][1],CELL_WALL_THICKNESS,CELL_SIZE});
        cell[index].Wall.push_back({cell[index].corners[0][0],cell[index].corners[0][1]+CELL_SIZE,CELL_SIZE+CELL_WALL_THICKNESS,CELL_WALL_THICKNESS});
        checked = true;
    };

    //botton right
    if(index == CELL_BOTTON_RIGHT && !checked) {
        cell[index].N.push_back(index - 1);
        cell[index].N.push_back(index - CELL_NUMBER_WIDTH);
        cell[index].Wall.push_back({cell[index].corners[0][0]+CELL_SIZE,cell[index].corners[0][1],CELL_WALL_THICKNESS,CELL_SIZE+CELL_WALL_THICKNESS});
        cell[index].Wall.push_back({cell[index].corners[0][0],cell[index].corners[0][1]+CELL_SIZE,CELL_SIZE+CELL_WALL_THICKNESS,CELL_WALL_THICKNESS});
        checked = true;
    }

    //*the Edges-------------------------*

    //wall up
    if(index > CELL_TOP_LEFT && index < CELL_TOP_RIGHT && !checked){
        cell[index].N.push_back(index - 1);
        cell[index].N.push_back(index + 1);
        cell[index].N.push_back(index + CELL_NUMBER_WIDTH);
        cell[index].Wall.push_back({cell[index].corners[0][0],cell[index].corners[0][1],CELL_SIZE,CELL_WALL_THICKNESS});
        checked = true;
    }
    //Wall Down
    if(index > CELL_BOTTON_LEFT && index < CELL_BOTTON_RIGHT && !checked){
        cell[index].N.push_back(index - 1);
        cell[index].N.push_back(index + 1);
        cell[index].N.push_back(index - CELL_NUMBER_WIDTH);
        cell[index].Wall.push_back({cell[index].corners[0][0],cell[index].corners[0][1]+CELL_SIZE,CELL_SIZE+CELL_WALL_THICKNESS,CELL_WALL_THICKNESS});
        checked = true;
    }
    //wall rigth and left
    for(int cindex = CELL_NUMBER_WIDTH;cindex < MAZE_CELL_NUMBER;cindex = cindex + CELL_NUMBER_WIDTH){

        /*Wall left----------------------*/
        if(index == cindex && index != CELL_BOTTON_LEFT && !checked){
            cell[index].N.push_back(index + 1);
            cell[index].N.push_back(index + CELL_NUMBER_WIDTH);
            cell[index].N.push_back(index - CELL_NUMBER_WIDTH);
            cell[index].Wall.push_back({cell[index].corners[0][0],cell[index].corners[0][1],CELL_WALL_THICKNESS,CELL_SIZE});
            checked = true;
        }
        
        /*Wall rightt----------------------*/
        if(index == cindex -1 && cindex != CELL_NUMBER_WIDTH-1 && !checked){
            cell[index].N.push_back(index - 1);
            cell[index].N.push_back(index + CELL_NUMBER_WIDTH);
            cell[index].N.push_back(index - CELL_NUMBER_WIDTH);
            cell[index].Wall.push_back({cell[index].corners[0][0]+CELL_SIZE,cell[index].corners[0][1],CELL_WALL_THICKNESS,CELL_SIZE+CELL_WALL_THICKNESS});
            checked = true;
        }
    }

    //if index is "deep"
    if(!checked && index < MAZE_CELL_NUMBER){
        cell[index].N.push_back(index - 1);
        cell[index].N.push_back(index + 1);
        cell[index].N.push_back(index + CELL_NUMBER_WIDTH);
        cell[index].N.push_back(index - CELL_NUMBER_WIDTH);
    }
  
    }
    std::cout << "NEIBORSH INITIALIZED SUCCESFULLY \n";
}

void Maze::MazeDraw(SDL_Renderer *renderer){
    for(auto c:cell){
        c.CellDraw(renderer);
    }
}

void Maze:: MazeMakeWall(int x){


    switch (step)
    {
    case 0:
        cell[iter1].Path[3] = true;
        cell[iter2].Path[1] = true;
        break;
    case 1:
        cell[iter1].Path[1] = true;
        cell[iter2].Path[3] = true;
        break;
    case 2:
        cell[iter1].Path[0] = true;
        cell[iter2].Path[2] = true;
        break;
    case 3:
        cell[iter1].Path[2] = true;
        cell[iter2].Path[0] = true;
        break;
    default:
        break;
    }

}

void Maze::MazeInit()
{ 

for(int i=0;i<1;i++){

    // IterLeft = MAZE_CELL_NUMBER;
    int randomness = distrib(rd);
    iter = distrib(rd)*randomness*10;

    while(true){

        // RandomIter = RandomPathGenerator(rd);
        // if(Current_cell.size() > 4){
        //     for(int i=0;i<2;i++){
        //         if(RandomIter == 2) Current_cell.pop_back();
        //     }
        // }

        if(!cell[iter].visited){
            cell[iter].visited = true;
            Current_cell.push_back(cell[iter]);

            if(Current_cell.size()>1){
                MazeDestroyWall();
            }
        }
        else{
            //check if every neibor has been checked;
            //wtf is this std::next XD
            Current_cell.back().N.erase(std::next(Current_cell.back().N.begin(),m));
            if(Current_cell.back().N.empty()){
                Current_cell.pop_back();
            }
        }

        if(Current_cell.empty()) break;

        if(i > 1) if(Current_cell.size()>0) {Current_cell.clear(); break;}

        MazeDirection();

    }

    for(auto& c:cell){
        c.visited = false;
    }

}

    for(auto& c:cell){
        c.WallMake();
    }

    std::cout << "WALL SUCCESFULLY CREATED!\n";
}

void Maze::MazeDirection(){

    while(true){
        m = distrib(rd);
        if(m < Current_cell.back().N.size()){
            break;
        } 
    }
    iter = Current_cell.back().N[m];

}

void Maze::MazeDestroyWall(){

    iter1 = Current_cell.back().index;
    iter2 = Current_cell[Current_cell.size()-2].index;

    step = iter1 - iter2;

    switch (step)
    {
    case 1:
        cell[iter1].Path[3] = true;
        cell[iter2].Path[1] = true;
        break;
    case -1:
        cell[iter1].Path[1] = true;
        cell[iter2].Path[3] = true;
        break;
    case CELL_NUMBER_WIDTH:
        cell[iter1].Path[0] = true;
        cell[iter2].Path[2] = true;
        break;
    case -CELL_NUMBER_WIDTH:
        cell[iter1].Path[2] = true;
        cell[iter2].Path[0] = true;
        break;
    default:
        break;
    }
    

}

int IterAdjust(int x){
    
    switch (x)
    {
    case 4:
        return 0;
        break;
    case 5 :
        return 1;
    default:
        return x;
        break;
    }

}

