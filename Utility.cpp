#include "Utility.h"

bool collides(SDL_Rect h1, SDL_Rect h2)
{
    if(h1.x>h2.x+h2.w)//Muy a la izquierda?
    {
        return false;
    }
    if(h1.x+h1.w<h2.x)//Muy a la derecha?
    {
        return false;
    }
    if(h1.y<h2.y-h2.h)//Muy arriba?
    {
        return false;
    }
    if(h1.y-h1.h>h2.y)//Muy abajo?
    {
        return false;
    }
    return true;
}

void drawRect(SDL_Renderer* renderer,int x, int y, int w, int h,
              int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;
    rect.w=w;
    rect.h=h;
    SDL_RenderDrawRect(renderer,&rect);
}
