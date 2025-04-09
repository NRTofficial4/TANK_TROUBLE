/*Now that bullet colide works like 90% of the time:
TO DO:----------------
PLayer (Tank body) and Weapon as  separate object
since there are going to be a lots of weapons - laser beam, machine gun, and the fucking Grenade Lancher
of course, tank body will be a rectangle, and the Tank Weapon will be collind with the wals separatly
if the program be to slow we can easily optymazie by looking for collisio only in a certain range of a object- easy peasy
Weapons whichc are basically just rectangle,but positioned perfect--*/

#pragma once
#include<iostream>
#include<vector>
#include"../../SDL/include/SDL2/SDL.h"
#include"../../SDL/include/SDL2/SDL_image.h"
#include"../../SDL/include/SDL2/SDL_mixer.h"

#include"../Weapons/Weapon.cpp"  
#include"../Weapons/BomboClat.cpp"
// #include"../Weapons/MachineGun.cpp"
//#include"../Weapons/TheMin.cpp"

//Im fucking stupid
#define RAD(x) (x * M_PI / 180)
#define DEGREES(x) (x*180)/M_PI;

#define TANKSPEED 4
#define TANK_TURNING_SPEED 4

//Number From 0 - 3 to select which cell to go (digitalenemy) 
std::uniform_int_distribution<>Rand5(-2,3);


class Tank{
    public:
        SDL_Rect rect;

        SDL_Rect cabrect;
        SDL_Texture*texture;

        Weapon weapon;
        SDL_Texture *tank_texture;
        Mix_Chunk *music;
        Mix_Chunk *HitMusic;

        const Uint8 *keys;
        struct Point{float x;float y;};

        /*vector to hold every rectangle on the maze and check if the Player is Coliding
        if the player is Coliding then it pushed to the list*/
        std::vector<SDL_Rect>SrcRect;

        Tank(int w,int h);

        void move(int kup, int kdown, int krp, int krm);
        /*for player that moves by mouse--------*/
        void MauseMove();

        void render(SDL_Renderer *renderer);
        void TankLoad(const char* filename,SDL_Renderer *renderer);

        /*Declare the corners value and use it in colision as max/min values on Pendicular Vector ----*/
        void RectDraw();
        void SoundLoad();

        /*Cabine ->*/
        void CabineLoad(const char* filename,SDL_Renderer *renderer);
        void RenderCabine(SDL_Renderer*renderer);

        /*COLISION DETECTION------------------------------*/
        
        //function to check if max and min values are intersectind, and if they are => they are coliding!
        //int index -> to capture the index of Minimum Distances -> lool at 
        void Intersect(int index);

        //Project x,y values of a object (and the player) into new axis made by pendicular Vectr (aka NormVector)
        void ProjectionColision(SDL_Rect objrect);
        /*-------------------------------------------------*/

        /*WEAPONS AND BULLET--------------------------------*/
        void Shotting(SDL_Renderer *renderer);
        bool shot;
        bool PLaySound;
        bool PlayedSound;

        /*---------------------------------------*/

    int PlayerIndex;
    /*GamePlay Law kinda shit---------------------*/
    /*Check if player is Killed or not (this Comment was very neccesary)*/
    bool Killed;
    /*Send signal to turn on the End rund Trigger, which clears the bullet and -> makes New Maze!!*/
    bool Ready2Spawn;

    /*after Rund is ended, player will be localized into random Position---*/
    float SpawnPoint;

    //I belive you are smart enaugh to ques 
    int Points;
    bool notkilled = true;
    /*-------------------------------------------*/


    /*position of the real corner position */
    Point topleft,topright,bottonleft,bottonright,center,BulletCenter;

    /*MausePos -> it converts the mause Position | MauseDetPos -> position mause "follows" and stop */
    Point MausePos,MauseDestPos;

    //Max and Min values on the pendicular vector of a player
    float MaxPlayer,MinPlayer;

    //Max and Min values of the object on the pendicular vector of a player
    float MaxObj,MinObj;

    /*angle to recognize corners with rotation*/
    float alfa,alfa2;

    //Check if the player colided or not
    bool Colided ;
    bool reverseangle;
    bool MachineShot;
    /*-----------------------------------------------------*/

    //MTV - minimum translation vector -> vector that pushes away from a colision----
    float MTV[2];
    /*The lenght of the MTV vector*/
    float Deepnes;

   /*x,y position of a tank,YES it has to be public, shut the fuck up Igor you Nerd*/
    float x,y;

    bool Shield;

    /*The Helath Bar ----------------*/
    struct Time{
        int frames;
        int seconds;
        void Timing(){
            frames++;
            if(frames == 60){
                frames = 0;
                seconds++;
            }
        }
    };  

    /*Health Bar 
    HealthRect -> corners of the health bar
    CurrenctHealhRect -> Actual HealthBar
    DeltaHealthRect -> Addition Health bar that shows how m a s s i v e damage player have received*/
    Time HealthUpdate;
    SDL_Rect HealthRect,CurrentHealthRect,DeltaHealthRect;
    int Health;
    int DeltaHealth;


    private:

    /*movement parameters*/
    int rotation;
    int velocity;
    int speed = TANKSPEED;
    int angle = 0;

    float MausePlayerLength;

    //VECTOR PROJECTION----------------------------------------------------------

    //Position of the rect in the pendicular vector
    float dot[4];
    float PlayerDot[4];
    /*1 index, the side index, 
    ATTENTION: index 0 and 1 is used to check the player side, the 2 and 3 index are used to check the obj side
    second index, the x,y values of a vector*/
    float NormVector[4][2];
    /*the same as NormVector but not normalized */
    float Vector2Mtvp[4][2];
    //length of NormVector;
    float length;

    //Find the object Center to repair the normal
    Point ObjectCenterRect;

    //Vector to to make sure the Normal are pointing in the same direction as wanted
    float VectorCenter[2];
    /*Dot product of a center object
    Needed to define if object is one "right" or "left" side of a player*/
    float ObjDotCenter,PlayerDotCenter;

    //Number of colision founded in all 4 direction, if = 4, then colided
    int ColisionFound;

    //X and Y Values of the Object 
    float xValues[4];
    float yValues[4];

    //minimum gap in one of the axes -> is used to generate a mtv vector
    float MinDotDistance;
    float DotDistance[4] = {20000,20000,20000,20000};

    //index to find the norm pendicular vector with the MinDotDistance
    int MinIndex;
    //--------------------------------------------------------------------------

    //Keep the T i m i n g  guys!!
    int FramesWhileDead;
    int SecondsWhileDead;
    
    int DDest;
    int DestRotation;
    int PrevDest = 0;
    
    int BarW,BarPosY;
    void ShakeBar();

};

void Tank::SoundLoad(){
 music= Mix_LoadWAV("Sound/dead.wav");
 bullet.ShotMusic = Mix_LoadWAV("Sound/BomboClatShot.wav");
 HitMusic = Mix_LoadWAV("Sound/TankHit.wav");
}


void Tank::Shotting(SDL_Renderer *renderer){

if(!Killed){
    BulletCenter.x = ((topleft.x + topright.x)/2) - bullet.rect.w/2;
    BulletCenter.y = ((topleft.y + topright.y)/2) - bullet.rect.h/2;

    weapon.angle = angle;
}
if(Killed){shot = false;}
    weapon.Shotting(renderer);
    weapon.Render(renderer,center.x,center.y);
}

void Tank::ProjectionColision(SDL_Rect objrect){

ColisionFound = 0;

/*Norm vector Player ----------------------------------------------------*/

//VERTICAL ---- 
NormVector[0][0] = -topleft.y + topright.y;
NormVector[0][1] = topleft.x - topright.x;

//HORIXONTAL  ---- 
NormVector[1][0] = -topright.y + bottonright.y;
NormVector[1][1] = topright.x - bottonright.x;

/*Norm Vector Object -----------------------------------------------------*/

//VERTICAL ---
NormVector[2][0] = 0;
NormVector[2][1] = objrect.w;

//HORIZONTAL ---
NormVector[3][0] = -objrect.h;
NormVector[3][1] = 0;

xValues[0] = objrect.x;
xValues[1] = objrect.x + objrect.w;
xValues[2] = objrect.x + objrect.w;
xValues[3] = objrect.x;

yValues[0] = objrect.y;
yValues[1] = objrect.y;
yValues[2] = objrect.y + objrect.h;
yValues[3] = objrect.y + objrect.h;

for(int index = 0;index<4;++index){

    length = sqrt(pow(NormVector[index][0],2)+pow(NormVector[index][1],2));

    //Vector normalization:
    NormVector[index][0] = NormVector[index][0]/length;
    NormVector[index][1] = NormVector[index][1]/length;

    ObjDotCenter = (objrect.x + objrect.w/2)*NormVector[index][0] + (objrect.y + objrect.h/2)*NormVector[index][1];
    PlayerDotCenter = center.x*NormVector[index][0] + center.y*NormVector[index][1];

    for(int i=0;i<4;i++){
        dot[i] = xValues[i]*NormVector[index][0] + yValues[i]*NormVector[index][1];
    }

    PlayerDot[0]= topleft.x*NormVector[index][0] + topleft.y*NormVector[index][1];
    PlayerDot[1]= topright.x*NormVector[index][0] + topright.y*NormVector[index][1];
    PlayerDot[2]= bottonright.x*NormVector[index][0] + bottonright.y*NormVector[index][1];
    PlayerDot[3]= bottonleft.x*NormVector[index][0] + bottonleft.y*NormVector[index][1];

/*--- Findin max and min values of the Player (on pendicular vector) ----*/

    MaxPlayer = -2000;
    MinPlayer = 2000;

    for(int i=0;i<4;i++){
        if(PlayerDot[i] > MaxPlayer){
            MaxPlayer = PlayerDot[i];
        }
        if(PlayerDot[i] < MinPlayer){
            MinPlayer = PlayerDot[i];
        }
    }

/*---Findin max and min values of the Object (on pendicular vector) ----*/

    MaxObj = -2000;
    MinObj = 2000;

    for(int i=0;i<4;i++){
        if(dot[i] > MaxObj){
            MaxObj = dot[i];
        }
        if(dot[i] < MinObj){
            MinObj = dot[i];
        }
    }

    Intersect(index);

    if(ColisionFound == 4){
        Colided = true;
    }
    else{
        // std::cout << "player position ok\n";
        Colided = false;
    }
}

/*Finding the MTV vector to recreate a "reaction" Player to object---------------------------*/

MinDotDistance = 2000000;
MinIndex = 0;

for(int i=0;i<4;i++){
    if(DotDistance[i] < MinDotDistance){
       MinDotDistance = DotDistance[i];
       MinIndex = i;
    }
}

ObjectCenterRect.x = objrect.x + objrect.w/2;
ObjectCenterRect.y = objrect.y + objrect.h/2;

VectorCenter[0] = center.x - ObjectCenterRect.x;
VectorCenter[1] = center.y - ObjectCenterRect.y;

if(VectorCenter[0] >= 0 && NormVector[MinIndex][0] < 0){
    NormVector[MinIndex][0] = -NormVector[MinIndex][0];
}
if(VectorCenter[0] < 0 && NormVector[MinIndex][0] >= 0){
    NormVector[MinIndex][0] = -NormVector[MinIndex][0];
}

if(VectorCenter[1] >= 0 && NormVector[MinIndex][1] < 0){
    NormVector[MinIndex][1] = -NormVector[MinIndex][1];
}
if(VectorCenter[1] < 0 && NormVector[MinIndex][1] >= 0){
    NormVector[MinIndex][1] = -NormVector[MinIndex][1];
}

// MTV[0] = speed*NormVector[MinIndex][0]*fabs(sin(RAD(rotation)));
// MTV[1] = speed*NormVector[MinIndex][1]*fabs(cos(RAD(rotation)));

MTV[0] = fabs(MinDotDistance)*NormVector[MinIndex][0];
MTV[1] = fabs(MinDotDistance)*NormVector[MinIndex][1];

}

/*Check if obstacles are intersecting on certain Axis -----------------------------------*/
void Tank::Intersect(int index){ 

//PLayer on the "right side" to the obstacle ----------------------------
    if(PlayerDotCenter >= ObjDotCenter){
        if(MinPlayer <= MaxObj){
            DotDistance[index] = MaxObj-MinPlayer;
            ColisionFound++;
        }
    }

//PLayer on the "left side" to the obstacle ----------------------------
    if(PlayerDotCenter < ObjDotCenter){
        if(MaxPlayer >= MinObj){
            DotDistance[index] = MaxPlayer-MinObj;
            ColisionFound++;
        }
    }
}

void Tank::MauseMove(){
    
    //determine if angle is below / over 360 degres 
    int a = 1;
   velocity = 0;

    if(!Killed){
        if(Colided){
            x += MTV[0];
            y += MTV[1];
        }
MausePlayerLength = sqrt((MausePos.y - center.y)*(MausePos.y - center.y) + (MausePos.x - center.x)*(MausePos.x - center.x));

/*IDK why but this shit reques some bulshit mechanism ------ b u l s h i t -----*/
/*Ok it makes sense, becose sin is 0 for 0 and for 180 degres, so ok ,Math is cool aj gues --------*/
if(MausePos.y <= center.y){
     DestRotation = -DEGREES(asin((MausePos.x - center.x)/MausePlayerLength));
}
if(MausePos.y > center.y) {
    DestRotation = 180-DEGREES(asin((center.x - MausePos.x)/MausePlayerLength));
}


if(PrevDest-DestRotation <= -340){
    rotation += 360;
    //std::cout << "PYK!!!\n";
} 
if(PrevDest-DestRotation >= 340) rotation -= 360;

//std::cout << PrevDest - DestRotation << "\n";

// if(abs(DestRotation - rotation > abs(DestRotation + rotation))) rotation -= TANK_TURNING_SPEED;
// if(abs(DestRotation - rotation < abs(DestRotation + rotation))) rotation += TANK_TURNING_SPEED;

if(DestRotation > rotation) rotation+=TANK_TURNING_SPEED;
if(DestRotation < rotation) rotation-=TANK_TURNING_SPEED;

//std::cout <<"  DestRot: " << DestRotation << " rot: " << rotation << "\n";

PrevDest = DestRotation;


        if(MausePlayerLength > rect.h/2){
            if(weapon.IndexWeapon != 3) velocity = -speed;
            else velocity = -1.5*speed;
        }
        else{
            velocity = 0;
        }

        x += velocity * sin(RAD(rotation));
        y += velocity * cos(RAD(rotation));

    /*-----"We add some newton here"----- -> push back the player if shoted ----*/
        x += weapon.OneAppleaDayKeepsTheDoctorAway* sin(RAD(rotation));
        y += weapon.OneAppleaDayKeepsTheDoctorAway* cos(RAD(rotation));
        
    rect.x = x;
    rect.y = y;
    }


     RectDraw();
}

void Tank::move(int kup, int kdown, int krp, int krm)
{
    keys =  SDL_GetKeyboardState(NULL);

    velocity = 0;

    if(keys[kup]) {
        if(weapon.IndexWeapon == 3) velocity = -1.5*speed;
        else velocity = -speed ;
    }
    if(keys[kdown]) {
        if(weapon.IndexWeapon == 3) velocity = 1.5*speed;
        else velocity = speed;
    }
    if(keys[krm]) rotation += TANK_TURNING_SPEED;
    if(keys[krp]) rotation -= TANK_TURNING_SPEED;

    if(!Killed){
        if(Colided){
            x += MTV[0];
            y += MTV[1];
        }
        x += velocity * sin(RAD(rotation)) ;
        y += velocity * cos(RAD(rotation));

    /*-----"We add some newton here"----- -> push back the player if shoted ----*/
        x += weapon.OneAppleaDayKeepsTheDoctorAway* sin(RAD(rotation));
        y += weapon.OneAppleaDayKeepsTheDoctorAway* cos(RAD(rotation));
        
    rect.x = x;
    rect.y = y;
    }

    RectDraw();

}

float diagonal;

void Tank::RectDraw(){

    center.x = x + rect.w/2;
    center.y = y + rect.h/2;

    diagonal = sqrt((rect.w*rect.w)/4+(rect.h*rect.h)/4);

    alfa = RAD(angle) - acos((rect.w/2)/diagonal);
    alfa2 = RAD(angle) + RAD(180) + acos((rect.w/2)/diagonal);

    topleft.x = center.x + diagonal*cos(alfa2);
    topleft.y = center.y + diagonal*sin(alfa2);

    topright.x = center.x + diagonal*cos(alfa);
    topright.y = center.y + diagonal*sin(alfa);

    bottonleft.x = center.x - diagonal*cos(alfa);
    bottonleft.y = center.y + diagonal*sin(-alfa);

    bottonright.x = center.x - diagonal*cos(alfa2);
    bottonright.y = center.y - diagonal*sin(alfa2);
}

void Tank::RenderCabine(SDL_Renderer*renderer){

    cabrect.w = 45; cabrect.h = 45;
    cabrect.x = center.x - cabrect.w/2;
    cabrect.y = center.y - cabrect.h/2;

    SDL_RenderCopyEx(renderer,texture,NULL,&cabrect,angle,NULL,SDL_FLIP_NONE);
}

Tank::Tank(int w,int h){
    rect.w = w;
    rect.h = h;
    Health = rect.h;
}

void Tank::TankLoad(const char* filename,SDL_Renderer *renderer){

    SDL_Surface *surface = IMG_Load(filename);
    if(surface == nullptr){
        std::cout << "Could not found the picture !\n";
    }
    tank_texture = SDL_CreateTextureFromSurface(renderer,surface);

    if(tank_texture == nullptr){
        std::cout << "ImTexture not initialized: !\n";
        if(renderer == nullptr){
            std::cout << "renderer not created! \n";
        }
    }
    SDL_FreeSurface(surface);
}

void Tank::CabineLoad(const char* filename,SDL_Renderer *renderer){
    SDL_Surface *surface= IMG_Load(filename);
    if(surface == nullptr) std::cout << "Could not found the picture !\n";
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if(texture == nullptr){
        std::cout << "ImTexture not initialized: !\n";
        if(renderer == nullptr){
            std::cout << "renderer not created! \n";
        }
    }
    SDL_FreeSurface(surface);

}

void Tank::render(SDL_Renderer *renderer){

    
    HealthRect.w = rect.h+2; // +4 -> to make bar show the health bar at very low level 
    HealthRect.h = rect.w/4;
    HealthRect.x = x - HealthRect.h/2 -1;
    HealthRect.y = y - rect.h + 50;

    CurrentHealthRect.x = x - HealthRect.h/2;
    CurrentHealthRect.y = y - rect.h + 50;
    CurrentHealthRect.w = Health;
    CurrentHealthRect.h = rect.w/4;

    DeltaHealthRect.x = CurrentHealthRect.x;
    DeltaHealthRect.y = CurrentHealthRect.y;
    DeltaHealthRect.h = CurrentHealthRect.h;

    BarW = CurrentHealthRect.w;
    BarPosY = CurrentHealthRect.y;

    angle = -rotation;

    if(DeltaHealthRect.w != CurrentHealthRect.w){
        HealthUpdate.Timing();
        if(HealthUpdate.frames == 30){
            HealthUpdate.frames = 0;
            DeltaHealthRect.w = Health;
        }
        if(HealthUpdate.frames % 2 == 0) ShakeBar();
    }

    if(!Killed){
        SDL_RenderCopyEx(renderer,tank_texture,NULL,&rect,angle,NULL,SDL_FLIP_NONE);

        SDL_SetRenderDrawColor(renderer,255,105,55,105);
        SDL_RenderFillRect(renderer,&DeltaHealthRect);

        SDL_SetRenderDrawColor(renderer,150,0,0,255);
        SDL_RenderFillRect(renderer,&CurrentHealthRect);

        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderDrawRect(renderer,&HealthRect);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
    }
    if(Killed){
        notkilled = false;
        std::cout << "PLayer Killed!\n";
    }
}

void Tank::ShakeBar(){

    CurrentHealthRect.w = BarW;
    CurrentHealthRect.y = BarPosY;

    CurrentHealthRect.x += Rand5(rd);
    CurrentHealthRect.y += Rand5(rd);
}

