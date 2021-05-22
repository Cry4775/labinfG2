#ifndef _MENU_H_
#define _MENU_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Utenti.h"
#include "Immagini.h"

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

/// <summary>
/// Questa procedura contiene tutte le funzioni del sottomenu Gestione Creatore
/// </summary>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
void GestioneCreatore(char nomeUtente[]);

/// <summary>
/// Questa procedura contiene tutte le funzioni del sottomenu Ricerca Immagine del CREATORE
/// </summary>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
void RicercaImmagineCreatore(char nomeUtente[]);

/// <summary>
/// Questa procedura contiene tutte le funzioni del sottomenu Ricerca Immagine dell'UTILIZZATORE
/// </summary>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
void RicercaImmagineUtilizzatore(char nomeUtente[]);

/// <summary>
/// Questa procedura contiene tutte le funzioni dell'opzione Ricerca Categoria del CREATORE
/// </summary>
/// <param name="file">File delle immagini</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
void RicercaCategoriaMenuCreatore(FILE* file, char nomeUtente[]);

/// <summary>
/// Questa procedura contiene tutte le funzioni dell'opzione Ricerca Tags del CREATORE
/// </summary>
/// <param name="file">File delle immagini</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
void RicercaTagsMenuCreatore(FILE* file, char nomeUtente[]);

/// <summary>
/// Questa procedura contiene tutte le funzioni dell'opzione Ricerca Categoria dell'UTILIZZATORE
/// </summary>
/// <param name="file">File delle immagini</param>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
void RicercaCategoriaMenuUtilizzatore(FILE* file, char nomeUtente[]);

/// <summary>
/// Questa procedura contiene tutte le funzioni dell'opzione Ricerca Tags dell'UTILIZZATORE
/// </summary>
/// <param name="file"></param>
/// <param name="nomeUtente"></param>
void RicercaTagsMenuUtilizzatore(FILE* file, char nomeUtente[]);

/// <summary>
/// Questa procedura contiene le funzioni dell'opzione Statistiche Creatore
/// </summary>
void StatisticheCreatore();

/// <summary>
/// Questa procedura contiene tutte le funzioni dell'opzione Classifiche
/// </summary>
void Classifiche();





#endif