#ifndef menu_h_
#define menu_h_
void run_menu(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor);
void draw_time(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor, Uint32 frametime);
void draw_score(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor, int score);
void pause(SDL_Renderer* renderer,int &nani);
void option(SDL_Renderer* renderer);
void printText(SDL_Renderer* renderer,std::string text,int x, int y,TTF_Font* font,SDL_Color textColor);
class dame
{
public:
    static double e_dame;
    static int e_step;
    static int lv;
    static int fps;
};
#endif menu_h_h;
