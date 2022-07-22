//
// Created by gianm on 07/02/2020.
//

#ifndef UNTITLED_ASSEMBLAGGIO_H
#define UNTITLED_ASSEMBLAGGIO_H

#define MAXCARATTERI 64 ///numero di caratteri massimi che può avere la stringa del nome del POI e del comune
#define MAXDESCRIZIONE 256 ///numero di caratteri massimi che può avere la descrizione di un POI
#define NOMEFILE 21 //////numero di caratteri massimi che può avere il nome del file deciso dall'utente

///minimo e massimo valore di LATITUDINE di un POI per rientrare nell'area di estensione della Sardegna
#define MINLATITUDINE 38.8644444
#define MAXLATITUDINE 41.2616667

///minimo e massimo valore di LONGITUDINE di un POI per rientrare nell'area di estensione della Sardegna
#define MINLONGITUDINE 8.133333333333333
#define MAXLONGITUDINE 9.833333333333334

///minimo e massimo valore di ALTITUDINE di un POI per rientrare nell'area di estensione della Sardegna
#define MINALTITUDINE 0
#define MAXALTITUDINE 1834

/*!
 * Definizione dell'enumerazione indicante a che categoria a cui appartiene un POI
 */
typedef enum {SPIAGGIA = 1, MONUMENTO, PARCO, LAGO, GROTTA, MUSEO, BELVEDERE, ALTRO} Categoria;


/*!
 * Definizione della struttura contenente le informazioni sul POI
 */
typedef  struct{
    char nomePOI[MAXCARATTERI];
    double latitudine;
    double longitudine;
    double altitudine;
    char comune[MAXCARATTERI];
    char info[MAXDESCRIZIONE];
    Categoria categoria;
}POI;


void start(char nomeFile[]);


#endif //UNTITLED_ASSEMBLAGGIO_H
