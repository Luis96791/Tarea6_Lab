#ifndef DEVICEBUTTON_H
#define DEVICEBUTTON_H


class DeviceButton
{
    public:
        int sdl_scancode_key;
        DeviceButton(){}
        DeviceButton(int sdl_scancode_key);
        virtual ~DeviceButton();
    protected:
    private:
};

#endif // DEVICEBUTTON_H
