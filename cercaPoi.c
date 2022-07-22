//
// Created by gianm on 06/02/2020.
//

#include "LibreriaAusilio.h"
#include "apriFile.h"
#include "assemblaggio.h"
#include <stdio.h>
#include <stdlib.h>


/*!
 * ricerca di una serie di POI conoscendone il comune di afferenza
 * @param nomeFile
 */
void poiPerComune(char nomeFile[]) {
    FILE *file = NULL;
    char comune[MAXCARATTERI];
    int j, nPOI, scelta;
    POI *vettore;
    int contatore = 1;
    FILE *fileTesto = NULL;

    printf("\n-Inserisci il nome del comune di cui si vogliono visualizzare i POI: ");
    getchar();
    scanf("%[^\n]s", comune);

    ///apro il file in modalità lettura, salvo sulla variabile nPOI e su un vettore tutti gli elementi del file
    file = apriCtrlFile(nomeFile, "rb");
    rewind(file);
    fread(&nPOI, sizeof(int), 1, file);

    fseek(file, sizeof(int), SEEK_SET);

    vettore = (POI *) malloc(sizeof(POI) * nPOI);
    fread(vettore, sizeof(POI), nPOI, file);

    fclose(file);

    ///stampo il POI solo se il suo comune di afferenza è uguale al comune inserito dall'utente
    for (j = 0; j < nPOI; j++) {
        if (compNoCaseSensitive(vettore[j].comune, comune) == 0) {
            printf("\nPOI numero %d", contatore);
            stampaPOI(vettore[j]);
            contatore++;
        }
    }
    printf("\nSono stati trovati %d POI appartenenti a questo comune\n", contatore - 1);

    ///chiedo all'utente se vuole ordinare i poi appena trovati e stampo a video in caso di risposta affermativa
    if (contatore - 1 > 0) {
        contatore = 1;
        if (ordinaCrescDecresc(vettore, nPOI) == 0) { ///stampo il vettore solo se si è scelto di ordinarlo
            for (j = 0; j < nPOI; j++) {
                if (compNoCaseSensitive(vettore[j].comune, comune) == 0) {
                    printf("\nPOI numero %d", contatore);
                    stampaPOI(vettore[j]);
                    contatore++;
                }
            }
        }

        ///chiedo se si vuole trascrivere su un file di testo i risultati della ricerca
        do {
            printf("\nSi vuole trascrivere su un file di testo i risultati della ricerca appena effettuata?"
                   "\nSi (premi 1)"
                   "\nNo (premi 2)\n");
            scanf("%d", &scelta);
        } while (scelta < 1 || scelta > 2);

        /**
         * se la risposta è affermativa apro il file di testo il scrittura (cancellando eventuali ricerche passate) e
         * stampando la ricerca fatta
         */
        if (scelta == 1) {

            fileTesto = apriCtrlFile("RisultatiRicerca.txt", "w");

            for (j = 0; j < nPOI; j++) {
                if (compNoCaseSensitive(vettore[j].comune, comune) == 0) {
                    stampaSuFileDiTesto(fileTesto, vettore[j]);
                }
            }
            printf("\n/////File di testo creato correttamente/////\n");
        }
    }
    free(vettore);
    fclose(fileTesto);
}


/*!
 * ricerca di una serie di POI conoscendone la categoria
 * @param nomeFile
 */
void poiPerCategoria(char nomeFile[]) {
    FILE *file = NULL;
    int categoria;
    int j, scelta;
    POI *vettore;
    int nPOI;
    int contatore = 1;
    FILE *fileTesto = NULL;

    ///l'utente inserisce la categoria di appartenenza dei POI che vuole visualizzare
    do {
        printf("\nInserisci il numero indicante la categoria di cui si desidera vedere i POI"
               "\n(Spiaggia(1), monumento(2), parco(3), lago(4), grotta(5), museo(6), belvedere(7), altro(8)):");
        scanf("%d", &categoria);
    } while (categoria < 1 || categoria > 8);

    ///apro il file in modalità lettura, salvo sulla variabile nPOI e su un vettore tutti gli elementi del file
    file = apriCtrlFile(nomeFile, "rb");
    rewind(file);
    fread(&nPOI, sizeof(int), 1, file);

    fseek(file, sizeof(int), SEEK_SET);

    vettore = (POI *) malloc(sizeof(POI) * nPOI);
    fread(vettore, sizeof(POI), nPOI, file);

    fclose(file);
    ///stampo il POI solo se la sua categoria di appartenenza è uguale alla categoria inserita dall'utente
    for (j = 0; j < nPOI; j++) {
        if (vettore[j].categoria == categoria) {
            printf("\nPOI numero %d", contatore);
            stampaPOI(vettore[j]);
            contatore++;
        }
    }

    printf("\nSono stati trovati %d POI appartenenti a questa categoria\n", contatore - 1);

    ///chiedo all'utente se vuole ordinare i poi appena trovati e stampo a video in caso di risposta affermativa
    if (contatore - 1 > 0) {
        contatore = 1;
        if (ordinaCrescDecresc(vettore, nPOI) == 0) { ///stampo il vettore solo se si è scelto di ordinarlo
            for (j = 0; j < nPOI; j++) {
                if (vettore[j].categoria == categoria) {
                    printf("\nPOI numero %d", contatore);
                    stampaPOI(vettore[j]);
                    contatore++;
                }
            }
        }

        do {
            printf("\nSi vuole trascrivere su un file di testo i risultati della ricerca appena effettuata?"
                   "\nSi (premi 1)"
                   "\nNo (premi 2)\n");
            scanf("%d", &scelta);
        } while (scelta < 1 || scelta > 2);

        /**
         * se la risposta è affermativa apro il file di testo il scrittura (cancellando eventuali ricerche passate) e
         * stampando la ricerca fatta
         */
        if (scelta == 1) {

            fileTesto = apriCtrlFile("RisultatiRicerca.txt", "w");

            for (j = 0; j < nPOI; j++) {
                if (vettore[j].categoria == categoria) {
                    stampaSuFileDiTesto(fileTesto, vettore[j]);
                }
            }
            printf("\n/////File di testo creato correttamente/////\n");
        }
    }
    free(vettore);
    fclose(fileTesto);
}

/*!
 * Procedura per la ricerca di una serie di POI sulla base di una keyword
 * @param nomeFile
 */
void poiPerKeyword(char nomeFile[]) {
    FILE *file = NULL;
    char keyword[21];
    int j, scelta;
    POI *vettore;
    int nPOI;
    int contatore = 1;
    FILE* fileTesto = NULL;

    ///chiedo all'utente di inserire una keyword, poi apro il file in lettura e salvo su una variabile e su un vettore
    ///tutte le informazioni
    printf("\nInserisci la keyword da ricercare tra i POI: ");
    scanf("%s", keyword);

    file = apriCtrlFile(nomeFile, "rb");
    rewind(file);
    fread(&nPOI, sizeof(int), 1, file);

    fseek(file, sizeof(int), SEEK_SET);

    vettore = (POI *) malloc(sizeof(POI) * nPOI);
    fread(vettore, sizeof(POI), nPOI, file);

    fclose(file);

    ///stampo il POI solo se la keyword inserita dall'utente è contenuta nella descrizione del POI stesso
    for (j = 0; j < nPOI; j++) {
        if (trovaParola(keyword, vettore[j].info) == 1) {
            printf("\nPOI numero %d", contatore);
            stampaPOI(vettore[j]);
            contatore++;
        }
    }
    printf("\nSono stati trovati %d POI associati alla keyword '%s'\n", contatore - 1, keyword);

    ///chiedo all'utente se vuole ordinare i poi appena trovati e stampo a video in caso di risposta affermativa
    if (contatore - 1 > 0) {
        contatore = 1;
        if (ordinaCrescDecresc(vettore, nPOI) == 0) { ///stampo il vettore solo se si è scelto di ordinarlo
            for (j = 0; j < nPOI; j++) {
                if (trovaParola(keyword, vettore[j].info) == 1) {
                    printf("\nPOI numero %d", contatore);
                    stampaPOI(vettore[j]);
                    contatore++;
                }
            }
        }

        ///chiedo se si vuole trascrivere su un file di testo i risultati della ricerca
        do {
            printf("\nSi vuole trascrivere su un file di testo i risultati della ricerca appena effettuata?"
                   "\nSi (premi 1)"
                   "\nNo (premi 2)\n");
            scanf("%d", &scelta);
        } while (scelta < 1 || scelta > 2);

        /**
         * se la risposta è affermativa apro il file di testo il scrittura (cancellando eventuali ricerche passate) e
         * stampando la ricerca fatta
         */
        if (scelta == 1) {

            fileTesto = apriCtrlFile("RisultatiRicerca.txt", "w");

            for (j = 0; j < nPOI; j++) {
                if (trovaParola(keyword, vettore[j].info) == 1) {
                    stampaSuFileDiTesto(fileTesto, vettore[j]);
                }
            }
            printf("\n/////File di testo creato correttamente/////\n");
        }
    }
    free(vettore);
    fclose(fileTesto);
}



/*!
 * procedura per la ricerca di un poi dato un certo raggio definito dall'utente
 * @param nomeFile
 */
void poiPerRaggio(char nomeFile[]) {
    double latitudine, longitudine;
    float raggio;
    FILE *file = NULL;
    int nPOI, j, scelta;
    int contatore = 1;
    POI *vettore;
    FILE *fileTesto = NULL;

    ///chiedo all'utente di inserire le coordinate geografiche e il raggio all'interno del quale cercare
    do {
        printf("\nInserisci la latitudine del centro del cerchio (usa i punti al posto delle virgole): ");
        scanf("%lf", &latitudine);
        if (latitudine < MINLATITUDINE || latitudine > MAXLATITUDINE)
            printf("Attenzione, la latitudine deve essere compresa tra 38.8644444 e 41.2616667");
    } while (latitudine < MINLATITUDINE || latitudine > MAXLATITUDINE);

    do {
        printf("\nInserisci la longitudine del centro del cerchio (usa i punti al posto delle virgole): ");
        scanf("%lf", &longitudine);
        if (longitudine < MINLONGITUDINE || longitudine > MAXLONGITUDINE)
            printf("Attenzione, la longitudine deve essere compresa tra 8.133333333333333 e 9.833333333333334");
    } while (longitudine < MINLONGITUDINE || longitudine > MAXLONGITUDINE);

    do {
        printf("\nInserisci il raggio entro cui cercare i POI (km): ");
        scanf("%f", &raggio);
        if (raggio <= 0)
            printf("Inserisci un raggio almeno pari a 1km");
    } while (raggio <= 0);

    ///apro il file in lettura e salvo su una variabile e su un vettore tutte le sue informazioni
    file = apriCtrlFile(nomeFile, "rb");
    rewind(file);
    fread(&nPOI, sizeof(int), 1, file);

    fseek(file, sizeof(int), SEEK_SET);

    vettore = (POI *) malloc(sizeof(POI) * (int) nPOI);
    fread(vettore, sizeof(POI), nPOI, file);

    fclose(file);

    ///stampo il POI solo se la sua posizione è entro il raggio definito dall'utente
    for (j = 0; j < nPOI; j++) {
        if (trovaPunto(latitudine, longitudine, raggio, vettore[j]) == 1) {
            printf("\nPOI numero %d", contatore);
            stampaPOI(vettore[j]);
            contatore++;
        }
    }

    printf("\nSono stati trovati %d POI entro questo raggio\n", contatore - 1);

    ///chiedo all'utente se vuole ordinare i poi appena trovati e stampo a video in caso di risposta affermativa
    if (contatore - 1 > 0) {
        contatore = 1;
        if (ordinaCrescDecresc(vettore, nPOI) == 0) { ///stampo il vettore solo se si è scelto di ordinarlo
            for (j = 0; j < nPOI; j++) {
                if (trovaPunto(latitudine, longitudine, raggio, vettore[j]) == 1) {
                    printf("\nPOI numero %d", contatore);
                    stampaPOI(vettore[j]);
                    contatore++;
                }
            }
        }

        do {
            printf("\nSi vuole trascrivere su un file di testo i risultati della ricerca appena effettuata?"
                   "\nSi (premi 1)"
                   "\nNo (premi 2)\n");
            scanf("%d", &scelta);
        } while (scelta < 1 || scelta > 2);

        /**
         * se la risposta è affermativa apro il file di testo il scrittura (cancellando eventuali ricerche passate) e
         * stampando la ricerca fatta
         */
        if (scelta == 1) {

            fileTesto = apriCtrlFile("RisultatiRicerca.txt", "w");

            for (j = 0; j < nPOI; j++) {
                if (trovaPunto(latitudine, longitudine, raggio, vettore[j]) == 1) {
                    stampaSuFileDiTesto(fileTesto, vettore[j]);
                }
            }
            printf("\n/////File di testo creato correttamente/////\n");
        }
    }
    free(vettore);
    fclose(fileTesto);
}


/*!
 * procedura per la ricerca di un poi data una certa altitudine
 */
void poiPerAltitudine(char nomeFile[]) {
    int scelta, scelta2;
    FILE *file = NULL;
    int nPOI, j;
    int contatore = 1;
    POI *vettore;
    FILE *fileTesto = NULL;

    ///chiedo all'utente di specificare l'altitudine dei POI che vuole visualizzare
    do {
        printf("\nVuoi cercare poi in pianura (premi 1), collina (premi 2) o montagna(premi 3)?\n");
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 3);

    ///apro il file in lettura e salvo su una variabile e su un vettore tutte le sue informazioni
    file = apriCtrlFile(nomeFile, "rb");
    rewind(file);
    fread(&nPOI, sizeof(int), 1, file);

    fseek(file, sizeof(int), SEEK_SET);

    vettore = (POI *) malloc(sizeof(POI) * (int) nPOI);
    fread(vettore, sizeof(POI), nPOI, file);

    fclose(file);

    ///a seconda della scelta effettuata stampo solo i POI che appartengono alla categoria selezionata dall'utente
    if (scelta == 1) {
        for (j = 0; j < nPOI; j++) {
            if (vettore[j].altitudine >= 0 && vettore[j].altitudine <= 50) {
                printf("\nPOI numero %d", contatore);
                stampaPOI(vettore[j]);
                contatore++;
            }
        }
    }
    if (scelta == 2) {
        for (j = 0; j < nPOI; j++) {
            if (vettore[j].altitudine > 50 && vettore[j].altitudine <= 800) {
                printf("\nPOI numero %d", contatore);
                stampaPOI(vettore[j]);
                contatore++;
            }
        }
    }
    if (scelta == 3) {
        for (j = 0; j < nPOI; j++) {
            if (vettore[j].altitudine > 800) {
                printf("\nPOI numero %d", contatore);
                stampaPOI(vettore[j]);
                contatore++;
            }
        }
    }

    printf("\nSono stati trovati %d POI appartenenti a questa categoria\n", contatore - 1);


    ///chiedo all'utente se vuole ordinare i poi appena trovati e stampo a video in caso di risposta affermativa
    if (contatore - 1 > 0) {

        ///se si è selezionato PIANURA
        if (scelta == 1) {
            if (ordinaCrescDecresc(vettore, nPOI) == 0) { ///stampo il vettore solo se si è scelto di ordinarlo
                for (j = 0; j < nPOI; j++) {
                    if (vettore[j].altitudine >= 0 && vettore[j].altitudine <= 50) {
                        printf("\nPOI numero %d", contatore);
                        stampaPOI(vettore[j]);
                    }
                }
            }


            do {
                printf("\nSi vuole trascrivere su un file di testo i risultati della ricerca appena effettuata?"
                       "\nSi (premi 1)"
                       "\nNo (premi 2)\n");
                scanf("%d", &scelta2);
            } while (scelta2 < 1 || scelta2 > 2);

            /**
            * se la risposta è affermativa apro il file di testo il scrittura (cancellando eventuali ricerche passate) e
            * stampando la ricerca fatta
            */
            if (scelta2 == 1) {
                fileTesto = apriCtrlFile("RisultatiRicerca.txt", "w");

                for (j = 0; j < nPOI; j++) {
                    if (vettore[j].altitudine >= 0 && vettore[j].altitudine <= 50) {
                        stampaSuFileDiTesto(fileTesto, vettore[j]);
                    }
                }
                printf("\n/////File di testo creato correttamente/////\n");
            }
        }

        ///se si è selezionato COLLINA
        if (scelta == 2) {
            if (ordinaCrescDecresc(vettore, nPOI) == 0) { ///stampo il vettore solo se si è scelto di ordinarlo
                for (j = 0; j < nPOI; j++) {
                    if (vettore[j].altitudine > 50 && vettore[j].altitudine <= 800) {
                        printf("\nPOI numero %d", contatore);
                        stampaPOI(vettore[j]);
                    }
                }
            }
            do {
                printf("\nSi vuole trascrivere su un file di testo i risultati della ricerca appena effettuata?"
                       "\nSi (premi 1)"
                       "\nNo (premi 2)\n");
                scanf("%d", &scelta2);
            } while (scelta2 < 1 || scelta2 > 2);


            /**
            * se la risposta è affermativa apro il file di testo il scrittura (cancellando eventuali ricerche passate) e
            * stampando la ricerca fatta
            */
            if (scelta2 == 1) {
                fileTesto = apriCtrlFile("RisultatiRicerca.txt", "w");

                for (j = 0; j < nPOI; j++) {
                    if (vettore[j].altitudine > 50 && vettore[j].altitudine <= 800) {
                        stampaSuFileDiTesto(fileTesto, vettore[j]);
                    }
                }
                printf("\n/////File di testo creato correttamente/////\n");
            }

        }

        ///se si è selezionato MONTAGNA
        if (scelta == 3) {
            if (ordinaCrescDecresc(vettore, nPOI) == 0) { ///stampo il vettore solo se si è scelto di ordinarlo
                for (j = 0; j < nPOI; j++) {
                    if (vettore[j].altitudine > 800) {
                        printf("\nPOI numero %d", contatore);
                        stampaPOI(vettore[j]);
                    }
                }
            }

            do {
                printf("\nSi vuole trascrivere su un file di testo i risultati della ricerca appena effettuata?"
                       "\nSi (premi 1)"
                       "\nNo (premi 2)\n");
                scanf("%d", &scelta2);
            } while (scelta2 < 1 || scelta2 > 2);

            /**
            * se la risposta è affermativa apro il file di testo il scrittura (cancellando eventuali ricerche passate) e
            * stampando la ricerca fatta
            */
            if (scelta2 == 1) {
                fileTesto = apriCtrlFile("RisultatiRicerca.txt", "w");

                for (j = 0; j < nPOI; j++) {
                    if (vettore[j].altitudine > 800) {
                        stampaSuFileDiTesto(fileTesto, vettore[j]);
                    }
                }
                printf("\n/////File di testo creato correttamente/////\n");
            }
        }
        ///libero la memoria allocata e chiudo il file di testo
        free(vettore);
        fclose(fileTesto);
    }
}



/*!
 * Procedura di ricerca standard e avanzata di un POI (menu' iniziale + diramazioni a seconda delle
 * scelte dell'utente
 * @param nomeFile
 */
void cercaPOI(char nomeFile[]){
    int scelta;

    ///ciclo per decisione del tipo di ricerca che si desidera fare
    do {
        printf("\nChe tipo di ricerca vuoi fare?"
               "\n-Standard --> ovvero per comune, categoria o keyword (premi 1)"
               "\n-Avanzata --> ovvero entro un certo raggio o per altitudine (premi 2)\n");
        scanf("%d", &scelta);
        if (scelta < 1 || scelta > 2)
            printf("\n___inserisci un numero tra 1 e 2___");
    } while (scelta < 1 || scelta > 2);

    ///se si vuole fare una ricerca standard
    if (scelta == 1){
        do {
            printf("\n-Cosa si vuole cercare?"
                   "\n-Comune (premi 1)"
                   "\n-Categoria (premi 2)"
                   "\n-Parola chiave (premi 3)\n");
            scanf("%d", &scelta);
        }while (scelta < 1 || scelta > 3);

        if (scelta == 1)
            poiPerComune(nomeFile);

        else if (scelta == 2)
            poiPerCategoria(nomeFile);

        else if (scelta == 3)
            poiPerKeyword(nomeFile);
    }

    ///se si è scelta la ricerca avanzata
    if (scelta == 2){

        do {
            printf("\nIn quale area si desidera cercare?"
                   "\n-Entro una circonferenza di cui si dovranno specificare posizione del centro e raggio (premi 1)"
                   "\n-Entro una certa altitudine (premi 2)\n");
            scanf("%d", &scelta);
        }while (scelta < 1 || scelta > 2);
        if (scelta == 1)
            poiPerRaggio(nomeFile);
        else
            poiPerAltitudine(nomeFile);
    }
}
