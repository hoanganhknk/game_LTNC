#ifndef draw_h_
#define draw_h_
#include "quaivat.h"
#include "boss.h"
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int step = 3;
bool init();
class draw
{
public :
    void die();
    void nextframe();
    void reset();
    void left(quaivat &slime, quaivat &ghost,quaivat &ghost2,BOSS &boss1);
    void right(quaivat &slime, quaivat &ghost,quaivat &ghost2,BOSS &boss1);
    void up(quaivat &slime, quaivat &ghost,quaivat &ghost2,BOSS &boss1);
    void down(quaivat &slime, quaivat &ghost,quaivat &ghost2,BOSS &boss1);
    SDL_Rect cc_rect={0,0,55,55},print={640,360,96,96};
    int movex =1,movey=1;
    double health =50;
    int score = 0;
    int play =0;
    int t=100;
    int action =0;
};

#endif draw_h_h;
