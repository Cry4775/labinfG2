#include "Utenti.h"

bool ControllaNomeUtenteCreatore(FILE* file, char buffer[])
{
    // Controlla le struct sul campo nome utente
    // Se il nome utente corrisponde con uno già esistente, ritorna true
    // Se invece non esiste, ritorna false

	while (!feof(file))
	{
		Creatore_t tempCreatore = { 0 };
		int esito = fread(&tempCreatore, sizeof(Creatore_t), 1, file);

		if (esito != 0)
		{
			if (strcmp(buffer, tempCreatore.nomeUtente) == 0)
				return true;
		}
		else 
			return false;
	}
}

bool ControllaNomeUtenteUtilizzatore(FILE* file, char buffer[])
{
	// Controlla le struct sul campo nome utente
	// Se il nome utente corrisponde con uno già esistente, ritorna true
	// Se invece non esiste, ritorna false

	while (!feof(file))
	{
		Utilizzatore_t tempUtilizzatore = { 0 };
		int esito = fread(&tempUtilizzatore, sizeof(Utilizzatore_t), 1, file);

		if (esito != 0)
		{
			if (strcmp(buffer, tempUtilizzatore.nomeUtente) == 0)
				return true;
		}
		else
			return false;
	}
}

bool ControllaPassword(FILE* file, char buffer[], char nomeUtente[])
{
    // Controlla la struct dell'utente che sta effettuando l'accesso
    // Ritorna true se la password è corretta, false altrimenti

	file = ApriFile(PERCORSO_FILE_CREATORI);

	while (!feof(file)) //while controllo creatori
	{
		Creatore_t tempCreatore = { 0 };
		int esito = fread(&tempCreatore, sizeof(Creatore_t), 1, file);

		if (esito != 0)
		{
			if ((strcmp(nomeUtente, tempCreatore.nomeUtente) == 0) && (strcmp(buffer, tempCreatore.password) == 0))
				return true;
		}
	}

	fclose(file);

	file = ApriFile(PERCORSO_FILE_UTILIZZATORI);

	while (!feof(file)) //while controllo utilizzatori
	{
		Utilizzatore_t tempUtilizzatore = { 0 };
		int esito = fread(&tempUtilizzatore, sizeof(Utilizzatore_t), 1, file);

		if (esito != 0)
		{
			if ((strcmp(nomeUtente, tempUtilizzatore.nomeUtente) == 0) && (strcmp(buffer, tempUtilizzatore.password) == 0))
				return true;
		}
		else
			return false;
	}

}

void InserisciDatiUtilizzatore(FILE* file, Utilizzatore_t* utilizzatore, char nomeUtente[])
{
	puts("Registrazione utente utilizzatore");
	// Inserimento NOME UTENTE
	bool errore = false;
	do
	{
		errore = false;
		printf("\nInserire un nome utente (min. 4 caratteri): ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100s", buffer);

		file = ApriFile(PERCORSO_FILE_CREATORI);

		bool giaEsistente = ControllaNomeUtenteCreatore(file, buffer);

		fclose(file);

		if (giaEsistente == false)
		{
			file = ApriFile(PERCORSO_FILE_UTILIZZATORI);

			giaEsistente = ControllaNomeUtenteUtilizzatore(file, buffer);

			fclose(file);
		}

		if (strlen(buffer) < MIN_CAR_NOME_UTENTE)
		{
			errore = true;
			puts("Errore! Inserire un nome utente di almeno 4 caratteri!\n");
		}
		else if (giaEsistente == true)
		{
			errore = true;
			puts("Errore! Nome utente gia' esistente!\n");
		}
		// Altrimenti procedi
		else
		{
			AssegnaStringa(utilizzatore->nomeUtente, buffer, false);
			strcpy(nomeUtente, buffer);
		}
	} while (errore);

	// Inserimento PASSWORD
	do
	{
		errore = false;
		printf("Inserire una password (min. 8 caratteri): ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100s", buffer);

		// Controlla che il minimo sia rispettato
		if (strlen(buffer) < MIN_CAR_PASSWORD)
		{
			errore = true;
			puts("Errore! Inserire una password di almeno 8 caratteri!\n");
		}

		// Altrimenti procedi
		else
			AssegnaStringa(utilizzatore->password, buffer, false);
	} while (errore);

	// Inserimento NOME
	do
	{
		errore = false;
		printf("Inserire il nome: ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100[^\n]", buffer);

		// Conversione della stringa in minuscolo
		ConversioneMinuscolo(buffer);

		// Controlla che non contenga simboli
		errore = ContieneSimboli(buffer, false);

		// Altrimenti procedi
		if (!errore)
			AssegnaStringa(utilizzatore->nome, buffer, true);
	} while (errore);

	// Inserimento COGNOME
	do
	{
		errore = false;
		printf("Inserire il cognome: ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100[^\n]", buffer);

		// Conversione della stringa in minuscolo
		ConversioneMinuscolo(buffer);

		// Controlla che non contenga simboli
		errore = ContieneSimboli(buffer, false);

		// Altrimenti procedi
		if (!errore)
			AssegnaStringa(utilizzatore->cognome, buffer, true);
	} while (errore);

	// Inserimento SESSO
	do
	{
		errore = false;
		printf("Inserire il sesso (M/F): ");
		SvuotaInput();
		scanf("%c", &utilizzatore->sesso);
		utilizzatore->sesso = toupper(utilizzatore->sesso);

		// Controllo errori
		if (utilizzatore->sesso != 'M' && utilizzatore->sesso != 'F')
		{
			errore = true;
			printf("Errore! Inserire M o F!\n");
		}
	} while (errore);

	// Inserimento PROFESSIONE
	do
	{
		errore = false;
		printf("Inserire la professione: ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100[^\n]", buffer);

		// Conversione della stringa in minuscolo
		ConversioneMinuscolo(buffer);

		// Controlla che non contenga simboli
		errore = ContieneSimboli(buffer, false);

		if (!errore)
			AssegnaStringa(utilizzatore->professione, buffer, true);
	} while (errore);

	// Inserimento NAZIONALITA
	do
	{
		errore = false;
		printf("Inserire la nazionalita': ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100[^\n]", buffer);

		// Conversione della stringa in minuscolo
		ConversioneMinuscolo(buffer);

		// Controlla che non contenga simboli
		errore = ContieneSimboli(buffer, false);

		// Altrimenti procedi
		if (!errore)
			AssegnaStringa(utilizzatore->nazionalita, buffer, true);
	} while (errore);

	// Inserimento DATA DI NASCITA
	do
	{
		errore = false;
		printf("Inserire la data di nascita (GG/MM/AAAA): ");
		scanf("%u/%u/%u", &utilizzatore->dataNascita.giorno, &utilizzatore->dataNascita.mese, &utilizzatore->dataNascita.anno);

		if (!DataCorretta(utilizzatore->dataNascita.giorno, utilizzatore->dataNascita.mese, utilizzatore->dataNascita.anno))
		{
			errore = true;
			printf("Errore! La data e' incorretta!\n");
		}
	} while (errore);

	// Assegnazione data di iscrizione
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	utilizzatore->dataIscrizione.giorno = tm.tm_mday;
	utilizzatore->dataIscrizione.mese = tm.tm_mon + 1;
	utilizzatore->dataIscrizione.anno = tm.tm_year + 1900;
}

void InserisciDatiCreatore(FILE* file, Creatore_t* creatore, char nomeUtente[])
{
	puts("Registrazione utente creatore");
	bool errore = false;

	// Inserimento NOME UTENTE
	do
	{
		errore = false;
		printf("\nInserire un nome utente (min. 4 caratteri): ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100s", buffer);


		file = ApriFile(PERCORSO_FILE_CREATORI);

		bool giaEsistente = ControllaNomeUtenteCreatore(file, buffer);

		fclose(file);

		// Controlliamo anche il file utilizzatori.dat se non l'ha già trovato
		if (giaEsistente == false)
		{
			file = ApriFile(PERCORSO_FILE_UTILIZZATORI);

			giaEsistente = ControllaNomeUtenteUtilizzatore(file, buffer);

			fclose(file);
		}

		if (strlen(buffer) < MIN_CAR_NOME_UTENTE)
		{
			errore = true;
			puts("Errore! Inserire un nome utente di almeno 4 caratteri!\n");
		}
		else if (giaEsistente == true)
		{
			errore = true;
			puts("Errore! Nome utente gia' esistente!\n");
		}
		// Altrimenti procedi
		else
		{
			AssegnaStringa(creatore->nomeUtente, buffer, false);
			strcpy(nomeUtente, buffer); // Passo al main il nomeUtente (per il menu principale) per conoscere chi ha fatto l'accesso
		}
	} while (errore);

	// Inserimento PASSWORD
	do
	{
		errore = false;
		printf("Inserire una password (min. 8 caratteri): ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100s", buffer);

		// Controlla che il minimo sia rispettato
		if (strlen(buffer) < MIN_CAR_PASSWORD)
		{
			errore = true;
			puts("Errore! Inserire una password di almeno 8 caratteri!\n");
		}

		// Altrimenti procedi
		else
			AssegnaStringa(creatore->password, buffer, false);
	} while (errore);

	// Inserimento NOME
	do
	{
		errore = false;
		printf("Inserire il nome: ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100[^\n]", buffer);

		// Conversione della stringa in minuscolo
		ConversioneMinuscolo(buffer);

		// Controlla che non contenga simboli
		errore = ContieneSimboli(buffer, false);

		// Altrimenti procedi
		if (!errore)
			AssegnaStringa(creatore->nome, buffer, true);
	} while (errore);

	// Inserimento COGNOME
	do
	{
		errore = false;
		printf("Inserire il cognome: ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100[^\n]", buffer);

		// Conversione della stringa in minuscolo
		ConversioneMinuscolo(buffer);

		// Controlla che non contenga simboli
		errore = ContieneSimboli(buffer, false);

		// Altrimenti procedi
		if (!errore)
			AssegnaStringa(creatore->cognome, buffer, true);
	} while (errore);

	// Inserimento SESSO
	do
	{
		errore = false;
		printf("Inserire il sesso (M/F): ");
		SvuotaInput();
		scanf("%c", &creatore->sesso);
		creatore->sesso = toupper(creatore->sesso);

		// Controllo errori
		if (creatore->sesso != 'M' && creatore->sesso != 'F')
		{
			errore = true;
			printf("Errore! Inserire M o F!\n");
		}
	} while (errore);

	// Inserimento PROFESSIONE
	do
	{
		errore = false;
		printf("Inserire la professione: ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100[^\n]", buffer);

		// Conversione della stringa in minuscolo
		ConversioneMinuscolo(buffer);

		// Controlla che non contenga simboli
		errore = ContieneSimboli(buffer, false);

		if (!errore)
			AssegnaStringa(creatore->professione, buffer, true);
	} while (errore);

	// Inserimento NAZIONALITA
	do
	{
		errore = false;
		printf("Inserire la nazionalita': ");
		char buffer[MAX_BUFFER] = { 0 };
		SvuotaInput();
		scanf("%100[^\n]", buffer);

		// Conversione della stringa in minuscolo
		ConversioneMinuscolo(buffer);

		// Controlla che non contenga simboli
		errore = ContieneSimboli(buffer, false);

		// Altrimenti procedi
		if (!errore)
			AssegnaStringa(creatore->nazionalita, buffer, true);
	} while (errore);

	// Inserimento DATA DI NASCITA
	do
	{
		errore = false;
		printf("Inserire la data di nascita (GG/MM/AAAA): ");
		scanf("%u/%u/%u", &creatore->dataNascita.giorno, &creatore->dataNascita.mese, &creatore->dataNascita.anno);

		if (!DataCorretta(creatore->dataNascita.giorno, creatore->dataNascita.mese, creatore->dataNascita.anno))
		{
			errore = true;
			printf("Errore! La data e' incorretta!\n");
		}
	} while (errore);

	// Assegnazione data di iscrizione
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	creatore->dataIscrizione.giorno = tm.tm_mday;
	creatore->dataIscrizione.mese = tm.tm_mon + 1;
	creatore->dataIscrizione.anno = tm.tm_year + 1900;
}

void SalvaDatiCreatore(FILE* file, Creatore_t* creatore)
{
	Creatore_t precCreatore = { 0 };																			//rendi l'essagnazione una funzione e aggiungi il controllo di id = 0 tra i record
	fseek(file, - (int)sizeof(Creatore_t), SEEK_END);
	fread(&precCreatore, sizeof(Creatore_t), 1, file);
	creatore->id = precCreatore.id + 1;
	fwrite(&*creatore, sizeof(Creatore_t), 1, file);
}

void SalvaDatiUtilizzatore(FILE* file, Utilizzatore_t* utilizzatore)
{
	Utilizzatore_t precUtilizzatore = { 0 };
	fseek(file, -(int)sizeof(Utilizzatore_t), SEEK_END);
	fread(&precUtilizzatore, sizeof(Utilizzatore_t), 1, file);
	utilizzatore->id = precUtilizzatore.id + 1;
	fwrite(&*utilizzatore, sizeof(Utilizzatore_t), 1, file);
}

bool AggiornaNumImmaginiCreatore(FILE* file, char nomeUtente[])
{
	while (!feof(file))
	{
		Creatore_t tempCreatore = { 0 };
		int esito = fread(&tempCreatore, sizeof(Creatore_t), 1, file);

		if (esito != 0)
		{
			if (strcmp(nomeUtente, tempCreatore.nomeUtente) == 0)
			{
				tempCreatore.numImmagini++;
				fseek(file, -(int)sizeof(Creatore_t), SEEK_CUR);
				fwrite(&tempCreatore, sizeof(Creatore_t), 1, file);
				return true;
			}
		}
		else
			return false;
	}
}
