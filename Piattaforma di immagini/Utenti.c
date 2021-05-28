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
	return false;
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
	return false;
}

bool ControllaPassword(FILE* file, char buffer[], const char nomeUtente[])
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
	return false;
}

void InserisciDatiUtilizzatore(FILE* file, Utilizzatore_t* utilizzatore, char nomeUtente[])
{
	bool errore = false;
	do {
		system("cls");
		errore = false;
		green();
		puts("**REGISTRAZIONE UTENTE UTILIZZATORE**");
		reset();
	

		char scelta = { 0 };

		green();
		printf("Vuoi che i dati vengano inseriti automaticamente? (Y/N): ");
		reset();

		scanf("%c", &scelta);
		SvuotaInput();

		scelta = toupper(scelta);
		if (scelta == 'Y')
		{
			for (size_t i = 0; i < 8; i++)
			{
				utilizzatore->nomeUtente[i] = RNG('a', 'z');
				utilizzatore->password[i] = RNG('a', 'z');
			}
			strcpy(nomeUtente, utilizzatore->nomeUtente); // Passo al main il nomeUtente (per il menu principale) per conoscere chi ha fatto l'accesso

			strcpy(utilizzatore->nome, "Test");
			strcpy(utilizzatore->cognome, "User");
			utilizzatore->sesso = 'M';
			strcpy(utilizzatore->professione, "TestProfessione");
			strcpy(utilizzatore->nazionalita, "Italia");
			utilizzatore->dataNascita.giorno = 1;
			utilizzatore->dataNascita.mese = 1;
			utilizzatore->dataNascita.anno = 1990;
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			utilizzatore->dataIscrizione.giorno = tm.tm_mday;
			utilizzatore->dataIscrizione.mese = tm.tm_mon + 1;
			utilizzatore->dataIscrizione.anno = tm.tm_year + 1900;

			green();
			printf("\nLe tue credenziali sono: ");
			reset();
			printf("\nNome utente: %s\nPassword: %s\n\n", utilizzatore->nomeUtente, utilizzatore->password);
			green();
			printf("\nRicordale! Potrai usarle in futuro per effettuare il login.");
			reset();
		}

		else if (scelta == 'N')
		{
			// Inserimento NOME UTENTE
			do
			{
				errore = false;
				green();
				printf("\nInserire un nome utente (min. 4 caratteri): ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };

				scanf("%100s", buffer);
				SvuotaInput();

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
					StampaErrore("Errore! Inserire un nome utente di almeno 4 caratteri!");
				}
				else if (giaEsistente == true)
				{
					errore = true;
					StampaErrore("Errore! Nome utente gia' esistente!");
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
				green();
				printf("Inserire una password (min. 8 caratteri): ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };

				scanf("%100s", buffer);
				SvuotaInput();

				// Controlla che il minimo sia rispettato
				if (strlen(buffer) < MIN_CAR_PASSWORD)
				{
					errore = true;
					StampaErrore("Errore! Inserire una password di almeno 8 caratteri!");
				}

				// Altrimenti procedi
				else
					AssegnaStringa(utilizzatore->password, buffer, false);
			} while (errore);

			// Inserimento NOME
			do
			{
				errore = false;
				green();
				printf("Inserire il nome: ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };

				scanf("%100[^\n]", buffer);
				SvuotaInput();

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
				green();
				printf("Inserire il cognome: ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };

				scanf("%100[^\n]", buffer);
				SvuotaInput();

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
				green();
				printf("Inserire il sesso (M/F): ");
				reset();

				scanf("%c", &utilizzatore->sesso);
				SvuotaInput();
				utilizzatore->sesso = toupper(utilizzatore->sesso);

				// Controllo errori
				if (utilizzatore->sesso != 'M' && utilizzatore->sesso != 'F')
				{
					errore = true;
					StampaErrore("Errore! Inserire M o F");
				}
			} while (errore);

			// Inserimento PROFESSIONE
			do
			{
				errore = false;
				green();
				printf("Inserire la professione: ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };

				scanf("%100[^\n]", buffer);
				SvuotaInput();

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
				green();
				printf("Inserire la nazionalita': ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };

				scanf("%100[^\n]", buffer);
				SvuotaInput();

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
				green();
				printf("Inserire la data di nascita (GG/MM/AAAA): ");
				reset();
				scanf("%u/%u/%u", &utilizzatore->dataNascita.giorno, &utilizzatore->dataNascita.mese, &utilizzatore->dataNascita.anno);
				SvuotaInput();

				if (!DataCorretta(utilizzatore->dataNascita.giorno, utilizzatore->dataNascita.mese, utilizzatore->dataNascita.anno))
				{
					errore = true;
					StampaErrore("Errore! La data e' incorretta!");
				}
			} while (errore);

			// Assegnazione data di iscrizione
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			utilizzatore->dataIscrizione.giorno = tm.tm_mday;
			utilizzatore->dataIscrizione.mese = tm.tm_mon + 1;
			utilizzatore->dataIscrizione.anno = tm.tm_year + 1900;
		}

		else
		{
			errore = true;
			StampaErrore("Selezionare un'opzione valida!");
		}
	} while (errore);
}

void InserisciDatiCreatore(FILE* file, Creatore_t* creatore, char nomeUtente[])
{
	bool errore = false;

	do
	{
		system("cls");
		errore = false;
		puts("**REGISTRAZIONE UTENTE CREATORE**");

		char scelta = { 0 };

		green();
		printf("Vuoi che i dati vengano inseriti automaticamente? (Y/N): ");
		reset();

		scanf("%c", &scelta);
		SvuotaInput();

		scelta = toupper(scelta);
		if (scelta == 'Y')
		{
			for (size_t i = 0; i < 8; i++)
			{
				creatore->nomeUtente[i] = RNG('a', 'z');
				creatore->password[i] = RNG('a', 'z');
			}
			strcpy(nomeUtente, creatore->nomeUtente); // Passo al main il nomeUtente (per il menu principale) per conoscere chi ha fatto l'accesso

			strcpy(creatore->nome, "Test");
			strcpy(creatore->cognome, "User");
			creatore->sesso = 'M';
			strcpy(creatore->professione, "TestProfessione");
			strcpy(creatore->nazionalita, "Italia");
			creatore->dataNascita.giorno = 1;
			creatore->dataNascita.mese = 1;
			creatore->dataNascita.anno = 1990;
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			creatore->dataIscrizione.giorno = tm.tm_mday;
			creatore->dataIscrizione.mese = tm.tm_mon + 1;
			creatore->dataIscrizione.anno = tm.tm_year + 1900;

			green();
			printf("\nLe tue credenziali sono: ");
			reset();
			printf("\nNome utente: %s\nPassword: %s\n\n", creatore->nomeUtente, creatore->password);
			green();
			printf("\nRicordale! Potrai usarle in futuro per effettuare il login.");
			reset();
		}

		else if (scelta == 'N')
		{
			system("cls");
			// Inserimento NOME UTENTE
			do
			{
				errore = false;
				green();
				printf("Inserire un nome utente (min. 4 caratteri): ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };
				scanf("%100s", buffer);
				SvuotaInput();


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
					StampaErrore("Errore! Inserire un nome utente di almeno 4 caratteri!");
				}
				else if (giaEsistente == true)
				{
					errore = true;
					StampaErrore("Errore! Nome utente gia' esistente!");
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
				green();
				printf("Inserire una password (min. 8 caratteri): ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };

				scanf("%100s", buffer);
				SvuotaInput();

				// Controlla che il minimo sia rispettato
				if (strlen(buffer) < MIN_CAR_PASSWORD)
				{
					errore = true;
					StampaErrore("Errore! Inserire una password di almeno 8 caratteri!");
				}

				// Altrimenti procedi
				else
					AssegnaStringa(creatore->password, buffer, false);
			} while (errore);

			// Inserimento NOME
			do
			{
				errore = false;
				green();
				printf("Inserire il nome: ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };

				scanf("%100[^\n]", buffer);
				SvuotaInput();

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
				green();
				printf("Inserire il cognome: ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };
				scanf("%100[^\n]", buffer);
				SvuotaInput();

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
				green();
				printf("Inserire il sesso (M/F): ");
				reset();
				scanf("%c", &creatore->sesso);
				SvuotaInput();
				creatore->sesso = toupper(creatore->sesso);

				// Controllo errori
				if (creatore->sesso != 'M' && creatore->sesso != 'F')
				{
					errore = true;
					StampaErrore("Errore! Inserire M o F!");
				}
			} while (errore);

			// Inserimento PROFESSIONE
			do
			{
				errore = false;
				green();
				printf("Inserire la professione: ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };

				scanf("%100[^\n]", buffer);
				SvuotaInput();

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
				green();
				printf("Inserire la nazionalita': ");
				reset();
				char buffer[MAX_BUFFER] = { 0 };
				scanf("%100[^\n]", buffer);
				SvuotaInput();

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
				green();
				printf("Inserire la data di nascita (GG/MM/AAAA): ");
				reset();
				scanf("%u/%u/%u", &creatore->dataNascita.giorno, &creatore->dataNascita.mese, &creatore->dataNascita.anno);
				SvuotaInput();

				if (!DataCorretta(creatore->dataNascita.giorno, creatore->dataNascita.mese, creatore->dataNascita.anno))
				{
					errore = true;
					StampaErrore("Errore! La data e' incorretta!");
				}
			} while (errore);

			// Assegnazione data di iscrizione
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			creatore->dataIscrizione.giorno = tm.tm_mday;
			creatore->dataIscrizione.mese = tm.tm_mon + 1;
			creatore->dataIscrizione.anno = tm.tm_year + 1900;
		}
		else
		{
			errore = true;
			StampaErrore("Selezionare un'opzione valida!");
		}

	} while (errore);
}

void SalvaDatiCreatore(FILE* file, Creatore_t* creatore)
{
	Creatore_t precCreatore = { 0 };

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

bool AggiornaNumImmaginiCreatore(FILE* file, const char nomeUtente[])
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

				// Aggiorno i dati
				fseek(file, -(int)sizeof(Creatore_t), SEEK_CUR);
				fwrite(&tempCreatore, sizeof(Creatore_t), 1, file);
				return true;
			}
		}
		else
			return false;
	}
	return false;
}

bool AggiornaNumDownloadCreatore(FILE* file, const char nomeUtente[])
{
	while (!feof(file))
	{
		Creatore_t tempCreatore = { 0 };
		int esito = fread(&tempCreatore, sizeof(Creatore_t), 1, file);

		if (esito != 0)
		{
			if (strcmp(nomeUtente, tempCreatore.nomeUtente) == 0)
			{
				tempCreatore.numDownloadTot++;

				// Aggiorno i dati
				fseek(file, -(int)sizeof(Creatore_t), SEEK_CUR);
				fwrite(&tempCreatore, sizeof(Creatore_t), 1, file);
				return true;
			}
		}
		else
			return false;
	}
	return false;
}

bool AggiornaMediaValutazioniCreatore(FILE* file, unsigned int valutazione)
{
	Creatore_t tempCreatore = { 0 };
	fseek(file, -(int)sizeof(Creatore_t), SEEK_CUR);
	if (fread(&tempCreatore, sizeof(Creatore_t), 1, file) != 0)
	{
		float sommaValutazioni = tempCreatore.mediaValutazioni * tempCreatore.numValutazioniRicevute;
		tempCreatore.numValutazioniRicevute++;
		sommaValutazioni += valutazione;
		tempCreatore.mediaValutazioni = sommaValutazioni / tempCreatore.numValutazioniRicevute;
		fseek(file, -(int)sizeof(Creatore_t), SEEK_CUR);
		fwrite(&tempCreatore, sizeof(Creatore_t), 1, file);
		return true;
	}
	else
		return false;
}

bool AggiornaNumDownloadUtilizzatore(FILE* file, const char nomeUtente[])
{
	while (!feof(file))
	{
		Utilizzatore_t tempUtilizzatore = { 0 };
		int esito = fread(&tempUtilizzatore, sizeof(Utilizzatore_t), 1, file);

		if (esito != 0)
		{
			if (strcmp(nomeUtente, tempUtilizzatore.nomeUtente) == 0)
			{
				tempUtilizzatore.numDownloadTot++;
				fseek(file, -(int)sizeof(Utilizzatore_t), SEEK_CUR);
				fwrite(&tempUtilizzatore, sizeof(Utilizzatore_t), 1, file);
				return true;
			}
		}
		else
			return false;
	}
	return false;
}

bool AggiornaNumValutazioniUtilizzatore(FILE* file)
{
	Utilizzatore_t tempUtilizzatore = { 0 };
	fseek(file, -(int)sizeof(Utilizzatore_t), SEEK_CUR);
	if (fread(&tempUtilizzatore, sizeof(Utilizzatore_t), 1, file) != 0)
	{
		tempUtilizzatore.numValutazioni++;
		fseek(file, -(int)sizeof(Utilizzatore_t), SEEK_CUR);
		fwrite(&tempUtilizzatore, sizeof(Utilizzatore_t), 1, file);
		return true;
	}
	else
		return false;
}



size_t CaricaArrayCreatori(FILE* file, Creatore_t creatore[])
{
	file = ApriFile(PERCORSO_FILE_CREATORI);

	size_t i = 0;
	while (!feof(file) && i < MAX_BUFFER)
	{
		fread(&creatore[i], sizeof(Creatore_t), 1, file);
		if (creatore[i].id != 0)
			i++;
	}


	fclose(file);
	return i;
}

void ScambiaCreatore(Creatore_t* creatoreA, Creatore_t* creatoreB)
{
	Creatore_t temp = *creatoreA;
	*creatoreA = *creatoreB;
	*creatoreB = temp;
}

void BubbleSortCreatore(Creatore_t creatore[], size_t n, const bool criterio)
{
	bool scambiato = false;

	if (criterio)
	{
		do
		{
			scambiato = false;
			for (size_t i = 0; i < n - 1; i++)
			{
				if (creatore[i].numDownloadTot < creatore[i + 1].numDownloadTot)
				{
					ScambiaCreatore(&creatore[i], &creatore[i + 1]);
					scambiato = true;
				}
			}
		} while (scambiato);
	}
	else
	{
		do
		{
			scambiato = false;
			for (size_t i = 0; i < n - 1; i++)
			{
				if (creatore[i].mediaValutazioni < creatore[i + 1].mediaValutazioni)
				{
					ScambiaCreatore(&creatore[i], &creatore[i + 1]);
					scambiato = true;
				}
			}
		} while (scambiato);
	}
}


size_t CaricaArrayUtilizzatori(FILE* file, Utilizzatore_t utilizzatore[])
{
	file = ApriFile(PERCORSO_FILE_UTILIZZATORI);

	size_t i = 0;
	while (!feof(file) && i < MAX_BUFFER)
	{
		fread(&utilizzatore[i], sizeof(Utilizzatore_t), 1, file);
		if (utilizzatore[i].id != 0)
			i++;
	}


	fclose(file);
	return i;
}

void ScambiaUtilizzatore(Utilizzatore_t* utilizzatoreA, Utilizzatore_t* utilizzatoreB)
{
	Utilizzatore_t temp = *utilizzatoreA;
	*utilizzatoreA = *utilizzatoreB;
	*utilizzatoreB = temp;
}

void BubbleSortUtilizzatore(Utilizzatore_t utilizzatore[], size_t n, const bool criterio)
{
	bool scambiato = false;

	if (criterio)
	{
		do {
			scambiato = false;
			for (size_t i = 0; i < n-1; i++)
			{
				if (utilizzatore[i].numDownloadTot < utilizzatore[i + 1].numDownloadTot)
				{
					ScambiaUtilizzatore(&utilizzatore[i], &utilizzatore[i + 1]);
					scambiato = true;
				}
			}
		} while (scambiato);
	}
	else
	{
		do
		{
			scambiato = false;
			for (size_t i = 0; i < n - 1; i++)
			{
				if (utilizzatore[i].numValutazioni < utilizzatore[i + 1].numValutazioni)
				{
					ScambiaUtilizzatore(&utilizzatore[i], &utilizzatore[i + 1]);
					scambiato = true;
				}
			}
		} while (scambiato);
	}
}