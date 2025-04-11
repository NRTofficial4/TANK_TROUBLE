/*Inclued Sound effect Method */

/*Sound Channels--------------------------------*/
/*Ind order to *mixing* we need to know which channel set to which Volume :D*/

/*LIST OF CHANNELS - M I X E R:-------------------------------------------------
0 - shot base Weapon -
1 - colide with wall soud (base weapon) -
2 - shot BomboClat Weapon 
3 - colide with Wall MainBullet
4 - colide with Wall Minions || Colide with Wall MiniGunBullets
5 - EndRundSound 
6 - PlayerKys sound
7 - TAnk Getting Hit by the bullets
*/

#include "window.cpp"

void Window::SoundEffect(){

    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT, 2, 1024);
    EndRundSound = Mix_LoadWAV("Sound/fart.mp3");
    BomboClatMainBullet.ShotMusic = Mix_LoadWAV("Sound/shoted.wav");
    BomboClatMainBullet.ExplodeMusic = Mix_LoadWAV("Sound/fart.wav");
    BomboClatMainBullet.BonceMusic = Mix_LoadWAV("Sound/BomboClatBounce.wav");
    tank_blue.weapon.ShotSound = Mix_LoadWAV("Sound/baseshot.wav");
    tank_red.weapon.ShotSound = Mix_LoadWAV("Sound/baseshot.wav");
    tank_green.weapon.ShotSound = Mix_LoadWAV("Sound/baseshot.wav");
    PLayerKys = Mix_LoadWAV("Sound/dead.wav");
    BaseWallSound = Mix_LoadWAV("Sound/Bonce.wav");
    MiniGunWallSound = Mix_LoadWAV("Sound/MiniGunWallSound.wav");
    backroundmusic = Mix_LoadMUS("Sound/ts_backround.wav");

/*------- M I X E R ------------ M I X E R --------- M I X E R ----------- M I X E R ----- M I X E R -------*/
    Mix_Volume(0,50);
    Mix_Volume(1,100);
    Mix_Volume(3,40);
    Mix_Volume(4,30);
    Mix_Volume(6,30);
    Mix_Volume(7,128);
    Mix_VolumeMusic(100);

    tank_blue.SoundLoad();
    tank_red.SoundLoad();
}

void Window::PlayBackroundMusic(){
    if(Mix_PlayingMusic() == 0) Mix_PlayMusic(backroundmusic,-1);
}