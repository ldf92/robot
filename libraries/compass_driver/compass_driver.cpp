/**
 Implementation for HMC5883L ditigal compass driver
 Requirements:
    1. the main file should include wire.h
 Pin layout:
    I2C:
        ANL 4 -> SDL
        ANL 5 -> SCL
*/

#include "Arduino.h"
#include <wire.h>
//function prototype

int readAngle();    //read the angle from x_axis

int original_direction_angle = 0;

/**
    Function: compass_init
    Description: setup the connection between the compass and cpu
 */
void compass_init(){
    Wire.begin();
    
    //Put the HMC5883 IC into the correct operating mode
    Wire.beginTransmission(COMPASS_ADDR); //open communication with HMC5883
    Wire.write(0x02); //select mode register
    Wire.write(0x00); //continuous measurement mode
    Wire.endTransmission();
    
    //sampling the original direction angle
    for( int i = 0; i < SAMPLE_SIZE; i++){
        
    }
}

/**
    Function: compass_get_angle
    Descripton: get the angle compared with its original direction
 */
int compass_get_angle();

