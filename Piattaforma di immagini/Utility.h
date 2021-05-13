#ifndef _UTILITY_H_
#define _UTILITY_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
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

// Ritorna true (1) se � corretta, false (0) se � scorretta
unsigned short int DataCorretta(unsigned short int giorno, unsigned short int mese, unsigned short int anno);

#endif