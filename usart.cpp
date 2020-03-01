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
            break;
        case 1:
            break;
        case 2:
            break;
        default: //3

    }
    return param;
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
    //todo
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
    //todo
}


