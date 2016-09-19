/*
CODE: CAN COMMS HEADER 
AUTHOR: John Mai, Thomas Paynter and Jack Evans
COMPANY:CURTIN MOTORSPORT TEAM
LAST EDITED: 30/11/15
TECH DETAILS:CAN communications over ID's 1 and 2 at a baud rate of 1Mbps.
*/

/*
HEADER DESCRIPTION:
 * This header file contains the CAN communication method declarations.
*/

void CAN_Initialise();

void CAN_Transmit(unsigned char data[8], unsigned int SID, unsigned char DLC);

void CAN_Receive(unsigned char ID);

