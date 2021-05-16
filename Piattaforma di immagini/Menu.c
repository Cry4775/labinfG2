#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"

unsigned short int MenuIniziale()
{
	unsigned int inEsecuzione = true;
	do
	{
		puts("Benvenuto sulla piattaforma di immagini! \n\n1. Registrazione utente\n2. Accesso utente\n3. Esci\n");

		unsigned int sceltaMenu;
		unsigned short int errore = false;
		scanf("%1d", &sceltaMenu);


		switch (sceltaMenu)
		{
		case 1: // Registrazione utente
		{
			system("cls");
			do
			{
				errore = false;
				Creatore_t creatore = { 0 };
				Utilizzatore_t utilizzatore = { 0 };

				puts("Che tipologia di utente sei?\n1. Creatore\n2. Utilizzatore\n3. Indietro\n");
				scanf("%1d", &sceltaMenu);

				system("cls");

				switch (sceltaMenu)
				{
					// Registrazione utente Creatore
					case 1: 
					{
						puts("Registrazione utente creatore");
						// Inserimento NOME UTENTE
						do
						{
							errore = false;
							printf("\nInserire un nome utente (min. 4 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };

							// METTERE GLI INPUT DA FILE
							scanf("%100s", buffer);


							file = fopen(PERCORSO_FILE_CREATORI, "r");
							unsigned int giaEsistente = false;

							// Se il file non esiste, creane uno
							if (file == NULL)
							{
								//file = fopen("creatori.dat", "w");
								file = fopen(PERCORSO_FILE_CREATORI, "w");
								fclose(file);
								file = fopen(PERCORSO_FILE_CREATORI, "r");
							}
							
							giaEsistente = ControllaNomeUtente(file, buffer);
							fclose(file);

							// Controlliamo anche il file utilizzatori.dat
							if (giaEsistente == false)
							{
								file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
								// Se è la prima esecuzione e/o il file non esiste, creane uno
								if (file == NULL)
								{
									file = fopen(PERCORSO_FILE_UTILIZZATORI, "w");
									fclose(file);
									file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
								}

								giaEsistente = ControllaNomeUtente(file, buffer);

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
								AssegnaStringa(&creatore.nomeUtente, buffer, false);
						} while (errore == true);

						// Inserimento PASSWORD
						do
						{
							errore = false;
							printf("Inserire una password (min. 8 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							// Controlla che il minimo sia rispettato
							if (strlen(buffer) < MIN_CAR_PASSWORD)
							{
								errore = true;
								puts("Errore! Inserire una password di almeno 8 caratteri!\n");
							}

							// Altrimenti procedi
							else
								AssegnaStringa(&creatore.password, buffer, false);
						} while (errore == true);

						// Inserimento NOME
						do
						{
							errore = false;
							printf("Inserire il nome: ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer);

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&creatore.nome, buffer, true);
						} while (errore == true);

						// Inserimento COGNOME
						do
						{
							errore = false;
							printf("Inserire il cognome: ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer);

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&creatore.cognome, buffer, true);
						} while (errore == true);

						// Inserimento SESSO
						do
						{
							errore = false;
							printf("Inserire il sesso (M/F): ");
							SvuotaInput();
							scanf("%c", &creatore.sesso);
							creatore.sesso = toupper(creatore.sesso);

							// Controllo errori
							if (creatore.sesso != 'M' && creatore.sesso != 'F')
							{
								errore = true;
								printf("Errore! Inserire M o F!\n");
							}
						} while (errore == true);

						// Inserimento PROFESSIONE
						do
						{
							errore = false;
							printf("Inserire la professione: ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer);

							if (errore == false)
								AssegnaStringa(&creatore.professione, buffer, true);
						} while (errore == true);

						// Inserimento NAZIONALITA
						do
						{
							errore = false;
							printf("Inserire la nazionalita': ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer);

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&creatore.nazionalita, buffer, true);
						} while (errore == true);

						// Inserimento DATA DI NASCITA
						do
						{
							errore = false;
							printf("Inserire la data di nascita (GG/MM/AAAA): ");
							scanf("%u/%u/%u", &creatore.dataNascita.giorno, &creatore.dataNascita.mese, &creatore.dataNascita.anno);

							if (DataCorretta(creatore.dataNascita.giorno, creatore.dataNascita.mese, creatore.dataNascita.anno) == false)
							{
								errore = true;
								printf("Errore! La data e' incorretta!\n");
							}
						} while (errore == true);

						// Assegnazione data di iscrizione
						time_t t = time(NULL);
						struct tm tm = *localtime(&t);
						creatore.dataIscrizione.giorno = tm.tm_mday;
						creatore.dataIscrizione.mese = tm.tm_mon + 1;
						creatore.dataIscrizione.anno = tm.tm_year + 1900;

						// Fase di salvataggio dei dati su file
						file = fopen(PERCORSO_FILE_CREATORI, "a");
						if (file == NULL)
						{
							printf("\n\n\nERRORE FATALE! Non e' stato possibile aprire il file\n");
							exit(1);
						}
						else
						{
							// dovrei estrarne una funzione
							fputs("nomeUtente:", file);
							fputs(creatore.nomeUtente, file);
							fputs("\n", file);
							free(creatore.nomeUtente);

							fputs("password:", file);
							fputs(creatore.password, file);
							fputs("\n", file);
							free(creatore.password);

							fputs("nome:", file);
							fputs(creatore.nome, file);
							fputs("\n", file);
							free(creatore.nome);

							fputs("cognome:", file);
							fputs(creatore.cognome, file);
							fputs("\n", file);
							free(creatore.cognome);

							fputs("sesso:", file);
							fputc(creatore.sesso, file);
							fputs("\n", file);

							fputs("professione:", file);
							fputs(creatore.professione, file);
							fputs("\n", file);
							free(creatore.professione);

							fputs("nazionalita:", file);
							fputs(creatore.nazionalita, file);
							fputs("\n", file);
							free(creatore.nazionalita);

							fputs("dataNascita:", file);
							fprintf(file, "%u/%u/%u\n", creatore.dataNascita.giorno, creatore.dataNascita.mese, creatore.dataNascita.anno);

							fputs("dataIscrizione:", file);
							fprintf(file, "%u/%u/%u\n", creatore.dataIscrizione.giorno, creatore.dataIscrizione.mese, creatore.dataIscrizione.anno);

							fputs("numImmagini:", file);
							fprintf(file, "%u\n", creatore.numImmagini);

							fputs("numDownloadTot:", file);
							fprintf(file, "%u\n", creatore.numDownloadTot);

							fputs("mediaValutazioni:", file);
							fprintf(file, "%f", creatore.mediaValutazioni);

							fclose(file);

							printf("Creatore correttamente registrato! Verrai ora reindirizzato al menu principale.\nPremere INVIO per continuare...");
							SvuotaInput();
							getc(stdin);
							return true;
						}
						break;
					}
					




					// Registrazione utente Utilizzatore
					case 2:
					{
						puts("Registrazione utente creatore");
						// Inserimento NOME UTENTE
						do
						{
							errore = false;
							printf("\nInserire un nome utente (min. 4 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							file = fopen(PERCORSO_FILE_CREATORI, "r");
							unsigned int giaEsistente = false;

							// Se il file non esiste, creane uno
							if (file == NULL)
							{
								file = fopen(PERCORSO_FILE_CREATORI, "w");
								fclose(file);
								file = fopen(PERCORSO_FILE_CREATORI, "r");
							}

							giaEsistente = ControllaNomeUtente(file, buffer);

							fclose(file);

							if (giaEsistente == false)
							{
								file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
								// Se il file non esiste, creane uno
								if (file == NULL)
								{
									file = fopen(PERCORSO_FILE_UTILIZZATORI, "w");
									fclose(file);
									file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
								}

								giaEsistente = ControllaNomeUtente(file, buffer);

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
								AssegnaStringa(&utilizzatore.nomeUtente, buffer, false);
						} while (errore == true);

						// Inserimento PASSWORD
						do
						{
							errore = false;
							printf("Inserire una password (min. 8 caratteri): ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							// Controlla che il minimo sia rispettato
							if (strlen(buffer) < MIN_CAR_PASSWORD)
							{
								errore = true;
								puts("Errore! Inserire una password di almeno 8 caratteri!\n");
							}

							// Altrimenti procedi
							else
								AssegnaStringa(&utilizzatore.password, buffer, false);
						} while (errore == true);

						// Inserimento NOME
						do
						{
							errore = false;
							printf("Inserire il nome: ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer);

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&utilizzatore.nome, buffer, true);
						} while (errore == true);

						// Inserimento COGNOME
						do
						{
							errore = false;
							printf("Inserire il cognome: ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							
							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer);

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&utilizzatore.cognome, buffer, true);
						} while (errore == true);

						// Inserimento SESSO
						do
						{
							errore = false;
							printf("Inserire il sesso (M/F): ");
							SvuotaInput();
							scanf("%c", &utilizzatore.sesso);
							utilizzatore.sesso = toupper(utilizzatore.sesso);

							// Controllo errori
							if (utilizzatore.sesso != 'M' && utilizzatore.sesso != 'F')
							{
								errore = true;
								printf("Errore! Inserire M o F!\n");
							}
						} while (errore == true);

						// Inserimento PROFESSIONE
						do
						{
							errore = false;
							printf("Inserire la professione: ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer);

							if (errore == false)
								AssegnaStringa(&utilizzatore.professione, buffer, true);
						} while (errore == true);

						// Inserimento NAZIONALITA
						do
						{
							errore = false;
							printf("Inserire la nazionalita': ");
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);

							// Conversione della stringa in minuscolo
							ConversioneMinuscolo(buffer);

							// Controlla che non contenga simboli
							errore = ContieneSimboli(buffer);

							// Altrimenti procedi
							if (errore == false)
								AssegnaStringa(&utilizzatore.nazionalita, buffer, true);
						} while (errore == true);

						// Inserimento DATA DI NASCITA
						do
						{
							errore = false;
							printf("Inserire la data di nascita (GG/MM/AAAA): ");
							scanf("%u/%u/%u", &utilizzatore.dataNascita.giorno, &utilizzatore.dataNascita.mese, &utilizzatore.dataNascita.anno);

							if (DataCorretta(utilizzatore.dataNascita.giorno, utilizzatore.dataNascita.mese, utilizzatore.dataNascita.anno) == false)
							{
								errore = true;
								printf("Errore! La data e' incorretta!\n");
							}
						} while (errore == true);

						// Assegnazione data di iscrizione
						time_t t = time(NULL);
						struct tm tm = *localtime(&t);
						utilizzatore.dataIscrizione.giorno = tm.tm_mday;
						utilizzatore.dataIscrizione.mese = tm.tm_mon + 1;
						utilizzatore.dataIscrizione.anno = tm.tm_year + 1900;

						// Fase di salvataggio dei dati su file
						file = fopen(PERCORSO_FILE_UTILIZZATORI, "a");
						if (file == NULL)
						{
							printf("\n\n\nERRORE FATALE! Non e' stato possibile aprire il file\n");
							return;
						}
						else
						{	
							//dovrei estrarne una funzione
							fputs("nomeUtente:", file);
							fputs(utilizzatore.nomeUtente, file);
							fputs("\n", file);
							free(utilizzatore.nomeUtente);

							fputs("password:", file);
							fputs(utilizzatore.password, file);
							fputs("\n", file);
							free(utilizzatore.password);

							fputs("nome:", file);
							fputs(utilizzatore.nome, file);
							fputs("\n", file);
							free(utilizzatore.nome);

							fputs("cognome:", file);
							fputs(utilizzatore.cognome, file);
							fputs("\n", file);
							free(utilizzatore.cognome);

							fputs("sesso:", file);
							fputc(utilizzatore.sesso, file);
							fputs("\n", file);

							fputs("professione:", file);
							fputs(utilizzatore.professione, file);
							fputs("\n", file);
							free(utilizzatore.professione);

							fputs("nazionalita:", file);
							fputs(utilizzatore.nazionalita, file);
							fputs("\n", file);
							free(utilizzatore.nazionalita);

							fputs("dataNascita:", file);
							fprintf(file, "%u/%u/%u\n", utilizzatore.dataNascita.giorno, utilizzatore.dataNascita.mese, utilizzatore.dataNascita.anno);

							fputs("dataIscrizione:", file);
							fprintf(file, "%u/%u/%u\n\n", utilizzatore.dataIscrizione.giorno, utilizzatore.dataIscrizione.mese, utilizzatore.dataIscrizione.anno);

							fputs("numValutazioni:", file);
							fprintf(file, "%u\n", utilizzatore.numValutazioni);

							fputs("numDownloadTot:", file);
							fprintf(file, "%u\n", utilizzatore.numDownloadTot);

							fclose(file);

							printf("\n\nUtilizzatore correttamente registrato! Verrai ora reindirizzato al menu principale.\nPremere INVIO per continuare...");
							SvuotaInput();
							getc(stdin);
							return true;
						}
						break;
					}
					// Indietro
					case 3:
						errore = false;
						break;
					default:
						errore = true;
						printf("Errore! Selezionare un'opzione valida!");
						break;
					}
			} while (errore == true);
			break;
		}






		// Accesso utente
		case 2:
		{
			do
			{
				system("cls");
				printf("Inserire il nome utente: ");
				char bufferNomeUtente[MAX_BUFFER] = { 0 };
				unsigned short int indietro = false;

				scanf("%s", bufferNomeUtente);

				if (bufferNomeUtente[0] == '0')
				{
					if (bufferNomeUtente[1] == '\0')
					{
						errore = false;
						indietro = true;
					}
				}

				if (indietro == false)
				{
					file = fopen(PERCORSO_FILE_CREATORI, "r");
					// Se il file non esiste, creane uno
					if (file == NULL)
					{
						file = fopen(PERCORSO_FILE_CREATORI, "w");
						fclose(file);
						file = fopen(PERCORSO_FILE_CREATORI, "r");
					}

					unsigned short int esisteNomeUtente = ControllaNomeUtente(file, bufferNomeUtente);

					

					if (esisteNomeUtente == false)
					{
						fclose(file);
						file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
						// Se è la prima esecuzione e/o il file non esiste, creane uno
						if (file == NULL)
						{
							file = fopen(PERCORSO_FILE_UTILIZZATORI, "w");
							fclose(file);
							file = fopen(PERCORSO_FILE_UTILIZZATORI, "r");
						}

						esisteNomeUtente = ControllaNomeUtente(file, bufferNomeUtente);
					}



					if (esisteNomeUtente == true)
					{
						printf("Inserire la password: ");
						char bufferPassword[MAX_BUFFER] = { 0 };

						scanf("%s", bufferPassword);
						unsigned short int passwordCorretta = ControllaPassword(file, bufferNomeUtente, bufferPassword);

						if (passwordCorretta == true)
						{
							fclose(file);
							return true;
						}
						else
						{
							printf("Errore! Password non corretta! Riprovare.\n\n");
							puts("Premere INVIO per continuare...");
							SvuotaInput();
							getc(stdin);
							errore = true;
						}

					}
					else
					{
						printf("Errore! Nome utente non esistente. Controllare il nome utente digitato oppure digita 0 per tornare al menu iniziale e registrarsi.\n\n");
						puts("Premere INVIO per continuare...");
						SvuotaInput();
						getc(stdin);
						errore = true;
					}
					fclose(file);
				}
			} while (errore == true);
		
			break;
		}
		case 3:
			inEsecuzione = false;
			break;
		default:
			puts("Errore! Selezionare un'opzione valida!\nPremere INVIO per continuare...");
			SvuotaInput();
			getc(stdin);
			break;
		}

		system("cls");

	} while (inEsecuzione == true);

	return false;
}

void MenuPrincipale()
{

}