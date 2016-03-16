#include "character2.h"

std::string toString1(int number)
{
    if (number == 0)
        return "0";

    if(number < 0)
        return "-"+toString1(-number);

    std::string temp="";
    std::string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

Character2::Character2(SDL_Renderer* renderer, int x, int y, bool flipped, string input_manager_file, string joystick_file_path)
{
    this->x=x;
    this->y=y;
    this->flipped=flipped;

    moves["idle1"]=getMove(renderer,"idle1",4);
    moves["air_kick"]=getMove(renderer,"air_kick",3);
    moves["jump"]=getMove(renderer,"jump",8);
    moves["kick"]=getMove(renderer,"kick",6);
    moves["punch"]=getMove(renderer,"punch",3);
    moves["walk_forward"]=getMove(renderer,"walk_forward",5);
    moves["walk_backward"]=getMove(renderer,"walk_backward",5);
    moves["on_hit"]=getMove(renderer,"on_hit",5);

    this->current_move = "idle1";
    this->current_sprite = 0;
    this->current_sprite_frame = 0;
    this->input_manager=new InputManager(input_manager_file,joystick_file_path);
}

Move* Character2::getMove(SDL_Renderer *renderer, string name, int sprite_amount)
{
    //Sprites load
    vector<Sprite*>sprites;
    string align_file_path = "assets/" + name + "/align.txt";
    ifstream align_file(align_file_path.c_str());
    for(int i=1;i<=sprite_amount;i++)
    {
        string path="assets/" + name + "/" + toString1(i) + ".png";
        int align_x;
        int align_y;
        align_file>>align_x;
        align_file>>align_y;

        //Hitboxes
        vector<Hitbox*>hitboxes;
        string hitbox_file_path = "assets/" + name + "/hitboxes/"+toString1(i)+".txt";
        ifstream hitbox_file(hitbox_file_path.c_str());
        int x,y,w,h;
        while(hitbox_file>>x)
        {
            hitbox_file>>y;
            hitbox_file>>w;
            hitbox_file>>h;
            hitboxes.push_back(new Hitbox(x,y,w,h));
        }

        //Hurtboxes
        vector<Hitbox*>hurtboxes;
        string hurtboxes_file_path = "assets/" + name + "/hurtboxes/"+toString1(i)+".txt";
        ifstream hurtboxes_file(hurtboxes_file_path.c_str());
        while(hurtboxes_file>>x)
        {
            hurtboxes_file>>y;
            hurtboxes_file>>w;
            hurtboxes_file>>h;
            hurtboxes.push_back(new Hitbox(x,y,w,h));

            cout<<"Hurtbox!"<<endl;
        }

        sprites.push_back(new Sprite(renderer,path,10,align_x,align_y,hitboxes,hurtboxes));
    }

    //Cancel load
    string cancels_file_path = "assets/" + name + "/cancel.txt";
    ifstream cancels_file(cancels_file_path.c_str());
    vector<string>cancels;
    string cancel_temp;
    while(cancels_file>>cancel_temp)
    {
        cancels.push_back(cancel_temp);
    }

    string buttons_file_path = "assets/" + name + "/buttons.txt";
    ifstream buttons_file(buttons_file_path.c_str());
    vector<Button*>buttons;
    char button_temp;
    while(buttons_file>>button_temp)
    {
        buttons.push_back(new Button(button_temp));
    }

    return new Move(renderer,sprites,cancels,buttons);
}

Character2::~Character2()
{
    //dtor
}

void Character2::logic()
{
    input_manager->update();

    if(this->current_move=="on_hit")
    {
        if(flipped)
            this->x+=1;
        else
            this->x-=1;
    }

    if(input_manager->isJoyDown(/*Boton*/0,/*Joystick*/0))
    {
        cout<<"Boton presionado"<<endl;
    }

    if( input_manager->isInBuffer(*moves["kick"]) )
    {
        if(moves["kick"]->canCancel(this->current_move))
        {
            cancel("kick");
        }
    }
    else if( input_manager->isInBuffer(*moves["punch"]) )
    {
        if(moves["punch"]->canCancel(this->current_move))
        {
            cancel("punch");
        }
    }
    else if( input_manager->isInBuffer(*moves["walk_forward"]) )
    {
        if(moves["walk_forward"]->canCancel(this->current_move))
        {
            if(this->current_move!="walk_forward")
            {
                this->current_sprite = 0;
            }
            this->current_move = "walk_forward";
        }
    }
    else if( input_manager->isInBuffer(*moves["walk_backward"]) )
    {
        if(moves["walk_backward"]->canCancel(this->current_move))
        {
            if(this->current_move!="walk_backward")
            {
                this->current_sprite = 0;
            }
            this->current_move = "walk_backward";
        }
    }
    else if( input_manager->isInBuffer(*moves["jump"]) )
    {
        if(moves["jump"]->canCancel(this->current_move))
        {
            if(this->current_move!="jump")
            {
                this->current_sprite = 0;
            }
            this->current_move = "jump";
        }
    }
    else if( input_manager->isInBuffer(*moves["air_kick"]) )
    {
        if(moves["air_kick"]->canCancel(this->current_move))
        {
            if(this->current_move!="air_kick")
            {
                this->current_sprite = 0;
            }
            this->current_move = "air_kick";
        }
    }
    else
    {
        if(this->current_move=="walk_forward" || this->current_move=="walk_backward")
        {
            cancel("idle1");
        }
        if(this->current_move=="jump"){
            cancel("punch");
        }
    }

    current_sprite_frame++;
    if(current_sprite_frame>=moves[current_move]->sprites[current_sprite]->frames)
    {
        current_sprite++;
        if(current_sprite>=moves[current_move]->sprites.size())
        {
            current_move= "idle1";
            current_sprite=0;
        }
        current_sprite_frame=0;
    }

    if(current_move=="walk_forward")
    {
        this->x+=3;
    }
    if(current_move=="walk_backward")
    {
        this->x-=3;
    }
    if(current_move=="jump"||current_move=="air_kick")
    {
        if(!flipped){
            this->x+=1;
        }else
            this->x-=1;
    }
}

void Character2::draw()
{
    moves[current_move]->draw(current_sprite,x,y,flipped);
}

vector<Hitbox*> Character2::getHitboxes()
{
    return moves[current_move]->sprites[current_sprite]->hitboxes;
}

vector<Hitbox*> Character2::getHurtboxes()
{
    return moves[current_move]->sprites[current_sprite]->hurtboxes;
}

void Character2::cancel(string new_move)
{
    this->current_move = new_move;
    this->current_sprite = 0;
}

