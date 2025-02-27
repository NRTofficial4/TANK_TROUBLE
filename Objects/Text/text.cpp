#include<iostream>

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<string>

class Text{
    public:

        Text(const char* skibidi,int x, int y);
        SDL_Rect rect;

        TTF_Font *font;
        SDL_Color color;
        SDL_Texture *TextTexture;
        SDL_Surface *surface;

        //text---
        const char *text;
        //font
        const char* FontName;

        /*Animation needs this*/
        float StaticPos_Y;
        float angle;

        /*strinf -> we convert Number to the string and string to const char**/
        std::string s ;

        void Texture(SDL_Renderer *renderer);
        void TextRendering(SDL_Renderer *renderer);
        void Number2Text(int Points);
        void NumberCenter(int x, int y);

    private:
};

Text::Text(const char* skibidi,int x, int y){
    FontName = skibidi;
    rect.x = x;
    rect.y = y;
    StaticPos_Y = rect.y;
}

void Text::Number2Text(int Points){
s = std::to_string(Points);
text = s.c_str();
}

void Text::Texture(SDL_Renderer *renderer){

    font = TTF_OpenFont(FontName, 100);
    if(!font) std::cout << "FONT NOT FONT!\n";
    rect.w = 100;
    rect.h = 150;

    surface = TTF_RenderText_Solid(font,text,color);

    if(surface == nullptr) std::cout << "Could not render text!\n";

    TextTexture = SDL_CreateTextureFromSurface(renderer,surface);

    if(TextTexture == nullptr) std::cout << "ImTexture not initialized ! "<< TTF_GetError()<< "\n";

    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
}

void Text::TextRendering(SDL_Renderer *renderer){

    // Texture(renderer);
    SDL_RenderCopy(renderer,TextTexture,NULL,&rect);

    /*animatinos*/
    angle += 4;
    rect.y = StaticPos_Y + 10*sin(RAD(angle));
    if(angle == 360) angle == 0;
}

