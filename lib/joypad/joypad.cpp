/**
 * joypad.cpp
 * Implements joypad.h
 **/

#include "joypad.h"

// Joypad constructors
Joypad::Joypad(){
    Joypad(JOYPADDEFAULT);
}

Joypad::Joypad(int joy_num){
    this->joy_num = joy_num;

    //set deadzones
    joy1_deadzones = DEADZONE;
    joy2_deadzones = DEADZONE;

    //set joystick scales
    setJoystickScale(1, JOYPADSCALE);
    setJoystickScale(2, JOYPADSCALE);

    //get 1st values from joypad
    update();
}

// Joypad functions

Joypad::update(){
    //update joystick values
    getJoystickSettings(joy_num);

    //update joystick vaules
    switch(joy_num){
        case 1:
            setJoyValue(1, joystick.joy1_x1, joystick.joy1_y1);
            setJoyValue(2, joystick.joy1_x2, joystick.joy1_y2);
            break;
        case 2:
            setJoyValue(1, joystick.joy2_x1, joystick.joy2_y1);
            setJoyValue(2, joystick.joy2_x2, joystick.joy2_y2);
            break;
        case *:
            joy1_x = 0;
            joy1_y = 0;
            joy2_x = 0;
            joy2_y = 0;
            break;
    }
}

Joypad::isButtonPressed(int button){
    int btn; 
 
    switch(joy_num){
        case 1:
            return (joystick.joy1_Buttons & (1 << (button - 1)) != 0)
            break;
        case 2:
            return (joystick.joy2_Buttons & (1 << (button - 1)) != 0)
            break;
        case *:
            return false;
    }
}

Joypad::setDeadzone(int joystick, int deadzone){
    switch(joystick){
        case 1:
            joy1_deadzone = deadzone;
            break;
        case 2:
            joy2_deadzone = deadzone;
            break;
        case *:
            break;
    }
}

Joypad::setJoystickScale(int joystick, double scale){
    setJoystickScale(joystick, scale, scale);
}

Joypad::setJoystickScale(int joystick, double scale_x, double scale_y){
    //Adjustment to fix range(-128 -> 127) to range(-100 -> 100)
    const double range_scale = 100/127;

    switch(joystick){
        case 1:
            joy1_scale_x = scale_x * range_scale;
            joy1_scale_y = scale_y * range_scale;
            break;
        case 2:
            joy2_scale_x = scale_x * range_scale;
            joy2_scale_y = scale_y * range_scale;
            break;
        case *:
            break;
    }
}

Joypad::setJoyValue(int joystick, int raw_x, int raw_y){

    //use pointers to limit memory and cpu overhead
    double * scale_x;
    double * scale_y;

    int * joy_x;
    int * joy_y;

    int * deadzone;

    switch(joystick){
        case 1:
            scale_x = &joy1_scale_x;
            scale_y = &joy1_scale_y;
            joy_x = &joy1_x;
            joy_y = &joy1_x;
            deadzone = &joy1_deadzone;
            break;
        case 2:
            scale_x = &joy2_scale_x;
            scale_y = &joy2_scale_y;
            joy_x = &joy2_x;
            joy_y = &joy2_x;
            deadzone = &joy2_deadzone;
            break;
    }

    if( abs(*joy_x) > *deadzone ){
        *joy_x = (int)( (double)raw_x * *scale_x );
    }
    else{
        *joy_x = 0;
    }

    if( abs(*joy_y) > *deadzone ){
        *joy_y = (int)( (double)raw_y * *scale_y );
    }
    else{
        *joy_y = 0;
    }
}
