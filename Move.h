#ifndef MOVE_H
#define MOVE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include <iostream>
#include <vector>
#include "Sprite.h"
#include "Button.h"

using namespace std;

class Move
{
    public:
        vector<Sprite*> sprites;
        SDL_Renderer* renderer;
        int frame;
        int current_sprite_frame;

        vector<string>cancels;

        vector<Button*>buttons;

        Move(SDL_Renderer* renderer,vector<Sprite*>sprites,vector<string>cancels,vector<Button*>buttons);
        virtual ~Move();
        void draw(int current_sprite,int character_x, int character_y,bool flipped);
        bool canCancel(string move_name);
    protected:
    private:
};

#endif // MOVE_H
