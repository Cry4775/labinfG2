#include "MenuCreatore.h"

void GestioneCreatore(char nomeUtente[])
{
	bool ripeti = false;
	bool errore = false;
	do
	{

		unsigned int sceltaMenu;
		ripeti = true;
		system("cls");

		StampaTitolo("*******************\n GESTIONE CREATORE \n*******************\n");

		puts("1. Carica immagine\n2. Modifica immagine\n3. Rimuovi immagine\n4. Visualizza immagine\n5. Indietro\n");
		green();
		printf("->");
		reset();
		if (scanf("%u", &sceltaMenu) == 1)
		{
			SvuotaInput();
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
					StampaErrore("Errore nell'aggiornamento del numero immagini creatore!");
				}
				else
				{
					green();
					printf("\nImmagine caricata con successo!\nPotrai visualizzarla in 'Visualizza immagine' nel menu di GESTIONE CREATORE\n");
					reset();
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
					green();
					printf("\nImmagine modificata con successo!\n\n");
					reset();
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
					red();
					printf("\nImmagine rimossa con successo!\n\n");
					reset();
					system("pause");
				}
				else
				{
					StampaErrore("Errore nella rimozione dell'immagine!");
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
					StampaErrore("Errore nella visualizzazione dell'immagine!");
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
				StampaErrore("Errore! Selezionare un'opzione valida!");
				ripeti = true;
				break;
			}
		}
		else
		{
			SvuotaInput();
			errore = true;
			StampaErrore("Errore! Sono ammessi solo numeri!");
		}
	} while (ripeti);
}

void RicercaImmagineCreatore(char nomeUtente[])
{
	bool ripeti = false;
	bool errore = false;
	do
	{
		errore = false;
		unsigned int sceltaMenu;
		ripeti = true;
		system("cls");

		StampaTitolo("*****************\nRICERCA IMMAGINI\n*****************\n");
		printf("\nSeleziona il metodo di ricerca che piu' preferisci!\n");
		puts("1. Popolari\n2. Categorie\n3. Tags\n4. Indietro\n");
		green();
		printf("->");
		reset();

		if (scanf("%u", &sceltaMenu) == 1)
		{
			SvuotaInput();
			Immagine_t immagine = { 0 };

			// Sottomenu Ricerca Immagine
			switch (sceltaMenu)
			{
			// Ricerca Immagine - Popolari
			case 1:
			{
				system("cls");
				file = ApriFile(PERCORSO_FILE_IMMAGINI);

				FILE* fileCreatori = ApriFile(PERCORSO_FILE_CREATORI);

				Immagine_t immagine[MAX_BUFFER] = { 0 };

				size_t numImmagini = CaricaArrayImmagini(file, immagine);

				SortImmagine(immagine, 0, numImmagini-1, true);
				blue();
				printf("%-30s%-30s%-30s%-30s\n", "Titolo", "Autore", "Numero di download", "Categoria");
				reset();

				// Limito la visualizzazione alle 10 più popolari
				if (numImmagini > 10)
					numImmagini = 10;

				for (size_t i = 0; i < numImmagini; i++)
				{
					printf("%-30s%-30s%-30u%-30s\n", immagine[i].titolo, immagine[i].nomeUtente, immagine[i].numDownload, immagine[i].categoria);
				}

				char autoreImmagine[MAX_BUFFER] = { 0 };
				bool scaricata = VisualizzaImmagine(file, autoreImmagine);
				if (scaricata)
				{
					if (!AggiornaNumDownloadCreatore(fileCreatori, autoreImmagine))
					{
						StampaErrore("Errore nell'aggiornamento del numero di download del creatore!");
					}
					else
					{
						green();
						printf("\nDownload effettuato!\n\n");
						reset();
						unsigned int valutazione = ValutaImmagine(file, nomeUtente);

						// Se non è già stata data la valutazione
						if (valutazione != 0)
						{
							if (AggiornaMediaValutazioniCreatore(fileCreatori, valutazione))
							{
								SalvaValutazione(file, nomeUtente, valutazione);
								green();
								printf("\nValutazione correttamente inviata! Grazie!\n\n");
								reset();
								system("pause");
							}
							else
							{
								StampaErrore("Errore nell'aggiornamento della media valutazioni del creatore!");
							}
						}
					}
				}

				fclose(fileCreatori);

				fclose(file);
				ripeti = true;
				break;
			}
			// Ricerca Immagine - Categorie
			case 2:
			{
				file = ApriFile(PERCORSO_FILE_IMMAGINI);

				RicercaCategoriaMenuCreatore(file, nomeUtente);

				fclose(file);

				ripeti = true;
				break;
			}
			// Ricerca Immagine - Tags
			case 3:
			{
				file = ApriFile(PERCORSO_FILE_IMMAGINI);

				RicercaTagsMenuCreatore(file, nomeUtente);

				fclose(file);

				ripeti = true;
				break;
			}
			// Ricerca Immagine - Indietro
			case 4:
				ripeti = false;
				break;
			default:
				ripeti = true;
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
	} while (ripeti);
}

void RicercaCategoriaMenuCreatore(FILE* file, char nomeUtente[])
{
	FILE* fileCreatori = ApriFile(PERCORSO_FILE_CREATORI);

	// Stampa le immagini a seconda della categoria scelta
	if (RicercaCategoria(file))
	{
		char autoreImmagine[MAX_BUFFER] = { 0 };
		bool scaricata = VisualizzaImmagine(file, autoreImmagine);
		if (scaricata)
		{
			if (!AggiornaNumDownloadCreatore(fileCreatori, autoreImmagine))
			{
				StampaErrore("Errore nell'aggiornamento del numero di download del creatore!");
			}
			else
			{
				unsigned int valutazione = ValutaImmagine(file, nomeUtente);

				// Se non è già stata data la valutazione
				if (valutazione != 0)
				{
					if (AggiornaMediaValutazioniCreatore(fileCreatori, valutazione))
					{
						SalvaValutazione(file, nomeUtente, valutazione);
						green();
						printf("\nValutazione correttamente inviata! Grazie!\n\n");
						reset();
						system("pause");
					}
					else
					{
						StampaErrore("Errore nell'aggiornamento della media valutazioni del creatore!");
					}
				}
			}
		}
	}
	fclose(fileCreatori);
}

void RicercaTagsMenuCreatore(FILE* file, char nomeUtente[])
{
	FILE* fileCreatori = ApriFile(PERCORSO_FILE_CREATORI);

	// Stampa le immagini a seconda della categoria scelta
	if (RicercaTags(file))
	{
		char autoreImmagine[MAX_BUFFER];
		bool scaricata = VisualizzaImmagine(file, autoreImmagine);
		if (scaricata)
		{
			if (!AggiornaNumDownloadCreatore(fileCreatori, autoreImmagine))
			{
				StampaErrore("Errore nell'aggiornamento del numero di download del creatore!");
			}
			else
			{
				unsigned int valutazione = ValutaImmagine(file, nomeUtente);

				// Se non è già stata data la valutazione
				if (valutazione != 0)
				{
					if (AggiornaMediaValutazioniCreatore(fileCreatori, valutazione))
					{
						SalvaValutazione(file, nomeUtente, valutazione);
						green();
						printf("\nValutazione correttamente inviata! Grazie!\n\n");
						reset();
						system("pause");
					}
					else
					{
						StampaErrore("Errore nell'aggiornamento della media valutazioni del creatore!");
					}
				}
			}
		}
	}
	fclose(fileCreatori);
}