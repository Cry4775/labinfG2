#ifndef _UTILITY_H_
#define _UTILITY_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define true 1
#define false 0
#define MAX_BUFFER 101

typedef struct
{
    unsigned int giorno;
    unsigned int mese;
    unsigned int anno;
} Data_t;

void SvuotaInput();

void AssegnaStringa(char** destinazione, char buffer[]);

// Ritorna true (1) se è corretta, false (0) altrimenti
unsigned short int DataCorretta(unsigned short int giorno, unsigned short int mese, unsigned short int anno);

void ConversioneMinuscolo(char buffer[]);

// Ritorna true (1) se contiene simboli, false (0) altrimenti
unsigned short int ContieneSimboli(char buffer[]);

#endif