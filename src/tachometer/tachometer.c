/*
CODE: TACHOMETER LIBRARY
AUTHOR: John Mai, Thomas Paynter and Jack Evans
COMPANY: CURTIN MOTORSPORT TEAM
LAST EDITED: 30/11/15
TECH DETAILS: Communicating to an TLC59116 LED driver to control the Dashboard's
 * tachometer over I2C.            
*/

/*
LIBRARY DESCRIPTION:
 *This library contains the functions to display the images, both numerical and 
 * non-numerical, onto the 8x8 LED matrix. Typically N, 1, 2, 3, 4, 5, 6 and CMT. 
*/
#include <xc.h>
#include <pic18f46k80.h> 
#include "I2C.h"
#include "tachometer.h"

void TLC_Init(char address)
{
    //Init the TLC 
I2C_Start_and_Address(address); //Select chip 1
I2C_Data(0b10000000); // MODE1 Address
I2C_Data(0b10000000); //MODE1
I2C_Data(0b00000000); //MODE2 - Enable error status flag - group control is dimming - Outputs change on stop
I2C_Data(225); //PWM0
I2C_Data(225); //PWM1
I2C_Data(225); //PWM2
I2C_Data(225); //PWM3
I2C_Data(225); //PWM4
I2C_Data(225); //PWM5
I2C_Data(225); //PWM6
I2C_Data(225); //PWM7
I2C_Data(225); //PWM8
I2C_Data(225); //PWM9
I2C_Data(225); //PWM10
I2C_Data(225); //PWM11
I2C_Data(225); //PWM12
I2C_Data(225); //PWM13
I2C_Data(225); //PWM14
I2C_Data(225); //PWM15

I2C_Data(255); //GRPPWM  
I2C_Data(0); //GRPFREQ  
I2C_Data(255); // LEDOUT0 Data
I2C_Data(255); // LEDOUT1 Data
I2C_Data(255); // LEDOUT2 Data
I2C_Data(255); // LEDOUT3 Data

I2C_Data(0b11010010); // ?
I2C_Data(0b11010100); // ?
I2C_Data(0b11011000); // ?
I2C_Data(0b11010000); // ?

I2C_Data(0b11000000); // IREF
I2C_Data(0b10000000); //MODE1 set to normal osc again, turning things on!!
I2C_Stop();
}

void TLC_Data(char address, char led0, char led1, char led2, char led3)
{
    SSPSTAT=0b10000000;
    SSPCON1=0b00101000;
    I2C_Start_and_Address(address); //Select chip
    I2C_Data(0b10010100); // LEDOUT0 Address
    I2C_Data(led0); // LEDOUT0 Data
    I2C_Data(led1); // LEDOUT1 Data
    I2C_Data(led2); // LEDOUT2 Data
    I2C_Data(led3); // LEDOUT3 Data
    I2C_Stop();
}

void TLC_Brightness(char address, char brightness)
{
    I2C_Start_and_Address(address); //Select chip 1
    I2C_Data(0x12); // GRPPWM Address
    I2C_Data(brightness); //MODE1
    I2C_Stop();
}
