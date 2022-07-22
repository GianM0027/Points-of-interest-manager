//
// Created by gianm on 06/02/2020.
//

///LIBRERIA PER L'APERTURA E CREAZIONE DI UN FILE

#ifndef UNTITLED_APRIFILE_H
#define UNTITLED_APRIFILE_H

#include <stdio.h>
#include "assemblaggio.h"

void aggiornaAggiunta(POI vettore[], char nomeFile[]);
void aggiungiPOI(char nomeFile[]);
void apriFile(char nomeFile[]);
POI inizializzaPOI(POI poi);
FILE* apriCtrlFile(char *nomeFile, char *mode);
void stampaFile(char nomeFile[]);
int verificaNomeFile(char nomeFile[]);
void creaFile(char nomeFile[]);
int ordinaCrescDecresc(POI vettore[], int nPoi);

#endif //UNTITLED_APRIFILE_H
