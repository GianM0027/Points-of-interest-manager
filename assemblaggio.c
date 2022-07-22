//
// Created by gianm on 07/02/2020.
//

#include "cercaPoi.h"
#include "apriFile.h"
#include "assemblaggio.h"
#include <stdio.h>

/*!
 * procedura contenente tutte le diramazioni, inizio del programma
 * @param nomeFile
 */
void start(char nomeFile[]) {
    int scelta;
    do {
        printf("\n///////////Che cosa vuoi fare?///////////"
               "\n-Aggiungere o cercare POI (premi 1)"
               "\n-Stampare il file e modificarne gli elementi (premi 2)\n");
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 2);

    if (scelta == 1) {
        apriFile(nomeFile);
        start(nomeFile);

    } else if (scelta == 2) {
        stampaFile(nomeFile);
        start(nomeFile);
    }
}
