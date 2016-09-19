/*
CODE: GEAR POSITION INDICATOR LIBRARY
AUTHOR: John Mai, Thomas Paynter and Jack Evans
COMPANY:CURTIN MOTORSPORT TEAM
LAST EDITED: 30/11/15
TECH DETAILS:Using a 8x8 LED matrix to display the gear position of the CMT '15 
 * vehicle. The LED matrix driver is a HT16K33.
*/

/*
LIBRARY DESCRIPTION:
 * This library contains the functions neccessary to display N, 1, 2, 3, 4, 5, 6
 * CMT and a dick on a mini 8x8 Matrix by Adafruit.
*/
#include <xc.h>
#include <pic18f46k80.h> 
#include "gearPos.h"
#include "I2C.h"

char row=0, j;

void gearPos_Init(char address)
{
//Internal System Clock Enable
    //Send Start
    SSPCON2bits.SEN=1;
    while(SSPCON2bits.SEN);
    //Loading Address
    SSPBUF= address;
    while(SSPSTATbits.BF);
    //Loading Data
    SSPBUF=0b00100001; //0x21 turn on oscillator
    while(SSPSTATbits.BF);
    //Send Stop
    SSPCON2bits.PEN=1;
    while(SSPCON2bits.PEN);

//ROW/INT Set 
    //Send Start
    SSPCON2bits.SEN=1;
    while(SSPCON2bits.SEN);
    //Loading Address
    SSPBUF= address;
    while(SSPSTATbits.BF);
    //Loading Data
    SSPBUF=0b10100000;
    while(SSPSTATbits.BF);
    //Send Stop
    SSPCON2bits.PEN=1;
    while(SSPCON2bits.PEN);

//Dimming Set
      //Send Start
    SSPCON2bits.SEN=1;
    while(SSPCON2bits.SEN);
    //Loading Address
    SSPBUF= address;
    while(SSPSTATbits.BF);
    //Loading Data
    SSPBUF=0b11101111;
    while(SSPSTATbits.BF);
    //Send Stop
    SSPCON2bits.PEN=1;
    while(SSPCON2bits.PEN);  
    
//Blinking Off and Display on!
    //Send Start
    SSPCON2bits.SEN=1;
    while(SSPCON2bits.SEN);
    //Loading Address
    SSPBUF= address;
    while(SSPSTATbits.BF);
    //Loading Data
    SSPBUF=0b10000001;
    while(SSPSTATbits.BF);
    //Send Stop
    SSPCON2bits.PEN=1;
    while(SSPCON2bits.PEN);
            
}

void gearPos_Rows(char rowdata)
{

    SSPBUF=rowdata;
    while(SSPSTATbits.BF);
    SSPBUF=0b00000000;
    while(SSPSTATbits.BF);
}

void gearPos_Show(const char screen[8])
{
char rownumber;

I2C_Start_and_Address(0b11100000);

I2C_Data(0b00000000); //Set to RAM address 1
        
// Send MATRIX Data
for(rownumber = 0; rownumber < 8; rownumber++)
{
 gearPos_Rows(screen[rownumber]);
}

//Send Stop
SSPCON2bits.PEN=1;
while(SSPCON2bits.PEN);
}