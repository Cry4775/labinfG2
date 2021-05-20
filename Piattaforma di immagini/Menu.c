#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"

bool MenuIniziale(bool* isCreatore, char nomeUtente[])
{
	bool inEsecuzione = true;
	do
	{
		puts("Benvenuto sulla piattaforma di immagini! \n\n1. Registrazione utente\n2. Accesso utente\n3. Esci\n");

		unsigned int sceltaMenu;
		bool errore = false;
		scanf("%1u", &sceltaMenu);


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
				scanf("%1u", &sceltaMenu);

				system("cls");

				switch (sceltaMenu)
				{
					// Registrazione utente Creatore
					case 1: 
					{
						InserisciDatiCreatore(file, &creatore, nomeUtente);
						
						// Fase di salvataggio dei dati su file
						file = fopen(PERCORSO_FILE_CREATORI, "rb+");
						if (file == NULL)
						{
							printf("\n\n\nERRORE FATALE! Non e' stato possibile aprire il file\n");
							exit(EXIT_SUCCESS);
						}
						else
						{
							SalvaDatiCreatore(file, &creatore);

							fclose(file);

							printf("Creatore correttamente registrato! Verrai ora reindirizzato al menu principale.\n\n");
							InvioPerContinuare();
							*isCreatore = true; // Do l'accesso al menu principale creatore
							return true;
						}
						break;
					}
					


					// Registrazione utente Utilizzatore
					case 2:
					{
						InserisciDatiUtilizzatore(file, &utilizzatore, nomeUtente);

						// Fase di salvataggio dei dati su file
						file = fopen(PERCORSO_FILE_UTILIZZATORI, "rb+");
						if (file == NULL)
						{
							printf("\n\n\nERRORE FATALE! Non e' stato possibile aprire il file\n");
							exit(EXIT_SUCCESS);
						}
						else
						{	
							SalvaDatiUtilizzatore(file, &utilizzatore);

							fclose(file);

							printf("\n\nUtilizzatore correttamente registrato! Verrai ora reindirizzato al menu principale.\n\n");
							InvioPerContinuare();
							*isCreatore = false;
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
			} while (errore);
			break;
		}




		// Accesso utente
		case 2:
		{
			do
			{
				errore = false;
				*isCreatore = false;
				bool indietro = false; // flag indietro
				system("cls");
				printf("Inserire il nome utente: ");
				char buffer[MAX_BUFFER] = { 0 };

				scanf("%100s", buffer);

				// Controlla se l'utente ha inserito '0', nel caso flagga indietro
				if (buffer[0] == '0')
				{
					if (buffer[1] == '\0')
					{
						errore = false;
						indietro = true;
					}
				}

				// Se invece ha messo un input valido per il nome utente prosegui
				// Controlla prima creatori e poi utilizzatori se necessario
				if (indietro == false)
				{
					file = fopen(PERCORSO_FILE_CREATORI, "rb+");
					// Se il file non esiste, creane uno
					if (file == NULL)
					{
						file = fopen(PERCORSO_FILE_CREATORI, "wb+");
						fclose(file);
						file = fopen(PERCORSO_FILE_CREATORI, "rb+");
					}

					bool esisteNomeUtente = ControllaNomeUtenteCreatore(file, buffer);
					if (esisteNomeUtente)
						*isCreatore = true;
					

					if (!esisteNomeUtente)
					{
						fclose(file);
						file = fopen(PERCORSO_FILE_UTILIZZATORI, "rb+");
						// Se è la prima esecuzione e/o il file non esiste, creane uno
						if (file == NULL)
						{
							file = fopen(PERCORSO_FILE_UTILIZZATORI, "wb+");
							fclose(file);
							file = fopen(PERCORSO_FILE_UTILIZZATORI, "rb+");
						}

						esisteNomeUtente = ControllaNomeUtenteUtilizzatore(file, buffer);
						*isCreatore = false;
						fclose(file);
					}


					// Se il nome utente inserito esiste, chiedi la password
					if (esisteNomeUtente)
					{
						strcpy(nomeUtente, buffer);
						printf("Inserire la password: ");
						char buffer[MAX_BUFFER] = { 0 };
						scanf("%100s", buffer);
						SvuotaInputGetChar();

						bool passwordCorretta = ControllaPassword(file, buffer, nomeUtente);

						if (passwordCorretta)
						{
							fclose(file);
							return true;
							// Esci dal menu iniziale e prosegui nel main col menu principale
						}
						else
						{
							printf("Errore! Password non corretta! Riprovare.\n\n");
							InvioPerContinuare();
							errore = true;
						}

					}
					else
					{
						printf("Errore! Nome utente non esistente. \nControllare il nome utente digitato oppure digita 0 per tornare al menu iniziale e registrarsi.\n\n");
						InvioPerContinuare();
						errore = true;
					}
					fclose(file);
				}
			} while (errore);
		
			break;
		}


		case 3:
			inEsecuzione = false;
			break;
		default:
			puts("Errore! Selezionare un'opzione valida!\n");
			InvioPerContinuare();
			break;
		}

		system("cls");

	} while (inEsecuzione == true);

	return false;
}

void MenuPrincipale(bool* isCreatore, char nomeUtente[])
{
	
	bool inEsecuzione = true;
	if (*isCreatore)
	{
		do
		{
			system("cls");

			puts("Benvenuto sulla piattaforma di immagini! \n\n1. Gestione creatore\n2. Ricerca immagine\n3. Statistiche creatore\n4. Classifiche\n5. Esci");

			unsigned int sceltaMenu;
			bool errore = false;
			scanf("%1u", &sceltaMenu);

			switch (sceltaMenu)
			{
				// Gestione creatore
				case 1:
				{
					system("cls");

					puts("1. Carica immagine\n2. Modifica immagine\n3. Rimuovi immagine\n4. Visualizza statistiche\n5. Indietro");
					scanf("%1u", &sceltaMenu);

					Immagine_t immagine = { 0 };

					// Sottomenu gestione creatore
					switch (sceltaMenu)
					{
						// Carica immagine
						case 1:
						{
							InserisciDatiImmagine(&immagine, nomeUtente);


							// Fase di salvataggio dei dati su file
							file = fopen(PERCORSO_FILE_IMMAGINI, "rb+");
							if (file == NULL)
							{
								file = fopen(PERCORSO_FILE_IMMAGINI, "wb+");
								fclose(file);
								file = fopen(PERCORSO_FILE_IMMAGINI, "rb+");
							}
							
							SalvaDatiImmagine(file, &immagine);
							fclose(file);

							if (file = fopen(PERCORSO_FILE_CREATORI, "rb+"))
							{
								if (!AggiornaNumImmaginiCreatore(file, nomeUtente))
								{
									printf("Errore nell'aggiornamento del profilo creatore!");
									InvioPerContinuare();
								}
								else
								{
									printf("Immagine caricata con successo!\n\n");
									InvioPerContinuare();
								}
								fclose(file);
							}
							
							break;
						}
						// Modifica immagine
						case 2:
						{
							file = fopen(PERCORSO_FILE_IMMAGINI, "rb+");
							if (file == NULL)
							{
								file = fopen(PERCORSO_FILE_IMMAGINI, "wb+");
								fclose(file);
								file = fopen(PERCORSO_FILE_IMMAGINI, "rb+");
							}

							ModificaImmagini(file, nomeUtente);
							break;
						}
						
					}
				}
			}






		} while (inEsecuzione == true);
	}
	
	else
	{
		// Menu Utilizzatore
	}
}