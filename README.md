# Arduino-USART
##### Libreria per la gestione delle porte seriali.
#### Con N si intende il numero della porta desiderata. Solitamente è una ma su alcune schede come Arduino MEGA se ne possono trovare fino a 4 (0,1,2,3)

# Uso:
### Importazione:
```c
#include <usart.h>
```
***

### Leggere i byte:
###### legge fino a 9bit di dato
* Sintassi 
```c
//per leggere il dato sulla porta predefinita (SERIAL0)
unsigned short read();
//per leggere il dato in una determinata porta
//le porte sono indicate con una costante SERIAL+numero porta
unsigned short read(char portn);
//legge il dato (su SERIAL0) solo se la condizione è 1
unsigned short readif(char condiction);
//legge il dato sulla porta n solo se la condizione è 1
unsigned short readif(char portn,char condiction);
```
Costante | Valore | Descrizione
:----:|:----:|---
SERIAL0|0|Condivisa con la porta USB
SERIAL1|1|Disponibile solo nelle board grandi
SERIAL2|2|Disponibile solo nelle board grandi
SERIAL3|3|Disponibile solo nelle board grandi

* Codice
```c
unsigned short rxdata=read(SERIAL3);

rxdata=readif(SERIAL3,rxdata==0?1:0);
```
***

### Controllo degli stati
###### ritorna la struttura `usartstat`:
```c
typedef struct param{
        //il buffer ha inviato il dato allo shift register?
        char bufferstat;
        //c'è un errore di frame?
        char frameerror;
        //è stato perso un bit?
        char bytelost;
        //c'è un errore di parità?
        char parityerror;
        //ci sono dati disponibili?
        char dataavaiable;
        //inviato?
        char sended;
    } usartstat;
```
* Sintassi
```c
//ritorna gli stati della porta SERIAL0
usartstat status();
//ritona gli stati della porta SERIALn
usartstat status(char portn);
```

* Codice
```c
char framerror=status().frameerror;
```
***

### Scrivere sulla porta seriale
###### E' possibile scrivere fino a un massimo di 9bit
* Sintassi
```c
//invia i bit tramite la porta SERIAL0
void write(unsigned short data);
//invia i bit tramite la porta n
void write(char portn,unsigned short data);
```
* Codice
```c
unsigned short MAX_9b=511;
write(SERIAL1,MAX_9b);
```
***

### Modalità della USART
* Sintassi
```c
//imposta il comportamento della porta predefinita
void setusartmode(char mode);
//imposta il comportamento della porta n
void setusartmode(char portn,char mode);
```
Costante|Valore|Descrizione
---|:---:|---
MODE_ASYNC|0|Modalità asincrona
MODE_SYNC|1|Modalità sincrona
MODE_MASTER_SPI|2|Modalità master SPI
* Codice 
```c
setusartmode(MODE_ASYNC);
```
***

### Parità
* Sintassi
```c
//imposta il comportamento della parità della porta SERIAL0
void setparity(char mode);
//imposta il comportamento della parità della porta n
void setparity(char portn,char mode);
```
Costante|Valore|Descrizione
---|:---:|---
PARITY_DISABLE|0|Parità non abilitata
PARITY_EVEN|1|Parità pari
PARITY_ODD|2|Parità dispari
* Codice
```c
setparity(PARITY_DISABLE);
```
***

### Costruttore veloce
###### Utilizza una struttura per configurare le cose principali:
###### modalità asincrona, parità disabilitata, un bit di stop, 8bit di dato, velocità 9600, modalità di campionamento del clock verso il basso
* Sintassi
```c
//connette la porta SERIAL0 con la modalità di ricezione o trasmissione o entrambi
void connect(char mode);
//connette la porta n
void connect(char portn.char mode);
```
Costante|Valore|Descrizione
:---:|:---:|---
ONLY_RX|0|Solo ricezione
ONLY_TX|1|Solo trasmissione
RXTX|2|Entrambi
* Codice
```c
connect(RXTX);
```
***

### Configura la ricezione
###### Abilita il pin dedicato alla ricezione dei dati e abilità l'interrupt
* Sintassi
```c
//configura la porta SERIAL0 in ricezione
connect(char mode);
//configura la porta n in ricezione
connect(char portn,char mode);

//interrupt
ISR(USARTN_RX_vect){
    //some code
}
```
* Codice `main.ino`
```c
//importazione di usart.h

void setup(){
    //some code
    connect(SERIAL2,ONLY_RX); //oppure RXTX 
    //some code
}
```
`rxinterrupt.ino`
```c
ISR(USART2_RX_vect){
    //some code
}
```
***

### Configura la trasmissione
###### Abilita il pin dedicato alla trasmissione dei dati e abilità l'interrupt
* Sintassi
```c
//imposta la porta SERIAL0 in trasmissione
void connect(char mode);
//imposta la porta n in trasmissione
void connect(char portn,char mode);

//interrupt
ISR(USARTN_TX_vect){
    //some code
}
```
* Codice `main.ino`
```c
//importazione di usart.h

void setup(){
    //some code
    connect(ONLY_TX); //oppure RXTX   
    //some code
}
```
`rxinterrupt.ino`
```c
ISR(USART0_TX_vect){
    //some code
}
```
***

### Bit di stop
###### Imposta quanti bit di stop devono esserci
* Sintassi
```c
//imposta la modalità di stop della porta SERIAL0
void setstopmode(char mode);
//imposta la modalità di stop della porta n;
void setstopmode(char portn,char mode);
```
Costante|Valore|Descrizione
---|:---:|---
STOPBIT_1|0|Necessita solo di un bit di stop
STOPBIT_2|1|Necessita di due bit di stop
* Codice
```c
setstopmode(STOPBIT_1);
```
***

### Dimensione del dato da inviare
###### Dimensione del dato in bit. Minimo 5, massimo 9
* Sintassi
```c
//imposta la lunghezza in bit del dato per la porta SERIAL0
void wordlen(char dim);
//imposta la lunghezza in bit del dato per la porta n
void wordlen(char portn,char dim);
```
Costante|Valore|Dimensione
---|:---:|---
DIM_5b|0|5 bit
DIM_6b|1|6 bit
DIM_7b|2|7 bit
DIM_8b|3|8 bit
DIM_9b|4|9 bit
* Codice
```c
wordlen(SERIAL1,DIM_8b);
```
***

### Polarità del clock
###### Indica quando campionare il bit
* Sintassi
```c
//imposta la modalità di campionamento del clock della porta SERIAL0
void clockmode(char mode);
//imposta la modalità di campionamento del clock della porta n
void clockmode(char portn,char mode);
```
Costante|Valore|Descrizione
---|:---:|---
TO_DOWN|0|Campiona quando il clock è in fronte di discesa
TO_UP|1|Campiona quando il clock è in fronte di salita
* Codice
```c
clockmode(SERIAL1,TO_DOWN);
```
***

### Impostazione della velocità
###### Quanti bit al secondo verranno trasmessi
* Sintassi
```c
//imposta la velocità di trasmissione della porta SERIAL0
void speed(char bps);
//imposta la velocità di trasmissione della porta n (e se deve essere raddoppiata)
void speed(char portn,char bps,char speedx2);
```
Costante (bps)|Valore|Velocità (speedx2=0)|Velocità (speedx1=1)
---|:---:|:---:|:---:
BPS_2400|0|2.4Kb/s|4.8Kb/s
BPS_4800|1|4.8Kb/s|9.6Kb/s
BPS_9600|2|9.6Kb/s|19.2Kb/s
BPS_14400|3|14.4Kb/s|28.8Kb/s
BPS_19200|4|19.2Kb/s|38.4Kb/s
BPS_28800|5|28.8Kb/s|57.6Kb/s
BPS_38400|6|38.4Kb/s|76.8Kb/s
BPS_57600|7|57.6Kb/s|115.2Kb/s
BPS_76800|8|76.8Kb/s|153.6Kb/s
BPS_115200|9|115.2Kb/s|230.4Kb/s
BPS_230400|10|230.4Kb/s|460.8Kb/s
BPS_250000|11|250Kb/s|500Kb/s
* Codice
```c
speed(SERIAL1,BPS_9600,False);
```
***