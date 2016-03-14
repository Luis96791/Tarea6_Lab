#ifndef UTILITYX_H
#define UTILITYX_H

#include<SDL2/SDL.h>
#include "Hitbox.h"

//void drawRect(SDL_Renderer* renderer,int x, int y, int w, int h,
//              int r, int g, int b, int a)
//{
//    SDL_SetRenderDrawColor(renderer, r, g, b, a);
//    SDL_Rect rect;
//    rect.x=x;
//    rect.y=y;
//    rect.w=w;
//    rect.h=h;
//    SDL_RenderDrawRect(renderer,&rect);
//}

bool collides(SDL_Rect h1, SDL_Rect h2);

void drawRect(SDL_Renderer* renderer,int x, int y, int w, int h,
              int r, int g, int b, int a);

#endif // UTILITY_H
