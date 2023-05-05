#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"
#include "menu.h"
#include "boss.h"
void BOSS::emove(SDL_Rect print,double &health)
{
    SDL_Rect rect =print;
    rect.x+=30;
    rect.y+=30;
    rect.w-=60;
    rect.h-=60;
    print.x+=print.w/2;
    print.y+=print.h/2;
    if(collision(boss_rect,rect)&&boss_health>0)
    {
        health-=dame::e_dame*2;
        attack=1;
        return;
    }
    if(boss_rect.y>print.y)
        boss_rect.y-=dame::e_step-1;
    else if(boss_rect.y<print.y)
        boss_rect.y+=dame::e_step-1;
    if(boss_rect.x>print.x)
        boss_rect.x-=dame::e_step-1;
    else
        boss_rect.x+=dame::e_step-1;
}
void BOSS::reset()
{
    boss_rect= {400,300,132,88};
    boss_health=100;
}

