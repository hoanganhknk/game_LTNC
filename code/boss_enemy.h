#ifndef boss_h_
#define boss_h_
#include "quaivat.h"
class BOSS: public quaivat
{
public :
    SDL_Rect boss_rect={400,300,132,88};
    int boss_health=100;
    void emove(SDL_Rect print,double &health);
    void reset();
};
#endif boss_h_h;
