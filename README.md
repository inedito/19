# 19 - File Transmission Bus
Definizione di uno strato per la trasmissione di messaggi su file, osservato da un insieme di attori.

## Prefazione

Il modello proposto definisce uno strato astratto ed osservato con l'obiettivo di consentire - ad un insieme di attori - di scambiare messaggi come alternativa all'implementazione di una infrastruttura socket secondo un'architettura *-tier.

## Caratteristiche

La struttura dello strato - noto anche come _bus_ - è composta dalle seguenti componenti:

* configurazione e descrizione del bucket di input;
* configurazione e descrizione delle regole degli attori osservatori;
* metodi per il monitoraggio e l'ascolto dei bucket.

Il _bucket di input_ rappresenta la directory nota al bus per analizzare i messaggi ricevuti, permettendo così di orchestrare lo spostamento dei file nei bucket definiti nel file di configurazione; ogni entità monitora il suo bucket ed ottiene la lista dei file/messaggi collezionati durante la lettura.

## Implementazione

Il linguaggio di programmazione adottato è il C; alcune note per l'esecuzione dell'esempio:

* il codice sorgente _main.c_ descrive come avviene il monitoraggio del bucket principale e di un attore;
* nella cartella _test/_ è presente il file di configurazione _configuration.txt_ da specificare in input all'esempio;
* occorre modificare il file di configurazione affinchè i puntamenti alle cartelle risultino corretti.

## Contributi

Segnala i tuoi suggerimenti e le tue indicazioni per migliorare il software: ogni contributo è benvenuto!
