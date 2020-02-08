#include <avr/io.h>

#ifndef True
    #define True (char)1
#endif
#ifndef False
    #define False (char)0
#endif

#define STATUS_BUFFER         0
#define STATUS_FRAMEERROR     1
#define STATUS_LOSTBYTE       2
#define STATUS_PARITYERROR    3
#define STATUS_DOUBLESPEED    4
#define STATUS_MULTIPROCESSOR 5

#define MODE_ASYNC      0
#define MODE_SYNC       1
#define MODE_MASTER_SPI 2

#define PARITY_DISABLE 0
#define PARITY_PAIR    1
#define PARITY_ODD     2

#define DIM_5b 0
#define DIM_6b 1
#define DIM_7b 2
#define DIM_8b 3
#define DIM_9b 4

#define BPS_2400   0
#define BPS_4800   1
#define BPS_9600   2
#define BPS_14400  3
#define BPS_19200  4
#define BPS_28800  5
#define BPS_38400  6
#define BPS_57600  7
#define BPS_76800  8
#define BPS_115200 9
#define BPS_230400 10
#define BPS_250000 11

#define STOPBIT_1 0
#define STOPBIT_2 1

#define TO_DOWN 0
#define TO_UP   1

#ifndef USARTLIB_USART_H
    #define USARTLIB_USART_H

    typedef struct USART{
        char mode;
        char parity;
        char stopbit;
        char dimension;
        char baudrate;
        char doublespeed;
        char rx[2];
        char tx[2];
    } usart;

    /**
     * legge il dato in arrivo
     * @return il contenuto del registro UDR0
     */
    unsigned short readserial();

    /**
     * @return 1 se c'è un byte pronto alla lettura
     */
    char isbyteavaiable();

    /**
     * @return 1 se il dato è stato completamente inviato
     */
    char issended();

    /**
     * legge un determinato bit di stato
     * @param status costante definita da define STATUS_x
     * @return 1 o 0 a seconda del bit
     */
    char getusartstatus(char status);

    /**
     * imposta la ricezione
     * @param enablepin abilita il pin 0 alla ricezione
     * @param enableinterrupt abilita la routine alla ricezione
     *
     * @code
     * si utilizza ISR(USART0_RX_vect){}
     * @endcode
     */
    void setrx0(char enablepin,char enableinterrupt);

    /**
     * imposta la trasmissione
     * @param enablepin abilita il pin 1 alla trasmissione
     * @param enableinterrupt abilita la routine alla trasmissione
     *
     * @code
     * si utilizza ISR(USART0_TX_vect){}
     * @endcode
     */
    void settx0(char enablepin,char enableinterrupt);

    /**
     * imposta la routine per il buffer vuoto
     * @param enableinterrupt abilita la routine per il buffer vuoto
     *
     * @code
     * si utilizza ISR(USART0_UDRE_vect){}
     * @endcode
     */
    void onemptybuffer(char enableinterrupt);

    /**
     * scrive sulla porta seriale
     * @param data il dato (puà avere fino a 9 bit)
     */
    void writeserial(unsigned short data);

    /**
     * va a determinare la modalità
     * @param mode costante definita da MODE_x
     */
    void usartmode(char mode);

    /**
     * va a determinare la modalità
     * @param mode costante definita da PARITY_x
     */
    void paritymode(char mode);

    /**
     * decidi se usare uno o due bit di stop
     * @param use True per usarne 2, False per usarne 1
     */
    void use2stopbit(char use);

    /**
     * imposta la dimensione del carattere
     * @param dim costante definita da DIM_xb
     */
    void dimensionofchar(char dim);

    /**
     * decide quando deve campionare il bit
     * @param polarity fronte di discesa o salita
     */
    void clockpolarity(char polarity);

    /**
     * imposta la velocità di trasferimento dati
     * @param bps velocità di baud rate BPS_x
     * @param speedx2 imposta se la velocità deve essere raddoppiata
     */
    void setbaudrate(char bps,char speedx2);

    /**
     * imposta la porta con una sola istruzione
     * @param config insieme di configurazioni
     */
    void setserial0(usart *config);
#endif //USARTLIB_USART_H
