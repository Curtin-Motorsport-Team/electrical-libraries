#include <pic18f46k80.h>
#include <xc.h>
#include "CAN.h"


extern unsigned char data1[8], data2[8];

void CAN_Initialise()
{

    /*CAN needs to be in CONFIG mode to edit the following settings.
    * We do that by editing CANCONbits.REQOP (Bits 7-5).*/
    CANCON = 0b10000000;

    /*To ensure we don't proceed before we have changed to CONFIG mode, we check
    * CANSTATbits.OPMODE and wait for it to change to 0b100*/
    while(!(CANSTATbits.OPMODE == 0b100));

    /* The PIC's CAN module has 3 modes, 2 of which are "CAN" and "ECAN"
    * (see pg 439 of datasheet)
    * We use "CAN" and "ECAN" is a newer version.
    * enhanced legacy mode mode is basically CAN, but a little bit better
    * Here we set the module to mode 1, enhanced legacy.*/
    ECANCON = 0b01000000;

    // Initialize CAN Timing
    //  Setting Baud Rate
    //  125 Kbps @ 16MHz

    //BRGCON1

    BRGCON1bits.SJW = 0b00; // Sync Jump Width is 1 TQ
    BRGCON1bits.BRP = 0; // Baud Rate Prescaler is Tq = 2*(BRP + 1)/Fosc = 0.125 us


    //BRGCON2
    BRGCON2bits.SEG2PHTS = 1; // Makes the SEG2 fully programmable
    BRGCON2bits.SAM = 0; // On reception the bit is sampled once at the intersection of SEG1 and SEG2
    BRGCON2bits.SEG1PH = 0b011; // SEG1 is 4*TQ
    BRGCON2bits.PRSEG = 0b000; // Propogation time is 1*TQ

    //BREGCON3
    BRGCON3bits.WAKDIS = 0; //Enable wakeup from CAN
    BRGCON3bits.WAKFIL = 0; //Disable filters for wakeup
    BRGCON3bits.SEG2PH = 0b001; //SEG2 is 2*TQ

    // Thus the timeline for the CAN bit is:
    //  1           1   4       2   = 8 TQ = 1 MBits/s
    // SyncSeg  PropSeg SEG1    SEG2

    BSEL0 = 0b11111100;                   //1=TX, 0=RX

	/* A bit on Masks and Filters!

	A filter is the be all and end all, it decides to accept the data to the buffer or
	dump it. A filter will be composed of a bit field as long as the ID of the CAN message.

	If the CAN ID matches the filter it is let throgut to the buffer.

	Now the mask is like a wild	card to the filter. If the corresponding mask bit is a
	1 then the filter bit MUST match the corresponding ID bit in order for it
	to be passed. If its a 0 then it is a dont care bit. ie

	Mask = 	0b01101101
	Filter=	0b11011011
	Passes=	0bx10x10x1
	  ie	0b11011011
			0b01011011
			0b11001001 ect

	Think of the mask as a filter bit enable function,  if it is a 0 it disables that filter
	checking ability*/

    /* Initialize Receive Masks
    The first mask is used that accepts all SIDs */
    RXM0SIDH = 0b11111111; // Standard ID MASK all 1s, meaning the filter must match EXACTLY!
    RXM0SIDL = 0b11100000;

    // Enable Filters
    // Only using first three filters
    RXFCON0 = 0b00000111;          //Enable Filters 0,1,2
    RXFCON1 = 0b00000000;          //Disable all others

    // Assign Filters to Masks
    MSEL0 = 0b11110000;                  //Assign Filters 0 to Mask 0, rest to no mask
    MSEL1 = 0b11111111;                  //Assign Filters 4-7 No mask
    MSEL2 = 0b11111111;                  //Assign Filters 8-11 to No mask
    MSEL3 = 0b11111111;                  //Assign Filters 12-15 to No mask

    // Assign Filters to Buffers
    RXFBCON0 = 0b00010000;               //Assign Filter 0 to RXB0, and Filter 1 to RXB1
    RXFBCON1 = 0b11111111;                     //Assign the rest of the buffers with no filter
    RXFBCON2 = 0b11111111;
    RXFBCON3 = 0b11111111;
    RXFBCON4 = 0b11111111;
    RXFBCON5 = 0b11111111;
    RXFBCON6 = 0b11111111;
    RXFBCON7 = 0b11111111;

    // Initialize Receive Filters
    RXF0SIDH = 0b00000000; // Set to ID1
    RXF0SIDL = 0b00100000;

    RXF1SIDH = 0b00000000; // Set to ID2
    RXF1SIDL = 0b01000000;

    /* In this case, we are only passing messages with ID=1 and 2 through.
    The SID has been split between  two registers,
    bits SID<10:3> lie in RXFnSIDH and SID<2:0> are in MSBs of RXFnSIDL.
    Thus the whole SID  is 0000000000100000.*/
    RXB0CON = 0x00;
    RXB1CON = 0x00;
    // Now we can set CAN back to normal mode and this allows it to actually use it.
    CANCON = 0b0000000;

    //Another while loop to check CANSTATbits.OPMODE,
    //and wait for it to change to 0b000 before continuing.
    while(!(CANSTATbits.OPMODE==0b000));

}

void CAN_Transmit(unsigned char data[8], unsigned int SID, unsigned char DLC)
{
   // We've left out the setup for extended ID transmit buffers, not used for sending standard ID messages, so currently not necessary.
    while(TXB0CONbits.TXREQ == 1); //Wait for last message to clear

/* Standard length ID transmit buffers, the actual identifier lies over the
* two registers, bits SID<10:3> lie in TXBnSIDH and SID<2:0> are in MSBs of
* TXBnSIDL. The TXBnSIDLbits.EXIDE, bit 3 bit should be 0 or 1 for
* standard/extended IDs, respectively. The remainder of TXBnSIDL should be
* set as 0 for standard IDs */
TXB0SIDH = (SID >> 3) & 0b11111111;                           //Thus the SID is 00110010 110 = 406
TXB0SIDL = (SID << 5) & 0b11100000;

/*   The TXBnDLCbits.TXRTR (bit 6) is the remote transmission request bit, and
      tells another node of that ID to send data.
      The TXBnDLCbits.DLC (bits 3:0) is an indication of how many bytes are to be sent, it can range from 0 to 8   */

TXB0DLC = DLC;                            //Thus DLC bytes will be sent! (This is the max)

/*  This is where the meat of the CAN it, this is it!!!!!
The TXBnDm register is the actual data you are to be sending over the
network  */
TXB0D0 = data[0];
TXB0D1 = data[1];
TXB0D2 = data[2];
TXB0D3 = data[3];
TXB0D4 = data[4];
TXB0D5 = data[5];
TXB0D6 = data[6];
TXB0D7 = data[7];

/*This bit literally says go for transmit!!*/
TXB0CONbits.TXREQ = 1;                     //Set the buffer to transmit

}

void CAN_Receive(unsigned char ID)
{
    // Checks if there is data in buffer number [buffer].
    // If there is then it copies register RXBn into the array data1[8]


        if ((RXB0CONbits.RXFUL) && (ID == 1) )          // receive buffer 0
            {
            data1[0] = RXB0D0;
            data1[1] = RXB0D1;
            data1[2] = RXB0D2;
            data1[3] = RXB0D3;
            data1[4] = RXB0D4;
            data1[5] = RXB0D5;
            data1[6] = RXB0D6;
            data1[7] = RXB0D7;

            RXB0CONbits.RXFUL = 0;   // Mark the buffer as read, and no longer contains a new message
            PIR5bits.RXB0IF = 0;     // reset receive buffer 0 interrupt flag
            }

        if ((RXB1CONbits.RXFUL) && (ID == 2) )           // receive buffer 1
        {
                data2[0] = RXB1D0;
                data2[1] = RXB1D1;
                data2[2] = RXB1D2;
                data2[3] = RXB1D3;
                data2[4] = RXB1D4;
                data2[5] = RXB1D5;
                data2[6] = RXB1D6;
                data2[7] = RXB1D7;

                RXB1CONbits.RXFUL = 0;   // Mark the buffer as read, and no longer contains a new message
                PIR5bits.RXB1IF = 0;     // reset receive buffer 1 interrupt flag
        }


}
