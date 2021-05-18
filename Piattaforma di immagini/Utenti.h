#ifndef _UTENTI_H_
#define _UTENTI_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Utility.h"

#define MIN_CAR_NOME_UTENTE 4
#define MIN_CAR_PASSWORD 8
#define PERCORSO_FILE_CREATORI "utenti/creatori.dat"
#define PERCORSO_FILE_UTILIZZATORI "utenti/utilizzatori.dat"

typedef struct
{
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
    float mediaValutazioni;
} Creatore_t;

typedef struct
{
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

bool ControllaNomeUtente(FILE* file, char buffer[]);

bool ControllaPassword(FILE* file, char buffer[]);

void SalvaDatiCreatore(FILE* file, Creatore_t* creatore);

void SalvaDatiUtilizzatore(FILE* file, Utilizzatore_t* utilizzatore);



#endif
