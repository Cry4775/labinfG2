#include "Menu.h"


bool MenuIniziale(bool* isCreatore, char nomeUtente[])
{
	bool inEsecuzione = true;
	bool errore = false;
	do
	{
		system("cls");
		errore = false;

		StampaTitolo("  ____                                  _                    _ _                         _                     _       _   _         __                                  _ _   _                                 _       _ _ ");
		StampaTitolo(" | __ )  ___ _ ____   _____ _ __  _   _| |_ ___    ___ _   _| | | __ _   _ __   ___  ___| |_ _ __ __ _   _ __ (_) __ _| |_| |_ __ _ / _| ___  _ __ _ __ ___   __ _    __| (_) (_)_ __ ___  _ __ ___   __ _  __ _(_)_ __ (_) |");
		StampaTitolo(" |  _ \\ / _ \\ '_ \\ \\ / / _ \\ '_ \\| | | | __/ _ \\  / __| | | | | |/ _` | | '_ \\ / _ \\/ __| __| '__/ _` | | '_ \\| |/ _` | __| __/ _` | |_ / _ \\| '__| '_ ` _ \\ / _` |  / _` | | | | '_ ` _ \\| '_ ` _ \\ / _` |/ _` | | '_ \\| | |");
		StampaTitolo(" | |_) |  __/ | | \\ V /  __/ | | | |_| | || (_) | \\__ \\ |_| | | | (_| | | | | | (_) \\__ \\ |_| | | (_| | | |_) | | (_| | |_| || (_| |  _| (_) | |  | | | | | | (_| | | (_| | | | | | | | | | | | | | | (_| | (_| | | | | | |_|");
		StampaTitolo(" |____/ \\___|_| |_|\\_/ \\___|_| |_|\\__,_|\\__\\___/  |___/\\__,_|_|_|\\__,_| |_| |_|\\___/|___/\\__|_|  \\__,_| | .__/|_|\\__,_|\\__|\\__\\__,_|_|  \\___/|_|  |_| |_| |_|\\__,_|  \\__,_|_| |_|_| |_| |_|_| |_| |_|\\__,_|\\__, |_|_| |_|_(_)");
		StampaTitolo("                                                                                                        |_|                                                                                                |___/             ");

		green();
		printf("\n\n###MENU INIZIALE###");
		reset();
		printf("\nInserisci il numero della tua scelta:");
		printf("\n\n1. Registrazione utente\n2. Accesso utente\n3. Esci\n");
		green();
		printf("\n->");
		reset();

		unsigned int sceltaMenu;
		
		if (scanf("%u", &sceltaMenu) == 1)
		{
			SvuotaInput();
			switch (sceltaMenu)
			{
			case 1: // Registrazione utente
			{
				do
				{
					system("cls");
					errore = false;
					Creatore_t creatore = { 0 };
					Utilizzatore_t utilizzatore = { 0 };

					green();
					puts("###Scegli il profilo con cui registrarti###");
					reset();
					printf("\n1.Creatore\n2.Utilizzatore\n3.Indietro\n");
					green();
					printf("\n->");
					reset();

					if (scanf("%u", &sceltaMenu) == 1)
					{
						SvuotaInput();
						switch (sceltaMenu)
						{
						// Registrazione utente Creatore
						case 1:
						{
							system("cls");
							InserisciDatiCreatore(file, &creatore, nomeUtente);

							// Fase di salvataggio dei dati su file
							file = ApriFile(PERCORSO_FILE_CREATORI);
							SalvaDatiCreatore(file, &creatore);

							fclose(file);

							green();
							printf("\nCreatore correttamente registrato! Verrai ora reindirizzato al menu principale.\n\n");
							reset();
							system("pause");
							*isCreatore = true; // Do l'accesso al menu principale creatore
							return true;
							break;
						}



						// Registrazione utente Utilizzatore
						case 2:
						{
							system("cls");
							InserisciDatiUtilizzatore(file, &utilizzatore, nomeUtente);

							// Fase di salvataggio dei dati su file
							file = ApriFile(PERCORSO_FILE_UTILIZZATORI);

							SalvaDatiUtilizzatore(file, &utilizzatore);

							fclose(file);

							red();
							printf("\nUtilizzatore correttamente registrato! Verrai ora reindirizzato al menu principale.\n\n");
							reset();
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
							StampaErrore("Errore! Selezionare un'opzione valida!");
							break;
						}
					}
					else
					{
						SvuotaInput();
						errore = true;
						StampaErrore("Errore! Sono ammessi solo numeri!");
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
					green();
					printf("Inserire il nome utente: ");
					reset();
					char buffer[MAX_BUFFER] = { 0 };

					scanf("%100s", buffer);
					SvuotaInput();

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
							green();
							printf("Inserire la password: ");
							reset();
							char buffer[MAX_BUFFER] = { 0 };
							scanf("%100s", buffer);
							SvuotaInput();


							bool passwordCorretta = ControllaPassword(file, buffer, nomeUtente);

							if (passwordCorretta)
							{
								fclose(file);
								return true;
								// Esci dal menu iniziale e prosegui nel main col menu principale
							}
							else
							{
								StampaErrore("Errore! Password non corretta! Riprovare.");
								errore = true;
							}

						}
						else
						{
							StampaErrore("Errore! Nome utente non esistente. \nControllare il nome utente digitato oppure digita 0 per tornare al menu iniziale e registrarsi");
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
				StampaErrore("Errore! Selezionare un'opzione valida!");
				errore = true;
				break;
			}
			system("cls");
		}
		else
		{
			SvuotaInput();
			errore = true;
			StampaErrore("Errore! Sono ammessi solo numeri!");
		}

	} while (inEsecuzione == true);

	return false;
}

void MenuPrincipale(bool* isCreatore, char nomeUtente[])
{
	
	bool inEsecuzione = true;
	bool errore = false;
	if (*isCreatore)
	{
		// Menu Creatore
		do
		{
			errore = false;
			system("cls");

			StampaTitolo("###################\n# MENU PRINCIPALE #\n###################\n");
			green();
			printf("Ciao %s!\nScegli a quale sezione accedere:\n\n", nomeUtente);
			reset();
			printf("1. Gestione creatore\n2. Ricerca immagine\n3. Statistiche creatore\n4. Classifiche\n5. Esci\n");
			green();
			printf("\n->");
			reset();
			unsigned int sceltaMenu;
			if (scanf("%u", &sceltaMenu) == 1)
			{
				SvuotaInput();
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
					RicercaImmagineCreatore(nomeUtente);
					break;
				}
				// Statistiche creatore
				case 3:
				{
					StatisticheCreatore();
					break;
				}
				// Classifiche
				case 4:
				{
					Classifiche();
					break;
				}
				// Esci
				case 5:
				{
					inEsecuzione = false;
					system("cls");
					break;
				}
				default:
					StampaErrore("Errore! Selezionare un'opzione valida!");
					break;
				}
			}
			else
			{
				SvuotaInput();
				errore = true;
				StampaErrore("Errore! Sono ammessi solo numeri!");
			}
		} while (inEsecuzione == true);
	}
	
	else
	{
		// Menu Utilizzatore
		do
		{
			errore = false;
			system("cls");
			StampaTitolo("###################\n# MENU PRINCIPALE #\n###################\n");
			green();
			printf("Ciao %s!\nScegli a quale sezione accedere:\n\n", nomeUtente);
			reset();
			printf("1. Ricerca immagine\n2. Statistiche creatore\n3. Classifiche\n4. Esci\n");
			green();
			printf("\n->");
			reset();

			unsigned int sceltaMenu;
			if (scanf("%u", &sceltaMenu) == 1)
			{
				SvuotaInput();
				switch (sceltaMenu)
				{
				// Ricerca immagine
				case 1:
				{
					RicercaImmagineUtilizzatore(nomeUtente);
					break;
				}
				// Statistiche creatore
				case 2:
				{
					StatisticheCreatore();
					break;
				}
				// Classifiche
				case 3:
				{
					Classifiche();
					break;
				}
				// Esci
				case 4:
				{
					inEsecuzione = false;
					system("cls");
					break;
				}
				default:
					StampaErrore("Errore! Selezionare un'opzione valida!");
					break;
				}
			}
			else
			{
				SvuotaInput();
				errore = true;
				StampaErrore("Errore! Sono ammessi solo numeri!");
			}
		} while (inEsecuzione == true);
	}
}