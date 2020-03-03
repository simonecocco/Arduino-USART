#include "usart.h"
//Serial3

void setrx3(char enablepin,char enableinterrupt){
    if(enableinterrupt){
        UCSR3B|=(1<<RXCIE3);
        SREG|=0B1000000;
    }else{
        UCSR3B&=~(1<<RXCIE3);
    }
    if(enablepin) UCSR3B|=(1<<RXEN3);
    else UCSR3B&=~(1<<RXEN3);
}

void settx3(char enablepin,char enableinterrupt){
    if(enableinterrupt){
        UCSR3B|=(1<<TXCIE3);
        SREG|=0B1000000;
    }else{
        UCSR3B&=~(1<<TXCIE3);
    }
    if(enablepin) UCSR3B|=(1<<TXEN3);
    else UCSR3B&=~(1<<TXEN3);
}

void onemptybuffer3(char enableinterrupt){
    if(enableinterrupt){
        UCSR3B|=(1<<UDRIE3);
        SREG|=0B1000000;
    }else{
        UCSR3B&=~(1<<UDRIE3);
    }
}

void writeserial3(unsigned short data){
    UDR3=data;
    unsigned char bit=(data>>8);
    if(bit)UCSR3B|=(1<<TXB83);
    else UCSR3B&=~(1<<TXB83);
}

void clockpolarity3(char polarity){
    if(polarity)UCSR3C|=(1<<UCPOL3);
    else UCSR3C&=~(1<<UCPOL3);
}

void setserial3(usart *config){
    usartmode3(config->mode);
    paritymode3(config->parity);
    use2stopbit3(config->stopbit);
    dimensionofchar3(config->dimension);
    setbaudrate3(config->baudrate,config->doublespeed);
    clockpolarity3(config->polarity);
    setrx3(config->rx[0],config->rx[1]);
    settx3(config->tx[0],config->tx[1]);
}
