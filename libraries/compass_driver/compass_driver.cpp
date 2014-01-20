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

int readAngle();    //read the current horizontal angle in degrees

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
    
    original_direction_angle = compass_get_angle();
    
    
}

/**
    Function: compass_get_angle
    Descripton: get the angle compared with its original direction
 */
int compass_get_angle(){
    int current_angle = 0;
    //sampling the original direction angle
    for( int i = 0; i < SAMPLE_SIZE; i++){
        current_angle += readAngle();
        delay( 250);
    }
    current_angle = current_angle/SAMPLE_SIZE;
    
    return current_angle;
}

/**
    Function: readAngle
    Description: connect with HMC5883 and get x,y,z data and calculate the horizontal angle in degrees
 */
int readAngle(){
    int x,y,z; //triple axis data
    float de_x,de_y,de_z;
    float heading,headingDegrees;  //the horizontal heading

    //Tell the HMC5883L where to begin reading data
    Wire.beginTransmission(address);
    Wire.write(0x03); //select register 3, X MSB register
    Wire.endTransmission();
    
    
    //Read data from each axis, 2 registers per axis
    Wire.requestFrom(address, 6);
    while(Wire.available() < 6);
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
    
    //convert x,y,z into radians
    de_x = x / 180.0 * PI;
    de_y = y / 180.0 * PI;
    de_z = z / 180.0 * PI;
    
    //calcuate teh heading
    float heading = atan2(de_y, de_x);
    
    //calibrate the heading by adding declination angle
    heading += DECLINATION_ANGLE;
    
    //wrap around the heading
    if(heading < 0)
        heading += 2*PI;
    
    if(heading > 2*PI)
        heading -= 2*PI;
    
    //convert heading into degrees
    headingDegrees = heading * 180.0/PI;
    
    //correcting the angle issue
    
    //map 0 - 90 degree
    if (headingDegrees >= 0 && headingDegrees < 122)
    {
        headingDegrees = map(headingDegrees,0,122,0,90);
    }
    //map 90 - 180 degree
    else if (headingDegrees >= 122 && headingDegrees < 222)
    {
        headingDegrees =  map(headingDegrees,122,222,90,180);
    }
    //map 180 - 270 degree
    else if( headingDegrees >= 222 && headingDegrees < 282){
        headingDegrees =  map(headingDegrees,222,282,180,270);
    }
    //map 270 - 360 degree
    else{
        headingDegrees = map(headingDegrees,282,360,270,360);
    }
    
    
    return headingDegrees;
}

