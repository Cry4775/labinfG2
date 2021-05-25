#ifndef _UTILITY_H_
#define _UTILITY_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <Windows.h>

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

// Svuota il buffer di input
void SvuotaInput();

// Copia la stringa da buffer a destinazione e se primaMaiuscola viene passata come true, la prima lettera verrà impostata maiuscola
void AssegnaStringa(char destinazione[], char buffer[], bool primaMaiuscola);

// Ritorna true (1) se è corretta, false (0) altrimenti
bool DataCorretta(unsigned short int giorno, unsigned short int mese, unsigned short int anno);

// Converte tutta la stringa buffer in minuscolo
void ConversioneMinuscolo(char buffer[]);

// Ritorna true (1) se la stringa buffer contiene simboli, false (0) altrimenti, 
// inoltre se numeriAmmessi viene passata come true, allora i numeri non saranno considerati come simboli
bool ContieneSimboli(char buffer[], bool numeriAmmessi);

// Genera un intero casuale tra MIN e MAX
int RNG(int MIN, int MAX);

// Apre il file richiesto e se non esiste ne crea uno
FILE* ApriFile(const char* percorsoFile);

// Crea l'istogramma dell'attività in statistiche creatore
const char* CreaIstogramma(unsigned int percentualeOccorrenza);

// Cambia il colore dell'output in rosso
void red();

// Cambia il colore dell'output in verde
void green();

// Cambia il colore dell'output in blu
void blue();

// Cambia il colore dell'output in azzurro
void cyan();

// Resetta il colore dell'output
void reset();

// Stampa una stringa in azzurro
void StampaTitolo(const char* testo);

// Stampa una stringa in rosso
void StampaErrore(const char* testo);

#endif