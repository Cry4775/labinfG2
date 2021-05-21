#ifndef _UTENTI_H_
#define _UTENTI_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Utility.h"
#include "Immagini.h"

#define MIN_CAR_NOME_UTENTE 4
#define MIN_CAR_PASSWORD 8
#define PERCORSO_FILE_CREATORI "utenti/creatori.dat"
#define PERCORSO_FILE_UTILIZZATORI "utenti/utilizzatori.dat"

typedef struct
{
    int id;
    char nomeUtente[MAX_BUFFER];
    char password[MAX_BUFFER];
    char nome[MAX_BUFFER];
    char cognome[MAX_BUFFER];
    char sesso;
    char professione[MAX_BUFFER];
    char nazionalita[MAX_BUFFER];
    Data_t dataNascita;
    Data_t dataIscrizione;
    unsigned int numImmagini;
    unsigned int numDownloadTot;
    unsigned int numValutazioniRicevute;
    float mediaValutazioni;
} Creatore_t;

typedef struct
{
    int id;
    char nomeUtente[MAX_BUFFER];
    char password[MAX_BUFFER];
    char nome[MAX_BUFFER];
    char cognome[MAX_BUFFER];
    char sesso;
    char professione[MAX_BUFFER];
    char nazionalita[MAX_BUFFER];
    Data_t dataNascita;
    Data_t dataIscrizione;
    unsigned int numValutazioni;
    unsigned int numDownloadTot;
} Utilizzatore_t;

/// <summary>
/// Questa funzione controlla nel file creatori se il nome utente è già registrato
/// </summary>
/// <param name="file">File dei creatori</param>
/// <param name="buffer"></param>
/// <returns>Restituisce 1 se è già esistente, 0 altrimenti</returns>
bool ControllaNomeUtenteCreatore(FILE* file, char buffer[]);

/// <summary>
/// Questa funzione controlla nel file utilizzatori se il nome utente è già registrato
/// </summary>
/// <param name="file">File degli utilizzatori</param>
/// <param name="buffer"></param>
/// <returns>Restituisce 1 se è già esistente, 0 altrimenti</returns>
bool ControllaNomeUtenteUtilizzatore(FILE* file, char buffer[]);

/// <summary>
/// Questa funzione serve a controllare se le credenziali al momento dell'accesso sono corrette
/// </summary>
/// <param name="file">File non aperto</param>
/// <param name="buffer"></param>
/// <param name="nomeUtente">Nome utente immesso immediatamente prima</param>
/// <returns>Restituisce 1 se la password è corretta, 0 altrimenti</returns>
bool ControllaPassword(FILE* file, char buffer[], char nomeUtente[]);

/// <summary>
/// Questa procedura permette l'inserimento dei dati al momento della registrazione creatore
/// </summary>
/// <param name="file">File dei creatori</param>
/// <param name="creatore">Struct del creatore</param>
/// <param name="nomeUtente">Permette la restituzione al main del nome utente appena registrato</param>
void InserisciDatiCreatore(FILE* file, Creatore_t* creatore, char nomeUtente[]);

/// <summary>
/// Questa procedura permette il salvataggio su file dei dati immediatamente prima immessi
/// </summary>
/// <param name="file">File dei creatori</param>
/// <param name="creatore">Struct del creatore</param>
void SalvaDatiCreatore(FILE* file, Creatore_t* creatore);

/// <summary>
/// Questa procedura permette l'inserimento dei dati al momento della registrazione utilizzatore
/// </summary>
/// <param name="file">File degli utilizzatori</param>
/// <param name="creatore">Struct dell'utilizzatore</param>
/// <param name="nomeUtente">Permette la restituzione al main del nome utente appena registrato</param>
void InserisciDatiUtilizzatore(FILE* file, Utilizzatore_t* utilizzatore, char nomeUtente[]);

/// <summary>
/// Questa procedura permette il salvataggio su file dei dati immediatamente prima immessi
/// </summary>
/// <param name="file">File degli utilizzatori</param>
/// <param name="utilizzatore">Struct dell'utilizzatore</param>
void SalvaDatiUtilizzatore(FILE* file, Utilizzatore_t* utilizzatore);

/// <summary>
/// Questa funzione permette l'aggiornamento del campo numImmagini del creatore
/// </summary>
/// <param name="file">File dei creatori</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
/// <returns>Ritorna 1 se è andato a buon fine, 0 altrimenti</returns>
bool AggiornaNumImmaginiCreatore(FILE* file, char nomeUtente[]);

/// <summary>
/// Questa funzione permette l'aggiornamento del campo numDownload del creatore
/// </summary>
/// <param name="file">File dei creatori</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
/// <returns>Ritorna 1 se è andato a buon fine, 0 altrimenti</returns>
bool AggiornaNumDownloadCreatore(FILE* file, char nomeUtente[]);

/// <summary>
/// Questa funzione permette l'aggiornamento della mediaValutazioni del creatore
/// </summary>
/// <param name="file">File dei creatori</param>
/// <param name="valutazione"></param>
/// <returns>Ritorna 1 se è andato a buon fine, 0 altrimenti</returns>
bool AggiornaMediaValutazioniCreatore(FILE* file, unsigned int valutazione);

#endif
