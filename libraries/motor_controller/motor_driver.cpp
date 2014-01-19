/*
  Implementation for motor controller driver
  pin layout: 
      pin 2 -> TXPIN
      pin 3 -> RXPIN
**/

#include "motor_driver.h"
// Included for serial communication
#include <SoftwareSerial.h>

#define FORWARD_COMMAND 0x01
#define BACKWARD_COMMAND 0X02

// Create an instance of the software serial
// communication object. This represents the
// interface with the TReX Jr device
SoftwareSerial pololu(MOTOR_RXPIN, MOTOR_TXPIN);

/**
 Function: motor_init
 Description: setup the connectin bewtween the motor controller and cpu
 */
void motor_init(){
    // Define the appropriate input/output pins
    pinMode(MOTOR_RXPIN, INPUT);
    pinMode(MOTOR_TXPIN, OUTPUT);
    
    pololu.begin(19200);
}

/**
 Function: motor_set_speed
 Descripton: set the left and right motor speed
 */
void motor_set_speed(int left_motor_speed,bool left_forward, int right_motor_speed, bool right_forward){
    // Send the "set" command based on the motor
    // Note that we do not accelerate to the
    // speed, we just instantly set it
    unsigned char sendByte = 0xD0;
    
    //  protocol
    //  0xD0|motor2|motor1
    //  4bit| 2bit | 2bit
    
    //motor 2 command
    if( left_forward){
        sendByte |= FORWARD_COMMAND * 4;
    }
    else{
        sendByte |= BACKWARD_COMMAND * 4;
    }
    
    //motor 1 command
    if( right_forward){
        sendByte |= FORWARD_COMMAND;
    }
    else{
        sendByte |= BACKWARD_COMMAND;
    }
    
    // Send the set speed command byte
    pololu.write(sendByte);
    
    // Send the left and right speed to ZERO
    pololu.write(right_motor_speed);    //motor 1 speed
    pololu.write(left_motor_speed);    //motor 2 speed
}


/**
 Function: motor_move_forward
 Description: keep moving forward at specific speed range from 0 to 127.
 NOTIC: do not set the speed below 90, otherwise the current is very high
 */
 void motor_move_forward(int speed){
     motor_set_speed(speed, true, speed, true);
     
 }

/**
 Function: motor_move_backward
 Description: keep moving backward at specific speed range from 0 to 127.
 NOTIC: do not set the speed below 90, otherwise the current is very high
 */
void motor_move_backward(int speed){
    motor_set_speed(speed, false, speed, false);
}

/**
 Function: motor_turn_right
 Description: the right motor will move backward while the left motor will move forward at specific speed
 */
void motor_turn_right(int speed){
    motor_set_speed(speed, true, speed, false);
}

/**
 Function: motor_turn_left
 Description: the left motor will move backward while the right motor will move forward at specific speed
 */
void motor_turn_left(int speed){
    motor_set_speed(speed, false, speed, true);

}


/**
 Function: motor_stop_moving
 Description: set the speed to ZERO
 */
void motor_stop_moving(){
    motor_set_speed(0, false, 0, false);
}


