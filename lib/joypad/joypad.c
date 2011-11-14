/**
 * joypad.cpp
 * Implements joypad.h
 **/

#include "joypad.h"

// Joypad constructors
void joypad_init(Joypad * self){
    joypad_init(&self, JOYPADDEFAULT);
}

void joypad_init(Joypad * self, int joy_num){

    self.joy_num = joy_num;

    //set deadzones
    self.joy1_deadzones = DEADZONE;
    self.joy2_deadzones = DEADZONE;

    //set joystick scales
    setJoystickScale(&self, 1, JOYPADSCALE);
    setJoystickScale(&self, 2, JOYPADSCALE);

    //get 1st values from joypad
    update(&self);
}

// Joypad functions
void update(Joypad * self){
    //update joystick values
    getJoystickSettings(self.joy_num);

    //update joystick vaules
    switch(self.joy_num){
        case 1:
            setJoyValue(&self, 1, joystick.joy1_x1, joystick.joy1_y1);
            setJoyValue(&self, 2, joystick.joy1_x2, joystick.joy1_y2);
            break;
        case 2:
            setJoyValue(&self, 1, joystick.joy2_x1, joystick.joy2_y1);
            setJoyValue(&self, 2, joystick.joy2_x2, joystick.joy2_y2);
            break;
        case *:
            //Currently, teleop only suports 2 joysticks
            self.joy1_x = 0;
            self.joy1_y = 0;
            self.joy2_x = 0;
            self.joy2_y = 0;
            break;
    }
}

bool isButtonPressed(Joypad * self, int button){
    switch(self.joy_num){
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

void setDeadzone(Joypad * self, int joystick, int deadzone){
    switch(joystick){
        case 1:
            self.joy1_deadzone = deadzone;
            break;
        case 2:
            self.joy2_deadzone = deadzone;
            break;
        case *:
            break;
    }
}

void setJoystickScale(Joypad * self, double scale){
    setJoystickScale(&self, 1, scale);
    setJoystickScale(&self, 2, scale);
}

void setJoystickScale(Joypad * self, int joystick, double scale){
    setJoystickScale(&self, joystick, scale, scale);
}

void setJoystickScale(Joypad * self, int joystick, double scale_x, double scale_y){
    //Adjustment to fix range(-128 -> 127) to range(-100 -> 100)
    const double range_scale = 100/127;

    switch(joystick){
        case 1:
            self.joy1_scale_x = scale_x * range_scale;
            self.joy1_scale_y = scale_y * range_scale;
            break;
        case 2:
            self.joy2_scale_x = scale_x * range_scale;
            self.joy2_scale_y = scale_y * range_scale;
            break;
        case *:
            break;
    }
}

void setJoyValue(Joypad * self, int joystick, int raw_x, int raw_y){
    switch(joystick){
        case 1:
            self.joy_x = scaleJoystick(raw_x, self.joy1_scale_x, self.joy1_deadzone);
            self.joy_y = scaleJoystick(raw_y, self.joy1_scale_y, self.joy1_deadzone);
            break;
        case 2:
            self.joy_x = scaleJoystick(raw_x, self.joy2_scale_x, self.joy2_deadzone);
            self.joy_y = scaleJoystick(raw_y, self.joy2_scale_y, self.joy2_deadzone);
            break;
    }
}

int scaleJoystick(int joy_raw, double scale, int deadzone){
    if( abs(joy_raw) > deadzone ){
        return (int)((double)joy_raw * scale);
    }
    else{
        //Return zero if joystick is within the deadzone
        return 0;
    }
}
