/*
CODE: TACHOMETER HEADER
AUTHOR: John Mai, Thomas Paynter and Jack Evans
COMPANY:CURTIN MOTORSPORT TEAM
LAST EDITED: 30/11/15
TECH DETAILS: Communicating to an TLC59116 LED driver to control the Dashboard's
 * tachometer over I2C.
*/

/*
HEADER DESCRIPTION:
 * This header file contains the TLC59116 LED driver communication method declarations. 
*/
#include <xc.h>
#include <pic18f46k80.h> 

void TLC_Init(char address);

void TLC_Data(char address, char led0, char led1, char led2, char led3);

void TLC_Brightness(char address, char brightness);

