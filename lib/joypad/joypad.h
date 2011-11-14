/**
 * joypad.h
 * library of fuctions and 'classes' that offers an advanced interface to the
 * Logitec joystick
 **/

#ifndef JOYPAD_H
#define JOYPAD_H

// Default deadzone size for joysticks
const int DEADZONE          = 3;
const int JOYPADDEFALT      = 1;
const double JOYPADSCALE    = 1.0;

//TODO: get real button values
const int BUTTON_A          = 1;
const int BUTTON_B          = 2;
const int BUTTON_X          = 3;
const int BUTTON_Y          = 4;
const int BUTTON_DPAD_UP    = 9;
const int BUTTON_DPAD_DOWN  = 9;
const int BUTTON_DPAD_LEFT  = 9;
const int BUTTON_DPAD_RIGHT = 9;
const int BUTTON_RS1        = 9;
const int BUTTON_RS2        = 9;
const int BUTTON_LS1        = 9;
const int BUTTON_LS2        = 9;

//Joystick class used for collecting i/o from logitec joypad when using tele-op
typedef struct Joypad {
  //public:
    /************** Variables **************/
    int joy1_x;
    int joy1_y;
    int joy2_x;
    int joy2_y;

  //private:
    //joystick offset
    int     joy_num;
    
    double  joy1_scale_x;
    double  joy1_scale_y;
    double  joy2_scale_x;
    double  joy2_scale_y;
    
    //dead zone varables
    int     joy1_deadzone;
    int     joy2_deadzone;
} Joypad

    
    /*************** Constructors **************/

    // Create joystick with default vaule
    void joypad_init(Joypad * self);

    // Pass in joystick's number
    void joypad_init(Joypad * self, int joy_num);


    /*************** Functions **************/

    /** Fuction: update
     * Discription: updates values for joystick.
     * IMPORTANT: call functions before an values are to be used
     **/
    void update(*Joypad self);
    
    //TODO
    bool isButtonPressed(*Joypad self, int button);

    //TODO
    void setDeadzone(*Joypad self, int joystick, int deadzone);

    //TODO
    void setJoystickScale(*Joypad self, int joystick, double scale);

    //TODO
    void setJoystickScale(*Joypad self, int joystick, double scale_x, double scale_y);

    //TODO
    int setJoyValue(*Joypad self, int joystick, int raw_value);


    /***************** Non-class fuctions******************/
    //TODO
    int scaleJoystick(int joy_raw, double scale, int deadzone);

#endif //JOYPAD_H
