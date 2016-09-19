#include <pic18f46k80.h>
#include <xc.h>
#include "timer0.h"

void timer0Init(void) {
  /*  T0CON
      7.1 - Enables TMR0
      6.0 - 16 bit mode
      5.0 - Input internal instruction timer
      4.x - Rising/Falling of external increment
      3.0 - Want a prescaller
      <2:0>.100 - 1:32
      */
  T0CON = 0b10000100;

  /*  INTCON
      7.1 - Enables high priority interrupts
      6.1 - Enables low priority interrupts
      5.1 - Enables TMR0 interrupt
      0000 */

  INTCON = 0b11100000;

  //Enable global interrupts

  RCONbits.IPEN = 1;

}
/*Interrupt Example ONLY!!!

// Low priority interrupt
void interrupt low_priority LPISR(void)
{
    ///Timer0
    if(INTCONbits.T0IF && INTCONbits.T0IE) {
        INTCONbits.T0IF = 0;            // Clear the interrupt flag
    }
}

//High priority interrupt
void interrupt HPISR(void)
{
    ///Timer0
    if(INTCONbits.T0IF && INTCONbits.T0IE) {
        INTCONbits.T0IF = 0;            // Clear the interrupt flag
    }
}
*/

/* Accessing Timer registers Always read the low byte first as this triggers
 * an atomic transfer of the timer into the high byteDO THIS FIRST, a read of the low

a = TMR0L;
b = TMR0H;

time = TMR0H * 256 + TMR0L

*/
