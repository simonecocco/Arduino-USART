#include "usart.h"
//Serial0

void setrx0(char enablepin,char enableinterrupt){
    if(enableinterrupt){
        UCSR0B|=(1<<RXCIE0);
        SREG|=0B1000000;
    }else{
        UCSR0B&=~(1<<RXCIE0);
    }
    if(enablepin) UCSR0B|=(1<<RXEN0);
    else UCSR0B&=~(1<<RXEN0);
}

void settx0(char enablepin,char enableinterrupt){
    if(enableinterrupt){
        UCSR0B|=(1<<TXCIE0);
        SREG|=0B1000000;
    }else{
        UCSR0B&=~(1<<TXCIE0);
    }
    if(enablepin) UCSR0B|=(1<<TXEN0);
    else UCSR0B&=~(1<<TXEN0);
}

void onemptybuffer0(char enableinterrupt){
    if(enableinterrupt){
        UCSR0B|=(1<<UDRIE0);
        SREG|=0B1000000;
    }else{
        UCSR0B&=~(1<<UDRIE0);
    }
}

void writeserial0(unsigned short data){
    UDR0=data;
    unsigned char bit=(data>>8);
    if(bit)UCSR0B|=(1<<TXB80);
    else UCSR0B&=~(1<<TXB80);
}

void clockpolarity0(char polarity){
    if(polarity)UCSR0C|=(1<<UCPOL0);
    else UCSR0C&=~(1<<UCPOL0);
}

void setserial0(usart *config){
    usartmode0(config->mode);
    paritymode0(config->parity);
    use2stopbit0(config->stopbit);
    dimensionofchar0(config->dimension);
    setbaudrate0(config->baudrate,config->doublespeed);
    clockpolarity0(config->polarity);
    setrx0(config->rx[0],config->rx[1]);
    settx0(config->tx[0],config->tx[1]);
}