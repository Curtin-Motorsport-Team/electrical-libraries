/*
CODE: CODE: I2C COMMS LIBRARY
AUTHOR: John Mai, Thomas Paynter and Jack Evans
COMPANY:CURTIN MOTORSPORT TEAM
LAST EDITED: 30/11/15
TECH DETAILS:Using PIC18F46K80 to communicate over an I2C bus.
*/

/*
LIBRARY DESCRIPTION:
 * This library provides basic the basic methods for I2C communication. 
*/
#include <xc.h>
#include <pic18f46k80.h> 
#include "I2C.h"

void I2C_Start_and_Address(char address)
{
    SSPCON2bits.SEN=1;
    while(SSPCON2bits.SEN);
    SSPBUF= address; //Loading Address
    while(SSPSTATbits.BF);

}

void I2C_Data(char data)
{
    SSPBUF=data; // Load Data
    while(SSPSTATbits.BF);
}

void I2C_Stop()
{
    //Send Stop
    SSPCON2bits.PEN=1;
    while(SSPCON2bits.PEN);
}

