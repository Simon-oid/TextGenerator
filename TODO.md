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