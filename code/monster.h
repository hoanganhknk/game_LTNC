#ifndef quaivat_h_
#define quaivat_h_
static const int e_num=3000;
static int time_spawn =2000;
static int e_w=672,e_h=32;
class quaivat
{
public :
    void spawn(SDL_Rect print,int i);
    virtual void emove(SDL_Rect print,double &health);
    virtual void reset();
    int x,y,num=0;
    SDL_Rect printf[e_num+1];
    int check[e_num+1]={0};
    int e_health=1;
    int attack=0;
    bool collision (SDL_Rect a,SDL_Rect b);
};
#endif quaivat_h_h;
