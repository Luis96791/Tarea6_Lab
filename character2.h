#ifndef CHARACTER2_H
#define CHARACTER2_H

#include <iostream>
#include <map>
#include <fstream>
#include "Move.h"
#include "InputManager.h"
using namespace std;

class Character2
{
    public:
        InputManager *input_manager;
        map<string,Move*>moves;
        string current_move;
        int current_sprite;
        int current_sprite_frame;
        int x;
        int y;
        bool flipped;
        Character2(SDL_Renderer* renderer, int x, int y, bool flipped, string input_manager_file, string joystick_file_path);
        virtual ~Character2();
        void logic();
        void draw();
        Move* getMove(SDL_Renderer *renderer, string name, int sprite_amount);
        vector<Hitbox*> getHitboxes();
        vector<Hitbox*> getHurtboxes();
        void cancel(string new_move);
    protected:
    private:
};

#endif // CHARACTER_H2

