#include<SDL2/SDL.h>
#include<vector>

class WeaponIcon{
    public:
        SDL_Rect rect;
        SDL_Texture*texture;
        std::vector<const char*>filenames;

        bool colide;
        bool ColideBlue;
        bool ColideRed;

        /* --for animation --*/
        float StaticPosX;
        float StaticPosY;

        /*index points to what type of Weapon it cointain :D*/
        int index;

        WeaponIcon();

        /*x,y -> position of the player naturlich*/
        void Colide(int x, int y);

        //x y - value of the center of cell :D

        void Position(int x,int y);

        void Render(SDL_Renderer *renderer);
        void Load(SDL_Renderer *renderer);


        // //select type of weapon which icon points to (Icon is a pointer wtf)
        // void SelectType();
    private:

    /*animation ---*/
    float angle;
};

WeaponIcon::WeaponIcon(){
    filenames.push_back("digiti");
    filenames.push_back("Assets/BomboClatIcon.png");
}

void WeaponIcon::Load(SDL_Renderer *renderer){
    SDL_Surface *surface = IMG_Load(filenames[index]);
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

void WeaponIcon::Colide(int x,int y){
    
    float dx = fabs(x - (rect.x + rect.w/2));
    float dy = fabs(y - (rect.y + rect.h/2));

    if(dx <= rect.h - 3 && dy < rect.h - 3) colide = true;

}

void WeaponIcon::Render(SDL_Renderer *renderer){

    angle += 3;

    rect.w = 50 + 4*sin(RAD3(angle));
    rect.h = 50 + 4*sin(RAD3(angle));

    rect.x = StaticPosX - 2*sin(RAD3(angle));
    rect.y = StaticPosY - 2*sin(RAD3(angle));

    SDL_RenderCopy(renderer,texture,NULL,&rect);
}