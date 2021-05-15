#ifndef _UTENTI_H_
#define _UTENTI_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "Utility.h"

#define MIN_CAR_NOME_UTENTE 4
#define MIN_CAR_PASSWORD 8

typedef struct
{
    char* nomeUtente;
    char* password;
    char* nome;
    char* cognome;
    char sesso;
    char* professione;
    char* nazionalita;
    Data_t dataNascita;
    Data_t dataIscrizione;
    unsigned int numImmagini;
    unsigned int numDownloadTot;
    float mediaValutazioni;
} Creatore_t;

typedef struct
{
    char* nomeUtente;
    char* password;
    char* nome;
    char* cognome;
    char sesso;
    char* professione;
    char* nazionalita;
    Data_t dataNascita;
    Data_t dataIscrizione;
    unsigned int numValutazioni;
    unsigned int numDownloadTot;
} Utilizzatore_t;

unsigned short int ControllaNomeUtente(FILE* file, char buffer[]);

#endif
