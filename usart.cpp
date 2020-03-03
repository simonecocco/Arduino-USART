#include "usart.h"

/*
#ifndef def_serial
#define def_serial 0
#endif

switch (portn){
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    default: //3

}
 */
unsigned short read(){
#ifndef def_serial
#define def_serial 0
#endif
    return read(def_serial);
}
unsigned short read(char portn){
    unsigned short b8;
    switch (portn){
        case 0:
            b8=((UCSR0B&(1<<RXB80))<<7);
            return b8|UDR0;
        case 1:
            b8=((UCSR1B&(1<<RXB81))<<7);
            return b8|UDR1;
        case 2:
            b8=((UCSR2B&(1<<RXB82))<<7);
            return b8|UDR2;
        default: //3
            b8=((UCSR3B&(1<<RXB83))<<7);
            return b8|UDR3;
    }
}

unsigned short readif(char condiction){
#ifndef def_serial
#define def_serial 0
#endif
    return readif(condiction,def_serial);
}
unsigned short readif(char condiction,char portn){
    return condiction?read(portn):0;
}

userstat status(){
#ifndef def_serial
#define def_serial 0
#endif
    return status(def_serial);
}
usartstat status(char portn){
    usartstat param;
    switch (portn){
        case 0:
            param=(usartstat){
                    .bufferstat=(UCSR0A&0B00100000)>>UDRE0,
                    .frameerror=(UCSR0A&0B00010000)>>FE0,
                    .bytelost=(UCSR0A&0B00001000)>>DOR0,
                    .parityerror=(UCSR0A&0B00000100)>>UPE0,
                    .dataavaiable=(UCSR0A&0B10000000)>>RXC0,
                    .sended=(UCSR0A&0B01000000)>>TXC0
            };
            break;
        case 1:
            param=(usartstat){
                    .bufferstat=(UCSR1A&0B00100000)>>UDRE1,
                    .frameerror=(UCSR1A&0B00010000)>>FE1,
                    .bytelost=(UCSR1A&0B00001000)>>DOR1,
                    .parityerror=(UCSR1A&0B00000100)>>UPE1,
                    .dataavaiable=(UCSR1A&0B10000000)>>RXC1,
                    .sended=(UCSR1A&0B01000000)>>TXC1
            };
            break;
        case 2:
            param=(usartstat){
                    .bufferstat=(UCSR2A&0B00100000)>>UDRE2,
                    .frameerror=(UCSR2A&0B00010000)>>FE2,
                    .bytelost=(UCSR2A&0B00001000)>>DOR2,
                    .parityerror=(UCSR2A&0B00000100)>>UPE2,
                    .dataavaiable=(UCSR2A&0B10000000)>>RXC2,
                    .sended=(UCSR2A&0B01000000)>>TXC2
            };
            break;
        default: //3
            param=(usartstat){
                    .bufferstat=(UCSR3A&0B00100000)>>UDRE3,
                    .frameerror=(UCSR3A&0B00010000)>>FE3,
                    .bytelost=(UCSR3A&0B00001000)>>DOR3,
                    .parityerror=(UCSR3A&0B00000100)>>UPE3,
                    .dataavaiable=(UCSR3A&0B10000000)>>RXC3,
                    .sended=(UCSR3A&0B01000000)>>TXC3
            };
    }
    return param;
}

void speed(char bps){
#ifndef def_serial
#define def_serial 0
#endif
    speed(def_serial,bps,False);
}
void speed(char portn,char bps,char speedx2){
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
    switch (portn){
        case 0:
            UBRR0H=code>>8;
            UBRR0L=code;
            break;
        case 1:
            UBRR1H=code>>8;
            UBRR1L=code;
            break;
        case 2:
            UBRR2H=code>>8;
            UBRR2L=code;
            break;
        default: //3
            UBRR3H=code>>8;
            UBRR3L=code;
    }
}

void wordlen(char dim){
#ifndef def_serial
#define def_serial 0
#endif
    wordlen(def_serial,dim);
}
void wordlen(char portn,char dim){
    switch (portn){
        case 0:
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
            }
            break;
        case 1:
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
            }
            break;
        case 2:
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
            }
            break;
        default: //3
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
            }
    }
}

void setstopmode(char mode){
#ifndef def_serial
#define def_serial 0
#endif
    setstopmode(def_serial,mode);
}
void setstopmode(char portn,char mode){
    switch (portn){
        case 0:
            UCSR0C=(mode?UCSR0C|(1<<USBS0):UCSR0C&~(1<<USBS0));
            break;
        case 1:
            UCSR1C=(mode?UCSR1C|(1<<USBS1):UCSR1C&~(1<<USBS1));
            break;
        case 2:
            UCSR2C=(mode?UCSR2C|(1<<USBS2):UCSR2C&~(1<<USBS2));
            break;
        default: //3
            UCSR3C=(mode?UCSR3C|(1<<USBS3):UCSR3C&~(1<<USBS3));
    }
}

void setparity(char mode){
#ifndef def_serial
#define def_serial 0
#endif
    setparity(def_serial,mode);
}
void setparity(char portn,char mode){
    switch (mode){
        case PARITY_EVEN:
            switch (portn){
                case 0:
                    UCSR0C&=~(1<<UPM00);
                    UCSR0C|=(1<<UPM01);
                    break;
                case 1:
                    UCSR1C&=~(1<<UPM10);
                    UCSR1C|=(1<<UPM11);
                    break;
                case 2:
                    UCSR2C&=~(1<<UPM20);
                    UCSR2C|=(1<<UPM21);
                    break;
                default: //3
                    UCSR3C&=~(1<<UPM30);
                    UCSR3C|=(1<<UPM31);
            }
            break;
        case PARITY_ODD:
            switch (portn){
                case 0:
                    UCSR0C|=((1<<UPM01)|(1<<UPM00));
                    break;
                case 1:
                    UCSR1C|=((1<<UPM11)|(1<<UPM10));
                    break;
                case 2:
                    UCSR2C|=((1<<UPM21)|(1<<UPM20));
                    break;
                default: //3
                    UCSR3C|=((1<<UPM31)|(1<<UPM30));
            }
            break;
        default: //PARITY_DISABLE
            switch (portn){
                case 0:
                    UCSR0C&=~((1<<UPM01)|(1<<UPM00));
                    break;
                case 1:
                    UCSR1C&=~((1<<UPM11)|(1<<UPM10));
                    break;
                case 2:
                    UCSR2C&=~((1<<UPM21)|(1<<UPM20));
                    break;
                default: //3
                    UCSR3C&=~((1<<UPM31)|(1<<UPM30));
            }
    }
}

void setusartmode(char mode){
#ifndef def_serial
#define def_serial 0
#endif
    setusartmode(def_serial,mode);
}
void setusartmode(char portn,char mode){
    unsigned char tmp=0;
    switch (mode){
        case MODE_ASYNC:
            switch (portn){
                case 0:
                    UCSR0C&=~((1<<UMSEL01)|(1<<UMSEL00));
                    break;
                case 1:
                    UCSR1C&=~((1<<UMSEL11)|(1<<UMSEL10));
                    break;
                case 2:
                    UCSR2C&=~((1<<UMSEL21)|(1<<UMSEL20));
                    break;
                default: //3
                    UCSR3C&=~((1<<UMSEL31)|(1<<UMSEL30));
            }
            break;
        case MODE_SYNC:
            switch (portn){
                case 0:
                    UCSR0C&=~(1<<UMSEL01);
                    UCSR0C|=(1<<UMSEL00);
                    break;
                case 1:
                    UCSR1C&=~(1<<UMSEL11);
                    UCSR1C|=(1<<UMSEL10);
                    break;
                case 2:
                    UCSR2C&=~(1<<UMSEL21);
                    UCSR2C|=(1<<UMSEL20);
                    break;
                default: //3
                    UCSR3C&=~(1<<UMSEL31);
                    UCSR3C|=(1<<UMSEL30);
            }
            break;
        default: //MODE_MASTER_SPI
            switch (portn){
                case 0:
                    UCSR0C|=((1<<UMSEL01)|(1<<UMSEL00));
                    break;
                case 1:
                    UCSR1C|=((1<<UMSEL11)|(1<<UMSEL10));
                    break;
                case 2:
                    UCSR2C|=((1<<UMSEL21)|(1<<UMSEL20));
                    break;
                default: //3
                    UCSR3C|=((1<<UMSEL31)|(1<<UMSEL30));
            }
    }
}

//todo void _settx(char portn,char enablepin,char enablerout)
//todo void _setrx(char portn,char enablepin,char enablerout)
//todo void _enableonemptybuffer(char enable)

void connect(char mode){
#ifndef def_serial
#define def_serial 0
#endif
    connect(def_serial,mode);
}
void connect(char portn,char mode){
    setusartmode(portn,MODE_ASYNC);
    setparity(portn,PARITY_DISABLE);
    setstopmode(portn,STOPBIT_1);
    wordlen(portn,DIM_8b);
    speed(portn,BPS_9600,False);
    //todo
}


