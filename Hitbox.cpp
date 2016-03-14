#include "Hitbox.h"

Hitbox::Hitbox(int x, int y, int w, int h)
{
    this->rect.x=x;
    this->rect.y=y;
    this->rect.w=w;
    this->rect.h=h;
}

Hitbox::~Hitbox()
{
    //dtor
}
