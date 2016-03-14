#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include<SDL2/SDL.h>
#include "Move.h"
#include "Button.h"
#include "DeviceButton.h"

#include <map>
#include <list>
#include <fstream>
using namespace std;

const int max_joystick_inputs=50;

class InputManager
{
    public:
        //Joystick
        bool JOYKEYS_player1[max_joystick_inputs];//joykey pressed
        bool JOYKEYS_player2[max_joystick_inputs];//joykey pressed
        bool joy_up_pressed_player_1;
        bool joy_down_pressed_player_1;
        bool joy_left_pressed_player_1;
        bool joy_right_pressed_player_1;
        bool joy_up_pressed_player_2;
        bool joy_down_pressed_player_2;
        bool joy_left_pressed_player_2;
        bool joy_right_pressed_player_2;


        map<char,DeviceButton*>input_map;
        map<char,int>joystick_map;
        list<Button*>buffer;
        vector<char>possible_buttons;
        InputManager(string file_path,string joystick_file_path);
        int sdlKeboardMap(string scancode_name);
        bool isPressed(Button button);
        bool isInBuffer(Move move);
        void update();

        bool isJoyDown(int joyCode,int joystick);
        void updateJoystick();

        virtual ~InputManager();
    protected:
    private:
};

#endif // INPUTMANAGER_H
