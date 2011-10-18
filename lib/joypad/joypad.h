/**
 * joypad.h
 * library of fuctions and classes that offers an advanced interface to the
 * Logitec joystick
 **/

#ifndef JOYPAD_H
#define JOYPAD_H

#include "JoystickDriver.c"

// Default deadzone size for joysticks
const int   DEADZONE = 3;
const int   JOYPADDEFALT = 1;
const double   JOYPADSCALE = 1.0;

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
class Joypad {

    /************** Variables **************/
    public int joy1_x;
    public int joy1_y;
    public int joy2_x;
    public int joy2_y;

    //joystick offset
    private int     joy_num;
    
    private double  joy1_scale_x;
    private double  joy1_scale_y;
    private double  joy2_scale_x;
    private double  joy2_scale_y;
    
    //dead zone varables
    private int     joy1_deadzone;
    private int     joy2_deadzone;


    /*************** Constructors **************/
    // Create joystick with default vaule
  public:
    Joypad();

    // Pass in joystick's number
    Joypad(int joy_num);

    /*************** Functions **************/
  public:
    /** Fuction: update
     * Discription: updates values for joystick.
     * IMPORTANT: call functions before an values are to be used
     **/
    void update();
    
    //TODO
    bool isButtonPressed(int button);

    //TODO
    void setDeadzone(int joystick, int deadzone);

    //TODO
    void setJoystickScale(int joystick, double scale);

    //TODO
    void setJoystickScale(int joystick, double scale_x, double scale_y);

  private:
    //TODO
    int setJoyValue(int joystick, int raw_value);
}

#endif //JOYPAD_H
