
/*Cool Weapons is the main "fun" in the game----------------------------
Weapons CUrentl planned:
BOmboclat -> bullet which explodes after like 5,6 seconds
LaserBeam -> HOW??
Machine gun -> kinda easy
Rocket launcher
// Granate?? -> do we want to destroy Walls?, and if then so how we can do it*/

/*Easy peasy one Class*/
/*
index which will be determined which type of the weapon, no to create one class for each weapon ofc
Random Spawn in Random cell -> every cell in the Maze neeed to have a accesible center Value 
in center values weapons will spawn, by the random time, and number -Ah shit here we go again
collision if the player have picked the weapon or not
every weapon is diffrent -> max ammo,range(seconds)
HOw the fuck i gonna make a laser beam lol
how the fuck i suppouse to make a bullet which will expolde after time

and lalsty -> making a rocket launcher which will chose the player which is closer
How fucked is the movement of that rocked XD
kill yourself safe :DD
*/

/*List Weapnos - INDEX:------------------------------------------------------
0 -> BaseWeapon
1 -> Bomboclat
2 -> MachineGun */

#pragma once
#include<iostream>
#include<random>

#include<SDL2/SDL.h>
#include"Bullet.hpp"
#include"WeaponIcon.hpp"

#define RAD(x) (x*M_PI/180)

Bullet bullet(10,10);
WeaponIcon Icon;

/*Index weapon -1*/
//This onl works for even number, works for 4,6 but does not work on 5 lmao 
Bullet BomboClatMinions(6,6);
BomboClat BomboClatMainBullet(20,20);

/*Index Weapon -2*/
Bullet MiniGun(9,9);

/*Index weapon -3*/
TheMin Mins(15,15);
Bullet SparkBullet(6,6);

/*Bruh i know randomnes is as darkess in my ass--------------------------------------------*/
std::random_device rd3;
std::mt19937 gen3(rd3());
std::uniform_int_distribution<>distrib_W(1,1);


class Weapon{
    public:
        SDL_Rect Iconrect;
        SDL_Rect rect;
        /*Animation --*/
        SDL_Rect srcrect;
        SDL_Texture *texture;
        Mix_Chunk *ShotSound;

        struct WeaponTexture{
            const char *filename;
            SDL_Texture *texture;
        };

        std::vector<Bullet>Bullets;
        std::vector<WeaponIcon>Icons;
        std::vector<BomboClat>MainBullet;
        
        //std::vector<Bullet>Minions;
        std::vector<Bullet>MiniGunBullets;

        std::vector<TheMin>MainMine;

        std::vector<WeaponTexture>WeapoonTextures;
        std::vector<const char*>Filenames;


        struct Point{float x;float y;};

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

        const Uint8 *keys;
        int PlayerIndex;
        /*Push the player Away when shouting :D*/
        float OneAppleaDayKeepsTheDoctorAway;

        /*use in animation, it cointains the value where the weapon is located */
        float LengthWeapon = 15 ;

        /*position of the real corner position - We use that to create am, cannon, which later we be colidind(later :DD)*/
        Point topleft,topright,bottonleft,bottonright,center;
        float angle;
        bool shot;

        int Damage; //-))
        //NUmber from 1 to 10 -> bigger number bigger chance to crit;
        int CritRate ;// XD

        /*Index weapon -> it decides which type of Weapon Player have for exapmle 0 means Base weapon and 1 mean bomboclat */
        int IndexWeapon ;

        Weapon();

        void Render(SDL_Renderer *renderer,int x, int y);
        //Random Generate Icons in the Map
        void Generate(SDL_Renderer *renderer,int x, int y);
        /*Change the weapon when player colide with new one :D*/
        void UpdateWeapon(SDL_Renderer *renderer);

/*massive murder complete disaster "shibua ahh Incydent" Accident everybody dying (me included) Yamato swims in openheimer spamming Bombs*/
        void Shotting(SDL_Renderer *renderer);

        void Load(SDL_Renderer *renderer,const char*filenamae);

/*Every Weapon will have their own function call for shutting :D*/
    private:

    void BaseWeapon();
    void BaseWeaponRender(SDL_Renderer *renderer);

    /*BomboClat Weapon Method-----------------------------*/
    void BomboclatWeaponShot();
    void BomboClatWeaponRender(SDL_Renderer *renderer);
    void LoadBomboClatWeapon(BomboClat &b);

    /*Machine Gun Method ---------------------------------*/
    void MachineWeaponShot();
    void MachineWeaponRender(SDL_Renderer *renderer);

    /*The Mins Shooter Methods ---------------------------*/
    void TheMinWeaponShot();
    void MinWeaponLoad(TheMin &m);
    void MinRenderWeapon(SDL_Renderer *renderer);
    
/*Time manager*/
Time IconsSpawnTime;
Time BomboClatTime;

/*Time betwens bullet what was one generated*/
Time MachineBulletTime;

    void Time();
    int Ammo;
    int MiniGunAmmo;
    int frames;
    int seconds;
};

//Generating Weapon Icons ------------------------------------------------------>
/*Firsly -> 
when generate -> for every 10 seconds 2 weapons -> first weapon spwan instantly lets "say"
where generate -> Random x,y -> from center of each cell -> generate a random number to pick up a cell -> done
when/wherer de generate -> when player "colide" -> just fucning center positioning, we not doing SAT for that shit*/ 
void Weapon::Generate(SDL_Renderer *renderer,int x, int y){
    IconsSpawnTime.Timing();

    if(IconsSpawnTime.seconds == 5){
        IconsSpawnTime.seconds = 0;
        Icon.rect.w = 50;Icon.rect.h = 50;
        Icon.index = distrib_W(rd3);
        // Icon.index = 3;
        Icon.rect.x = x - Icon.rect.w/2;
        Icon.rect.y = y - Icon.rect.h/2;
        Icon.StaticPosX = x - Icon.rect.w/2;
        Icon.StaticPosY = y - Icon.rect.h/2;
        Icon.colide = false;
        Icon.Load(renderer);
        Icons.push_back(Icon);
    }
}

/*Constructor to Add new Weapon*/
/*Attention the order is sensitive to Weapon Index, dont touch it */
Weapon::Weapon(){
    Filenames.push_back("Assets/Base.png");
    Filenames.push_back("Assets/BomboClat.png");
    Filenames.push_back("Assets/MiniGunAni.png");
    Filenames.push_back("Assets/tank_SecurityWeapon.png");
    //Filenames.push_back("Assets/BomboClat.png");
    srcrect.x = 0; srcrect.y = 0;
}
void Weapon::UpdateWeapon(SDL_Renderer *renderer){
    Load(renderer,Filenames[IndexWeapon]);
}

void Weapon::Render(SDL_Renderer *renderer,int x,int y){

    switch (IndexWeapon)
    {
    case 0:
        rect.w = 20; rect.h = 60;
        srcrect.h = 600; srcrect.w = 200;
        Damage = 20;
        CritRate = 15;
        break;
    case 1:
        Damage = 10;
        rect.w = 30; rect.h = 60;
        srcrect.h = 600; srcrect.w = 200;
        CritRate = 30;
        break;
    case 2:
        Damage = 15;
        rect.w = 30; rect.h = 50;
        srcrect.h = 600; srcrect.w = 100;
        CritRate = 20;
        break;
    case 3:
        Damage = 20;
        CritRate = 30;
        rect.w = 80; rect.h = 80;
        srcrect.h = 400; srcrect.w = 400;
        
        break;

    default:
        break;
    }

    if(IndexWeapon != 3){
    rect.x = x -LengthWeapon*sin(RAD(-angle))-rect.w/2;
    rect.y = y -LengthWeapon*cos(RAD(-angle))-rect.h/2;
    }
    else{
        rect.x = x - rect.w/2 ; rect.y = y - rect.h/2;
    }

    if(LengthWeapon < 15) LengthWeapon ++;

    center.x = rect.x + rect.w/2;
    center.y = rect.y + rect.h/2;

    SDL_SetRenderDrawColor(renderer,255,0,0,250);
    SDL_RenderCopyEx(renderer,texture,&srcrect,&rect,angle,NULL,SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
}

 void Weapon::BaseWeaponRender(SDL_Renderer *renderer){
    for(int iter=0;iter<Bullets.size();iter++){
        Bullets[iter].BombTime.Timing();
        if(Bullets[iter].seconds > 5){
            Bullets.erase(Bullets.begin() + iter);
        }
        Bullets[iter].Shot();
        Bullets[iter].Render(renderer);
    }
 }


void Weapon::Load(SDL_Renderer *renderer,const char*filename){

    SDL_Surface *surface = IMG_Load(filename);
    if(surface == nullptr){
        std::cout << "Could not found the picture !\n";
    }
    texture = SDL_CreateTextureFromSurface(renderer,surface);

    if(texture == nullptr){
        std::cout << "ImTexture not initialized: !\n";
        if(renderer == nullptr){
            std::cout << "renderer not created! \n";
        }
    }
    SDL_FreeSurface(surface);
}

void Weapon::Time(){
    frames++;
    if(frames == 60){
        frames = 0;
        seconds++;
    }
    if(seconds == 60) seconds = 0;
}

void Weapon::Shotting(SDL_Renderer *renderer){

    OneAppleaDayKeepsTheDoctorAway = 0;

    bullet.x = center.x - rect.h*sin(RAD(-angle))/2;
    bullet.y = center.y - rect.h*cos(RAD(-angle))/2;

    switch (IndexWeapon)
    {
    case 0:
        Ammo = 5;
        BaseWeapon();
        break;
    case 1:
        BomboclatWeaponShot();
        break;
    case 2:
        Ammo = 10;
        if(shot) MachineWeaponShot();
        break;
    // case 3:
    //     if(shot) TheMinWeaponShot();
    //     break;
    default:
        break;
    }
    BaseWeaponRender(renderer);

}

void Weapon::BaseWeapon(){
    if(shot){
        if(Bullets.size() <= Ammo){
            Mix_PlayChannel(0,ShotSound,0);
            bullet.angle = -angle;
            bullet.direction.x = 1;
            bullet.direction.y = 1;
            Bullets.push_back(bullet);
            OneAppleaDayKeepsTheDoctorAway = 5;
            LengthWeapon = 8;
        }
    }
    shot = false;
}
