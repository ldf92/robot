/**
 Header for HMC5883L ditigal compass driver
 Requirements:
    1. the main file should include wire.h
 Pin layout:
    I2C:
        ANL 4 -> SDL
        ANL 5 -> SCL
*/

#ifndef compass_driver_h
#define compass_driver_h

#include "Arduino.h"
#include <wire.h>

//Define pins you're using for I2C communication
#define SDLPIN 4
#define SCLPIN 5

#define SAMPLE_SIZE 5
#define COMPASS_ADDR 0x1E //0011110b, I2C 7bit address of HMC5883
#define DECLINATION_ANGLE -10.0/180.0*PI    //-10.0 for state college, convert to radians
/**
    Function: compass_init
    Description: setup the connection between the compass and cpu
 */
void compass_init();

/**
    Function: compass_get_angle
    Descripton: get the angle compared with its original direction
 */
int compass_get_angle();





#endif