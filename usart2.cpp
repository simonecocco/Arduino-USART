#include "usart.h"
//Serial2

unsigned short readserial2(){
    unsigned short b8=((UCSR2B&(1<<RXB82))<<7);
    return b8|UDR2;
}

char isbyteavaiable2(){
    return (UCSR2A&0B10000000)>>RXC2;
}

char issended2(){
    return (UCSR2A&0B01000000)>>TXC2;
}

char getusartstatus2(char status){
    switch(status){
        case STATUS_BUFFER:
            return (UCSR2A&0B00100000)>>UDRE2;
        case STATUS_FRAMEERROR:
            return (UCSR2A&0B00010000)>>FE2;
        case STATUS_LOSTBYTE:
            return (UCSR2A&0B00001000)>>DOR2;
        case STATUS_PARITYERROR:
            return (UCSR2A&0B00000100)>>UPE2;
        case STATUS_DOUBLESPEED:
            return (UCSR2A&0B00000010)>>U2X2;
        case STATUS_MULTIPROCESSOR:
            return (UCSR2A&0B00000001)>>MPCM2;
        default: return (char)0;
    }
}

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

void usartmode2(char mode){
    switch (mode){
        case MODE_ASYNC:
            UCSR2C&=~((1<<UMSEL21)|(1<<UMSEL20));
            return;
        case MODE_SYNC:
            UCSR2C&=~(1<<UMSEL21);
            UCSR2C|=(1<<UMSEL20);
            return;
        case MODE_MASTER_SPI:
            UCSR2C|=((1<<UMSEL21)|(1<<UMSEL20));
            return;
        default: return;
    }
}

void paritymode2(char mode){
    switch (mode){
        case PARITY_DISABLE:
            UCSR2C&=~((1<<UPM21)|(1<<UPM20));
            return;
        case PARITY_EVEN:
            UCSR2C&=~(1<<UPM20);
            UCSR2C|=(1<<UPM21);
            return;
        case PARITY_ODD:
            UCSR2C|=((1<<UPM21)|(1<<UPM20));
            return;
        default: return;
    }
}

void use2stopbit2(char use){
    UCSR2C=(use?UCSR2C|(1<<USBS2):UCSR2C&~(1<<USBS2));
}

void dimensionofchar2(char dim){
    switch(dim){
        case DIM_5b:
            UCSR2B&=~(1<<UCSZ22);
            UCSR2C&=~(1<<UCSZ21);
            UCSR2C&=~(1<<UCSZ20);
            return;
        case DIM_6b:
            UCSR2B&=~(1<<UCSZ22);
            UCSR2C&=~(1<<UCSZ21);
            UCSR2C|=(1<<UCSZ20);
            return;
        case DIM_7b:
            UCSR2B&=~(1<<UCSZ22);
            UCSR2C|=(1<<UCSZ21);
            UCSR2C&=~(1<<UCSZ20);
            return;
        case DIM_8b:
            UCSR2B&=~(1<<UCSZ22);
            UCSR2C|=(1<<UCSZ21);
            UCSR2C|=(1<<UCSZ20);
            return;
        case DIM_9b:
            UCSR2B|=(1<<UCSZ22);
            UCSR2C|=(1<<UCSZ21);
            UCSR2C|=(1<<UCSZ20);
            return;
        default: return;
    }
}

void clockpolarity2(char polarity){
    if(polarity)UCSR2C|=(1<<UCPOL2);
    else UCSR2C&=~(1<<UCPOL2);
}

void setbaudrate2(char bps,char speedx2){
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
    UBRR2H=code>>8;
    UBRR2L=code;
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
