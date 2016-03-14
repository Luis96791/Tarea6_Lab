#include "Move.h"

Move::Move(SDL_Renderer* renderer,vector<Sprite*>sprites,vector<string>cancels,vector<Button*>buttons)
{
    this->renderer=renderer;
    for(int i=0;i<sprites.size();i++)
    {
        this->sprites.push_back(sprites[i]);
    }
    frame=0;
    current_sprite_frame=0;
    this->cancels = cancels;
    this->buttons = buttons;
}

Move::~Move()
{
    //dtor
}

void Move::draw(int current_sprite,int character_x, int character_y,bool flipped)
{
    Sprite* sprite = sprites[current_sprite];
    sprite->draw(character_x,character_y,flipped);
    frame++;
}

bool Move::canCancel(string move_name)
{
    for(int i=0;i<cancels.size();i++)
    {
        if(cancels[i]==move_name)
        {
            return true;
        }
    }
    return false;
}
