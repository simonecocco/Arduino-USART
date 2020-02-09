# Arduino-USART
##### Libreria per la gestione della porta seriale 0

# Uso:

### Importazione:

###### se si trova nella cartella del progetto
```c
#include "usart.h"
```

###### se si trova nella cartella delle librerie di arduino
```c
#include <usart.h>
```
***

### Leggere i byte:
###### legge fino a 9bit di dato
* Sintassi 
```c
unsigned short readserial()
```
* Codice
```c
unsigned short rxdata=readserial();
```
***

### Verificare che siano stati ricevuti dei byte
###### Verifica che il registro di ricezione non sia vuoto
* Sintassi
```c
char isbyteavaiable()
```
* Codice
```c
if(isbyteavaiable()){
    //some code
}else{
    //todo
}
```
***

### Verificare che il dato sia stato del tutto inviato
###### La trasmissione del dato è stata completata
* Sintassi
```c
char issended()
```
* Codice
```c
if(issended()){
    //some code
}else{
    //todo
}
```
***

### Controllo degli stati
###### Controlla 6 stati differenti. Può rendere True (1) o False (0)
* Sintassi
```c
char getusartstatus(char status)
```
Costante | Valore | Descrizione
--- | :---: | ---
STATUS_BUFFER | 0 | Il suo stato, se è a True, indica che il valore da inviare è stato trasferito allo shift register
STATUS_FRAMEERROR | 1 | Se il bit è a True indica che è avvenuto un errore di frame in ricezione
STATUS_LOSTBYTE | 2 | Se è a True indica che è il byte ricevuto non è stato letto in tempo ed è stato sovrascritto da uno nuovo
STATUS_PARITYERROR | 3 | Se è True indica un errore di parità
STATUS_DOUBLESPEED | 4 | Velocità USART0 raddoppiata
STATUS_MULTIPROCESSOR | 5 | Metodo di comunicazione multiprocessore

* Codice
```c
char framerror=getusartstatus(STATUS_FRAMEERROR);
```
***

### Configura la ricezione
###### Abilita il pin0 alla ricezione dei dati e abilità l'interrupt
* Sintassi
```c
void setrx0(char enablepin,char enableinterrupt)
```
enablepin | Descrizione
:---:|:---:
False (0) | disabilita il pin0
True (1) | abilita il pin0

enableinterrupt | Descrizione
:---:|:---:
False (0) | disabilita l'interrupt
True (1) | abilita l'interrupt
* Codice `main.ino`
```c
//importazione di usart.h

void setup(){
    //some code
    setrx0(True,True);    
    //some code
}
```
`rxinterrupt.ino`
```c
ISR(USART0_RX_vect){
    //some code
}
```
***

### Configura la trasmissione
###### Abilita il pin1 alla trasmissione dei dati e abilità l'interrupt
* Sintassi
```c
void settx0(char enablepin,char enableinterrupt)
```
enablepin | Descrizione
:---:|:---:
False (0) | disabilita il pin1
True (1) | abilita il pin1

enableinterrupt | Descrizione
:---:|:---:
False (0) | disabilita l'interrupt
True (1) | abilita l'interrupt
* Codice `main.ino`
```c
//importazione di usart.h

void setup(){
    //some code
    settx0(True,True);    
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

### Quando il buffer si vuota
###### Quando il dato sta per essere inviato e si trova sullo shift register
* Sintassi
```c
void onemptybuffer(char enableinterrupt)
```
* Codice `main.ino`
```c
//importazione di usart.h

void setup(){
    //some code
    onemptybuffer(True);
    //some code
}
```
`bufferoutine.ino`
```c
ISR(USART0_UDRE_vect){
    //some code
}
```
***

### Scrivere sulla porta seriale
###### E' possibile scrivere fino a un massimo di 9bit
* Sintassi
```c
void writeserial(unsigned short data)
```
* Codice
```c
unsigned short MAX_9b=511;
writeserial(MAX_9b);
```
***

### Modalità della USART0
* Sintassi
```c
void usartmode(char mode)
```
Costante|Valore|Descrizione
---|:---:|---
MODE_ASYNC|0|Modalità asincrona
MODE_SYNC|1|Modalità sincrona
MODE_MASTER_SPI|2|Modalità master SPI
* Codice 
```c
usartmode(MODE_ASYNC);
```
***

### Parità
* Sintassi
```c
void paritymode(char mode)
```
Costante|Valore|Descrizione
---|:---:|---
PARITY_DISABLE|0|Parità non abilitata
PARITY_PAIR|1|Parità pari
PARITY_ODD|2|Parità dispari
* Codice
```c
paritymode(PARITY_DISABLE);
```
***

### Bit di stop
###### Imposta quanti bit di stop devono esserci
* Sintassi
```c
void use2stopbit(char use)
```
Costante|Valore|Descrizione
---|:---:|---
STOPBIT_1|0|Necessita solo di un bit di stop
STOPBIT_2|1|Necessita di due bit di stop
* Codice
```c
use2stopbit(STOPBIT_1);
```
***

### Dimensione del dato da inviare
###### Dimensione del dato in bit. Minimo 5, massimo 9
* Sintassi
```c
void dimensionofchar(char dim)
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
dimensionofchar(DIM_8b);
```
***

### Polarità del clock
###### Indica quando campionare il bit
* Sintassi
```c
void clockpolarity(char polarity)
```
Costante|Valore|Descrizione
---|:---:|---
TO_DOWN|0|Campiona quando il clock è in fronte di discesa
TO_UP|1|Campiona quando il clock è in fronte di salita
* Codice
```c
clockpolarity(TO_DOWN);
```
***

### Impostazione della velocità
###### Quanti bit al secondo verranno trasmessi
* Sintassi
```c
void setbaudrate(char bps,char speedx2);
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
setbaudrate(BPS_9600,False);
```
***

### Costruttore veloce
###### Utilizza una struttura per configurare le cose principali
* Sintassi
```c
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

void setserial0(usart *config)
```
usart param|Codice corrispondente
---|---
mode|`usartmode(usart->mode)`
parity|`paritymode(usart->parity)`
stopbit|`use2stopbit(usart->stopbit)`
dimension|`dimensionofchar(usart->dimension)`
baudrate|`setbaudrate(usart->baudrate,usart->doublespeed)`
doublespeed|`setbaudrate(usart->baudrate,usart->doublespeed)`
rx[2]|`setrx0(usart->rx[0],usart->[1])`
tx[2]|`settx0(usart->tx[0],usart->[1])`
* Codice (utilizzando `malloc`)
```c
#include <stdlib.h>
//importazione di usart.h

usart *config=malloc(sizeof(usart));
config->mode=MODE_ASYNC;
config->parity=PARITY_DISABLE;
config->stopbit=STOPBIT_1;
config->dimension=DIM_8b;
config->baudrate=BPS_9600;
config->doublespeed=False;
config->rx[0]=True;
config->rx[1]=True;
config->tx[0]=True;
config->tx[1]=True;

setserial0(config);
free(config);
```
(senza `malloc`)
```c
//importazione di usart.h
usart config=(usart){
    .mode=MODE_ASYNC,
    .parity=PARITY_DISABLE,
    .stopbit=STOPBIT_1,
    .dimension=DIM_8b,
    .baudrate=BPS_9600,
    .doublespeed=False
};
config.rx[0]=True;
config.rx[1]=True;
config.tx[0]=True;
config.tx[1]=True;

setserial0(&config);
```