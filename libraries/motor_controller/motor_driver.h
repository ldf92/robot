/*
 Header for motor controller driver
 Requirements:
    1. the main file should include SoftwareSerial.h
 
 Pin layout:
    pin 2 -> TXPIN
    pin 3 -> RXPIN
 **/
#ifndef motor_driver_h
#define motor_driver_h

#include "Arduino.h"
#include <SoftwareSerial.h>
// Define pins you're using for serial communication
// Do not use pins 0 or 1 as they are reserved for
// standard I/O and programming
#define MOTOR_TXPIN 2
#define MOTOR_RXPIN 3


/**
    Function: motor_init
    Description: setup the connectin bewtween the motor controller and cpu
 */
void motor_init();

/**
    Function: motor_move_forward
    Description: keep moving forward at specific speed range from 0 to 127.
                 NOTIC: do not set the speed below 90, otherwise the current is very high
 */
void motor_move_forward(int speed);

/**
    Function: motor_move_backward
    Description: keep moving backward at specific speed range from 0 to 127.
                 NOTIC: do not set the speed below 90, otherwise the current is very high
 */
void motor_move_backward(int speed);

/**
    Function: motor_turn_right
    Description: the right motor will move backward while the left motor will move forward at specific speed
 */
void motor_turn_right(int speed);

/**
 Function: motor_turn_left
 Description: the left motor will move backward while the right motor will move forward at specific speed
 */
void motor_turn_left(int speed);

/**
    Function: motor_stop_moving
    Description: set the speed to ZERO
 */
void motor_stop_moving(int speed);


/**
    Function: motor_set_speed
    Descripton: set the left and right motor speed
 */
void motor_set_speed(int left_motor_speed,bool left_forward, int right_motor_speed, bool right_forward);


#endif
