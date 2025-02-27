/*--------------------------------THIS SHIT IS NOT WORKING-------------------------------------------------*/
/*Problems with making the Weapon and Ideas to solve them: */

/*Problem 1: - drawing a laser beam-------------------------------*/
/*IDEA - use the vector of a bullet and numeritically go to check if colision
if colision detected then we push up a point to a --Points list of a leaser--
Range: The Laser can "bouce of the wall" max 5 times*/

/*Problem 2: shotting a laser beam-------------------------------- */
/*IDEA1 create severals equlaly laserbeam on main laserbeam, and then render it depending on setting a speed of LaserBeam which is 
how long takes to render one segment 
    ->Every Segment(from one point colided to another) will be divided in 3 or 5 Segments
    ->Rendering Each of A segment in specific const value of time
    ->Speed of the LAser will be very fast, so change in the speed of the laser could be not so important

IDEA2 kill yourself*/

#include<iostream>
#include<vector>
#include<SDL2/SDL.h>

#include"Weapon.cpp"

class Laser{
    public:
        struct Point {float x;float y;};
        struct Lines{Point point1;Point point2;};
        Lines line;

        /*First StartPoint of the Laser - */
        Point StartPoint;

        /*The Point that checkes if the are some Lines to intersect with*/
        Point EndPoint;

        //List of poins which Laser can reflect

        std::vector<Point>ReflectPoints;
        std::vector<Lines>WallLines;

        void CreateReflectPoints();
        void CreateWallLines(SDL_Rect rect);
        void LaserColide(SDL_Rect rect);
        void Draw(SDL_Renderer *renderer); 
        int MaxLaserReflectPoints = 1;
        //How much we take a step to look at the Wall
        float LaserRange = 300;
        float angle;
        bool colide = false;

    private:

    /*Converter from rect values :D*/
    float xWall,yWall;
    /*Lines INtersect*/
    float Alfa,Beta;
    float a,b,c;


    /*The same as a bullet - detect from what sides*/
    Point Direction;
};

/*Bruh so like here the End Point.x Values are fucked and const but in Draw function is works becouse yes (bruh)*/

 void Laser::CreateWallLines(SDL_Rect rect){

    ReflectPoints.push_back(StartPoint);

    EndPoint.x = StartPoint.x - LaserRange*sin(RAD3(-angle));
    EndPoint.y = StartPoint.y - LaserRange*cos(RAD3(-angle));

    ReflectPoints.push_back(EndPoint);

    xWall = rect.x;
    yWall = rect.y;

    WallLines.clear();
    WallLines.push_back({{xWall,yWall},{xWall+rect.w,yWall}});
    WallLines.push_back({{xWall+rect.w,yWall},{xWall+rect.w,yWall+rect.h}});
    WallLines.push_back({{xWall+rect.w,yWall+rect.h},{xWall,yWall+rect.h}});
    WallLines.push_back({{xWall,yWall+rect.h},{xWall,yWall}});

    LaserColide(rect);

}
void Laser::LaserColide(SDL_Rect rect){
        for(auto W:WallLines){
        a = (W.point2.x - W.point1.x)*(W.point1.y - StartPoint.y) -(W.point2.y - W.point1.y)*(W.point1.x - StartPoint.x) ;
        c = (EndPoint.x - StartPoint.x)*(W.point1.y - StartPoint.y) -(EndPoint.y - StartPoint.y)*(W.point1.x - StartPoint.x) ;
        b = ((W.point2.x - W.point1.x)*(EndPoint.y - StartPoint.y) -(W.point2.y - W.point1.y)*(EndPoint.x - StartPoint.x) );

        if(b != 0){
            Alfa = a/b;
            Beta = c/b;
        }

        if(Alfa == Beta && b!=0) {
            colide = true;
            break;
        }
        else{
        }
    
    }
    if(colide) {
        std::cout << "LINDES ARE COLIDING\n";
        colide = false;
        // EndPoint.x = StartPoint.x + Alfa*(EndPoint.x - StartPoint.x);
        // EndPoint.y = StartPoint.y + Alfa*(EndPoint.y - StartPoint.y);
    }
    else{
        std::cout << "LINDES ARE NOT COLIDING\n";
    }

}

void Laser::CreateReflectPoints(){
// for(int index=0;index<MaxLaserReflectPoints;index++){

// }

}

void Laser::Draw(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer,255,0,0,155);
    for(int index=0;index< ReflectPoints.size();index++){
if(index != 0) SDL_RenderDrawLine(renderer,ReflectPoints[index-1].x,ReflectPoints[index-1].y,ReflectPoints[index].x,ReflectPoints[index].y);
    }
    
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    ReflectPoints.clear();
}