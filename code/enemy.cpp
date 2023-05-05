#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "enemy.h"
#include "draw.h"
#include "menu.h"
using namespace std;
void enemy::spawn(SDL_Rect print,int i)
{
    printf[i]= {0,0,30,30};
    int x2=0,y2=0;
    if(i%4==1)
    {
        y2=rand()%150 +1;
    }
    if(i%4==2)
    {
        x2=260;
        y2=rand()% 150+1;
    }
    if(i%4==3)
    {
        x2=rand()% 260+1;
    }
    if(i%4==0)
    {
        y2=150;
        x2=rand()%260+1;
    }
    printf[i].x=x2*5;
    printf[i].y=y2*5;
    if(num<=e_num)
    {
        num++;
    }
    check[i]=e_health;
}
void enemy::emove(SDL_Rect print,double &health)
{
    SDL_Rect rect =print;
    rect.x+=30;
    rect.y+=30;
    rect.w-=60;
    rect.h-=60;
    print.x+=print.w/2;
    print.y+=print.h/2;
    for(int i=0; i<num; i++)
    {
        if(collision(printf[i],rect)&&check[i])
        {
            health-=dame::e_dame;
            attack=1;
            continue;
        }
        if(i%3==0)
        {
            if(abs(printf[i].x-print.x)>=abs(printf[i].y-print.y))
            {
                if(printf[i].x>print.x)
                    printf[i].x-=dame::e_step;
                else if(printf[i].x<print.x)
                    printf[i].x+=dame::e_step;
                else if(printf[i].y>print.y)
                    printf[i].y-=dame::e_step;
                else
                    printf[i].y+=dame::e_step;
            }
            else
            {
                if(printf[i].y>print.y)
                    printf[i].y-=dame::e_step;
                else if(printf[i].y<print.y)
                    printf[i].y+=dame::e_step;
                else if(printf[i].x>print.x)
                    printf[i].x-=dame::e_step;
                else
                    printf[i].x+=dame::e_step;
            }
        }
        if(i%3==1)
        {
            if(printf[i].y>print.y)
                printf[i].y-=dame::e_step;
            else if(printf[i].y<print.y)
                printf[i].y+=dame::e_step;
            if(printf[i].x>print.x)
                printf[i].x-=dame::e_step;
            else
                printf[i].x+=dame::e_step;
        }
        if(i%3==2)
        {
            if(abs(printf[i].x-print.x)>=abs(printf[i].y-print.y)*2)
            {
                if(printf[i].x>print.x)
                    printf[i].x-=dame::e_step;
                else if(printf[i].x<print.x)
                    printf[i].x+=dame::e_step;
                else if(printf[i].y>print.y)
                    printf[i].y-=dame::e_step;
                else
                    printf[i].y+=dame::e_step;
            }
            else
            {
                if(printf[i].y>print.y)
                    printf[i].y-=dame::e_step;
                else if(printf[i].y<print.y)
                    printf[i].y+=dame::e_step;
                else if(printf[i].x>print.x)
                    printf[i].x-=dame::e_step;
                else
                    printf[i].x+=dame::e_step;
            }
        }
    }
}
bool enemy::collision (SDL_Rect a,SDL_Rect b)
{

    if(a.x>=b.x&&a.x<=b.x+b.w&&a.y>=b.y&&a.y<=b.y+b.h)
        return 1;
    if(a.x+a.w>=b.x&&a.x+a.w<=b.x+b.w&&a.y>=b.y&&a.y<=b.y+b.h)
        return 1;
    if(a.x>=b.x&&a.x<=b.x+b.w&&a.y+a.h>=b.y&&a.y+a.h<=b.y+b.h)
        return 1;
    if(a.x+a.w>=b.x&&a.x+a.w<=b.x+b.w&&a.y+a.h>=b.y&&a.y+a.h<=b.y+b.h)
        return 1;
    return 0;
}
void enemy::reset()
{
    num=0;
    for(int i=0; i<=e_num; i++)
    {
        check[i]= {0};
        printf[i]= {0,0,0,0};

    }
}
