#include "InputManager.h"

InputManager::InputManager(string file_path, string joystick_file_path)
{
    possible_buttons.push_back('8');
    possible_buttons.push_back('2');
    possible_buttons.push_back('4');
    possible_buttons.push_back('6');
    possible_buttons.push_back('a');
    possible_buttons.push_back('b');
    possible_buttons.push_back('c');
    possible_buttons.push_back('j');
    possible_buttons.push_back('w');
    possible_buttons.push_back('z');

    ifstream in(file_path.c_str());
    char input;
    string device;
    while(in>>input)
    {
        in>>device;
        input_map[input]=new DeviceButton(sdlKeboardMap(device));
    }

    ifstream joystick_file(joystick_file_path.c_str());
    int joystick_input;
    while(joystick_file>>input)
    {
        joystick_file>>joystick_input;
        joystick_map[input]=joystick_input;
    }

    for(int i=0;i<20;i++)
    {
        buffer.push_back(new Button('5'));
    }

    for(int i = 0; i < max_joystick_inputs; i++)   // init them all to false
    {
        JOYKEYS_player1[i] = false;
    }
    for(int i = 0; i < max_joystick_inputs; i++)   // init them all to false
    {
        JOYKEYS_player2[i] = false;
    }

    joy_up_pressed_player_1=false;
    joy_down_pressed_player_1=false;
    joy_left_pressed_player_1=false;
    joy_right_pressed_player_1=false;
    joy_up_pressed_player_2=false;
    joy_down_pressed_player_2=false;
    joy_left_pressed_player_2=false;
    joy_right_pressed_player_2=false;
}

InputManager::~InputManager()
{
    //dtor
}

bool InputManager::isPressed(Button button)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    DeviceButton* device_button = input_map[button.value];
    if(device_button!=NULL)
    {
        if(currentKeyStates[device_button->sdl_scancode_key])
            return true;
        else
            return false;
    }
}

void InputManager::update()
{
    updateJoystick();
//    for(list<Button*>::iterator i=buffer.begin();
//        i!=buffer.end();
//        i++)
//        cout<<(*i)->value;
//    cout<<endl;
//    cout.flush();

    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    bool is_button_pressed = false;
    for(int i=0;i<possible_buttons.size();i++)
    {
        if(isPressed(possible_buttons[i]))
        {
            buffer.push_back(new Button(possible_buttons[i]));
            buffer.pop_front();
            is_button_pressed=true;
            break;
        }
    }

    for(map<char,int>::iterator i=joystick_map.begin();
        i!=joystick_map.end();
        i++)
    {
        if(isJoyDown((*i).second,0))
        {
            buffer.push_back(new Button((*i).first));
            is_button_pressed=true;
        }
    }

//    if(isJoyDown(0,0))
//    {
//        buffer.push_back(new Button('a'));
//        is_button_pressed=true;
//    }
//
//    if(isJoyDown(-4,0))
//    {
//        buffer.push_back(new Button('4'));
//        is_button_pressed=true;
//    }
//
//    if(isJoyDown(-6,0))
//    {
//        buffer.push_back(new Button('6'));
//        is_button_pressed=true;
//    }

    if(!is_button_pressed)
    {
        buffer.push_back(new Button('5'));
        buffer.pop_front();
    }
}

bool InputManager::isInBuffer(Move move)
{
    move.buttons;
    buffer;
    list<Button*>::iterator buffer_iterator=buffer.end();
    buffer_iterator--;

    for(int i=move.buttons.size()-1;i>=0;i--)
    {
        if((*buffer_iterator)->value!=move.buttons[i]->value)
        {
            return false;
        }
        buffer_iterator--;
    }
    return true;
}

int InputManager::sdlKeboardMap(string scancode_name)
{
    map<string,int>sdl_key_constants;
    sdl_key_constants["SDL_SCANCODE_Q"]=SDL_SCANCODE_Q;
    sdl_key_constants["SDL_SCANCODE_W"]=SDL_SCANCODE_W;
    sdl_key_constants["SDL_SCANCODE_E"]=SDL_SCANCODE_E;
    sdl_key_constants["SDL_SCANCODE_R"]=SDL_SCANCODE_R;
    sdl_key_constants["SDL_SCANCODE_T"]=SDL_SCANCODE_T;
    sdl_key_constants["SDL_SCANCODE_Y"]=SDL_SCANCODE_Y;
    sdl_key_constants["SDL_SCANCODE_U"]=SDL_SCANCODE_U;
    sdl_key_constants["SDL_SCANCODE_I"]=SDL_SCANCODE_I;
    sdl_key_constants["SDL_SCANCODE_O"]=SDL_SCANCODE_O;
    sdl_key_constants["SDL_SCANCODE_P"]=SDL_SCANCODE_P;

    sdl_key_constants["SDL_SCANCODE_A"]=SDL_SCANCODE_A;
    sdl_key_constants["SDL_SCANCODE_S"]=SDL_SCANCODE_S;
    sdl_key_constants["SDL_SCANCODE_D"]=SDL_SCANCODE_D;
    sdl_key_constants["SDL_SCANCODE_F"]=SDL_SCANCODE_F;
    sdl_key_constants["SDL_SCANCODE_G"]=SDL_SCANCODE_G;
    sdl_key_constants["SDL_SCANCODE_H"]=SDL_SCANCODE_H;
    sdl_key_constants["SDL_SCANCODE_J"]=SDL_SCANCODE_J;
    sdl_key_constants["SDL_SCANCODE_K"]=SDL_SCANCODE_K;
    sdl_key_constants["SDL_SCANCODE_L"]=SDL_SCANCODE_L;

    sdl_key_constants["SDL_SCANCODE_Z"]=SDL_SCANCODE_Z;
    sdl_key_constants["SDL_SCANCODE_X"]=SDL_SCANCODE_X;
    sdl_key_constants["SDL_SCANCODE_C"]=SDL_SCANCODE_C;
    sdl_key_constants["SDL_SCANCODE_V"]=SDL_SCANCODE_V;
    sdl_key_constants["SDL_SCANCODE_B"]=SDL_SCANCODE_B;
    sdl_key_constants["SDL_SCANCODE_N"]=SDL_SCANCODE_N;
    sdl_key_constants["SDL_SCANCODE_M"]=SDL_SCANCODE_M;

    return sdl_key_constants[scancode_name];
}


bool InputManager::isJoyDown(int joyCode,int joystick)
{
    if(joystick==0)
    {
        if(joyCode==-1)
            return joy_down_pressed_player_1 && joy_left_pressed_player_1;
        if(joyCode==-3)
            return joy_down_pressed_player_1 && joy_right_pressed_player_1;
        if(joyCode==-7)
            return joy_up_pressed_player_1 && joy_left_pressed_player_1;
        if(joyCode==-9)
            return joy_up_pressed_player_1 && joy_right_pressed_player_1;
        if(joyCode==-2)
            return joy_down_pressed_player_1;
        if(joyCode==-4)
            return joy_left_pressed_player_1;
        if(joyCode==-6)
            return joy_right_pressed_player_1;
        if(joyCode==-8)
            return joy_up_pressed_player_1;
        if(JOYKEYS_player1[joyCode])
        {
            return true;
        }
        return false;
    }
    if(joystick==1)
    {
        if(joyCode==-1)
            return joy_down_pressed_player_2 && joy_left_pressed_player_2;
        if(joyCode==-3)
            return joy_down_pressed_player_2 && joy_right_pressed_player_2;
        if(joyCode==-7)
            return joy_up_pressed_player_2 && joy_left_pressed_player_2;
        if(joyCode==-9)
            return joy_up_pressed_player_2 && joy_right_pressed_player_2;
        if(joyCode==-2)
            return joy_down_pressed_player_2;
        if(joyCode==-4)
            return joy_left_pressed_player_2;
        if(joyCode==-6)
            return joy_right_pressed_player_2;
        if(joyCode==-8)
            return joy_up_pressed_player_2;
        if(JOYKEYS_player2[joyCode])
        {
            return true;
        }
        return false;
    }
    return false;
}


void InputManager::updateJoystick()
{
    //While there's events to handle
    SDL_Event event;
    while( SDL_PollEvent( &event ) )
    {
        //If the user has Xed out the window
        if( event.type == SDL_QUIT )
        {
            exit(0);
        }
        if( event.type == SDL_JOYBUTTONDOWN )
        {
            for(int i=0; i<max_joystick_inputs; i++)
            {
                if ( event.jbutton.button == i
                        && event.jbutton.which==0)
                {
                    JOYKEYS_player1[i]=true;
                }
            }
            for(int i=0; i<max_joystick_inputs; i++)
            {
                if ( event.jbutton.button == i
                        && event.jbutton.which==1)
                {
                    JOYKEYS_player2[i]=true;
                }
            }
        }
        if( event.type == SDL_JOYBUTTONUP )
        {
            for(int i=0; i<max_joystick_inputs; i++)
            {
                if ( event.jbutton.button == i
                        && event.jbutton.which==0)
                {
                    JOYKEYS_player1[i]=false;
                }
            }
            for(int i=0; i<max_joystick_inputs; i++)
            {
                if ( event.jbutton.button == i
                        && event.jbutton.which==1)
                {
                    JOYKEYS_player2[i]=false;
                }
            }
        }

        if( event.type == SDL_JOYHATMOTION)
        {
            //If joystick 0 has moved
            if( event.jhat.which == 0 )
            {
                joy_left_pressed_player_1=false;
                joy_right_pressed_player_1=false;
                joy_up_pressed_player_1=false;
                joy_down_pressed_player_1=false;
                switch(event.jhat.value)
                {
                case 8://Left
                    joy_left_pressed_player_1=true;
                    break;
                case 2://Right
                    joy_right_pressed_player_1=true;
                    break;
                case 1://Up
                    joy_up_pressed_player_1=true;
                    break;
                case 4://Down
                    joy_down_pressed_player_1=true;
                    break;
                case 9://Left up
                    joy_left_pressed_player_1=true;
                    joy_up_pressed_player_1=true;
                    break;
                case 3://Right up
                    joy_right_pressed_player_1=true;
                    joy_up_pressed_player_1=true;
                    break;
                case 12://left down
                    joy_left_pressed_player_1=true;
                    joy_down_pressed_player_1=true;
                    break;
                case 6://Right down
                    joy_right_pressed_player_1=true;
                    joy_down_pressed_player_1=true;
                    break;
                }

            }
            if( event.jhat.which == 1 )
            {
                joy_left_pressed_player_2=false;
                joy_right_pressed_player_2=false;
                joy_up_pressed_player_2=false;
                joy_down_pressed_player_2=false;
                switch(event.jhat.value)
                {
                case 8://Left
                    joy_left_pressed_player_2=true;
                    break;
                case 2://Right
                    joy_right_pressed_player_2=true;
                    break;
                case 1://Up
                    joy_up_pressed_player_2=true;
                    break;
                case 4://Down
                    joy_down_pressed_player_2=true;
                    break;
                case 9://Left up
                    joy_left_pressed_player_2=true;
                    joy_up_pressed_player_2=true;
                    break;
                case 3://Right up
                    joy_right_pressed_player_2=true;
                    joy_up_pressed_player_2=true;
                    break;
                case 12://left down
                    joy_left_pressed_player_2=true;
                    joy_down_pressed_player_2=true;
                    break;
                case 6://Right down
                    joy_right_pressed_player_2=true;
                    joy_down_pressed_player_2=true;
                    break;
                }
            }
        }

        if( event.type == SDL_JOYAXISMOTION )
        {
            //If joystick 0 has moved
            if( event.jaxis.which == 0 )
            {
                if( event.jaxis.axis == 0 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_left_pressed_player_1=false;
                        joy_right_pressed_player_1=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_left_pressed_player_1=true;
                            joy_right_pressed_player_1=false;
                        }
                        else
                        {
                            joy_right_pressed_player_1=true;
                            joy_left_pressed_player_1=false;
                        }
                    }
                }
                //If the Y axis changed
                else if( event.jaxis.axis == 1 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_up_pressed_player_1=false;
                        joy_down_pressed_player_1=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_up_pressed_player_1=true;
                            joy_down_pressed_player_1=false;
                        }
                        else
                        {
                            joy_down_pressed_player_1=true;
                            joy_up_pressed_player_1=false;
                        }
                    }
                }
            }

            if( event.jaxis.which == 1 )
            {
                if( event.jaxis.axis == 0 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_left_pressed_player_2=false;
                        joy_right_pressed_player_2=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_left_pressed_player_2=true;
                            joy_right_pressed_player_2=false;
                        }
                        else
                        {
                            joy_left_pressed_player_2=false;
                            joy_right_pressed_player_2=true;
                        }
                    }
                }
                //If the Y axis changed
                else if( event.jaxis.axis == 1 )
                {
                    if( ( event.jaxis.value > -8000 ) && ( event.jaxis.value < 8000 ) )
                    {
                        joy_up_pressed_player_2=false;
                        joy_down_pressed_player_2=false;
                    }
                    else
                    {
                        if( event.jaxis.value < 0 )
                        {
                            joy_up_pressed_player_2=true;
                            joy_down_pressed_player_2=false;
                        }
                        else
                        {
                            joy_up_pressed_player_2=false;
                            joy_down_pressed_player_2=true;
                        }
                    }
                }
            }
        }

    }
}
