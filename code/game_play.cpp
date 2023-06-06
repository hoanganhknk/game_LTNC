#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"
#include "quaivat.h"
#include "game_characterplay.h"
using namespace std;
const Uint8* state = SDL_GetKeyboardState(NULL);
void thanks_mau(SDL_Renderer* renderer,draw &game_character, SDL_Rect &mau,SDL_Rect &thanh_mau)
{
    if(game_character.movex > 0){
        mau.x=game_character.print.x+6;
        thanh_mau.x=game_character.print.x+5;
    }
    else{
        mau.x=game_character.print.x+19;
        thanh_mau.x=game_character.print.x+18;
    }
    mau.y=game_character.print.y+game_character.print.h-29;
    mau.h=4;
    mau.w=(double)(game_character.print.w*game_character.health)/50.0-30;
    thanh_mau.h=6;
    thanh_mau.y=game_character.print.y+game_character.print.h-30;
    thanh_mau.w=game_character.print.w-28;
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
void destroy(draw &nv,quaivat &slime)
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
void sword(quaivat &slime, draw &game_character)
{
    game_character.action =1;
    game_character.cc_rect.x=0;
    destroy(game_character,slime);
}
void charmove(SDL_Event e, draw &game_character,int &sword_time,quaivat &slime,quaivat &ghost, quaivat &ghost2,BOSS &boss1)
{
    SDL_PollEvent(&e);
    if(game_character.action)
    {
        game_character.nextframe();
        return ;
    }
    if(sword_time<clock()-300)
        if(e.type==SDL_MOUSEBUTTONDOWN||state[SDL_SCANCODE_SPACE])
        {
            sword_time=clock();
            sword(slime,game_character);
            sword(ghost,game_character);
            sword(ghost2,game_character);
        }
    if(state[SDL_SCANCODE_ESCAPE])
    {
        game_character.play=2;
        }
    if(state[SDL_SCANCODE_ESCAPE])
    {
        game_character.play=2;
    }
    if (state[SDL_SCANCODE_LEFT]||state[SDL_SCANCODE_A])
    {

            game_character.left(slime,ghost,ghost2,boss1);
    }
    if (state[SDL_SCANCODE_RIGHT]||state[SDL_SCANCODE_D])
    {
        game_character.right(slime,ghost,ghost2,boss1);
    }
    if (state[SDL_SCANCODE_UP]||state[SDL_SCANCODE_W])
    {
        game_character.up(slime, ghost,ghost2,boss1);
    }
    if (state[SDL_SCANCODE_DOWN]||state[SDL_SCANCODE_S])
    {
       game_character.down(slime,ghost,ghost2,boss1);
    }
    if (state[SDL_SCANCODE_N])
        game_character.score+=20;
    if(SDL_PollEvent(&e))
        if(e.type==SDL_QUIT)
            exit(0);

}
