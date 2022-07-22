#include <stdio.h>
#include "assemblaggio.h"
#include "apriFile.h"

int main() {

    /*!
     * come prima cosa chiedo all'utente su quale file vuole lavorare, poi faccio partire il programma che si baserà
     * sul file che l'utente ha scelto
     */
    char nomeFile[NOMEFILE];
    int scelta;

    do {
        printf("\nInserisci il nome del file su cui lavorare (se non esiste verra' creato da zero): ");
        scanf("%s", nomeFile);

        ///verifico se il file esiste già o meno
        if (verificaNomeFile(nomeFile) == 1){
            printf("\nSi lavorera' su un file gia' esistente, procedere?"
                   "\nSi (premi 1)"
                   "\nNo (premi 2)\n");
            scanf("%d", &scelta);
        }
        else{
            printf("\nNon esiste un file con questo nome? Si desidera creare un nuovo documento?"
                   "\nSi (premi 1)"
                   "\nNo (premi 2)\n");
            scanf("%d", &scelta);
            if (scelta == 1){
                creaFile(nomeFile);
                printf("Inserire il primo punto di interesse\n");
                aggiungiPOI(nomeFile);
            }
        }
    }while (scelta ==2);

    ///inizio del programma
    start(nomeFile);
    return 0;
}