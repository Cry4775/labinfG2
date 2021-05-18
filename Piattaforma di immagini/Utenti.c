#include "Utenti.h"

bool ControllaNomeUtente(FILE* file, char buffer[])
{
    // Controlla le struct sul campo nome utente
    // Se il nome utente corrisponde con uno già esistente, ritorna true
    // Se invece non esiste, ritorna false
}

bool ControllaPassword(FILE* file, char buffer[])
{
    // Controlla la struct dell'utente che sta effettuando l'accesso
    // Quindi una volta inserito il nome utente e verificato che esiste, è inutile chiudere il file, basta leggere il campo successivo (password)
    // Ritorna true se la password è corretta, false altrimenti
}

void SalvaDatiCreatore(FILE* file, Creatore_t* creatore)
{
	
}

void SalvaDatiUtilizzatore(FILE* file, Utilizzatore_t* utilizzatore)
{

}