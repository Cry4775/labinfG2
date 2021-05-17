#ifndef _IMMAGINI_H_
#define _IMMAGINI_H_

#include "Utility.h"

#define NUM_FORMATI 8
#define NUM_CATEGORIE 7
#define NUM_TAGS 21

#define MAX_TAGS 3

#define PERCORSO_FILE_IMMAGINI "immagini/immagini.dat"

extern const char* formato[NUM_FORMATI];
extern const char* tipologia[NUM_FORMATI];
extern const char* categoria[NUM_CATEGORIE];
extern const char* tags[NUM_TAGS];

typedef struct
{
    unsigned int x;
    unsigned int y;
} Risoluzione_t;

typedef struct
{
    char* titolo;
    char* categoria;
    char* tags[MAX_TAGS];
    
    char* nomeUtente;
    char* formato;
    char* tipologia;
    char* nomeFile; // titolo + formato
    unsigned int valutazione;
    float valutazioneMedia;
    unsigned int numDownload;
    float dimensione;
    Risoluzione_t risoluzione;
    Data_t dataCaricamento;
} Immagine_t;

void SalvaDatiImmagine(FILE* file, Immagine_t* immagine);


#endif