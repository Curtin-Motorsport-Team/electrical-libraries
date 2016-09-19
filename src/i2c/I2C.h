/*
CODE: I2C COMMS HEADER 
AUTHOR: John Mai, Thomas Paynter and Jack Evans
COMPANY:CURTIN MOTORSPORT TEAM
LAST EDITED: 30/11/15
TECH DETAILS:Using PIC18F46K80 to communicate over an I2C bus.
*/

/*
HEADER DESCRIPTION:
 * This header file contains the I2C communication method declarations. 
*/

void I2C_Start_and_Address(char address);

void I2C_Data(char data);

void I2C_Stop();