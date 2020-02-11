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
unsigned short readserialN()
```
* Codice
```c
unsigned short rxdata=readserial0();
```
***

### Verificare che siano stati ricevuti dei byte
###### Verifica che il registro di ricezione non sia vuoto
* Sintassi
```c
char isbyteavaiableN()
```
* Codice
```c
if(isbyteavaiable0()){
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
char issendedN()
```
* Codice
```c
if(issended0()){
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
char getusartstatusN(char status)
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
char framerror=getusartstatus0(STATUS_FRAMEERROR);
```
***

### Configura la ricezione
###### Abilita il pin dedicato alla ricezione dei dati e abilità l'interrupt
* Sintassi
```c
void setrxN(char enablepin,char enableinterrupt)

//interrupt
ISR(USARTN_RX_vect){
    //todo
}
```
enablepin | Descrizione
:---:|:---:
False (0) | disabilita il pin dedicato
True (1) | abilita il pin dedicato

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
###### Abilita il pin dedicato alla trasmissione dei dati e abilità l'interrupt
* Sintassi
```c
void settxN(char enablepin,char enableinterrupt)

//interrupt
ISR(USARTN_TX_vect){
    //todo
}
```
enablepin | Descrizione
:---:|:---:
False (0) | disabilita il pin dedicato
True (1) | abilita il pin dedicato

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
void onemptybufferN(char enableinterrupt)

//interrupt
ISR(USARTN_UDRE_vect){
    //todo
}
```
* Codice `main.ino`
```c
//importazione di usart.h

void setup(){
    //some code
    onemptybuffer0(True);
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
void writeserialN(unsigned short data)
```
* Codice
```c
unsigned short MAX_9b=511;
writeserial0(MAX_9b);
```
***

### Modalità della USART
* Sintassi
```c
void usartmodeN(char mode)
```
Costante|Valore|Descrizione
---|:---:|---
MODE_ASYNC|0|Modalità asincrona
MODE_SYNC|1|Modalità sincrona
MODE_MASTER_SPI|2|Modalità master SPI
* Codice 
```c
usartmode0(MODE_ASYNC);
```
***

### Parità
* Sintassi
```c
void paritymodeN(char mode)
```
Costante|Valore|Descrizione
---|:---:|---
PARITY_DISABLE|0|Parità non abilitata
PARITY_EVEN|1|Parità pari
PARITY_ODD|2|Parità dispari
* Codice
```c
paritymode0(PARITY_DISABLE);
```
***

### Bit di stop
###### Imposta quanti bit di stop devono esserci
* Sintassi
```c
void use2stopbitN(char use)
```
Costante|Valore|Descrizione
---|:---:|---
STOPBIT_1|0|Necessita solo di un bit di stop
STOPBIT_2|1|Necessita di due bit di stop
* Codice
```c
use2stopbit0(STOPBIT_1);
```
***

### Dimensione del dato da inviare
###### Dimensione del dato in bit. Minimo 5, massimo 9
* Sintassi
```c
void dimensionofcharN(char dim)
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
dimensionofchar0(DIM_8b);
```
***

### Polarità del clock
###### Indica quando campionare il bit
* Sintassi
```c
void clockpolarityN(char polarity)
```
Costante|Valore|Descrizione
---|:---:|---
TO_DOWN|0|Campiona quando il clock è in fronte di discesa
TO_UP|1|Campiona quando il clock è in fronte di salita
* Codice
```c
clockpolarity0(TO_DOWN);
```
***

### Impostazione della velocità
###### Quanti bit al secondo verranno trasmessi
* Sintassi
```c
void setbaudrateN(char bps,char speedx2);
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
setbaudrate0(BPS_9600,False);
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
    char polarity;
    char rx[2];
    char tx[2];
} usart;

void setserialN(usart *config)
```
usart param|Codice corrispondente
---|---
mode|`usartmodeN(usart->mode)`
parity|`paritymodeN(usart->parity)`
stopbit|`use2stopbitN(usart->stopbit)`
dimension|`dimensionofcharN(usart->dimension)`
baudrate|`setbaudrateN(usart->baudrate,usart->doublespeed)`
doublespeed|`setbaudrateN(usart->baudrate,usart->doublespeed)`
polarity|`clockpolarityN(usart->polarity)`
rx[2]|`setrxN(usart->rx[0],usart->[1])`
tx[2]|`settxN(usart->tx[0],usart->[1])`
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
config->polarity=TO_DOWN;
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
    .doublespeed=False,
    .polarity=TO_DOWN
};
config.rx[0]=True;
config.rx[1]=True;
config.tx[0]=True;
config.tx[1]=True;

setserial0(&config);
```