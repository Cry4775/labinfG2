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
							file = ApriFile(PERCORSO_FILE_CREATORI);
							SalvaDatiCreatore(file, &creatore);

							fclose(file);

							printf("Creatore correttamente registrato! Verrai ora reindirizzato al menu principale.\n\n");
							system("pause");
							*isCreatore = true; // Do l'accesso al menu principale creatore
							return true;
							break;
						}
					


						// Registrazione utente Utilizzatore
						case 2:
						{
							InserisciDatiUtilizzatore(file, &utilizzatore, nomeUtente);

							// Fase di salvataggio dei dati su file
							file = ApriFile(PERCORSO_FILE_UTILIZZATORI);
						
							SalvaDatiUtilizzatore(file, &utilizzatore);

							fclose(file);

							printf("\n\nUtilizzatore correttamente registrato! Verrai ora reindirizzato al menu principale.\n\n");
							system("pause");
							*isCreatore = false;
							return true;
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
						file = ApriFile(PERCORSO_FILE_CREATORI);

						bool esisteNomeUtente = ControllaNomeUtenteCreatore(file, buffer);
						if (esisteNomeUtente)
							*isCreatore = true;
					

						if (!esisteNomeUtente)
						{
							fclose(file);
							file = ApriFile(PERCORSO_FILE_UTILIZZATORI);

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
							SvuotaInput();
							scanf("%100s", buffer);
						

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
								system("pause");
								errore = true;
							}

						}
						else
						{
							printf("Errore! Nome utente non esistente. \nControllare il nome utente digitato oppure digita 0 per tornare al menu iniziale e registrarsi.\n\n");
							system("pause");
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
				system("pause");
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

			printf("Benvenuto sulla piattaforma di immagini %s! \n\n1. Gestione creatore\n2. Ricerca immagine\n3. Statistiche creatore\n4. Classifiche\n5. Esci\n", nomeUtente);

			unsigned int sceltaMenu;
			bool ripeti = false;
			scanf("%1u", &sceltaMenu);

			switch (sceltaMenu)
			{
				// Gestione creatore
				case 1:
				{
					GestioneCreatore(nomeUtente);
					break;
				}
				// Ricerca immagine
				case 2:
				{
					RicercaImmagine(nomeUtente);

					break;
				}
					
				// case 2, case 3, case 4, case 5 del menu PRINCIPALE
			}
		} while (inEsecuzione == true);
	}
	
	else
	{
		// Menu Utilizzatore
	}
}

void GestioneCreatore(char nomeUtente[])
{
	bool ripeti;
	do
	{
		unsigned int sceltaMenu;
		ripeti = false;
		system("cls");

		puts("1. Carica immagine\n2. Modifica immagine\n3. Rimuovi immagine\n4. Visualizza immagine\n5. Indietro");
		scanf("%1u", &sceltaMenu);

		Immagine_t immagine = { 0 };

		// Sottomenu gestione creatore
		switch (sceltaMenu)
		{
		// Carica immagine - Creatore
		case 1:
		{
			InserisciDatiImmagine(&immagine, nomeUtente);

			// Fase di salvataggio dei dati su file
			file = ApriFile(PERCORSO_FILE_IMMAGINI);

			SalvaDatiImmagine(file, &immagine);

			fclose(file);

			file = ApriFile(PERCORSO_FILE_CREATORI);

			if (!AggiornaNumImmaginiCreatore(file, nomeUtente))
			{
				printf("Errore nell'aggiornamento del profilo creatore!");
				system("pause");
			}
			else
			{
				printf("Immagine caricata con successo!\n\n");
				system("pause");
			}

			fclose(file);
			ripeti = true;
			break;
		}
		// Modifica immagine - Creatore
		case 2:
		{
			file = ApriFile(PERCORSO_FILE_IMMAGINI);

			if (ModificaImmagini(file, nomeUtente))
			{
				printf("\n\nImmagine modificata con successo!\n\n");
				system("pause");
			}
			else
			{
				printf("\n\nErrore nell'aggiornamento dell'immagine!\n\n");
				system("pause");
			}

			fclose(file);
			ripeti = true;
			break;
		}
		// Rimuovi immagine - Creatore
		case 3:
		{
			file = ApriFile(PERCORSO_FILE_IMMAGINI);

			if (RimuoviImmagine(file, nomeUtente))
			{
				printf("\n\nImmagine rimossa con successo!\n\n");
				system("pause");
			}
			else
			{
				printf("\n\nErrore nella rimozione dell'immagine!\n\n");
				system("pause");
			}

			fclose(file);
			ripeti = true;
			break;
		}
		// Visualizza immagine - Creatore
		case 4:
		{
			file = ApriFile(PERCORSO_FILE_IMMAGINI);

			if (VisualizzaImmagineCreatore(file, nomeUtente))
				system("pause");
			else
			{
				printf("\n\nErrore nella visualizzazione dell'immagine!\n\n");
				system("pause");
			}

			fclose(file);
			ripeti = true;
			break;
		}
		// Indietro - Creatore
		case 5:
			ripeti = false;
			break;
		default:
			printf("Errore! Selezionare un'opzione valida!\n\n");
			ripeti = true;
			system("pause");
			break;
		}
	} while (ripeti);
}

void RicercaImmagine(char nomeUtente[])
{
	bool ripeti;
	do
	{
		unsigned int sceltaMenu;
		ripeti = false;
		system("cls");

		puts("1. Popolari\n2. Categorie\n3. Tags\n4. Indietro\n");
		scanf("%1u", &sceltaMenu);

		Immagine_t immagine = { 0 };

		// Sottomenu Ricerca Immagine
		switch (sceltaMenu)
		{
			// Ricerca Immagine - Popolari
			case 1:
			{
				file = ApriFile(PERCORSO_FILE_IMMAGINI);

				// Da fare

				fclose(file);
				ripeti = true;
				break;
			}
			// Ricerca Immagine - Categorie
			case 2:
			{
				file = ApriFile(PERCORSO_FILE_IMMAGINI);
				FILE* fileCreatori = ApriFile(PERCORSO_FILE_CREATORI);

				if (RicercaCategoria(file))
				{
					bool scaricata = VisualizzaImmagine(file);
					if (scaricata)
					{
						if (!AggiornaNumDownloadCreatore(fileCreatori, nomeUtente))
						{
							printf("Errore nell'aggiornamento dei dati del creatore!\n\n");
							system("pause");
						}
						else
						{
							unsigned int valutazione = ValutaImmagine(file);
							if (AggiornaMediaValutazioniCreatore(fileCreatori, valutazione))
							{
								printf("Valutazione correttamente inviata! Grazie!\n\n");
								system("pause");
							}
							else
							{
								printf("Errore nell'aggiornamento dei dati del creatore!\n\n");
								system("pause");
							}
						}
					}
				}

				fclose(file);
				fclose(fileCreatori);
				ripeti = true;
				break;
			}
		}
	} while (ripeti);
}

