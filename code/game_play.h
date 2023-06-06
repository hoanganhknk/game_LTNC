#ifndef gameplay_h_
#define gameplay_h_
#include "draw.h"
#include "quaivat.h"
void destroy(draw &nv,quaivat &slime);
void charmove(SDL_Event e, draw &game,int &sword_time,quaivat &slime,quaivat &ghost, quaivat &ghost2,BOSS &boss1);
void sword(quaivat &slime, draw &game);
void thanks_mau(SDL_Renderer* renderer, draw &game, SDL_Rect &mau,SDL_Rect &thanh_mau);
const int range_attack=96;
#endif gameplay_h_h;
