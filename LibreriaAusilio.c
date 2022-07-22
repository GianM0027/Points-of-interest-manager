//
// Created by gianm on 27/02/2020.
//

#include "apriFile.h"
#include "assemblaggio.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*!
 * Funzione che compara due stringhe (case insensitive)
 * @param stringa1 Prima stringa
 * @param stringa2 Seconda stringa
 * @return comparazione = 0 se le stringhe sono uguali, un altro valore se sono diverse
 */
int compNoCaseSensitive(char stringa1[], char stringa2[]) {
    int comparazione;
    int i;
    char a, b, c, d;

    ///faccio in modo che le due stringhe diventino completamente maiuscole prima del confronto
    for (i = 0; i < 64; i++) {
        a = stringa1[i];
        if (a > 96 && a < 123)
            a -= 32;
        stringa1[i] = a;
    }

    for (i = 0; i < 64; i++) {
        b = stringa2[i];
        if (b > 96 && b < 123)
            b -= 32;
        stringa2[i] = b;
    }

    ///confronto le due stringhe
    comparazione = strcmp(stringa1, stringa2);

    ///riporto le due stringhe alla normalità (la prima lettera resta maiuscola)
    for (i = 1; i < 64; i++) {
        c = stringa1[i];
        if (c > 64 && c < 91)
            c += 32;
        stringa1[i] = c;
    }

    for (i = 1; i < 64; i++) {
        d = stringa2[i];
        if (d > 64 && d < 91)
            d += 32;
        stringa2[i] = d;
    }

    return comparazione;
}




/*!
 * Funzione di stampa di un singolo POI
 * @param punto di interesse
 */
void stampaPOI(POI poi){
    printf("\nNome del POI: %s", poi.nomePOI);
    printf("\nLatitudine: %lf", poi.latitudine);
    printf("\nLongitudine: %lf", poi.longitudine);
    printf("\nAltitudine: %lf", poi.altitudine);
    printf("\nComune di afferenza: %s", poi.comune);
    printf("\nCategoria: ", poi.categoria);
    switch (poi.categoria){
        case 1: printf("spiaggia");
            break;
        case 2: printf("monumento");
            break;
        case 3: printf("parco");
            break;
        case 4: printf("lago");
            break;
        case 5: printf("grotta");
            break;
        case 6: printf("museo");
            break;
        case 7: printf("belvedere");
            break;
        case 8: printf("altro");
            break;
    }
    printf("\nDescrizione: %s\n", poi.info);
}



/*!
 * procedura per l'aggiornamento di un file a seguito della modifica di un POI
 * @param nomeFile
 * @param vettore contenente i POI da modificare
 * @param numPoi numero di elementi contenuti nel vettore
 */
void aggiornaModifica(char nomeFile[], POI vettore[], int numPoi){
    int scelta;
    FILE* file = NULL;
    int i;

    ///chiedo all'utente se vuole aggiornare il file
    do {
        printf("\nSi vuole aggiornare il file con le ultime modifiche?"
               "\nSi (premi 1)"
               "\nNo (premi 2)\n");
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 2);

    ///apro il file in scrittura (resettandolo) e riscrivendo tutti i POI con le dovute modifiche
    if (scelta == 1){
        file = apriCtrlFile(nomeFile, "wb");
        fwrite(&numPoi, sizeof(int), 1, file);
        fseek(file, sizeof(int), SEEK_SET);
        for (i = 0; i < numPoi; i++){
            fwrite(&vettore[i], sizeof(POI), 1, file);
        }
        free(vettore);
        fclose(file);

        printf("///FILE AGGIORNATO///\n");
    } else{
        free(vettore);
        printf("\nFILE NON AGGIORNATO");
    }
}


/*!
 * Procedura per l'aggiornamento del file a seguito dell'eliminazione di un POI
 * @param nomeFile
 * @param vettore contenente tutti i POI appena trovati
 * @param cellaEliminazione cella del vettore da cancellare
 * @param numPoi Numero dei Poi dopo l'aggiornamento
 */
void aggiornaEliminazione(char nomeFile[], POI vettore[], int cellaEliminazione, int numPoi) {
    FILE *file = NULL;
    int i;
    int scelta;

    ///chiedo all'utente se vuole aggiornare il file
    do {
        printf("\nSi vuole aggiornare il file con le ultime modifiche?"
               "\nSi (premi 1)"
               "\nNo (premi 2)\n");
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 2);

    /*!
     * in caso di risposta affermativa la cella da cancellare prende il POI della sua successiva e così via fino alla
     *fine del vettore, alla fine rialloco la memoria per cancellare l'ultima cella del vettore
     */
    if (scelta == 1) {
        for (i = cellaEliminazione; i <= numPoi; i++)
            vettore[i] = vettore [i + 1];
        vettore = realloc(vettore, sizeof(POI)*numPoi);

        ///apro il file il scrittura (resettandolo) e riscrivo il nuovo vettore con un elemento in meno
        file = apriCtrlFile(nomeFile, "wb");
        fwrite(&numPoi, sizeof(int), 1, file);

        fseek(file, sizeof(int), SEEK_SET);
        for (i = 0; i < numPoi; i++)
            fwrite(&vettore[i], sizeof(POI), 1, file);

        free(vettore);
        fclose(file);

        printf("///FILE AGGIORNATO///\n");
    }
    else {
        free(vettore);
        printf("\nFILE NON AGGIORNATO");
    }
}


/*!
 * Funzione per la modifica di uno qualsiasi dei campi di un POI
 * @param poi
 * @return il punto di interesse con le modifiche apportate
 */
POI modificaCampo(POI poi) {
    int scelta;
    do {
        printf("\nIndica il numero del campo che vuoi modificare"
               "\n1)Nome"
               "\n2)Latitudine"
               "\n3)Longitudine"
               "\n4)Altitudine"
               "\n5)Comune di afferenza"
               "\n6)Categoria di appartenenza"
               "\n7)Descrizione del POI\n");
        scanf("%d", &scelta);
    }while (scelta < 1 || scelta > 7);

    switch (scelta) {
        case 1:
            printf("\nInserisci il nuovo nome del POI (max 63 caratteri): ");
            getchar();
            scanf("%[^\n]s", poi.nomePOI);
            break;
        case 2: do {
                printf("\nInserisci la nuova latitudine a cui si trova il POI (usa i punti al posto delle virgole): ");
                scanf("%lf", &poi.latitudine);
                if (poi.latitudine < MINLATITUDINE || poi.latitudine > MAXLATITUDINE)
                    printf("Attenzione, la latitudine deve essere compresa tra 38.8644444 e 41.2616667");
            }while (poi.latitudine < MINLATITUDINE || poi.latitudine > MAXLATITUDINE);
            break;
        case 3: do {
                printf("\nInserisci la nuova longitudine a cui si trova il POI (usa i punti al posto delle virgole): ");
                scanf("%lf", &poi.longitudine);
                if (poi.longitudine < MINLONGITUDINE || poi.longitudine > MAXLONGITUDINE)
                    printf("Attenzione, la longitudine deve essere compresa tra 8.133333333333333 e 9.833333333333334");
            }while (poi.longitudine < MINLONGITUDINE || poi.longitudine > MAXLONGITUDINE);
            break;
        case 4: do {
                printf("\nInserisci la nuova altitudine a cui si trova il POI (usa i punti al posto delle virgole): ");
                scanf("%lf", &poi.altitudine);
                if (poi.altitudine < MINALTITUDINE || poi.altitudine > MAXALTITUDINE)
                    printf("Attenzione, l'altitudine deve essere compresa tra 0 e 1834");
            }while (poi.altitudine < MINALTITUDINE || poi.altitudine > MAXALTITUDINE);
            break;
        case 5: printf("\nInserisci il nuovo comune di afferenza (max 63 caratteri): ");
            getchar();
            scanf("%[^\n]s", poi.comune);
            break;
        case 6: do {
                printf("\nInserisci il numero indicante la nuova categoria di appartenenza"
                       "\n(Spiaggia(1), monumento(2), parco(3), lago(4), grotta(5), museo(6), belvedere(7), altro(8)):");
                scanf("%d", &poi.categoria);
            }while (poi.categoria < 1 || poi.categoria > 8);
            break;
        case 7: printf("\nInserisci la nuova descrizione del POI (max 255 caratteri): ");
            getchar();
            scanf("%[^\n]s", poi.info);
    }
    return poi;
}


/*!
 * Procedura che chiede all'utente se si desidera modificare uno dei POI stampati a video
 * @param nomeFile -> nome del file aperto
 * @param vettore -> vettore su cui sono stati salvati i POI da file
 * @param nPoi -> numero di elementi del vettore
 */
void chiediModifica(char nomeFile[], POI vettore[], int numPoi){
    int scelta;
    int i;
    FILE* file = NULL;
    char nomePoi[MAXCARATTERI];

    do {
        printf("\nVuoi eliminare o modificare uno dei POI appena trovati?"
               "\nSi, modificare (premi 1)"
               "\nSi, eliminare (premi 2)"
               "\nNo (premi 3)\n");
        scanf("%d", &scelta);
    }while (scelta < 1 || scelta > 4);

    ///se si vuole modificare
    if (scelta == 1){
        printf("\nInserisci il nome del POI che si desidera modificare: ");
        getchar();
        scanf("%[^\n]s", nomePoi);

        for (i = 0; i < numPoi; i++){
            if (compNoCaseSensitive(vettore[i].nomePOI, nomePoi) == 0){
                vettore[i] = modificaCampo(vettore[i]);
                aggiornaModifica(nomeFile, vettore, numPoi);
                start(nomeFile);
            }
        }
    }

    ///se si vuole eliminare
    else if (scelta == 2){
        printf("\nInserisci il nome del POI che si desidera eliminare: ");
        getchar();
        scanf("%[^\n]s", nomePoi);

        for (i = 0; i < numPoi; i++){
            if (compNoCaseSensitive(vettore[i].nomePOI, nomePoi) == 0){
                aggiornaEliminazione(nomeFile, vettore, i, numPoi - 1);
            }
        }
    }
    else{
        free(vettore);
        fclose(file);
    }
}


/*!
 * funzione che date due stringhe vede se la prima è contenuta nella seconda
 * @param keyword
 * @param descrizione del POI
 * @return trovato = 1 se la keyword è contenuta almeno una volta nella descrizione
 */
int trovaParola(char keyword[], char descrizione[]){
    int i = -1, j = 1;
    int lunghKey = strlen(keyword);
    int lunghDescr = strlen(descrizione);
    int trovato = 0;

    ///scorro la descrizione del POI cercando congruenze con la keyword digitata dall'utente
    do {
        i++;
        if (descrizione[i] == keyword[0]){
            trovato = 1;
            while (j < lunghKey && trovato){
                if(descrizione[i + j] != keyword[j]){
                    trovato = 0;
                }
                else
                    j++;
            }
        }
    }while (i < (lunghDescr - lunghKey));

    return trovato;
}



/*!
 * Funzione per il calcolo della distanza tra due punti date le loro coordinate geografiche
 * @param lat latitudine definita dall'utente
 * @param longit longitudine definita dall'utente
 * @param raggio definito dell'utente
 * @param poi di cui si misurerà la distanza dalle coordinate definite dall'utente
 * @return 1 se il poi è interno all'area del cerchio definito dall'utente, 0 se è esterno
 */
int trovaPunto(double lat, double longit, float raggio, POI poi){
    double distanza;
    int raggioTerreste = 6371;

    double minlat, maxlat, minlong, maxlong;

    ///conversione coordinate da gradi a radianti per poter utilizzare la formula di calcolo della distanza
    minlat = lat * (2 * M_PI)/360;
    maxlat = poi.latitudine * (2 * M_PI)/360;
    minlong = longit  * (2 * M_PI)/360;
    maxlong = poi.longitudine  * (2 * M_PI)/360;

    ///calcolo della distanza tra le coordinate indicate dall'utente e quelle di un certo POI
    distanza = acos(sin(minlat) * sin(maxlat) + cos(minlat) * cos(maxlat) * cos(maxlong - minlong)) * raggioTerreste;

    if (distanza <= raggio)
        return 1;
    else if (distanza > raggio)
        return 0;
}

/*!
 * procedura per la stampa di un POI su un file di testo
 * @param fileTesto sul quale scrivere
 * @param poi Punto di interesse
 */
void stampaSuFileDiTesto(FILE* fileTesto, POI poi){

    fprintf(fileTesto, "\nNome del POI: %s", poi.nomePOI);
    fprintf(fileTesto, "\nLatitudine: %lf", poi.latitudine);
    fprintf(fileTesto, "\nLongitudine: %lf", poi.longitudine);
    fprintf(fileTesto, "\nAltitudine: %lf", poi.altitudine);
    fprintf(fileTesto, "\nComune di afferenza: %s", poi.comune);
    fprintf(fileTesto, "\nCategoria: ", poi.categoria);
    switch (poi.categoria) {
        case 1:
            fprintf(fileTesto, "spiaggia");
            break;
        case 2:
            fprintf(fileTesto, "monumento");
            break;
        case 3:
            fprintf(fileTesto, "parco");
            break;
        case 4:
            fprintf(fileTesto, "lago");
            break;
        case 5:
            fprintf(fileTesto, "grotta");
            break;
        case 6:
            fprintf(fileTesto, "museo");
            break;
        case 7:
            fprintf(fileTesto, "belvedere");
            break;
        case 8:
            fprintf(fileTesto, "altro");
            break;
    }
    fprintf(fileTesto, "\nDescrizione: %s\n", poi.info);
}