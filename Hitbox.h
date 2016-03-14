#ifndef HITBOX_H
#define HITBOX_H

#include<SDL2/SDL.h>

class Hitbox
{
    public:
        SDL_Rect rect;
        Hitbox(int x, int y, int w, int h);
        virtual ~Hitbox();
    protected:
    private:
};

#endif // HITBOX_H
