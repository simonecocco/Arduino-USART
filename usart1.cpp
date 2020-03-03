#include "usart.h"
//Serial1

void setrx1(char enablepin,char enableinterrupt){
    if(enableinterrupt){
        UCSR1B|=(1<<RXCIE1);
        SREG|=0B1000000;
    }else{
        UCSR1B&=~(1<<RXCIE1);
    }
    if(enablepin) UCSR1B|=(1<<RXEN1);
    else UCSR1B&=~(1<<RXEN1);
}

void settx1(char enablepin,char enableinterrupt){
    if(enableinterrupt){
        UCSR1B|=(1<<TXCIE1);
        SREG|=0B1000000;
    }else{
        UCSR1B&=~(1<<TXCIE1);
    }
    if(enablepin) UCSR1B|=(1<<TXEN1);
    else UCSR1B&=~(1<<TXEN1);
}

void onemptybuffer1(char enableinterrupt){
    if(enableinterrupt){
        UCSR1B|=(1<<UDRIE1);
        SREG|=0B1000000;
    }else{
        UCSR1B&=~(1<<UDRIE1);
    }
}

void writeserial1(unsigned short data){
    UDR1=data;
    unsigned char bit=(data>>8);
    if(bit)UCSR1B|=(1<<TXB81);
    else UCSR1B&=~(1<<TXB81);
}

void clockpolarity1(char polarity){
    if(polarity)UCSR1C|=(1<<UCPOL1);
    else UCSR1C&=~(1<<UCPOL1);
}

void setserial1(usart *config){
    usartmode1(config->mode);
    paritymode1(config->parity);
    use2stopbit1(config->stopbit);
    dimensionofchar1(config->dimension);
    setbaudrate1(config->baudrate,config->doublespeed);
    clockpolarity1(config->polarity);
    setrx1(config->rx[0],config->rx[1]);
    settx1(config->tx[0],config->tx[1]);
}
