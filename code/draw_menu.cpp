#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "menu.h"
#include "quaivat.h"
#include "draw.h"
using namespace std;
SDL_Texture* backgound=NULL;
SDL_Texture* op=NULL;
SDL_Texture* pau=NULL;
SDL_Texture* info=NULL;
SDL_Texture* blur=NULL;
Mix_Chunk* gclick= NULL;
SDL_Rect but_start,but_option,but_quit,but_info,option_pic,but_easy,but_medium,but_hard,but_info2;
const Uint8* st = SDL_GetKeyboardState(NULL);
string text_game= "I've Been Killing Monster";
string text_game2= "for 300 Years";
double dame::dame =0.5;
int dame::step=1;
int dame::lv=1;
int dame::fps=60;
void draw_menu(SDL_Renderer* renderer)
{
    but_start ={470,280,400,110};
    but_option ={470,425,400,110};
    but_quit ={470,555,400,110};
    but_info ={1150,590,65,65};
    option_pic={305,60,720,621};
    but_easy = {510,150,300,95};
    but_medium ={510,320,300,95};
    but_hard = {510,455,300,95};
    but_info2 ={950,570,45,45};
    backgound=IMG_LoadTexture(renderer,"image/menu.png");
    op=IMG_LoadTexture(renderer,"image/option.png");
    pau=IMG_LoadTexture(renderer,"image/pause.png");
    info = IMG_LoadTexture(renderer,"image/info.png");
    blur = IMG_LoadTexture(renderer,"image/blur.png");
    gclick= Mix_LoadWAV("sound/click.wav");
    SDL_RenderCopy(renderer,backgound,NULL,NULL);
    SDL_RenderPresent(renderer);
}
void option(SDL_Renderer* renderer)
{
    int mouseX, mouseY;
    SDL_Event e;
    while(1)
    {
        SDL_RenderCopy(renderer,backgound,NULL,NULL);
        SDL_RenderCopy(renderer,blur,NULL,NULL);
        SDL_RenderCopy(renderer,op,NULL,&option_pic);
        SDL_RenderPresent(renderer);
        SDL_PollEvent(&e);
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_easy.x&&mouseX<=but_easy.x+but_easy.w&&mouseY>=but_easy.y&&mouseY<=but_easy.y+but_easy.h)
        {
            dame::dame=0.5;
            dame::step=1;
            dame::lv=1;
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_medium.x&&mouseX<=but_medium.x+but_medium.w&&mouseY>=but_medium.y&&mouseY<=but_medium.y+but_medium.h)
        {
            dame::dame=1;
            dame::step=1;
            dame::lv=2;
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_hard.x&&mouseX<=but_hard.x+but_hard.w&&mouseY>=but_hard.y&&mouseY<=but_hard.y+but_hard.h)
        {
            dame::dame=1.5;
            dame::step=2;
            dame::lv=3;
            Mix_PlayChannel( -1, gclick, 0 );
            cout<<"hard";
            break;
        }
        if(e.type==SDL_QUIT)
            exit(0);
        if(e.type == SDL_MOUSEMOTION)
        {
            mouseX = e.button.x;
            mouseY = e.button.y;
        }
        SDL_RenderClear(renderer);
        SDL_Delay(5);
    }
    //cout<<dame;
}
void printtext_game(SDL_Renderer* renderer,string text_game,int x, int y,TTF_Font* font,SDL_Color text_gameColor)
{
    SDL_Surface* surface = TTF_Rendertext_Solid(font, text_game.c_str(),text_gameColor);
    SDL_texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = 21*text_game.size();
    dest.h = 45;
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
 	SDL_FreeSurface(surface);
}
void run_menu(SDL_Renderer* renderer,TTF_Font* font,SDL_Color text_gameColor)
{

    int mouseX, mouseY;
    SDL_Event e;
    while(1)
    {
        SDL_PollEvent(&e);
        draw_menu(renderer);
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_start.x&&mouseX<=but_start.x+but_start.w&&mouseY>=but_start.y&&mouseY<=but_start.y+but_start.h)
        {
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_option.x&&mouseX<=but_option.x+but_option.w&&mouseY>=but_option.y&&mouseY<=but_option.y+but_option.h)
        {
            Mix_PlayChannel( -1, gclick, 0 );
            option(renderer);
        }
        if(e.type==SDL_QUIT||(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_quit.x&&mouseX<=but_quit.x+but_quit.w&&mouseY>=but_quit.y&&mouseY<=but_quit.y+but_quit.h))
        {
            Mix_PlayChannel( -1, gclick, 0 );
            exit(0);
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_info.x&&mouseX<=but_info.x+but_info.w&&mouseY>=but_info.y&&mouseY<=but_info.y+but_info.h)
        {
            Mix_PlayChannel( -1, gclick, 0 );
            SDL_Event e;
            while(1)
            {
                SDL_PollEvent(&e);
                if(st[SDL_SCANCODE_ESCAPE])
                    break;
                if(e.type==SDL_QUIT)
                    exit(0);
                SDL_RenderCopy(renderer,backgound,NULL,NULL);
                SDL_RenderCopy(renderer,blur,NULL,NULL);
                SDL_RenderCopy(renderer,info,NULL,&option_pic);
                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
                SDL_Delay(10);
            }
        }
        if(e.type == SDL_MOUSEMOTION)
        {
            mouseX = e.button.x;
            mouseY = e.button.y;
        }
    }
    //cout<<dame;
}
void pause(SDL_Renderer* renderer,int &nani)
{
    int mouseX, mouseY;
    SDL_Event e;
    while(1)
    {
        SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
        SDL_RenderFillRect(renderer,NULL);
        SDL_RenderCopy(renderer,pau,NULL,&option_pic);
        SDL_RenderPresent(renderer);
        SDL_PollEvent(&e);
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_easy.x&&mouseX<=but_easy.x+but_easy.w&&mouseY>=but_easy.y&&mouseY<=but_easy.y+but_easy.h)
        {
            nani=1;
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_medium.x&&mouseX<=but_medium.x+but_medium.w&&mouseY>=but_medium.y&&mouseY<=but_medium.y+but_medium.h)
        {
            nani=2;
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_hard.x&&mouseX<=but_hard.x+but_hard.w&&mouseY>=but_hard.y&&mouseY<=but_hard.y+but_hard.h)
        {
            nani=3;
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_info2.x&&mouseX<=but_info2.x+but_info2.w&&mouseY>=but_info2.y&&mouseY<=but_info2.y+but_info2.h)
        {
            Mix_PlayChannel( -1, gclick, 0 );
            SDL_Event e;
            while(1)
            {
                SDL_PollEvent(&e);
                if(st[SDL_SCANCODE_ESCAPE])
                    break;
                SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
                SDL_RenderFillRect(renderer,NULL);
                SDL_RenderCopy(renderer,blur,NULL,NULL);
                SDL_RenderCopy(renderer,info,NULL,&option_pic);
                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
                SDL_Delay(10);
                if(e.type==SDL_QUIT)
                    exit(0);
            }
        }
        if(e.type==SDL_QUIT)
            exit(0);
        if(e.type == SDL_MOUSEMOTION)
        {
            mouseX = e.button.x;
            mouseY = e.button.y;
        }
        SDL_RenderClear(renderer);
        SDL_Delay(5);
    }

}
void draw_time(SDL_Renderer* renderer,TTF_Font* font,SDL_Color text_gameColor, Uint32 frametime)
{
    // Set time clock
    string text_game4 = "Time : ";
    int seconds, minutes;
    seconds = int(frametime)/1000;
    minutes = seconds/60;
    seconds = seconds%60;
    string str_minutes = to_string(minutes);
    string str_seconds = to_string(seconds);
    if(minutes < 10){
        if(seconds < 10){
            text_game4 = text_game4 +"0"+ str_minutes +":"+ "0" +str_seconds;
        }
        else{
            text_game4 = text_game4 +"0"+ str_minutes +":"+ str_seconds;
        }
    }
    else{
        if(seconds < 10){
            text_game4 = text_game4 + str_minutes +":"+ "0" +str_seconds;
        }
        else{
            text_game4 = text_game4 + str_minutes +":"+ str_seconds;
        }
    }
    printtext_game(renderer,text_game4,600,0,font,text_gameColor);
//    SDL_RenderPresent(renderer);
}
void draw_score(SDL_Renderer* renderer,TTF_Font* font,SDL_Color text_gameColor, int score)
{
    // Set score:
    string text_game3 = "SCORE : ";
    string temp = to_string(score);

    text_game3 = text_game3 + temp;

    printtext_game(renderer,text_game3,0,0,font,text_gameColor);
    //SDL_RenderPresent(renderer);
}
