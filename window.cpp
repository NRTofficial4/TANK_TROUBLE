/*TO DO :
problem: some bug is hapen and player is not bouncing away from a object
Posible solution:
1) - Optymalization -> only chceking all walls in the cell when player is currnetly at
2) kill yourself*/

#pragma once
#include<iostream>

#include"SDL/include/SDL2/SDL.h"

#include"SDL/include/SDL2/SDL_mixer.h"
#include"SDL/include/SDL2/SDL_ttf.h"

#include"Map/CellInit.cpp"
#include"Map/MazeInit.cpp"
#include"Objects/Player/Player.cpp"
#include"Objects/Text/text.cpp"


#define WIN_HEIGH 1080
#define WIN_WIDTH 1920

#define TANK_W 60
#define TANK_H (2*CELL_SIZE/5) + 20

// #define TANK_W 3*CELL_SIZE/10
// #define TANK_H (2*CELL_SIZE/5) + 20

Tank tank_blue(TANK_W,TANK_H);
Tank tank_red(TANK_W,TANK_H);
Tank tank_green(TANK_W,TANK_H);

Maze maze;

Text text_red("fonts/free.ttf",1740,-20);
Text text_blue("fonts/free.ttf",0,-20);
Text text_green("fonts/free.ttf",WIN_WIDTH/2-80,-20);

Weapon IconWeapnos;

/*Bruh i know randomnes is as darkess in my ass--------------------------------------------*/
std::random_device rd2;
std::mt19937 gen2(rd2());
std::uniform_int_distribution<>distrib2(0,CELL_NUMBER_HEIGH*CELL_NUMBER_HEIGH -1);
//Number From 0 - 100 % 
std::uniform_int_distribution<>CritChance(0,100);

class Window{

    public:

/*Comonn i know what does what*/
    SDL_Window*window;
    SDL_Renderer *renderer;
    SDL_Event event;
    Mix_Music *backroundmusic;
    Mix_Chunk *EndRundSound;
    Mix_Chunk *PLayerKys;
    Mix_Chunk *DrawMusic;
    Mix_Chunk *BaseWallSound;
    Mix_Chunk *MiniGunWallSound;
    Mix_Chunk *BomboClatExplodeSound;

    const Uint8 *keys;

/*Time Managment*/
    struct Time{
        int frames = 0;
        int seconds = 0;
        void Timing(){
            frames++;
            if(frames == 60){
            frames = 0;
            seconds++;
            }
            if(seconds == 60) seconds = 0;
        }
        };
    /*Optymalisaztion FPs*/
    int FrameStart;
    int FrameSet = 1000/60;
    int frame;

    bool running ;
    bool endrund;

    bool Colide[2] = {false,false};

    /*Window initialization, all assets loading, creating renderer and window :))*/
    void WindowInit();

    /*Some shit program needs to close without any problems*/
    void DestroyWindow();

    /*Rendering- basicaly doing everything in one frame*/
    void Render();

    /*Handling Keyboard Inputs*/
    void Events();

    /*Handling Text, points*/
    void TextDisplay();

    /*Keepeing Framing - 60FPS defaults*/
    void FrameOptymalisation();
    
    /*playing music in the backround*/
    void PlayBackroundMusic(); 

    private:

    /*Reset the rund after someone died and check if somebody died too*/
    Time Dead;

    /*Randomize postioning of a player based on inde of a cell*/
    int BlueSPawnCellIndex,RedSpawnCellIndex,GreenSpawCellIndex;
    
    //Select random INdexCell
    int IndexCell;

    //IterCell -> Current Cell, dir -> direction to go next
    int IterCell,dir;

    void SoundEffect();

    /*Collision -since the maze is basically a lot o rects, which are btw sometimes 1 or sometimes 2 in the same position*/
    void Colision(Tank &tank);

    //Shit get mesyy when lot of weapno so uga buga we making a new meber functions hell yea
    void BulletColision(Tank &tank);

    /*Kill, Respawn playerer, Points Number*/
    void KillPlayer(Tank &tank1,Tank &tank2);

    /*GenerateIcon in random places*/
    void GenerateIcon();

    /*When one or both player got killed*/
    void EndRund();

    /*If one player Grab Icon it dissapear and PLayer receive new Weapon-----*/
    void TakeWapon(Tank &tank);

    /*clear all bullets, and PLayers*/
    void ClearPlayer(Tank &tank);
    /*Set the player to new point on the map after maze is reinitialized*/
    void SpawnPLayer(Tank &tank);

    /*Emm,so the mins dont work so yeah*/
    void Mining();

};

void Window::WindowInit(){

    SDL_Init(SDL_INIT_VIDEO);
    if(SDL_Init(SDL_INIT_VIDEO) < 0) std::cout << "FATAL ERROR SDL not initialized!" << SDL_GetError() <<"\n";

    SDL_Init(SDL_INIT_AUDIO);
    if(SDL_Init(SDL_INIT_AUDIO) < 0) std::cout << "FATAL ERROR SDL not initialized!" << SDL_GetError() <<"\n";

    TTF_Init();
    if(TTF_Init() == -1) std::cout << "FATAL ERROR SDL not initialized!" << TTF_GetError() <<"\n";

    window = SDL_CreateWindow("TANK_TROUBLE",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIN_WIDTH,WIN_HEIGH,SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window,0,0);
    running = true;

    maze.MazeCellInitialize();
    maze.MazeInit();

    std::cout << "Maze fully Initalized!!\n";

    tank_blue.TankLoad("Assets/tank_blue.png",renderer);
    tank_green.TankLoad("Assets/tank_green.png",renderer);
    tank_red.TankLoad("Assets/tank_red.png",renderer);

    tank_blue.CabineLoad("Assets/tank_blue_kabine.png",renderer);
    tank_red.CabineLoad("Assets/tank_red_kabine.png",renderer);
    tank_green.CabineLoad("Assets/tank_green_kabine.png",renderer);

    tank_blue.weapon.Load(renderer,"Assets/Base.png");
    tank_red.weapon.Load(renderer,"Assets/Base.png");
    tank_green.weapon.Load(renderer,"Assets/Base.png");

    bullet.LoadTexture(renderer,"Assets/Bullet.png");
    BomboClatMainBullet.LoadTexture(renderer,"Assets/Bullet.png");
    BomboClatMinions.LoadTexture(renderer,"Assets/Bullet.png");
    // MiniGun.LoadTexture(renderer,"Assets/Bullet.png"); -- it not work properly
    
    tank_blue.PlayerIndex = 0;
    tank_red.PlayerIndex = 1;
    tank_green.PlayerIndex = 2;

    text_blue.color = {0,75,155};
    text_red.color = {155,75,0};
    text_green.color = {75,155,0};
    text_blue.text = "0"; text_red.text = "0"; 
    text_green.text = "0";


/*Text Loading -------------------------------*/
    text_blue.Texture(renderer);
    text_red.Texture(renderer);
    text_green.Texture(renderer);
    
/*Sound Loading ----------------------------*/
SoundEffect();

/*take the player and set ther herer, 
blue tank is in topleft
red tank is in bottonright
*/
    tank_blue.x = maze.cell[0].center.x - tank_blue.rect.w/2;
    tank_blue.y = maze.cell[0].center.y - tank_blue.rect.h/2;

    tank_green.x = maze.cell[2].center.x - tank_green.rect.w/2;
    tank_green.y = maze.cell[2].center.y - tank_green.rect.h/2;

    tank_red.x = maze.cell[maze.cell.size()-1].center.x - tank_red.rect.w/2;
    tank_red.y = maze.cell[maze.cell.size()-1].center.y - tank_red.rect.h/2;
}

void Window::Events(){


    while(SDL_PollEvent(&event)){

        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                if(!tank_blue.Killed) tank_blue.weapon.shot = true;
                break;
            case SDLK_SPACE:
                if(!tank_red.Killed) tank_red.weapon.shot = true;
                break;
            case SDLK_p:
                endrund = true;
                break;
            default:
                break;
            }
        break;
        case SDL_MOUSEMOTION:
        tank_green.MausePos.x = event.button.x;
        tank_green.MausePos.y = event.button.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
        if(!tank_green.Killed) tank_green.weapon.shot = true;
        default:
            break;
        }
    }
}

void Window::GenerateIcon(){
    IndexCell = distrib2(rd2);
    IconWeapnos.Generate(renderer,maze.cell[IndexCell].center.x,maze.cell[IndexCell].center.y);
    //IconWeapnos.Generate(renderer,maze.cell[0].center.x,maze.cell[0].center.y);
    TakeWapon(tank_blue);
    TakeWapon(tank_red);
    TakeWapon(tank_green);
}

void Window::TakeWapon(Tank &tank){
    //for(int iter=0;iter<1;iter++){
    for(int iter=0;iter<IconWeapnos.Icons.size();iter++){
        IconWeapnos.Icons[iter].Colide(tank.center.x,tank.center.y);
        if(IconWeapnos.Icons[iter].colide){ 
            tank.weapon.IndexWeapon = IconWeapnos.Icons[iter].index;
            tank.weapon.UpdateWeapon(renderer);
        }
        if(IconWeapnos.Icons[iter].colide){
            IconWeapnos.Icons[iter].colide = false;
            IconWeapnos.Icons.erase(IconWeapnos.Icons.begin()+iter);
        }
        else{
            IconWeapnos.Icons[iter].Render(renderer);
        }
    }

}

void Window::TextDisplay(){

text_blue.TextRendering(renderer);
text_red.TextRendering(renderer);
text_green.TextRendering(renderer);

}

/*ATTENTION -Render basically emm
make sure to not gamble with the order with a function -> 
some shit get kinda meessy and is sensitive more then Szymon when I tell him i dont wanna watch Dorahedoro after he asked me 50 times
*/
void Window::Render(){

    SDL_RenderClear(renderer);

    maze.MazeDraw(renderer);
    TextDisplay();

    GenerateIcon();

    Colision(tank_blue);
    Colision(tank_red);
    Colision(tank_green);

    tank_blue.move(SDL_SCANCODE_W,SDL_SCANCODE_S,SDL_SCANCODE_D,SDL_SCANCODE_A);
    tank_red.move(SDL_SCANCODE_UP,SDL_SCANCODE_DOWN,SDL_SCANCODE_RIGHT,SDL_SCANCODE_LEFT);
    tank_green.MauseMove();

    Mining();

    KillPlayer(tank_blue,tank_red);
    KillPlayer(tank_blue,tank_green);

    KillPlayer(tank_red,tank_blue);
    KillPlayer(tank_red,tank_green);

    KillPlayer(tank_green,tank_blue);
    KillPlayer(tank_green,tank_red);

if((tank_blue.Killed && tank_red.Killed) || (tank_blue.Killed && tank_green.Killed) || (tank_green.Killed && tank_red.Killed)) Dead.Timing();

    tank_blue.render(renderer);
    tank_red.render(renderer);
    tank_green.render(renderer);

    tank_blue.Shotting(renderer);
    tank_red.Shotting(renderer);
    tank_green.Shotting(renderer);

    tank_blue.RenderCabine(renderer);
    tank_red.RenderCabine(renderer);
    tank_green.RenderCabine(renderer);

/*Sooou, player was killed, (do the Draw opportinuty), new Map init, and reset :D------------ */
    if(Dead.seconds==4){ 
        endrund = true; 
        Dead.seconds = 0;
    }

/*"We had to add some skibidi in there"*/
    if(endrund) EndRund();
    
    SDL_RenderPresent(renderer);
} 

void Window::EndRund(){

    Mix_PlayChannel(5,EndRundSound, 0);
/*Points ->*/
if(!(tank_blue.notkilled && tank_red.notkilled && tank_green.notkilled)){
    if(tank_blue.notkilled) tank_blue.Points++;
    if(tank_red.notkilled) tank_red.Points++;
    if(tank_green.notkilled) tank_green.Points++;
}

text_blue.Number2Text(tank_blue.Points);
text_red.Number2Text(tank_red.Points);
text_green.Number2Text(tank_green.Points);

text_blue.Texture(renderer);
text_red.Texture(renderer);
text_green.Texture(renderer);


/*Clearing, no shit on the map is left*/

ClearPlayer(tank_green);
ClearPlayer(tank_blue);
ClearPlayer(tank_red);

/*Destroying Map Like Hitler did Warsa....ok not funnny*/
    maze.cell.clear();
    maze.Current_cell.clear();
    maze.MazeCellInitialize();
    maze.MazeInit();
    IconWeapnos.Icons.clear();

SpawnPLayer(tank_blue);
SpawnPLayer(tank_green);
SpawnPLayer(tank_red);

}

void Window::ClearPlayer(Tank &tank){

/*Reseting Players to base weapon:-----------------------*/
    tank.weapon.IndexWeapon = 0;
    tank.weapon.UpdateWeapon(renderer);

/*Index 0------------------------*/
    tank.weapon.Bullets.clear();
/*Index 1------------------------*/
    tank.weapon.MainBullet.clear();
/*Index 2------------------------*/
    tank.weapon.MiniGunBullets.clear();

/*not bugging guys are we*/
    tank.Killed = false;
    tank.notkilled = true;
}

/*Repositioning Player*/
void Window::SpawnPLayer(Tank &tank){
    tank.SpawnPoint = distrib2(rd2);
    tank.x = maze.cell[tank.SpawnPoint].center.x - tank_blue.rect.w/2;
    tank.y = maze.cell[tank.SpawnPoint].center.y - tank_blue.rect.h/2;
    tank.Health = tank.rect.h;
}

void Window::FrameOptymalisation(){
    int Frametime = FrameStart - SDL_GetTicks();
    if(Frametime < FrameSet){
        SDL_Delay(FrameSet - Frametime);
    }
    // std::cout << frame << "\n";
    // frame++;
}

void Window::DestroyWindow(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}