/*README
Bullets: Bomboclat objcet and Minions are defined in WEapon.cpp due to them working properly */

#include"Weapon.cpp"


void Weapon::BomboclatWeaponShot(){

    BomboClatMainBullet.x = center.x - BomboClatMainBullet.rect.w/2;
    BomboClatMainBullet.y = center.y - BomboClatMainBullet.rect.h/2;

    if(shot){
        if(MainBullet.size() < 2){
            Mix_PlayChannel(-1,BomboClatMainBullet.ShotMusic,0);
            BomboClatMainBullet.angle = -angle;
            BomboClatMainBullet.direction.x = 1;
            BomboClatMainBullet.direction.y = 1;
            BomboClatMainBullet.BombTime.seconds = 0;
            BomboClatMainBullet.BombTime.frames = 0;
            BomboClatMainBullet.exploded = false;
            BomboClatMainBullet.velocity = BomboClatMainBullet.speed/(1.3);
            LengthWeapon = 0;
            OneAppleaDayKeepsTheDoctorAway = 10;
            MainBullet.push_back(BomboClatMainBullet);
        }
    }
    shot = false;
}

void Weapon::LoadBomboClatWeapon(BomboClat &b){
    for(int iter=0;iter<15;iter++){
        BomboClatMinions.x = b.rect.x;
        BomboClatMinions.y = b.rect.y;
        BomboClatMinions.angle = BomboClatMinions.angle + 360/15;
        BomboClatMinions.direction.x = 1;
        BomboClatMinions.direction.y = 1;
        b.Minions.push_back(BomboClatMinions);
        b.Loaded = true;
    }
    Mix_PlayChannel(-1,BomboClatMainBullet.ExplodeMusic,0);
}

void Weapon::BomboClatWeaponRender(SDL_Renderer *renderer){
    
    if(!MainBullet.empty()){
    for(int index=0;index < MainBullet.size();index++){
        if(!MainBullet[index].exploded) MainBullet[index].BombTime.Timing();
        if(MainBullet[index].BombTime.seconds == 2){
            MainBullet[index].explode = true;
            MainBullet[index].exploded = true;
        }
        if(MainBullet[index].explode){
            MainBullet[index].explode = false;
            if(!MainBullet[index].Loaded) LoadBomboClatWeapon(MainBullet[index]);
        }
        if(!MainBullet[index].exploded){
            MainBullet[index].Shot();
            MainBullet[index].Render(renderer); 
        }
        else{
            if(MainBullet[index].Minions.empty()){
                MainBullet.erase(MainBullet.begin() + index);
            }
        }
    }
}

for(auto& b:MainBullet){
    if(!b.Minions.empty()){
        for(int iter=0;iter<b.Minions.size();iter++){
            b.Minions[iter].BombTime.Timing();
                b.Minions[iter].Shot();
                b.Minions[iter].Render(renderer);
                if(b.Minions[iter].BombTime.seconds >= 2){
                    b.Minions.clear();
                    break;
                }
            }
        }
    }
}