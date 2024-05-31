# TextGenerator project

======================== 20/05/24 =====================
## TODO:

- [ ] implementare il text generator
- [ ] implementare il programma single_threaded 
- [ ] implementare il programma multi_process 
- [ ] cambiare il main cosi' che si possa scegliere tra signle threaded / multi_threaded (e' necessario anche implementare il poter scegliere una singola funzionalita' del progetto)
## DONE:

- ### rework alla struttura del progetto:
  - [x] ricreato il progetto da zero 
  - [x] creata la directory Documentation
  - [x] creata la directory include:
    - [x] creato il file frequency_table.h
    - [x] creato il file text_generator.h
  - [x] creata la directory src:
    - [x] creato il file frequency_table.c
    - [x] creato il file main.c
    - [x] creato il file multi_process.c
    - [x] creato il file single_threaded.c
    - [x] creato il file text_generator.c
  - [x] modificato il file CMakeLists.txt in modo da fittare i cambiamenti
  - [x] creato il file TODO.md

======================= 21/05/24 ======================
## TODO:

- [ ] reworkare il frequency_table.c:
  -  [ ] fare in modo che quando il comando 1 viene eseguito, l'output venga scritto sul file output.csv
  -  [ ] il simbolo ":" non dovrebbe essere considerato una parola, ne deve essere accorpato ad altre parole
  -  [ ] le maiuscole vengono elminate invece di essere considerate minuscole
  -  [ ] modificare il main.c in modo da poter debuggare l'output, la scelta di quale funzione utilizzare non funziona come dovrebbe
- [ ] implementare il text generator
- [ ] implementare il programma single_threaded
- [ ] implementare il programma multi_process
- [ ] cambiare il main cosi' che si possa scegliere tra signle threaded / multi_threaded (e' necessario anche implementare il poter scegliere una singola funzionalita' del progetto)

## DONE:
- [ ] schifo ;-;

======================= 22/05/24 ======================

## TODO:

### HIGH PRIO:

- [ ] implementare il text generator:
    - [ ] cucinare qualcosa per la generazione del testo (per ora c'e' un problema con la dichiarazione della variabile frequency)
- [ ] implementare il programma single_threaded
- [ ] implementare il programma multi_process


### LOW PRIO:
- [x] reworkare il frequency_table.c:
  - [ ] nel file output.csv le lettere maiuscole sono scritte come maiuscole ma non sono considerate come tali durante la costruzione della frequency_table
  - [ ] nel file del professore la prima coppia di parola ha sempre come prima parola un "." nella mia versione non avviene (per ora e' in standby)  
---------------------------------------------------

## DONE:
-  [x] fare in modo che quando il comando 1 viene eseguito, l'output venga scritto sul file output.csv
-  [x] il simbolo ":" non dovrebbe essere considerato una parola, ne deve essere accorpato ad altre parole
-  [x] le maiuscole vengono elminate invece di essere considerate minuscole
-  [x] modificare il main.c in modo da poter debuggare l'output, la scelta di quale funzione utilizzare non funziona come dovrebbe
-  [x] cambiare il main cosi' che si possa scegliere tra signle threaded / multi_threaded (e' necessario anche implementare il poter scegliere una singola funzionalita' del progetto)

======================= 24/05/24 ======================

## TODO:

### HIGH PRIO:

- [ ] implementare il programma single_threaded
- [ ] implementare il programma multi_process


### LOW PRIO:
- [x] reworkare il frequency_table.c:
  - [ ] nel file output.csv le lettere maiuscole sono scritte come maiuscole ma non sono considerate come tali durante la costruzione della frequency_table
  - [ ] nel file del professore la prima coppia di parola ha sempre come prima parola un "." nella mia versione non avviene (per ora e' in standby)
---------------------------------------------------

## DONE:
- [x] implementare il text generator
- [x] cucinare qualcosa per la generazione del testo (per ora c'e' un problema con la dichiarazione della variabile frequency)
- [x] fixato il main per fittare i cambiamenti
- [x] fixati gli header per fittare i cambiamenti

===================== 25/05/24 ===================

## TODO:

### HIGH PRIO:

- [ ] implementare il programma multi_process:
    - [ ] bisogna implementare la memoria condivisa per i processi, al momento i puntatori non vengono updatati correttamente dopo l'esecuzione di un processo


### LOW PRIO:
- [x] reworkare il frequency_table.c:
  - [ ] nel file output.csv le lettere maiuscole sono scritte come maiuscole ma non sono considerate come tali durante la costruzione della frequency_table
  - [ ] nel file del professore la prima coppia di parola ha sempre come prima parola un "." nella mia versione non avviene (per ora e' in standby)
---------------------------------------------------

## DONE:
- [x] implementare il programma single_threaded
- [x] reworkato il main cosi' da poter scegliere quali funzione/versione del programma runnare

===================== 26/05/24 ===================
## TODO:

### HIGH PRIO:

- [ ] implementare il programma multi_process:
  - [ ] bisogna implementare la memoria condivisa per i processi, al momento i puntatori non vengono updatati correttamente dopo l'esecuzione di un processo


### LOW PRIO:
- [x] reworkare il frequency_table.c:
  - [ ] nel file output.csv le lettere maiuscole sono scritte come maiuscole ma non sono considerate come tali durante la costruzione della frequency_table
  - [ ] nel file del professore la prima coppia di parola ha sempre come prima parola un "." nella mia versione non avviene (per ora e' in standby)
---------------------------------------------------

## DONE:
  - [x] idk

===================== 27/05/24 ===================
## TODO:

### HIGH PRIO:

- [ ] implementare il programma multi_process:
  - [ ] bisogna implementare la memoria condivisa per i processi, al momento i puntatori non vengono updatati correttamente dopo l'esecuzione di un processo


### LOW PRIO:
- [x] reworkare il frequency_table.c:
  - [ ] nel file output.csv le lettere maiuscole sono scritte come maiuscole ma non sono considerate come tali durante la costruzione della frequency_table
  - [ ] nel file del professore la prima coppia di parola ha sempre come prima parola un "." nella mia versione non avviene (per ora e' in standby)
---------------------------------------------------

## DONE:
  - [x] schifo


===================== 28/05/24 ===================
## TODO:

### HIGH PRIO:

- [ ] implementare il programma multi_process:
  - [ ] bisogna implementare la memoria condivisa per i processi, al momento i puntatori non vengono updatati correttamente dopo l'esecuzione di un processo


### LOW PRIO:
- [x] reworkare il frequency_table.c:
  - [ ] nel file output.csv le lettere maiuscole sono scritte come maiuscole ma non sono considerate come tali durante la costruzione della frequency_table
  - [ ] nel file del professore la prima coppia di parola ha sempre come prima parola un "." nella mia versione non avviene (per ora e' in standby)
---------------------------------------------------

## DONE:
- [x] fixato il caricamento per la frequency_table nel programma multiprocesso
- [x] aggiunti print statements e debugging per errori comuni che possono accadere con l'esecuzion del programma
- [x] fixare il fatto che durante la generazione delle parole soltanto 2 loop vengono eseguiti
- [x] fixata la funzione: deserializeWordRelations()
- [x] fixato il fatto che il programma multiprocess generava ma una frase di n parole identiche
- [x] implementare il programma multi_process
- [x] migliorato leggermente il modo in cui le parole vengono scelte dal metodo: getRandomNextWord() (e' ancora visibile un pattern, da fixare)

===================== 29/05/24 ===================
## TODO:

### HIGH PRIO:

- [ ] verificare che le seguenti caratteristiche siano rispettate:
  - [ ] le punteggiature ., ?, ! devono essere trattate come parole separate; gli apostrofi
  fanno parte della parola; la rimanente punteggiatura può essere scartata. Vedere il
  file allegato per alcuni esempi di testo di input e la corrispondente tabella;
  - [ ] maiuscole/minuscole non hanno effetto: ad es., ‘oggi’= ‘Oggi’ = ’OGGI’ = etc.
  - [ ] la prima parola del testo si intende preceduta dal carattere
    punto . ;
  - [ ] nel generare il testo casuale si può specificare una prima parola, altrimenti il
    programma seleziona una punteggiatura a caso tra ., ?, ! (secondo la tabella di
    input) e genera la parola successiva;
  - [ ] nel generare il testo casuale la parola all’inizio di una frase (cioè la parola dopo un
    punto ., ?, o !) deve avere l'iniziale maiuscola;
  - [ ] si assuma che una parola sia lunga al massimo 30 caratteri stampabili.
  - 
### LOW PRIO:
---------------------------------------------------

## DONE:
- [x] fatto in modo che il programma prenda come input un file .txt
- [x] fatto in modo che i pattern che si verificano prima non siano cosi' comuni quando generando una frase randomica
- [x] aggiunto README.md 
- [x] aggiunta compatibilita' con il `make` cosi' da poter eseguire il programma in console

===================== 31/05/24 ===================
## TODO:

### HIGH PRIO:


### LOW PRIO:
---------------------------------------------------

## DONE:
- [x] le punteggiature ., ?, ! devono essere trattate come parole separate; gli apostrofi
  fanno parte della parola; la rimanente punteggiatura può essere scartata. Vedere il
  file allegato per alcuni esempi di testo di input e la corrispondente tabella;
- [x] maiuscole/minuscole non hanno effetto: ad es., ‘oggi’= ‘Oggi’ = ’OGGI’ = etc.
- [x] la prima parola del testo si intende preceduta dal carattere
  punto . ;
- [x] nel generare il testo casuale si può specificare una prima parola, altrimenti il
  programma seleziona una punteggiatura a caso tra ., ?, ! (secondo la tabella di
  input) e genera la parola successiva;
- [x] nel generare il testo casuale la parola all’inizio di una frase (cioè la parola dopo un
  punto ., ?, o !) deve avere l'iniziale maiuscola;
- [x] si assuma che una parola sia lunga al massimo 30 caratteri stampabili.
- [x] fixati i leak alla memoria nel programma multiprocess
- [x] fixato il caso in cui il programma multiprocess falliva per via di una race condition