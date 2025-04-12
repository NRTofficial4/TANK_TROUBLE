/*FIle includes Collision detection Method -Killing,Bouncing of wall, detect if player touched Icon ect*/

#include"window.cpp"

//Tank 1-tank that is shotting
//Tank 2 tank that gets shot


void Window::Mining(){
    for(auto& m:tank_blue.weapon.MainMine){
        m.InRange(tank_green.center.x,tank_green.center.y);
        m.InRange(tank_red.center.x,tank_red.center.y);
    }
    for(auto& m:tank_red.weapon.MainMine){
        m.InRange(tank_green.center.x,tank_green.center.y);
        m.InRange(tank_blue.center.x,tank_blue.center.y);
    }
     for(auto& m:tank_green.weapon.MainMine){
        m.InRange(tank_red.center.x,tank_red.center.y);
        m.InRange(tank_blue.center.x,tank_blue.center.y);
    }
}

void Window::KillPlayer(Tank &tank1,Tank &tank2){

switch (tank1.weapon.IndexWeapon)
{
/*Base Weapon-----------------------------*/
case 0:

    if(!tank1.weapon.Bullets.empty()){
        for(int index =0; index < tank1.weapon.Bullets.size();index++){
            if(!tank2.Killed) tank2.ProjectionColision(tank1.weapon.Bullets[index].rect);

            //Check if the player took what Adam ussually say to serious (check if the PLayer Kill Himself)
            if(!tank1.Killed) tank1.ProjectionColision(tank1.weapon.Bullets[index].rect);
            
            if(!tank2.Killed){
                if(tank2.Colided){
                    Mix_PlayChannel(7,tank2.HitMusic,0);
                    tank1.weapon.Bullets.erase(tank1.weapon.Bullets.begin()+index);
                    if(CritChance(rd) <= tank1.weapon.CritRate) tank2.Health = tank2.Health - 3*tank1.weapon.Damage;
                    else tank2.Health = tank2.Health - tank1.weapon.Damage;
                    if(tank2.Health <= 0){
                        tank2.Killed = true;
                        tank2.Colided = false;
                    }
                }
            }
            if(tank1.Colided){
                tank1.weapon.Bullets.erase(tank1.weapon.Bullets.begin()+index);
                tank1.Health = tank1.Health - tank1.weapon.Damage;
                if(tank1.Health <= 0){
                    tank1.Killed = true;
                    tank1.Colided = false;
                    Mix_PlayChannel(6,PLayerKys,0);
                }
            }
        }
    }
    break;
case 1:
/*BomboClat Weapon ---------------------------------------------------------*/

for(int index =0; index < tank1.weapon.MainBullet.size();index++){

for(int iter=0;iter<tank1.weapon.MainBullet[index].Minions.size();iter++){

    if(!tank2.Killed) tank2.ProjectionColision(tank1.weapon.MainBullet[index].Minions[iter].rect);
    //Check if the player took what Adam ussually say to serious (check if the PLayer Kill Himself)
    if(!tank1.Killed) tank1.ProjectionColision(tank1.weapon.MainBullet[index].Minions[iter].rect);

    if(!tank2.Killed){
        if(tank2.Colided){

                Mix_PlayChannel(7,tank2.HitMusic,0);
                tank1.weapon.MainBullet[index].Minions.erase(tank1.weapon.MainBullet[index].Minions.begin()+iter);

                if(CritChance(rd) <= tank1.weapon.CritRate) tank2.Health = tank2.Health - 3*tank1.weapon.Damage;
                else tank2.Health = tank2.Health - tank1.weapon.Damage;

                if(tank2.Health <= 0){
                    tank2.Killed = true;
                    tank2.Colided = false;
                }
            }
    }

    if(tank1.Colided){
        tank1.weapon.MainBullet[index].Minions.erase(tank1.weapon.MainBullet[index].Minions.begin()+iter);
        tank1.Health = tank1.Health - tank1.weapon.Damage;
        if(tank1.Health <= 0){
            tank1.Killed = true;
            tank1.Colided = false;
            Mix_PlayChannel(6,PLayerKys,0);
        }
    }

}
}
/*MiniGUn Weapon-----------------------------*/
//Minigun dont kill the shotter becouse it will make game unbalance (propably)
case 2:

    if(!tank1.weapon.MiniGunBullets.empty()){
        for(int index =0; index < tank1.weapon.MiniGunBullets.size();index++){
            if(!tank2.Killed) tank2.ProjectionColision(tank1.weapon.MiniGunBullets[index].rect);

            if(!tank2.Killed){   
                if(tank2.Colided){
                    Mix_PlayChannel(7,tank2.HitMusic,0);
                    tank1.weapon.MiniGunBullets.erase(tank1.weapon.MiniGunBullets.begin()+index);

                    if(CritChance(rd) <= tank1.weapon.CritRate) tank2.Health = tank2.Health - 3*tank1.weapon.Damage;
                    else tank2.Health = tank2.Health - tank1.weapon.Damage;

                    if(tank2.Health <= 0){
                        tank2.Killed = true;
                        tank2.Colided = false;
                    }
                }
        }
        }
    }
    break;

case 3:
    for(auto& m:tank1.weapon.MainMine){
    if(!m.ExplosionBullet.empty()){
        for(int index = 0; index < m.ExplosionBullet.size();index++){
            if(!tank2.Killed) tank2.ProjectionColision(m.ExplosionBullet[index].rect);
            if(tank2.Colided){
                //tank2.Health = tank2.Health - tank1.weapon.Damage;
                tank2.Killed = true;
                tank2.Colided = false;
            }
        }
    }
    }
    break;

default:
    break;
}

}

/*- Quick update to Collision -*/
float mtv[2] = {0,0};
void Window::Colision(Tank &tank){

/*Colision Detection Algorythm ----------------------*/
    for(auto& c:maze.cell){
        for(auto& w:c.Wall){
            if(fabs(tank.center.x - w.x + w.w/2) < 300 && fabs(tank.center.y - w.y + w.h/2) < 300){
                tank.ProjectionColision(w);
                if(tank.Colided){
                    tank.Colided = false;
                    tank.SrcRect.push_back(w);
                }
            }
        }
    }
/*TANK KOLISION: --------------------------*/
    if(!tank.SrcRect.empty()) {
        
        tank.Colided = true;

    /*Old option that worked but not so good $-$*/
        for(auto& src:tank.SrcRect){
            // std::cout << tank.SrcRect.size();
            tank.ProjectionColision(src);
            mtv[0] += tank.MTV[0];
            mtv[1] += tank.MTV[1];
            
        }
        if(tank.SrcRect.size() != 1){
            tank.MTV[0] = mtv[0]/2;
            tank.MTV[1] = mtv[1]/2;
        }
        else{
            tank.MTV[0] = mtv[0];
            tank.MTV[1] = mtv[1];
        }

        mtv[0] = 0;
        mtv[1] = 0;

        tank.SrcRect.clear();
    }

    /*BULLET COLISION:------------------------*/
    BulletColision(tank);
}

void Window::BulletColision(Tank &tank){


//INDEX 0 -----------------------------------------------------------------------------
for(auto& b:tank.weapon.Bullets){
    for(auto& c:maze.cell){
        for(auto& w:c.Wall){
        b.Colide(w);
            if(b.colide){
            b.colide = false;
            b.WallRects.push_back(w);
            }
        }
    }
}

for(auto& b:tank.weapon.Bullets){
    if(!b.WallRects.empty()){
        b.colide = true;
        Mix_PlayChannel(1,BaseWallSound,0);
        b.Colide(b.WallRects[0]);
    }
    b.WallRects.clear();
} 


//INDEX 1----------------------------------------------------------

for(auto& b:tank.weapon.MainBullet){
    for(auto& c:maze.cell){
        for(auto& w:c.Wall){
        b.Colide(w);
            if(b.colide){
            b.colide = false;
            b.WallRects.push_back(w);
            }
        
        for(auto& m:b.Minions){
            if(fabs(m.rect.x - w.x + w.w/2) < 200 && fabs(m.rect.y - w.y +w.h/2) < 200 ){
                m.Colide(w);
                if(m.colide){
                    m.colide = false;
                    m.WallRects.push_back(w);
                }
            }
        }
        }
    }
}

for(auto& b:tank.weapon.MainBullet){
    if(!b.WallRects.empty()){
        b.colide = true;
        Mix_PlayChannel(3,BomboClatMainBullet.BonceMusic,0);
        b.Colide(b.WallRects[0]);
    }
    b.WallRects.clear();
    for(auto& m:b.Minions){
        if(!m.WallRects.empty()){
            m.colide = true;
            m.Colide(m.WallRects[0]);
        }
    }
    b.WallRects.clear();
    for(auto& m:b.Minions){
        m.WallRects.clear();
    }
}

//INDEX 2 -----------------------------------------------------------------------------
for(auto& b:tank.weapon.MiniGunBullets){
    for(auto& c:maze.cell){
        for(auto& w:c.Wall){
        if(fabs(b.rect.x - w.x + w.w/2) < 200 && fabs(b.rect.y - w.y +w.h/2) < 200 ){
        b.Colide(w);
            if(b.colide){
            b.colide = false;
            b.WallRects.push_back(w);
            }
        }
        }
    }
}

for(auto& b:tank.weapon.MiniGunBullets){
    if(!b.WallRects.empty()){
        //Mix_PlayChannel(4,MiniGunWallSound,0);
        b.colide = true;
        b.Colide(b.WallRects[0]);
    }
    b.WallRects.clear();
} 

//INDEX 3----------------------------------------------------------
for(auto& b:tank.weapon.MainMine){
    for(auto& c:maze.cell){
        for(auto& w:c.Wall){
        b.Colide(w);
            if(b.colide){
            b.colide = false;
            b.WallRects.push_back(w);
            }
        
        for(auto& m:b.ExplosionBullet){
            if(fabs(m.rect.x - w.x + w.w/2) < 200 && fabs(m.rect.y - w.y +w.h/2) < 200 ){
                m.Colide(w);
                if(m.colide){
                    m.colide = false;
                    m.WallRects.push_back(w);
                }
            }
        }
        }
    }
}

for(auto& b:tank.weapon.MainMine){
    if(!b.WallRects.empty()){
        b.colide = true;
        b.Colide(b.WallRects[0]);
    }
    b.WallRects.clear();
    for(auto& m:b.ExplosionBullet){
        if(!m.WallRects.empty()){
            m.colide = true;
            m.Colide(m.WallRects[0]);
        }
    }
    b.WallRects.clear();
    for(auto& m:b.ExplosionBullet){
        m.WallRects.clear();
    }
}
}