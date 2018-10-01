# 19 - File Transmission Bus
Definizione di uno strato per la trasmissione di messaggi su file, osservato da un insieme di attori.

## Prefazione

Il modello proposto definisce uno strato astratto ed osservato con l'obiettivo di consentire - ad un insieme di attori - di scambiare messaggi come alternativa all'implementazione di una infrastruttura socket secondo un'architettura *-tier.

## Caratteristiche

La struttura dello strato - noto anche come _bus_ - e' composta dalle seguenti componenti:

* configurazione e descrizione del bucket di input;
* configurazione e descrizione delle regole degli attori osservatori;
* metodi per il monitoraggio e l'ascolto dei bucket.

Il _bucket di input_ rappresenta la directory nota al bus per analizzare i messaggi ricevuti, permettendo cosi' di orchestrare lo spostamento dei file nei bucket definiti nel file di configurazione.
Ogni entita' monitora il suo bucket ed ottiene la lista dei file/messaggi collezionati durante la lettura.

## Implementazione

Il linguaggio di programmazione adottato e' C.
Il codice sorgente _example.c_ descrive come avviene il monitoraggio del bucket principale e di un attore.

## Contributi

Segnala i tuoi suggerimenti e le tue indicazioni per migliorare il software: ogni contributo e' benvenuto!
