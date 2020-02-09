#include "usart.h"

unsigned short readserial(){
    unsigned short b8=((UCSR0B&(1<<RXB80))<<7);
    return b8|UDR0;
}

char isbyteavaiable(){
    return (UCSR0A&0B10000000)>>RXC0;
}

char issended(){
    return (UCSR0A&0B01000000)>>TXC0;
}

char getusartstatus(char status){
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

void onemptybuffer(char enableinterrupt){
    if(enableinterrupt){
        UCSR0B|=(1<<UDRIE0);
        SREG|=0B1000000;
    }else{
        UCSR0B&=~(1<<UDRIE0);
    }
}

void writeserial(unsigned short data){
    UDR0=data;
    unsigned char bit=(data>>8);
    if(bit)UCSR0B|=(1<<TXB80);
    else UCSR0B&=~(1<<TXB80);
}

void usartmode(char mode){
    switch (mode){
        case MODE_ASYNC:
            UCSR0C&=~((1<<UMSEL01)|(1<<UMSEL00));
            return;
        case MODE_SYNC:
            UCSR0C&=~(1<<UMSEL01);
            UCSR0C|=(1<<UMSEL00);
            return;
        case MODE_MASTER_SPI:
            UCSR0C|=((1<<UMSEL01)|(1<<UMSEL00));
            return;
        default: return;
    }
}

void paritymode(char mode){
    switch (mode){
        case PARITY_DISABLE:
            UCSR0C&=~((1<<UPM01)|(1<<UPM00));
            return;
        case PARITY_PAIR:
            UCSR0C&=~(1<<UPM00);
            UCSR0C|=(1<<UPM01);
            return;
        case PARITY_ODD:
            UCSR0C|=((1<<UPM01)|(1<<UPM00));
            return;
        default: return;
    }
}

void use2stopbit(char use){
    UCSR0C=(use?UCSR0C|(1<<USBS0):UCSR0C&~(1<<USBS0));
}

void dimensionofchar(char dim){
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

void clockpolarity(char polarity){
    if(polarity)UCSR0C|=(1<<UCPOL0);
    else UCSR0C&=~(1<<UCPOL0);
}

void setbaudrate(char bps,char speedx2){
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

void setserial(usart *config){
    usartmode(config->mode);
    paritymode(config->parity);
    use2stopbit(config->stopbit);
    dimensionofchar(config->dimension);
    setbaudrate(config->baudrate,config->doublespeed);
    setrx0(config->rx[0],config->rx[1]);
    settx0(config->tx[0],config->tx[1]);
}
