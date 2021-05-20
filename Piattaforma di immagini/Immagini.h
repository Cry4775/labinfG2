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
    int id;
    char titolo[MAX_BUFFER];
    char categoria[MAX_BUFFER];
    char tags[MAX_TAGS][MAX_BUFFER];
    char nomeUtente[MAX_BUFFER];
    char formato[MAX_BUFFER];
    char tipologia[MAX_BUFFER];
    char nomeFile[MAX_BUFFER]; // titolo + formato
    unsigned int valutazione;
    float valutazioneMedia;
    unsigned int numDownload;
    float dimensione;
    Risoluzione_t risoluzione;
    Data_t dataCaricamento;
} Immagine_t;

void SalvaDatiImmagine(FILE* file, Immagine_t* immagine);

void InserisciDatiImmagine(Immagine_t* immagine, char nomeUtente[]);

bool ModificaImmagini(FILE* file, char nomeUtente[]);

void StampaTagsImmagine(Immagine_t immagine);

void StampaCategorieDisponibili();

void StampaTagsDisponibili();

void InserisciTagsCaricamento(Immagine_t** immagine);

void InserisciTags(Immagine_t* immagine);       //aggiungi MODIFICA nel nome

void InserisciCategoriaCaricamento(Immagine_t** immagine);

void InserisciCategoria(Immagine_t* immagine);  //aggiungi MODIFICA nel nome

bool StampaImmaginiCaricate(FILE* file, char nomeUtente[]);

bool RimuoviImmagine(FILE* file, char nomeUtente[]);

#endif