#include "usart.h"
//Serial3

unsigned short readserial3(){
    unsigned short b8=((UCSR3B&(1<<RXB83))<<7);
    return b8|UDR3;
}

char isbyteavaiable3(){
    return (UCSR3A&0B10000000)>>RXC3;
}

char issended3(){
    return (UCSR3A&0B01000000)>>TXC3;
}

char getusartstatus3(char status){
    switch(status){
        case STATUS_BUFFER:
            return (UCSR3A&0B00100000)>>UDRE3;
        case STATUS_FRAMEERROR:
            return (UCSR3A&0B00010000)>>FE3;
        case STATUS_LOSTBYTE:
            return (UCSR3A&0B00001000)>>DOR3;
        case STATUS_PARITYERROR:
            return (UCSR3A&0B00000100)>>UPE3;
        case STATUS_DOUBLESPEED:
            return (UCSR3A&0B00000010)>>U2X3;
        case STATUS_MULTIPROCESSOR:
            return (UCSR3A&0B00000001)>>MPCM3;
        default: return (char)0;
    }
}

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

void usartmode3(char mode){
    switch (mode){
        case MODE_ASYNC:
            UCSR3C&=~((1<<UMSEL31)|(1<<UMSEL30));
            return;
        case MODE_SYNC:
            UCSR3C&=~(1<<UMSEL31);
            UCSR3C|=(1<<UMSEL30);
            return;
        case MODE_MASTER_SPI:
            UCSR3C|=((1<<UMSEL31)|(1<<UMSEL30));
            return;
        default: return;
    }
}

void paritymode3(char mode){
    switch (mode){
        case PARITY_DISABLE:
            UCSR3C&=~((1<<UPM31)|(1<<UPM30));
            return;
        case PARITY_EVEN:
            UCSR3C&=~(1<<UPM30);
            UCSR3C|=(1<<UPM31);
            return;
        case PARITY_ODD:
            UCSR3C|=((1<<UPM31)|(1<<UPM30));
            return;
        default: return;
    }
}

void use2stopbit3(char use){
    UCSR3C=(use?UCSR3C|(1<<USBS3):UCSR3C&~(1<<USBS3));
}

void dimensionofchar3(char dim){
    switch(dim){
        case DIM_5b:
            UCSR3B&=~(1<<UCSZ32);
            UCSR3C&=~(1<<UCSZ31);
            UCSR3C&=~(1<<UCSZ30);
            return;
        case DIM_6b:
            UCSR3B&=~(1<<UCSZ32);
            UCSR3C&=~(1<<UCSZ31);
            UCSR3C|=(1<<UCSZ30);
            return;
        case DIM_7b:
            UCSR3B&=~(1<<UCSZ32);
            UCSR3C|=(1<<UCSZ31);
            UCSR3C&=~(1<<UCSZ30);
            return;
        case DIM_8b:
            UCSR3B&=~(1<<UCSZ32);
            UCSR3C|=(1<<UCSZ31);
            UCSR3C|=(1<<UCSZ30);
            return;
        case DIM_9b:
            UCSR3B|=(1<<UCSZ32);
            UCSR3C|=(1<<UCSZ31);
            UCSR3C|=(1<<UCSZ30);
            return;
        default: return;
    }
}

void clockpolarity3(char polarity){
    if(polarity)UCSR3C|=(1<<UCPOL3);
    else UCSR3C&=~(1<<UCPOL3);
}

void setbaudrate3(char bps,char speedx2){
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
    UBRR3H=code>>8;
    UBRR3L=code;
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
