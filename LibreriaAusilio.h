//
// Created by gianm on 27/02/2020.
//

#ifndef UNTITLED_LIBRERIAAUSILIO_H
#define UNTITLED_LIBRERIAAUSILIO_H

#include "assemblaggio.h"
#include <stdio.h>
int compNoCaseSensitive(char stringa1[], char stringa2[]);
void stampaPOI(POI poi);
void aggiornaModifica(char nomeFile[], POI vettore[], int numPoi);
void aggiornaEliminazione(char nomeFile[], POI vettore[], int cellaEliminazione, int numPoi);
POI modificaCampo(POI poi);
void chiediModifica(char nomeFile[], POI vettore[], int nPoi);
int trovaParola(char keyword[],char descrizione[]);
int trovaPunto(double latitudine, double longitudine, float raggio, POI poi);
void stampaSuFileDiTesto(FILE* fileTesto, POI poi);
#endif //UNTITLED_LIBRERIAAUSILIO_H
