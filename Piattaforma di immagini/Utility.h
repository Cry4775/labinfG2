#ifndef _UTILITY_H_
#define _UTILITY_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_BUFFER 101

typedef struct
{
    unsigned int giorno;
    unsigned int mese;
    unsigned int anno;
} Data_t;

typedef enum {
    false,
    true
} bool;

void SvuotaInput();

void AssegnaStringa(char** destinazione, char buffer[], unsigned short int primaMaiuscola);

// Ritorna true (1) se è corretta, false (0) altrimenti
bool DataCorretta(unsigned short int giorno, unsigned short int mese, unsigned short int anno);

void ConversioneMinuscolo(char buffer[]);

// Ritorna true (1) se contiene simboli, false (0) altrimenti
bool ContieneSimboli(char buffer[]);

void InvioPerContinuare();

#endif