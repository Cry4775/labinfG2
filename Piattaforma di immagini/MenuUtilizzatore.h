#ifndef _MENUUTILIZZATORE_H_
#define _MENUUTILIZZATORE_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Utenti.h"
#include "Immagini.h"
#include "Menu.h"

/// <summary>
/// Questa procedura contiene tutte le funzioni del sottomenu Ricerca Immagine dell'UTILIZZATORE
/// </summary>
/// <param name="nomeUtente">Nome utente dell'utente loggato</param>
void RicercaImmagineUtilizzatore(char nomeUtente[]);

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