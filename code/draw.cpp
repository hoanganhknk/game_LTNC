#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"
#include "enemy.h"
#include "gameplay.h"
#include "menu.h"
#include <ctime>
using namespace std;
void draw::nextframe()
{
    if(action)
    {
        cc_rect.y=48*6-5;
        cc_rect.x+=48;
        if(cc_rect.x>=4*48)
        {
            action=0;
            cc_rect.y=0;
            cc_rect.x=0;
        }
    }
    cc_rect.x+=48;
    if(cc_rect.x>48*5)
    {
        cc_rect.x=0;
        cc_rect.y+=48;
    }
    if(cc_rect.y>=48*1 && cc_rect.x>=48*5)
    {
        cc_rect.x=0;
        cc_rect.y=0;
    }
}
void draw::left(enemy &slime, enemy &ghost, enemy &ghost2,BOSS &boss1)
{
    for(int i=0;i<=e_num;i++)
    {
        if(slime.check[i])
        {
            slime.printf[i].x+=step;
        }
        if(ghost.check[i])
        {
            ghost.printf[i].x+=step;
        }
        if(ghost2.check[i])
        {
            ghost2.printf[i].x+=step;
        }
    }
    if(dame::lv==3)
        boss1.boss_rect.x+=step;
    movex--;
    if(movex<=-5)
    {
        movex=-1;
        movey=-1;
        nextframe();
    }
}
void draw::right(enemy &slime, enemy &ghost, enemy &ghost2,BOSS &boss1)
{
    for(int i=0;i<=e_num;i++)
    {
        if(slime.check[i])
        {
            slime.printf[i].x-=step;
        }
        if(ghost.check[i])
        {
            ghost.printf[i].x-=step;
        }
        if(ghost2.check[i])
        {
            ghost2.printf[i].x-=step;
        }
    }
    if(dame::lv==3)
        boss1.boss_rect.x-=step;
    movex++;
    if(movex>=5)
    {
        movex=1;
        movey=1;
        nextframe();
    }
}
void draw::up(enemy &slime, enemy &ghost, enemy &ghost2,BOSS &boss1)
{
    for(int i=0;i<=e_num;i++)
    {
        if(slime.check[i])
        {
            slime.printf[i].y+=step;
        }
        if(ghost.check[i])
        {
            ghost.printf[i].y+=step;
        }
        if(ghost2.check[i])
        {
            ghost2.printf[i].y+=step;
        }
    }
    if(dame::lv==3)
        boss1.boss_rect.y+=step;
    movey--;
    if(movey<=-5)
    {
        movex=movex/abs(movex);
        movey=-1;
        nextframe();
    }
}
void draw::down(enemy &slime, enemy &ghost, enemy &ghost2,BOSS &boss1)
{
    for(int i=0;i<=e_num;i++)
    {
        if(slime.check[i])
        {
            slime.printf[i].y-=step;
        }
        if(ghost.check[i])
        {
            ghost.printf[i].y-=step;
        }
        if(ghost2.check[i])
        {
            ghost2.printf[i].y-=step;
        }
    }
    if(dame::lv==3)
        boss1.boss_rect.y-=step;
    movey++;
    if(movey>=5)
    {
        movex=movex/abs(movex);
        movey=1;
        nextframe();
    }
}
void draw::die()
{
    cc_rect.y=48*19;
    if(cc_rect.x<48*6)
        cc_rect.x+=48;
    if(t==0)
        play=0;
    t--;
}
void draw::reset()
{
    cc_rect={0,0,55,55},print={640,360,96,96};
    movex =1,movey=1;
    action =0;
    health =50;
    score = 0;
    t=100;
}


