#include <avr/io.h>

#ifndef True
    #define True (char)1
#endif
#ifndef False
    #define False (char)0
#endif

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
        char sended;
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
     * todo da fare la descrizione
     */
    usartstat status(char portn);
    usartstat status();

    /**
     * imposta la ricezione
     * @param enablepin abilita il pin 0 alla ricezione
     * @param enableinterrupt abilita la routine alla ricezione
     *
     * @code
     * si utilizza ISR(USARTn_RX_vect){}
     * @endcode
     */
    void _setrx(char portn,char enablepin,char enablerout);

    /**
     * imposta la trasmissione
     * @param enablepin abilita il pin 1 alla trasmissione
     * @param enableinterrupt abilita la routine alla trasmissione
     *
     * @code
     * si utilizza ISR(USARTn_TX_vect){}
     * @endcode
     */
    void _settx(char portn,char enablepin,char enablerout);

    /**
     * imposta la routine per il buffer vuoto
     * @param enableinterrupt abilita la routine per il buffer vuoto
     *
     * @code
     * si utilizza ISR(USARTn_UDRE_vect){}
     * @endcode
     */
    void _setemptybuffer(char portn,char enable);

    /**
     * scrive sulla porta seriale
     * @param data il dato (puà avere fino a 9 bit)
     */
    void write(char portn, unsigned short data);
    void write(unsigned short data);

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
    void wordlen(char portn,char dim);
    void wordlen(char dim);

    /**
     * decide quando deve campionare il bit
     * @param polarity fronte di discesa o salita
     */
    void clockmode(char portn,char mode);
    void clockmode(char mode);

    /**
     * imposta la velocità di trasferimento dati
     * @param bps velocità di baud rate BPS_x
     * @param speedx2 imposta se la velocità deve essere raddoppiata
     */
    void speed(char portn,char bps,char speedx2);
    void speed(char bps);

    /**
     * configura inizialmente una porta seriale
     * @param portn il numero della porta
     * @param mode la modalità di connessione
     */
    void connect(char portn,char mode);
    void connect(char mode);
#endif //USARTLIB_USART_H
