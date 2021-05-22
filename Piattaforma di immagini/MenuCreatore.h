#ifndef _MENUCREATORE_H_
#define _MENUCREATORE_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Utenti.h"
#include "Immagini.h"
#include "Menu.h"

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

#endif