#ifndef _MENU_H_
#define _MENU_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Utenti.h"
#include "Immagini.h"
#include "MenuCreatore.h"
#include "MenuUtilizzatore.h"

FILE* file;

/// <summary>
/// Questa funzione contiene le funzionalità del menu iniziale quali Registrazione e Accesso
/// </summary>
/// <param name="isCreatore">Viene restituita al main per dare eventualmente l'accesso al menu principale da creatore</param>
/// <param name="nomeUtente">Viene restituita al main per dare il nome utente dell'utente loggato</param>
/// <returns>Restituisce 1 se l'accesso è stato eseguito, 0 se è stata scelta l'uscita</returns>
bool MenuIniziale(bool* isCreatore, char nomeUtente[]);

/// <summary>
/// Questa funzione contiene le funzionalità del menu principale
/// </summary>
/// <param name="isCreatore">Per dare l'accesso al menu creatore</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
void MenuPrincipale(bool* isCreatore, char nomeUtente[]);







#endif