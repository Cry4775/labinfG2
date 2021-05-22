#ifndef _IMMAGINI_H_
#define _IMMAGINI_H_

#include "Utility.h"
#include "Utenti.h"

#define NUM_FORMATI 8
#define NUM_CATEGORIE 7
#define NUM_TAGS 21

#define MAX_TAGS 3

#define PERCORSO_FILE_IMMAGINI "immagini/immagini.dat"
#define PERCORSO_FILE_VALUTAZIONI "immagini/valutazioni.dat"

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
    unsigned int numValutazioni;
    float valutazioneMedia;
    unsigned int numDownload;
    float dimensione;
    Risoluzione_t risoluzione;
    Data_t dataCaricamento;
} Immagine_t;

// Struct per il salvataggio dell'elenco valutazioni
typedef struct
{
    char nomeUtenteValutatore[MAX_BUFFER];
    unsigned int valutazione;
    int idImmagineValutata;
} Valutazione_t;

/// <summary>
/// Questa procedura permette il salvataggio dei dati dell'immagine sul file delle immagini al momento del caricamento
/// </summary>
/// <param name="file">File delle immagini</param>
/// <param name="immagine">Struct dell'immagine</param>
void SalvaDatiImmagine(FILE* file, Immagine_t* immagine);

/// <summary>
/// Questa procedura permette l'inserimento dei dati dell'immagine al momento del caricamento
/// </summary>
/// <param name="immagine">Struct dell'immagine</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
void InserisciDatiImmagine(Immagine_t* immagine, char nomeUtente[]);

/// <summary>
/// Questa funzione permette la modifica delle immagini
/// </summary>
/// <param name="file">File delle immagini</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
/// <returns>Restituisce 1 se è andato a buon fine, 0 altrimenti</returns>
bool ModificaImmagini(FILE* file, char nomeUtente[]);

/// <summary>
/// Questa funzione permette la visualizzazione in elenco di tutte le immagini caricate dall'utente loggato nel menu creatore.
/// </summary>
/// <param name="file">File delle immagini</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
/// <returns>Restituisce 1 se è andato a buon fine, 0 altrimenti</returns>
bool StampaImmaginiCaricate(FILE* file, char nomeUtente[]);

/// <summary>
/// Questa funzione permette la rimozione dell'immagine selezionata nel menu creatore.
/// Sostituisce la porzione di file interessata con una struct vuota che verrà poi rimpiazzata
/// </summary>
/// <param name="file">File delle immagini</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
/// <returns>Restituisce 1 se è andato a buon fine, 0 altrimenti</returns>
bool RimuoviImmagine(FILE* file, char nomeUtente[]);

/// <summary>
/// Questa funzione permette la visualizzazione dettagliata dell'immagine selezionata nel menu creatore.
/// NON PERMETTE IL DOWNLOAD!
/// </summary>
/// <param name="file">File delle immagini</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
/// <returns>Restituisce 1 se è andato a buon fine, 0 altrimenti</returns>
bool VisualizzaImmagineCreatore(FILE* file, char nomeUtente[]);

/// <summary>
/// Questa funzione permette la visualizzazione dettagliata dell'immagine selezionata e ne permette anche il download
/// </summary>
/// <param name="file">File delle immagini</param>
/// <param name="autoreImmagine">Nome utente dell'autore dell'immagine selezionata (lo restituisce)</param>
/// <returns>Restituisce 1 se è andato a buon fine, 0 altrimenti</returns>
bool VisualizzaImmagine(FILE* file, char autoreImmagine[]);

/// <summary>
/// Questa procedura stampa i tags dell'immagine passata
/// </summary>
/// <param name="immagine">Struct dell'immagine da visualizzare</param>
void StampaTagsImmagine(Immagine_t immagine);

/// <summary>
/// Questa procedura stampa la lista ordinata delle categorie disponibili
/// </summary>
void StampaCategorieDisponibili();

/// <summary>
/// Questa procedura stampa la lista ordinata dei tags disponibili
/// </summary>
void StampaTagsDisponibili();

/// <summary>
/// Questa procedura permette l'inserimento dei tags nell'immagine
/// Va chiamata nella sezione CARICAMENTO dell'immagine
/// </summary>
/// <param name="immagine">Puntatore a struct dell'immagine da caricare</param>
void InserisciTagsCaricamento(Immagine_t** immagine);

/// <summary>
/// Questa procedura permette l'inserimento dei tags nell'immagine
/// Va chiamata nella sezione MODIFICA dell'immagine
/// </summary>
/// <param name="immagine">Struct dell'immagine da modificare</param>
void InserisciTagsModifica(Immagine_t* immagine);

/// <summary>
/// Questa procedura permette l'inserimento della categoria nell'immagine
/// Va chiamata nella sezione CARICAMENTO del menu
/// </summary>
/// <param name="immagine">Puntatore a struct dell'immagine da caricare</param>
void InserisciCategoriaCaricamento(Immagine_t** immagine);

/// <summary>
/// Questa procedura permette l'inserimento della categoria nell'immagine
/// Va chiamata nella sezione MODIFICA del menu
/// </summary>
/// <param name="immagine">Struct dell'immagine da modificare</param>
void InserisciCategoriaModifica(Immagine_t* immagine);

/// <summary>
/// Questa funzione permette di ricercare le immagini a seconda della loro categoria
/// </summary>
/// <param name="file">File delle immagini</param>
/// <returns>Restituisce 1 se è andata a buon fine, 0 altrimenti</returns>
bool RicercaCategoria(FILE* file);

bool RicercaTags(FILE* file);

/// <summary>
/// Questa funzione permette di valutare l'immagine selezionata attualmente
/// </summary>
/// <param name="file">File delle immagini</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
/// <returns>Restituisce la valutazione data (da 1 a 5). Restituisce 0 se la valutazione è stata già data</returns>
unsigned int ValutaImmagine(FILE* file, char nomeUtente[]);

/// <summary>
/// Questa procedura salva le informazioni essenziali della valutazione data, per permettere in seguito
/// di controllare se la valutazione è stata già data dall'utente su quell'immagine
/// </summary>
/// <param name="fileImmagine">File delle immagini</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
/// <param name="valutazione">Valutazione data dall'utente</param>
void SalvaValutazione(FILE* fileImmagine, char nomeUtente[], unsigned int valutazione);

/// <summary>
/// Carica in un array tutte le immagini
/// </summary>
/// <param name="file">File delle immagini</param>
/// <param name="immagine">Array che riceve le immagini</param>
/// <returns>Restituisce il numero di immagini caricate</returns>
size_t CaricaArrayImmagini(FILE* file, Immagine_t immagine[]);

void ScambiaImmagine(Immagine_t *immagineA, Immagine_t *immagineB);

/// <summary>
/// Bubble sort per le immagini
/// </summary>
/// <param name="immagine">Array pieno di immagini</param>
/// <param name="n">Numero di elementi</param>
/// <param name="criterio">True se vogliamo ordinare per numero di download, false per media valutazioni</param>
void BubbleSortImmagine(Immagine_t immagine[], size_t n, bool criterio);

#endif