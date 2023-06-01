#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"
#include "enemy.h"
#include "game_characterplay.h"
#include "menu.h"
#include "boss.h"
#include <ctime>
using namespace std;
SDL_Window* gWindow = NULL;
static SDL_Renderer* renderer = NULL;
SDL_Rect C_rect;
SDL_Rect mau= {0,0,0,0},thanh_mau= {0,0,0,0};
SDL_Texture* character;
SDL_Texture* slime=NULL;
SDL_Texture* ghost=NULL;
SDL_Texture* ghost2=NULL;
SDL_Texture* boss=NULL;
Mix_Music* gamemusic=NULL;
Mix_Chunk* sword_sound_effect=NULL;
TTF_Font* font=NULL;
SDL_Color textColor = {255, 255, 255};
int frametime;
int spawn_num;
draw game_character;
enemy slime;
enemy ghost;
enemy ghost2;
BOSS boss1;
Uint32 gamestart = SDL_GetTicks();
int cnt_time, sword_time,spawn_time;
int angle = 5,v=1;
bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ||IMG_Init(IMG_INIT_JPG) < 0||SDL_INIT_AUDIO<0||TTF_Init()<0||Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
        gWindow = SDL_CreateWindow( "I've Been Killing Monsters for 300 Years", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gmusic = Mix_LoadMUS("sound/music.mp3");
    font = TTF_OpenFont("font/ThaleahFat.ttf",50);
    sword_sound = Mix_LoadWAV("sound/sword_sound.wav");
    return success;
}
void spawn_enemy(enemy &slime, enemy &ghost, enemy &ghost2)
{
    if(spawn_time+time_spawn<=clock())
    {
        spawn_num++;
        spawn_num=min(spawn_num,200);
        spawn_time=clock();
        for(int j=0; j<=spawn_num/20; j++)
        {
            for(int i=0; i<=e_num; i++)
            {
                if(slime.check[i]==0)
                {
                    slime.spawn(game.print,i);
                    break;
                }
                if(ghost.check[i]==0&&game.score>=10)
                {
                    ghost.spawn(game.print,i);
                    break;
                }
                if(ghost2.check[i]==0&&game.score>=20)
                {
                    ghost2.spawn(game.print,i);
                    break;
                }
            }
            if(time_spawn>=200)
                time_spawn-=10;
        }
    }
}

void draw_enemy()
{
    for(int i=0; i<slime.num; i++)
    {
        if(dame::lv==3)
            SDL_RenderCopyEx(renderer,boss, NULL,&boss1.boss_rect, angle, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderCopyEx(renderer,slime, NULL,&slime.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderCopyEx(renderer,ghost, NULL,&ghost.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderCopyEx(renderer,ghost2, NULL,&ghost2.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
    }
}
void end_game()
{
    while(1)
    {
        SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
        SDL_RenderFillRect(renderer,NULL);
        printText(renderer,"YOU LOSE",580,250,font,textColor);
        draw_enemy();
        if(game_character.movex>0)
            SDL_RenderCopy(renderer, character, &game_character.cc_rect,&game_character.print);
        else
            SDL_RenderCopyEx(renderer,character, &game_character.cc_rect, &game_character.print, 0, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderPresent(renderer);
        if(clock()-20>=cnt_time)
        {
            game_character.die();
            cnt_time=clock();
            slime.emove(game_character.print,game_character.health);
            ghost.emove(game_character.print,game_character.health);
            ghost2.emove(game_character.print,game_character.health);
            if(abs(angle)==5)
                v=-v;
            angle+=v;
        }
        SDL_Event e;
        if(SDL_PollEvent(&e))
            if(e.type==SDL_QUIT)
                exit(0);
        if(game_character.play==0)
            break;
    }
    game_character.reset();
    slime.reset();
    ghost.reset();
    ghost2.reset();
    boss1.reset();

}
void render()
{
    frametime = SDL_GetTicks() - game_characterstart;
    SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
    SDL_RenderFillRect(renderer,NULL);
    SDL_Rect cur=game_character.cc_rect;
    if(slime.attack||ghost.attack||ghost2.attack||boss1.attack)
        game_character.cc_rect={0,48*18,55,55};
    if(game_character.movex>0)
        SDL_RenderCopy(renderer, character, &game_character.cc_rect,&game_character.print);
    else
        SDL_RenderCopyEx(renderer,character, &game_character.cc_rect, &game_character.print, 0, NULL, SDL_FLIP_HORIZONTAL);
    spawn_enemy(slime,ghost,ghost2);
    draw_enemy();
    thanks_mau(renderer, game_character, mau, thanh_mau);
    draw_score(renderer, font, textColor, game_character.score);
    draw_time(renderer,font,textColor,frametime);
    slime.attack=0;ghost.attack=0;ghost2.attack=0;boss1.attack=0;
    game_character.cc_rect=cur;
    SDL_RenderPresent(renderer);
}
void but_pause()
{
    int get_pause=SDL_GetTicks();
    int nani=0;
    pause(renderer,nani);
    if(nani==1)
    {
        game_character.reset();
        slime.reset();
        ghost.reset();
        ghost2.reset();
        game_character.play=1;
        game_characterstart = SDL_GetTicks();
    }
    if(nani==2)
    {
        game_character.play=1;
        game_characterstart+=SDL_GetTicks()-get_pause;
    }
    if(nani==3)
    {
        game_character.play=0;
        game_character.reset();
        slime.reset();
        ghost.reset();
        ghost2.reset();
        game_characterstart = SDL_GetTicks();
    }
}
void are_you_winning()
{
    if(dame::lv==1)
    {
        if((game_character.score>=20&&frametime>=120000)||game_character.score>=40)
        {
            game_character.play=0;
            game_character.reset();
            slime.reset();
            ghost.reset();
            ghost2.reset();
            game_characterstart = SDL_GetTicks();
            int t=5000;
            while(t--)
            {
                SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
                SDL_RenderFillRect(renderer,NULL);
                if(game_character.movex>0)
                    SDL_RenderCopy(renderer, character, &game_character.cc_rect,&game_character.print);
                else
                    SDL_RenderCopyEx(renderer,character, &game_character.cc_rect, &game_character.print, 0, NULL, SDL_FLIP_HORIZONTAL);
                printText(renderer,"YOU WIN",580,250,font,textColor);
                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
            }

        }
    }
    if(dame::lv==2)
    {
        if((game_character.score>=30&&frametime>=180000)||game_character.score>=60)
        {
            game_character.play=0;
            game_character.reset();
            slime.reset();
            ghost.reset();
            ghost2.reset();
            game_characterstart = SDL_GetTicks();
            int t=5000;
            while(t--)
            {
                SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
                SDL_RenderFillRect(renderer,NULL);
                if(game_character.movex>0)
                    SDL_RenderCopy(renderer, character, &game_character.cc_rect,&game_character.print);
                else
                    SDL_RenderCopyEx(renderer,character, &game_character.cc_rect, &game_character.print, 0, NULL, SDL_FLIP_HORIZONTAL);
                printText(renderer,"YOU WIN",580,250,font,textColor);
                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
            }

        }
    }
    if(dame::lv==3)
    {
        if((game_character.score>=50&&frametime>=250000)||game_character.score>=100)
        {
            game_character.play=0;
            game_character.reset();
            slime.reset();
            ghost.reset();
            ghost2.reset();
            game_characterstart = SDL_GetTicks();
            int t=5000;
            while(t--)
            {
                SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
                SDL_RenderFillRect(renderer,NULL);
                if(game_character.movex>0)
                    SDL_RenderCopy(renderer, character, &game_character.cc_rect,&game_character.print);
                else
                    SDL_RenderCopyEx(renderer,character, &game_character.cc_rect, &game_character.print, 0, NULL, SDL_FLIP_HORIZONTAL);
                printText(renderer,"YOU WIN",580,250,font,textColor);
                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
            }

        }
    }
}
int main( int argc, char* args[] )
{

    if( !init() )
        printf( "Failed to initialize!\n" );
    else
    {
        renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        character =IMG_LoadTexture(renderer,"image/char.png");
        slime =IMG_LoadTexture(renderer,"image/ghost.png");
        ghost =IMG_LoadTexture(renderer,"image/cyclops.png");
        ghost2 = IMG_LoadTexture(renderer,"image/monster.png");
        boss=IMG_LoadTexture(renderer,"image/boss.png");
        slime.e_health=1;
        ghost.e_health=2;
        ghost2.e_health=3;
        SDL_Event e;
        while(1)
        {
            int framestart=clock();
            if(!game_character.play)
            {
                Mix_PlayMusic(gmusic,1);
                run_menu(renderer,font,textColor);
                Mix_HaltMusic();
                game_character.play=1;
                game_characterstart = SDL_GetTicks();
            }
            if(game_character.play==2)
            {
                but_pause();
            }
            if(game_character.health<=0)
            {
                end_game_character();
                continue;
            }
            if(game_character.action==1)
            {
                Mix_HaltChannel(-1);
                Mix_PlayChannel( -1, sword_sound, 0 );
                game_character.action==2;
            }
            are_you_winning();
            if(clock()-30>=cnt_time)
            {
                cnt_time=clock();
                slime.emove(game_character.print,game_character.health);
                ghost.emove(game_character.print,game_character.health);
                ghost2.emove(game_character.print,game_character.health);
                if(dame::lv==3)
                    boss1.emove(game_character.print,game_character.health);
                if(abs(angle)==5)
                    v=-v;
                angle+=v;
            }
            charmove(e,game_character,sword_time,slime, ghost, ghost2,boss1);
            render();
            SDL_RenderClear(renderer);
            int delay=max((long long)(1000/dame::fps-(clock()-framestart)),0ll);
            SDL_Delay(delay);
        }
    }
    return 0;
}

