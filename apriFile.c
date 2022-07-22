//
// Created by gianm on 06/02/2020.
//

#include "LibreriaAusilio.h"
#include "cercaPoi.h"
#include "apriFile.h"
#include "assemblaggio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * Domando all'utente se vuole aggiornare il file con gli ultimi POI aggiunti
 * @param numero di POI da aggiungere al file
 * @param vettore contenente le informazioni da aggiungere
 */
void aggiornaAggiunta(POI vettore[], char nomeFile[]) {
    FILE *file = NULL;
    int scelta;
    int POItotali;
    int i;

    ///chiedo se si vuole aggiornare il file
    do {
        printf("\nSi vuole aggiornare il file con le ultime modifiche?"
               "\nSi (premi 1)"
               "\nNo (premi 2)\n");
        scanf("%d", &scelta);
    } while (scelta < 1 || scelta > 2);

    if (scelta == 1) {
        ///Apro il file in lettura e calcolo il nuovo numero di POI totali che saranno contenuti nel file stesso
        file = apriCtrlFile(nomeFile, "rb");
        fread(&POItotali, sizeof(int), 1, file);

        ///Se i file era vuoto elimino qualche passaggio senza bisogno di allocare memoria aggiuntiva
        if (POItotali == 0) {
            POItotali = 1;
            file = apriCtrlFile(nomeFile, "wb");
            fwrite(&POItotali, sizeof(int), 1, file);
            fseek(file, sizeof(int), SEEK_SET);
            fwrite(vettore, sizeof(POI), POItotali, file);
            fclose(file);
            free(vettore);
            printf("///FILE AGGIORNATO///\n");
        }

            ///Se il file non era vuoto rialloco memoria, poi cancello e sovrascrivo il file
        else {
            POItotali += 1;

            ///rialloco il vettore con il numero di celle di POI totali e mi sposto oltre i primi 4 bytes del file
            vettore = realloc(vettore, POItotali * sizeof(POI));
            fseek(file, sizeof(int), SEEK_SET);

            ///aggiungo al vettore con i POI inizializzati dall'utente anche i vecchi POI e chiudo il file
            for (i = 0; i < (POItotali - 1); i++)
                fread(&vettore[i + 1], sizeof(POI), 1, file);
            fclose(file);

            ///riapro il file in scrittura (resettandolo) e riscrivo le informazioni aggiornate, chiudo il file e
            /// dealloco la memoria
            file = apriCtrlFile(nomeFile, "wb");
            fwrite(&POItotali, sizeof(int), 1, file);

            for (i = 0; i < POItotali; i++) {
                fseek(file, 0L, SEEK_END);
                fwrite(&vettore[i], sizeof(POI), 1, file);
            }

            fclose(file);
            free(vettore);
            printf("///FILE AGGIORNATO///\n");
        }

    } else if (scelta == 2)
        printf("\nFILE NON AGGIORNATO");
}

/*!
 * Aggiunge 1 POI in testa a un file specificato dall'utente
 * @param nomeFile
 */
void aggiungiPOI(char nomeFile[]) {
    ///Dichiarazione delle variabili/vettori/puntatori
    POI *vettore;
    POI poi;

    ///allocamento su vettore, inizializzazione e assegnamento del numero di POI scelti dall'utente
    vettore = (POI *) malloc(sizeof(POI) * 1);

    vettore[0] = inizializzaPOI(poi);

    ///Domando all'utente se vuole aggiornare il file con gli ultimi POI aggiunti
    aggiornaAggiunta(vettore, nomeFile);
}


/*!
 * Procedura per l'apertura e la modifica di un file
 * @param nomeFile
 */
void apriFile(char nomeFile[]) {
    int scelta;

    ///ciclo per scelta (aggiunta/ricerca di un POI)
    do {
        printf("\nScegli un'azione:"
               "\n-Aggiungi POI (premi 1)"
               "\n-Cercare un POI gia' esistente (premi 2)\n");
        scanf("%d", &scelta);
        if (scelta < 1 || scelta > 2)
            printf("\n___inserisci un numero tra 1 e 2___");
    } while (scelta < 1 || scelta > 2);

    if (scelta == 1)
        aggiungiPOI(nomeFile);
    else if (scelta == 2) {
        cercaPOI(nomeFile);
    }
}


/*!
 * funzione per l'inizializzazione di un POI da parte dell'utente
 * @param poi (passo alla funzione una struttura POI)
 * @return il punto di interesse inizializzato
 */
POI inizializzaPOI(POI poi) {
    printf("\nInserisci il nome del POI (max 63 caratteri): ");
    getchar();
    scanf("%[^\n]s", poi.nomePOI);
    do {
        printf("\nInserisci la latitudine a cui si trova il POI (usa i punti al posto delle virgole): ");
        scanf("%lf", &poi.latitudine);
        if (poi.latitudine < MINLATITUDINE || poi.latitudine > MAXLATITUDINE)
            printf("Attenzione, la latitudine deve essere compresa tra 38.8644444 e 41.2616667");
    }while (poi.latitudine < MINLATITUDINE || poi.latitudine > MAXLATITUDINE);
    do {
        printf("\nInserisci la longitudine a cui si trova il POI (usa i punti al posto delle virgole): ");
        scanf("%lf", &poi.longitudine);
        if (poi.longitudine < MINLONGITUDINE || poi.longitudine > MAXLONGITUDINE)
            printf("Attenzione, la longitudine deve essere compresa tra 8.133333333333333 e 9.833333333333334");
    }while (poi.longitudine < MINLONGITUDINE || poi.longitudine > MAXLONGITUDINE);
    do {
        printf("\nInserisci l'altitudine a cui si trova il POI (usa i punti al posto delle virgole): ");
        scanf("%lf", &poi.altitudine);
        if (poi.altitudine < MINALTITUDINE || poi.altitudine > MAXALTITUDINE)
            printf("Attenzione, l'altitudine deve essere compresa tra 0 e 1834");
    }while (poi.altitudine < MINALTITUDINE || poi.altitudine > MAXALTITUDINE);
    printf("\nInserisci comune di afferenza (max 63 caratteri): ");
    getchar();
    scanf("%[^\n]s", poi.comune);
    do {
        printf("\nInserisci il numero indicante la categoria di appartenenza"
               "\n(Spiaggia(1), monumento(2), parco(3), lago(4), grotta(5), museo(6), belvedere(7), altro(8)):");
        scanf("%d", &poi.categoria);
    }while (poi.categoria < 1 || poi.categoria > 8);
    printf("\nInserisci una breve descrizione del POI (max 255 caratteri): ");
    getchar();
    scanf("%[^\n]s", poi.info);

    return poi;
}


/**
 * Apre ed esegue tutti i controlli quando si apre un file
 * @param nomeFile nome del file da aprire
 * @param mode modalità di apertura del file
 * @return puntatore al file aperto
 */
FILE *apriCtrlFile(char *nomeFile, char *mode) {
    FILE *fp = fopen(nomeFile, mode);

    if (fp == NULL) {
        printf("\nC'e' stato un problema nell'apertura del file\n\n");
        start(nomeFile);
    }
    return fp;
}


/*!
 * Procedura di stampa di un intero file
 * @param nomeFile
 */
void stampaFile(char nomeFile[]){
    FILE* file;
    POI* vettore;
    int nPOI;
    int i;

    ///Apro il file e verifico quanti POI sono presenti, alloco memoria in funzione del numero di POI
    file = apriCtrlFile(nomeFile, "rb");
    fread(&nPOI, sizeof(int), 1, file);

    vettore = (POI*)malloc(sizeof(POI) * nPOI);

    ///Mi sposto di 4 bytes olte l'inizio del file e salvo su vettore tutti i POI presenti
    fseek(file, sizeof(int), SEEK_SET);
    fread(vettore, sizeof(POI), nPOI, file);

    ///Stampo il numero di POI totali e a seguire i POI stessi
    printf("\n/////////////////////////"
           "\n//// POI totali: %d ////"
           "\n////////////////////////\n", nPOI);
    for (i = 0; i < nPOI; i++){
        stampaPOI(vettore[i]);
    }

    fclose(file);

    ///chiedo all'utente se vuole apportare modifiche ai POI appena trovati
    if (nPOI > 0)
        chiediModifica(nomeFile, vettore, nPOI);
}


/*!
 * verifica che un file esista effettivamente (impedisce di provare ad aprire un file inesistente)
 * @param nomeFile
 * @return esiste = 1 se il file può essere aperto in lettura, dunque se esiste un file con quel nome
 */
int verificaNomeFile(char nomeFile[]){
    FILE* file;
    int esiste;

    file = fopen(nomeFile, "rb");
    if (file == NULL)
        esiste = 0;
    else
        esiste = 1;
    fclose(file);

    return esiste;
}


/*!
 * Procedura per la creazione di un file
 * @param nomeFile
 */
void creaFile(char nomeFile[]) {
    FILE *file = NULL;
    int valoreIniziale = 0;

    ///creazione del file
    file = apriCtrlFile(nomeFile, "w+b");
    fwrite(&valoreIniziale, sizeof(int), 1, file);
    fclose(file);
    printf("\n/////File creato con successo/////\n");
}


/*!
 * Procedura che organizza un vettore di POI in ordine alfabetico
 * @param vettore
 * @param nPoi
 * @return 0 se si vuole riordinare in qualche modo il vettore di POI
 */
int ordinaCrescDecresc(POI vettore[], int nPoi) {
    int i, j;
    int comparazione;
    POI sostegno;
    int scelta;

    printf("\nSi vogliono ordinare i POI appena ottenuti in ordine alfabetico?"
           "\nSi, dalla A alla Z (premi 1)"
           "\nSi, dalla Z alla A (premi 2)"
           "\nNo (premi 3)\n");
    scanf("%d", &scelta);

    if (scelta == 1) {
        ///Fin quando una stringa sarà maggiore della sua successiva queste due si scambieranno di posto
        for (j = 0; j < nPoi; j++) {
            for (i = 0; i < nPoi - 1 - j; i++) {
                comparazione = strcmp(vettore[i].nomePOI, vettore[i + 1].nomePOI);
                if (comparazione > 0) {
                    sostegno = vettore[i + 1];
                    vettore[i + 1] = vettore[i];
                    vettore[i] = sostegno;
                }
            }
        }
        return 0;
    }
    else if (scelta == 2){
        ///Fin quando una stringa sarà minore della sua successiva queste due si scambieranno di posto
        for (j = 0; j < nPoi; j++) {
            for (i = 0; i < nPoi - 1 - j; i++) {
                comparazione = strcmp(vettore[i].nomePOI, vettore[i + 1].nomePOI);
                if (comparazione < 0) {
                    sostegno = vettore[i + 1];
                    vettore[i + 1] = vettore[i];
                    vettore[i] = sostegno;
                }
            }
        }
        return 0;
    }
}

