/*
CODE: GEAR POSITION INDICATOR HEADER
AUTHOR: John Mai, Thomas Paynter and Jack Evans
COMPANY:CURTIN MOTORSPORT TEAM
LAST EDITED: 30/11/15
TECH DETAILS:Using a 8x8 LED matrix to display the gear position of the CMT '15 
 * vehicle. The LED matrix driver is a HT16K33.
*/

/*
HEADER DESCRIPTION:
 * This header file contains the HT16K33 LED driver method declarations.
*/

void gearPos_Init(char address);

void gearPos_Rows(char rowdata);

void gearPos_Show(const char screen[8]);

