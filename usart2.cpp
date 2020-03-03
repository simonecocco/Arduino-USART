#include "usart.h"
//Serial2

void setrx2(char enablepin,char enableinterrupt){
    if(enableinterrupt){
        UCSR2B|=(1<<RXCIE2);
        SREG|=0B1000000;
    }else{
        UCSR2B&=~(1<<RXCIE2);
    }
    if(enablepin) UCSR2B|=(1<<RXEN2);
    else UCSR2B&=~(1<<RXEN2);
}

void settx2(char enablepin,char enableinterrupt){
    if(enableinterrupt){
        UCSR2B|=(1<<TXCIE2);
        SREG|=0B1000000;
    }else{
        UCSR2B&=~(1<<TXCIE2);
    }
    if(enablepin) UCSR2B|=(1<<TXEN2);
    else UCSR2B&=~(1<<TXEN2);
}

void onemptybuffer2(char enableinterrupt){
    if(enableinterrupt){
        UCSR2B|=(1<<UDRIE2);
        SREG|=0B1000000;
    }else{
        UCSR2B&=~(1<<UDRIE2);
    }
}

void writeserial2(unsigned short data){
    UDR2=data;
    unsigned char bit=(data>>8);
    if(bit)UCSR2B|=(1<<TXB82);
    else UCSR2B&=~(1<<TXB82);
}

void clockpolarity2(char polarity){
    if(polarity)UCSR2C|=(1<<UCPOL2);
    else UCSR2C&=~(1<<UCPOL2);
}

void setserial2(usart *config){
    usartmode2(config->mode);
    paritymode2(config->parity);
    use2stopbit2(config->stopbit);
    dimensionofchar2(config->dimension);
    setbaudrate2(config->baudrate,config->doublespeed);
    clockpolarity2(config->polarity);
    setrx2(config->rx[0],config->rx[1]);
    settx2(config->tx[0],config->tx[1]);
}
