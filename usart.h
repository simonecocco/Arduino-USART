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
#define PARITY_EVEN    1
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

#define SERIAL0 0
#define SERIAL1 1
#define SERIAL2 2
#define SERIAL3 3

#define ONLY_RX 0
#define ONLY_TX 1
#define RXTX 2

#ifndef USARTLIB_USART_H
    #define USARTLIB_USART_H

    typedef struct param{
        char bufferstat;
        char frameerror;
        char bytelost;
        char parityerror;
        char dataavaiable;
    } usartstat;

    /**
     * legge il dato nella porta
     * @param portn (se dovesse mancare serve che venga
     *              dichiarata una costante "def_serial"
     *              con il numero della porta)
     * @return
     */
    unsigned short read(char portn);
    unsigned short read();

    /**
     * legge il dato nella porta se la condizione è vera
     */
     unsigned short readif(char condiction,char portn);
     unsigned short readif(char condiction);

    /**
     * @return 1 se c'è un byte pronto alla lettura
     */
    char isbyteavaiable0();
    char isbyteavaiable1();
    char isbyteavaiable2();
    char isbyteavaiable3();

    usartstat status(char portn);
    usartstat status();

    /**
     * @return 1 se il dato è stato completamente inviato
     */
    char issended0();
    char issended1();
    char issended2();
    char issended3();

    /**
     * legge un determinato bit di stato
     * @param status costante definita da define STATUS_x
     * @return 1 o 0 a seconda del bit
     */
    char getusartstatus0(char status);
    char getusartstatus1(char status);
    char getusartstatus2(char status);
    char getusartstatus3(char status);

    /**
     * imposta la ricezione
     * @param enablepin abilita il pin 0 alla ricezione
     * @param enableinterrupt abilita la routine alla ricezione
     *
     * @code
     * si utilizza ISR(USARTn_RX_vect){}
     * @endcode
     */
    void setrx0(char enablepin,char enableinterrupt);
    void setrx1(char enablepin,char enableinterrupt);
    void setrx2(char enablepin,char enableinterrupt);
    void setrx3(char enablepin,char enableinterrupt);

    /**
     * imposta la trasmissione
     * @param enablepin abilita il pin 1 alla trasmissione
     * @param enableinterrupt abilita la routine alla trasmissione
     *
     * @code
     * si utilizza ISR(USARTn_TX_vect){}
     * @endcode
     */
    void settx0(char enablepin,char enableinterrupt);
    void settx1(char enablepin,char enableinterrupt);
    void settx2(char enablepin,char enableinterrupt);
    void settx3(char enablepin,char enableinterrupt);

    /**
     * imposta la routine per il buffer vuoto
     * @param enableinterrupt abilita la routine per il buffer vuoto
     *
     * @code
     * si utilizza ISR(USARTn_UDRE_vect){}
     * @endcode
     */
    void onemptybuffer0(char enableinterrupt);
    void onemptybuffer1(char enableinterrupt);
    void onemptybuffer2(char enableinterrupt);
    void onemptybuffer3(char enableinterrupt);

    /**
     * scrive sulla porta seriale
     * @param data il dato (puà avere fino a 9 bit)
     */
    void writeserial0(unsigned short data);
    void writeserial1(unsigned short data);
    void writeserial2(unsigned short data);
    void writeserial3(unsigned short data);

    /**
     * importa la modalità di utilizzo della porta
     * @param portn
     * @param mode
     */
    void setusartmode(char portn,char mode);
    void setusartmode(char mode);

    /**
     * va a determinare la modalità
     * @param mode costante definita da PARITY_x
     */
    void setparity(char portn,char mode);
    void setparity(char mode);

    /**
     * decidi se usare uno o due bit di stop
     * @param use True per usarne 2, False per usarne 1
     */
    void setstopmode(char portn,char mode);
    void setstopmode(char mode);

    /**
     * imposta la dimensione del carattere
     * @param dim costante definita da DIM_xb
     */
    void dimensionofchar0(char dim);
    void dimensionofchar1(char dim);
    void dimensionofchar2(char dim);
    void dimensionofchar3(char dim);

    /**
     * decide quando deve campionare il bit
     * @param polarity fronte di discesa o salita
     */
    void clockpolarity0(char polarity);
    void clockpolarity1(char polarity);
    void clockpolarity2(char polarity);
    void clockpolarity3(char polarity);

    /**
     * imposta la velocità di trasferimento dati
     * @param bps velocità di baud rate BPS_x
     * @param speedx2 imposta se la velocità deve essere raddoppiata
     */
    void setbaudrate0(char bps,char speedx2);
    void setbaudrate1(char bps,char speedx2);
    void setbaudrate2(char bps,char speedx2);
    void setbaudrate3(char bps,char speedx2);

    /**
     * imposta la porta con una sola istruzione
     * @param config insieme di configurazioni
     */
    void setserial0(usart *config);
    void setserial1(usart *config);
    void setserial2(usart *config);
    void setserial3(usart *config);

    /**
     * configura inizialmente una porta seriale
     * @param portn il numero della porta
     * @param mode la modalità di connessione
     */
    void connect(char portn,char mode);
    void connect(char mode);
#endif //USARTLIB_USART_H
