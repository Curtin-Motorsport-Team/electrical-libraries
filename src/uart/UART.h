void uartInitialisation(void);
/* Initialises the EUSART1 buffer to Asynchronous 9600 baud rate, assuming 
 * a 8 MHz Fosc*/

void uartTransmitByte(unsigned char data);
/* Transmits the selected byte. It WILL hang if the buffer is not empty when it 
 * starts*/

unsigned char uartRecieveByte(unsigned char *data);
/* Returns a 0 if there is no data in the buffer, 
 * Returns 1 if there is valid data and then places that in the pointer, 
 * Returns 2 if there is corrupted data and discards it.*/