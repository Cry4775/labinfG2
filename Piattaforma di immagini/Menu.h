#ifndef _MENU_H_
#define _MENU_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Utenti.h"
#include "Immagini.h"

FILE* file;

// Gestisce le funzionalità del Menu Iniziale, quali registrazione e accesso utente
bool MenuIniziale(bool* isCreatore, char nomeUtente[]);

void MenuPrincipale(bool* isCreatore, char nomeUtente[]);

#endif