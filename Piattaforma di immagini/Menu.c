#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"

void MenuIniziale()
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
			do
			{
				errore = false;
				Creatore_t creatore = { 0 };

				puts("\nChe tipologia di utente sei?\n1. Creatore\n2. Utilizzatore\n3. Indietro\n");
				scanf("%1d", &sceltaMenu);

				switch (sceltaMenu)
				{
				case 1: // Registrazione utente Creatore
					do
					{
						errore = false;
						printf("\nInserire un nome utente (min. 4 caratteri): ");
						char buffer[MAX_BUFFER] = { 0 };
						scanf("%100s", buffer);
						if (strlen(buffer) < MIN_CAR_NOME_UTENTE)
						{
							errore = true;
							puts("Errore! Inserire un nome utente di almeno 4 caratteri!\n");
						}
						//else if nomeUtente già esistente, da implementare coi file
						// Altrimenti procedi
						else
							AssegnaStringa(&creatore.nomeUtente, buffer);
						//free(creatore.nomeUtente)
					} while (errore == true);

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
							AssegnaStringa(&creatore.password, buffer);
					} while (errore == true);

					do
					{
						errore = false;
						printf("Inserire il nome: ");
						char buffer[MAX_BUFFER] = { 0 };
						scanf("%100s", buffer);
						buffer[0] = toupper(buffer[0]);

						// Controlla che non si inseriscano numeri
						size_t i = 0;
						while (i < strlen(buffer) && errore == false)
						{
							if (buffer[i] >= '0' && buffer[i] <= '9')
							{
								//errore = true;
								printf("Errore! I numeri non sono ammessi!\n");
							}
							i++;
						}

						// Altrimenti procedi
						if (errore == false)
							AssegnaStringa(&creatore.nome, buffer);
					} while (errore == true);

					do
					{
						errore = false;
						printf("Inserire il cognome: ");
						char buffer[MAX_BUFFER] = { 0 };
						scanf("%100s", buffer);
						buffer[0] = toupper(buffer[0]);

						// Controlla che non si inseriscano numeri
						size_t i = 0;
						while (i < strlen(buffer) && errore == false)
						{
							if (buffer[i] >= '0' && buffer[i] <= '9')
							{
								errore = true;
								printf("Errore! I numeri non sono ammessi!\n");
							}
							i++;
						}

						// Altrimenti procedi
						if (errore == false)
							AssegnaStringa(&creatore.cognome, buffer);
					} while (errore == true);

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

					errore = false;
					printf("Inserire la professione: ");
					char buffer[MAX_BUFFER] = { 0 };
					scanf("%100s", buffer);
					buffer[0] = toupper(buffer[0]);
					AssegnaStringa(&creatore.professione, buffer);

					do
					{
						errore = false;
						printf("Inserire la nazionalita': ");
						char buffer[MAX_BUFFER] = { 0 };
						scanf("%100s", buffer);
						buffer[0] = toupper(buffer[0]);

						// Controlla che non si inseriscano numeri
						size_t i = 0;
						while (i < strlen(buffer) && errore == false)
						{
							if (buffer[i] >= '0' && buffer[i] <= '9')
							{
								errore = true;
								printf("Errore! I numeri non sono ammessi!\n");
							}
							i++;
						}

						// Altrimenti procedi
						if (errore == false)
							AssegnaStringa(&creatore.nazionalita, buffer);
					} while (errore == true);

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

					// Assegna data di iscrizione
					time_t t = time(NULL);
					struct tm tm = *localtime(&t);
					creatore.dataIscrizione.giorno = tm.tm_mday;
					creatore.dataIscrizione.mese = tm.tm_mon + 1;
					creatore.dataIscrizione.anno = tm.tm_year + 1900;
					break;
				default:
					break;
				}
			} while (errore == true);
			break;
		case 3:
			inEsecuzione = false;
			break;
		default:
			puts("Errore! Selezionare un'opzione valida!");
			break;
		}
	} while (inEsecuzione == true);
}