#include "usart.h"
//Serial1

char isbyteavaiable1(){
    return (UCSR1A&0B10000000)>>RXC1;
}

char issended1(){
    return (UCSR1A&0B01000000)>>TXC1;
}

char getusartstatus1(char status){
    switch(status){
        case STATUS_BUFFER:
            return (UCSR1A&0B00100000)>>UDRE1;
        case STATUS_FRAMEERROR:
            return (UCSR1A&0B00010000)>>FE1;
        case STATUS_LOSTBYTE:
            return (UCSR1A&0B00001000)>>DOR1;
        case STATUS_PARITYERROR:
            return (UCSR1A&0B00000100)>>UPE1;
        case STATUS_DOUBLESPEED:
            return (UCSR1A&0B00000010)>>U2X1;
        case STATUS_MULTIPROCESSOR:
            return (UCSR1A&0B00000001)>>MPCM1;
        default: return (char)0;
    }
}

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

void dimensionofchar1(char dim){
    switch(dim){
        case DIM_5b:
            UCSR1B&=~(1<<UCSZ12);
            UCSR1C&=~(1<<UCSZ11);
            UCSR1C&=~(1<<UCSZ10);
            return;
        case DIM_6b:
            UCSR1B&=~(1<<UCSZ12);
            UCSR1C&=~(1<<UCSZ11);
            UCSR1C|=(1<<UCSZ10);
            return;
        case DIM_7b:
            UCSR1B&=~(1<<UCSZ12);
            UCSR1C|=(1<<UCSZ11);
            UCSR1C&=~(1<<UCSZ10);
            return;
        case DIM_8b:
            UCSR1B&=~(1<<UCSZ12);
            UCSR1C|=(1<<UCSZ11);
            UCSR1C|=(1<<UCSZ10);
            return;
        case DIM_9b:
            UCSR1B|=(1<<UCSZ12);
            UCSR1C|=(1<<UCSZ11);
            UCSR1C|=(1<<UCSZ10);
            return;
        default: return;
    }
}

void clockpolarity1(char polarity){
    if(polarity)UCSR1C|=(1<<UCPOL1);
    else UCSR1C&=~(1<<UCPOL1);
}

void setbaudrate1(char bps,char speedx2){
    unsigned short code=0;
    switch(bps){
        case BPS_2400:
            code=speedx2?832:416;
            break;
        case BPS_4800:
            code=speedx2?416:207;
            break;
        case BPS_9600:
            code=speedx2?207:103;
            break;
        case BPS_14400:
            code=speedx2?138:68;
            break;
        case BPS_19200:
            code=speedx2?103:51;
            break;
        case BPS_28800:
            code=speedx2?68:34;
            break;
        case BPS_38400:
            code=speedx2?51:25;
            break;
        case BPS_57600:
            code=speedx2?34:16;
            break;
        case BPS_76800:
            code=speedx2?25:12;
            break;
        case BPS_115200:
            code=speedx2?16:8;
            break;
        case BPS_230400:
            code=speedx2?8:3;
            break;
        case BPS_250000:
            code=speedx2?7:3;
            break;
        default: return;
    }
    UBRR1H=code>>8;
    UBRR1L=code;
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
