# TextGenerator
 
### Progetto di SO2 - TextGenerator

Il progetto consiste in un generatore di testo che prende in input un file di testo e genera un nuovo file di testo con le stesse parole del file di input, ma con le parole ordinate in modo casuale.

### Struttura del progetto

Il progetto è composto da 3 file sorgente principali:

- `main.c`: file principale del progetto, contiene la funzione `main` che gestisce l'input dell'utente e chiama le funzioni necessarie per generare il nuovo file di testo.
- `text_generator.c`: file che contiene la funzione `generate_text` che si occupa di generare il nuovo file di testo.
- `frequency_table.c`: file che contiene le funzioni necessarie per creare e manipolare la tabella di frequenza delle parole del file di input.
- `single_threaded.c`: file che contiene la funzione `single_threaded` che si occupa di generare il nuovo file di testo in modo single-threaded.
- `multi_process.c`: file che contiene la funzione `multi_process` che si occupa di generare il nuovo file di testo in modo multi-process.

### Utilizzo

Il progetto permette all'utente di scegliere tra due modalità di esecuzione principali: single-threaded e multi-process.

Inoltre è possibile scegliere di eseguire solo una delle due funzionalità del progetto: generare la tabella di frequenza delle parole del file di input(`frequency_table.c`) o generare il nuovo file di testo(`text_generator.c`).


### Compilazione

Per compilare il progetto è sufficiente eseguire il comando `make` da terminale. Verranno generati i file eseguibili necessari.

### Esecuzione

Per eseguire il progetto è sufficiente eseguire il comando `./TextGenerator` da terminale. Verrà visualizzato un menu che permette all'utente di scegliere tra le varie funzionalità del progetto.
Se si sceglie di generare il nuovo file di testo utilizzando la versione del programma multi-process e il programma non genera' un output, sara' necessario riavviare il programma fino a quando non verra' generato un nuovo output. (il programma funziona ma e' inconsistente)