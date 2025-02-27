/*IDEA is simple Player have like 5-6 bullets, they all "explode" when player is close enoucgh, also the workind through Walls :D (eay)*/

#include"Weapon.cpp"

void Weapon::TheMinWeaponShot(){

    Mins.x = center.x - Mins.rect.w/2;
    Mins.y = center.y - Mins.rect.h/2;

    if(shot){
        if(MainMine.size() < 6){
            Mins.angle = -angle;
            Mins.direction.x = 1;
            Mins.direction.y = 1;
            Mins.MinsToExplode.frames = 0;
            Mins.MinsToExplode.seconds = 0;
            Mins.loaded = false;
            LengthWeapon = 5;
            MainMine.push_back(Mins);
        }
    }
    shot = false;
}

void Weapon::MinWeaponLoad(TheMin &m){
    m.exploded = true;
    if(!m.loaded){
        for(int iter=0;iter<20;iter++){
        BomboClatMinions.x = m.rect.x;
        BomboClatMinions.y = m.rect.y;
        BomboClatMinions.angle = BomboClatMinions.angle + 360/20;
        BomboClatMinions.direction.x = 1;
        BomboClatMinions.direction.y = 1;
        m.ExplosionBullet.push_back(BomboClatMinions);
        m.loaded = true;
        }
    }
    if(m.ExplosionBullet.empty()) m.loaded == false;
}

void Weapon::MinRenderWeapon(SDL_Renderer *renderer){

    std::cout << "MainMIneSize:: " << MainMine.size() <<"\n";
    for(int index =0;index < MainMine.size(); index++){
        if(!MainMine[index].colide) MainMine[index].Shot();
        else{ 
            MainMine[index].MinsToExplode.Timing();
            MinWeaponLoad(MainMine[index]);
        }
        for(int iter = 0;iter < MainMine[index].ExplosionBullet.size();iter++){
             MainMine[index].ExplosionBullet[iter].MinMinErase.Timing();
            if(!MainMine[index].ExplosionBullet[iter].colide || !MainMine[index].ExplosionBullet[iter].MinMinErase.seconds == 5) {
                MainMine[index].ExplosionBullet[iter].Shot();
                MainMine[index].ExplosionBullet[iter].Render(renderer);
            }
            else{ 
                if(MainMine[index].ExplosionBullet[iter].MinMinErase.seconds == 5) {
                    MainMine[index].ExplosionBullet.clear();
                    MainMine[index].ExplosionBullet[iter].MinMinErase.seconds == 5 ; 
            }
                else{
                    MainMine[index].ExplosionBullet.erase(MainMine[index].ExplosionBullet.begin() + iter);
                    iter--;
                }           
                }
        }

        if(MainMine[index].exploded && MainMine[index].ExplosionBullet.empty()) {
            MainMine.erase(MainMine.begin() + index);
        }
        if(!MainMine[index].exploded) MainMine[index].Render(renderer);
        SDL_RenderCopy(renderer,NULL,NULL,&rect);
    }
}



