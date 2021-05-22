#include "MenuCreatore.h"

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

void RicercaImmagineCreatore(char nomeUtente[])
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

			// Da fare con l'ordinamento
			FILE* fileCreatori = ApriFile(PERCORSO_FILE_CREATORI);

			Immagine_t immagine[MAX_BUFFER] = { 0 };

			size_t numImmagini = CaricaArrayImmagini(file, immagine);

			BubbleSortImmagine(immagine, numImmagini, true);
			printf("%-30s%-30s%-30s%-30s\n", "Titolo", "Autore", "Numero di download", "Categoria");

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
					printf("Errore nell'aggiornamento dei dati del creatore!\n\n");
					system("pause");
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
							printf("Valutazione correttamente inviata! Grazie!\n\n");
							system("pause");
						}
						else
						{
							printf("Errore nell'aggiornamento dei dati!\n\n");
							system("pause");
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
				printf("Errore nell'aggiornamento dei dati del creatore!\n\n");
				system("pause");
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
				printf("Errore nell'aggiornamento dei dati del creatore!\n\n");
				system("pause");
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
	}
	fclose(fileCreatori);
}