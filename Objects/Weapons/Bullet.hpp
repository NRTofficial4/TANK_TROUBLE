#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_image.h>
#include<vector>

/*IDEA OF SHOOTING
PLayer have 5 bullets
each Bullet Colide with the wall and with the  other player
The bullet can kill it shoter  

TO DO:
 function to colide with walls, (figure out how the angle is gonna change) (skull emoji)
 to do that, use the SAT but on circle, so should be eaasier 
 kill yourself
 function to track the time when was the last time the bullet was shoted
 make each bullet disapear after like 10 second 
 Load Textures*/

#define RAD3(x) (x * M_PI / 180)

class Bullet{
    public:
    /*Position of a bullet------------------------------ */
    SDL_Rect rect;
    SDL_Texture *texture;
    Mix_Chunk *ShotMusic;
    Bullet(int w, int h);

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
    
    Time BombTime;
    Time MinsToExplode;
    Time MinMinErase;

    struct Point{float x;float y;};
    Point WallCenter;
    Point center,topleft,topright,bottonleft,bottonright;

    //Colision
    std::vector<SDL_Rect>WallRects;

    double angle;

    float x;
    float y;
    float speed = -6;
    float velocity = speed;
    //Direction of a bullet, when colided it changes value to -1 or 1
    Point direction ;
    /*---------------------------------------------------------------*/

    bool colide;
    bool PlayShotMusic;

    //time how much bullet will be going
    int max_ammo = 5;
    int seconds = 0;

    int index;

    /*Function to "move" bullets,----------*/
    void Shot();
    void Render(SDL_Renderer *renderer);
    void Time();
    /*niga kill me please*/
    void Colide(SDL_Rect wallrect);

    /*find the minimum and maximum values for object*/
    void MinMax();

    void LoadTexture(SDL_Renderer *renderer,const char* filename);

    void PlaySound();

    void AdjustVelocity();
    
    //check if the bullets is shoted or not
    bool shoted = false;

    private:

    int frame = 0;
    float xvalue[4];
    float yvalue[4];
    Point Max,Min;
    Point Direct;
    Point ObjMax,ObjMin;
    int colisions;
};

class BomboClat: public Bullet{
    public:
    Mix_Chunk *ExplodeMusic;
    Mix_Chunk *BonceMusic;
    bool explode = false;
    bool exploded = false;
    bool Loaded = false;
    std::vector<Bullet>Minions;
    BomboClat(int w,int h): Bullet(w,h){
        rect.w = w; rect.h = h;
    };
};

class TheMin :public Bullet{
    public:
    bool loaded = false;
    bool explode = false;
    bool exploded = false; // --xD--
    std::vector<Bullet>ExplosionBullet;
    bool InRange(float x,float y);
    bool PlayerInRange = false;
    TheMin(int w,int h): Bullet(w,h){
        rect.w = w;rect.h = h;
    }
};

bool TheMin::InRange(float x,float y){

    float dx = fabs(x - (rect.x + rect.w/2));
    float dy = fabs(y - (rect.y + rect.h/2));

    std::cout << dx << ", "<< dy <<"\n";

    if(dx <= 100 && dy <= 100) {
        return true;
        std::cout << "PLAYER IN RANGEEEEE\n";
    }
    else return false;
}

void Bullet::LoadTexture(SDL_Renderer *renderer,const char* filename){

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

void Bullet::PlaySound(){
    Mix_PlayChannel(-1,ShotMusic,0);
}
int count = 0;

void Bullet::AdjustVelocity(){

    if(Direct.x == Direct.y) {
        direction.x = -direction.x;
        direction.y = -direction.y;
    }
    if(Direct.x < Direct.y) direction.x = -direction.x;
    if(Direct.x > Direct.y) direction.y = -direction.y;

    // if(SideColide[0]) direction.x = -direction.x;
    // if(SideColide[1]) direction.y = -direction.y;

}

Bullet::Bullet(int w, int h){
    rect.w = w;
    rect.h = h;
    ShotMusic = Mix_LoadWAV("Sound/shoted.wav");
}

void Bullet::Colide(SDL_Rect wallrect){

    colisions = 0;
    colide = false;

    /*making it ease to read :DDD*/

    WallCenter.x = wallrect.x + wallrect.w/2;
    WallCenter.y = wallrect.y + wallrect.h/2;
    center.x = rect.x + rect.w/2;
    center.y = rect.y + rect.h/2;

    MinMax();

    //X axis - player on left
    if(center.x < WallCenter.x && Max.x >= wallrect.x) {
        colisions ++;
        Direct.x = fabs(Max.x - wallrect.x);    
        };
    //X axis - player on right
    if(center.x >= WallCenter.x && Min.x <= wallrect.x + wallrect.w) {
        colisions ++;
        Direct.x = fabs(Min.x - (wallrect.x + wallrect.w)); 
    }
     //Y axis - player on top
    if(center.y < WallCenter.y && Max.y >= wallrect.y) {
        colisions ++;
        Direct.y = fabs(Max.y - wallrect.y); 
    }
    //Y axis - player on botton
    if(center.y >= WallCenter.y && Min.y <= wallrect.y + wallrect.h) {
        colisions ++;
        Direct.y = fabs(Min.y - (wallrect.y + wallrect.h)); 
    }  

    if(colisions == 2){
        colide = true;
        // std::cout << "BULLET COLIDED! " << count << "\n";
        count++;
    }
    else{
        colide = false;
    }
}


void Bullet::MinMax(){

 /*making it ease to read :DDD---------*/
    topleft.x = rect.x;
    topright.x = rect.x + rect.w;
    bottonright.x = rect.x + rect.w;
    bottonleft.x = rect.x ;

    topleft.y = rect.y;
    topright.y = rect.y;
    bottonright.y = rect.y + rect.h;
    bottonleft.y = rect.y + rect.h;

    xvalue[0] = topleft.x;
    xvalue[1] = topright.x;
    xvalue[2] = bottonright.x;
    xvalue[3] = bottonleft.x;

    yvalue[0] = topleft.y;
    yvalue[1] = topright.y;
    yvalue[2] = bottonright.y;
    yvalue[3] = bottonleft.y;

    Max = {0,0};
    Min = {20000,20000};

    for(int i=0;i<4;i++){
        /*X max and min values*/
        if(xvalue[i] > Max.x){
            Max.x = xvalue[i];
        }
        if(xvalue[i] < Min.x){
            Min.x = xvalue[i];
        }

        /*Y max and min values*/
        if(yvalue[i] > Max.y){
            Max.y = yvalue[i];
        }
        
        if(yvalue[i] < Min.y){
            Min.y = yvalue[i];
        } 
    }

}

void Bullet::Time(){
    frame++;
    if(frame == 60){
        frame = 0;
        seconds++;
    }
}
void Bullet::Shot(){

    max_ammo = 5;
    if(colide){
        x -= velocity*sin(RAD3(angle))*direction.x;
        y -= velocity*cos(RAD3(angle))*direction.y;
        AdjustVelocity();
        colide = false;
    }
    x += velocity*sin(RAD3(angle))*direction.x;
    y += velocity*cos(RAD3(angle))*direction.y;

}
void Bullet::Render(SDL_Renderer *renderer){

    rect.x = x;
    rect.y = y;
    Time();
    // SDL_SetRenderDrawColor(renderer,0,0,0,0);
    // SDL_RenderFillRect(renderer,&rect);
    // SDL_SetRenderDrawColor(renderer,255,255,255,150);
    SDL_RenderCopy(renderer,texture,NULL,&rect);
}