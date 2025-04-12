#include"Weapon.cpp"

std::random_device rdMachineGUn;
std::mt19937 gen_machine(rdMachineGUn());

/*We used random distribution to generate bullet with difrient ammount of angle to*/
std::uniform_int_distribution<>MachineGunAngleDistrib(-15,15);

void Weapon::MachineWeaponShot(){

    MiniGun.x = center.x - rect.h*sin(RAD(-angle))/2;
    MiniGun.y = center.y - rect.h*cos(RAD(-angle))/2;
    MiniGun.direction.x = 1;
    MiniGun.direction.y = 1;

MachineBulletTime.Timing();

if(MiniGunBullets.size() <= Ammo && MachineBulletTime.frames == 4){
    Mix_PlayChannel(0,ShotSound,0);
    srcrect.x += 15;
    if(srcrect.x >= 200) srcrect.x = 0;
    MiniGun.angle = -angle + MachineGunAngleDistrib(rdMachineGUn);
    MiniGun.velocity = MiniGun.speed*1.2;
    MiniGunBullets.push_back(MiniGun);
    MachineBulletTime.frames = 0;
    OneAppleaDayKeepsTheDoctorAway = 10;

}

if(MiniGunBullets.size() == Ammo) {
    srcrect.x = 0;
    shot = false;
}

}

void Weapon::MachineWeaponRender(SDL_Renderer *renderer){
    for(int iter=0;iter<MiniGunBullets.size();iter++){
        MiniGunBullets[iter].BombTime.Timing();
        if(MiniGunBullets[iter].seconds > 3){
            MiniGunBullets.erase(MiniGunBullets.begin() + iter);
        }
        MiniGunBullets[iter].Shot();
        MiniGunBullets[iter].Render(renderer);
    }
}
