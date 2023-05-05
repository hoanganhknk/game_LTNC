#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"
#include "enemy.h"
#include "gameplay.h"
using namespace std;
const Uint8* state = SDL_GetKeyboardState(NULL);
void thanks_mau(SDL_Renderer* renderer,draw &game, SDL_Rect &mau,SDL_Rect &thanh_mau)
{
    if(game.movex > 0){
        mau.x=game.print.x+6;
        thanh_mau.x=game.print.x+5;
    }
    else{
        mau.x=game.print.x+19;
        thanh_mau.x=game.print.x+18;
    }
    mau.y=game.print.y+game.print.h-29;
    mau.h=4;
    mau.w=(double)(game.print.w*game.health)/50.0-30;
    thanh_mau.h=6;
    thanh_mau.y=game.print.y+game.print.h-30;
    thanh_mau.w=game.print.w-28;
    if(mau.w<0){
        mau.w = 0;
    }
    SDL_SetRenderDrawColor(renderer,255,255,255,0);
    SDL_RenderFillRect(renderer,&thanh_mau);
    SDL_SetRenderDrawColor(renderer,255,0,0,0);
    SDL_RenderFillRect(renderer,&mau);
    //cout<<thanh_mau.h<<" "<<thanh_mau.w<<" "<<thanh_mau.x<<" "<<thanh_mau.y<<endl;
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
}
void destroy(draw &nv,enemy &slime)
{
    int x_mid=nv.print.x;
    int y_mid=nv.print.y;
    for(int i=0;i<slime.num;i++)
    {
//        if(slime.printf[i].x >= x_mid - 15 && slime.printf[i].y <= y_mid +1 ){
//                nv.health = nv.health- 10;
//        }
        if(nv.movex>0)
        {
            if(slime.printf[i].x<=x_mid+range_attack
            &&slime.printf[i].x>=x_mid
            &&slime.printf[i].y<=y_mid+range_attack
            &&slime.printf[i].y>=y_mid-range_attack/3
            && nv.action ==1 && slime.check[i] )
            {
                slime.check[i]--;
                if(slime.check[i]==0)
                {
                    slime.printf[i]={0,0,0,0};
                    nv.score ++;
                }

            }
        }
        else
        {
            if(slime.printf[i].x>=x_mid-range_attack/3
            &&slime.printf[i].x<=x_mid+range_attack/2
            &&slime.printf[i].y<=y_mid+range_attack
            &&slime.printf[i].y>=y_mid-(range_attack/5)*2
            &&nv.action ==1&& slime.check[i])
            {
                slime.check[i]--;
                if(slime.check[i]==0)
                {
                    slime.printf[i]={0,0,0,0};
                    nv.score ++;
                }
            }
        }
    }
}
void sword(enemy &slime, draw &game)
{
    game.action =1;
    game.cc_rect.x=0;
    destroy(game,slime);
}
void charmove(SDL_Event e, draw &game,int &sword_time,enemy &slime,enemy &ghost, enemy &ghost2,BOSS &boss1)
{
    SDL_PollEvent(&e);
    if(game.action)
    {
        game.nextframe();
        return ;
    }
    if(sword_time<clock()-300)
        if(e.type==SDL_MOUSEBUTTONDOWN||state[SDL_SCANCODE_SPACE])
        {
            sword_time=clock();
            sword(slime,game);
            sword(ghost,game);
            sword(ghost2,game);
        }
    if(state[SDL_SCANCODE_ESCAPE])
    {
        game.play=2;
        }
    if(state[SDL_SCANCODE_ESCAPE])
    {
        game.play=2;
    }
    if (state[SDL_SCANCODE_LEFT]||state[SDL_SCANCODE_A])
    {

            game.left(slime,ghost,ghost2,boss1);
    }
    if (state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D])
    {
        game.right(slime,ghost,ghost2,boss1);
    }
    if (state[SDL_SCANCODE_UP]||state[SDL_SCANCODE_W])
    {
        game.up(slime, ghost,ghost2,boss1);
    }
    if (state[SDL_SCANCODE_DOWN]||state[SDL_SCANCODE_S])
    {
       game.down(slime,ghost,ghost2,boss1);
    }
    if (state[SDL_SCANCODE_N])
        game.score+=20;
    if(SDL_PollEvent(&e))
        if(e.type==SDL_QUIT)
            exit(0);

}
