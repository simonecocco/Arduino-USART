#include "usart.h"
//Serial0

char isbyteavaiable0(){
    return (UCSR0A&0B10000000)>>RXC0;
}

char issended0(){
    return (UCSR0A&0B01000000)>>TXC0;
}

char getusartstatus0(char status){
    switch(status){
        case STATUS_BUFFER:
            return (UCSR0A&0B00100000)>>UDRE0;
        case STATUS_FRAMEERROR:
            return (UCSR0A&0B00010000)>>FE0;
        case STATUS_LOSTBYTE:
            return (UCSR0A&0B00001000)>>DOR0;
        case STATUS_PARITYERROR:
            return (UCSR0A&0B00000100)>>UPE0;
        case STATUS_DOUBLESPEED:
            return (UCSR0A&0B00000010)>>U2X0;
        case STATUS_MULTIPROCESSOR:
            return (UCSR0A&0B00000001)>>MPCM0;
        default: return (char)0;
    }
}

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

void dimensionofchar0(char dim){
    switch(dim){
        case DIM_5b:
            UCSR0B&=~(1<<UCSZ02);
            UCSR0C&=~(1<<UCSZ01);
            UCSR0C&=~(1<<UCSZ00);
            return;
        case DIM_6b:
            UCSR0B&=~(1<<UCSZ02);
            UCSR0C&=~(1<<UCSZ01);
            UCSR0C|=(1<<UCSZ00);
            return;
        case DIM_7b:
            UCSR0B&=~(1<<UCSZ02);
            UCSR0C|=(1<<UCSZ01);
            UCSR0C&=~(1<<UCSZ00);
            return;
        case DIM_8b:
            UCSR0B&=~(1<<UCSZ02);
            UCSR0C|=(1<<UCSZ01);
            UCSR0C|=(1<<UCSZ00);
            return;
        case DIM_9b:
            UCSR0B|=(1<<UCSZ02);
            UCSR0C|=(1<<UCSZ01);
            UCSR0C|=(1<<UCSZ00);
            return;
        default: return;
    }
}

void clockpolarity0(char polarity){
    if(polarity)UCSR0C|=(1<<UCPOL0);
    else UCSR0C&=~(1<<UCPOL0);
}

void setbaudrate0(char bps,char speedx2){
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
    UBRR0H=code>>8;
    UBRR0L=code;
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