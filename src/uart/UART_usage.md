How To Use UART
===============

For EUSART1 to be used the following must occur:
- SPEN(RCSTA1<7>)must be set (=1)
- For Asynchronous and Synchronous Master modes, TRISx<x> must be cleared (= 0)
- For Synchronous Slavemode, TRISx<x> must be set (= 1)

Asynchronous UART
-----------------

Using EUSART1 as an example.


### Initialisation ###

```c
RCSTA1bits.SPEN = 1;
TRISBITS.TRISC6 = 0;
TRISbits.TRISC7 = 0;
```

![TXTAx](https://github.com/Curtin-Motorsport-Team/electrical-libraries/raw/master/src/uart/TXTAx.png)

8 Bit transmission mode.
Transmit disabled, for now
Asynchronous mode
*high speed or low speed

```c
TXTA1 = 0b00000000;
```

![RCSTAx](https://github.com/Curtin-Motorsport-Team/electrical-libraries/raw/master/src/uart/RCSTAx.png)

Enable serial port.
8 Bit reception
Enable reciever

```c
RCSTA1 = 0b10010000;
```

![BAUDCONx](https://github.com/Curtin-Motorsport-Team/electrical-libraries/raw/master/src/uart/BAUDCONx.png)
Non-inverted logic levels
Lines idle high.
16-bit baud rate
```c
BAUDCON1 = 0b00001000;
```

Setting the baud rate for the asynchronous operation of the chip is done with the SPBRGHx:SPBRGx register pair, such that:

![Baud Table](https://github.com/Curtin-Motorsport-Team/electrical-libraries/raw/master/src/uart/baudTable.png)

As a result for a 250 kbps communication, at 16 MHz, with the 16-bit timer. The value of the SPBRGHx:SPBRGx pair must be 3.

```c
SPBRGH1 = 0;
SPBRG1 = 3;
```


Transmission
------------

Enable transmission, and load data.

```c
TXTA1bits.TXEN = 1;
TXREG1 = data; \\This automatically initiates transmission
```

Optionally wait until the byte is sent

```c
while(TXTA1bits.TRMT == 0);
```


Reception
---------

Poll RC1IF untill its set, then read in the data.

```c

if(RC1IF == 1) {
  data = RCREG1;
}
```
