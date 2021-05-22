#include "MenuUtilizzatore.h"


void RicercaImmagineUtilizzatore(char nomeUtente[])
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
			FILE* fileUtilizzatori = ApriFile(PERCORSO_FILE_UTILIZZATORI);

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
				else if (!AggiornaNumDownloadUtilizzatore(fileUtilizzatori, nomeUtente))
				{
					printf("Errore nell'aggiornamento dei dati dell'utilizzatore!\n\n");
					system("pause");
				}
				else
				{
					unsigned int valutazione = ValutaImmagine(file, nomeUtente);

					// Se non � gi� stata data la valutazione
					if (valutazione != 0)
					{
						if (AggiornaMediaValutazioniCreatore(fileCreatori, valutazione) && AggiornaNumValutazioniUtilizzatore(fileUtilizzatori))
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
			fclose(fileUtilizzatori);

			fclose(file);
			ripeti = true;
			break;
		}
		// Ricerca Immagine - Categorie
		case 2:
		{
			file = ApriFile(PERCORSO_FILE_IMMAGINI);

			RicercaCategoriaMenuUtilizzatore(file, nomeUtente);

			fclose(file);

			ripeti = true;
			break;
		}
		// Ricerca Immagine - Tags
		case 3:
		{
			file = ApriFile(PERCORSO_FILE_IMMAGINI);

			RicercaTagsMenuUtilizzatore(file, nomeUtente);

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

void RicercaCategoriaMenuUtilizzatore(FILE* file, char nomeUtente[])
{
	FILE* fileCreatori = ApriFile(PERCORSO_FILE_CREATORI);
	FILE* fileUtilizzatori = ApriFile(PERCORSO_FILE_UTILIZZATORI);

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
			else if (!AggiornaNumDownloadUtilizzatore(fileUtilizzatori, nomeUtente))
			{
				printf("Errore nell'aggiornamento dei dati dell'utilizzatore!\n\n");
				system("pause");
			}
			else
			{
				unsigned int valutazione = ValutaImmagine(file, nomeUtente);

				// Se non � gi� stata data la valutazione
				if (valutazione != 0)
				{
					if (AggiornaMediaValutazioniCreatore(fileCreatori, valutazione) && AggiornaNumValutazioniUtilizzatore(fileUtilizzatori))
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
	fclose(fileUtilizzatori);
	fclose(fileCreatori);
}

void RicercaTagsMenuUtilizzatore(FILE* file, char nomeUtente[])
{
	FILE* fileCreatori = ApriFile(PERCORSO_FILE_CREATORI);
	FILE* fileUtilizzatori = ApriFile(PERCORSO_FILE_UTILIZZATORI);

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
			else if (!AggiornaNumDownloadUtilizzatore(fileUtilizzatori, nomeUtente))
			{
				printf("Errore nell'aggiornamento dei dati dell'utilizzatore!\n\n");
				system("pause");
			}
			else
			{
				unsigned int valutazione = ValutaImmagine(file, nomeUtente);

				// Se non � gi� stata data la valutazione
				if (valutazione != 0)
				{
					if (AggiornaMediaValutazioniCreatore(fileCreatori, valutazione) && AggiornaNumValutazioniUtilizzatore(fileUtilizzatori))
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
	fclose(fileUtilizzatori);
	fclose(fileCreatori);
}

void StatisticheCreatore()
{
	bool errore = false;
	do
	{
		file = ApriFile(PERCORSO_FILE_CREATORI);
		errore = false;

		system("cls");

		char buffer[MAX_BUFFER] = { 0 };
		printf("Inserire il nome utente del creatore di cui si vogliono visualizzare le statistiche: ");
		SvuotaInput();
		scanf("%s", buffer);

		bool trovato = false;
		Creatore_t creatore = { 0 };

		while (!feof(file) && !trovato)
		{
			int esito = fread(&creatore, sizeof(Creatore_t), 1, file);

			if (esito != 0)
			{
				if (strcmp(creatore.nomeUtente, buffer) == 0)
					trovato = true;
			}
			else
				trovato = false;
		}

		fclose(file);

		if (trovato)
		{
			// Stampa l'intestazione delle statistiche
			system("cls");
			printf("Nome utente: %s\n\n", creatore.nomeUtente);
			printf("%-30s%-30s%-30s\n", "Categorie", "Numero di download", "Attivita'");

			FILE* fileImmagini = ApriFile(PERCORSO_FILE_IMMAGINI);
			Immagine_t immagine = { 0 };

			unsigned int occorrenzeCategoria[NUM_CATEGORIE] = { 0 };
			unsigned int numDownloadCategoria[NUM_CATEGORIE] = { 0 };

			// Calcola occorrenze e numeri di download nelle categorie
			while (!feof(fileImmagini))
			{
				int esito = fread(&immagine, sizeof(Immagine_t), 1, fileImmagini);

				if (esito != 0)
				{
					if (strcmp(immagine.nomeUtente, creatore.nomeUtente) == 0)
					{
						size_t i = 0;
						trovato = false;

						while (i < NUM_CATEGORIE && !trovato)
						{
							if (strcmp(immagine.categoria, categoria[i]) == 0)
							{
								occorrenzeCategoria[i]++;
								numDownloadCategoria[i] = numDownloadCategoria[i] + immagine.numDownload;
								trovato = true;
							}
							else
								i++;
						}
					}
				}
			}


			unsigned int occorrenzeTot = 0;
			// Calcola l'istogramma
			for (size_t i = 0; i < NUM_CATEGORIE; i++)
			{
				occorrenzeTot += occorrenzeCategoria[i];
			}

			float percentualiOccorrenze[NUM_CATEGORIE] = { 0 };

			for (size_t i = 0; i < NUM_CATEGORIE; i++)
			{
				percentualiOccorrenze[i] = ((float)occorrenzeCategoria[i] / (float)occorrenzeTot) * 10;
			}

			// Visualizza le statistiche
			for (size_t i = 0; i < NUM_CATEGORIE; i++)
			{
				if (occorrenzeCategoria[i] != 0)
				{
					printf("%-30s%-30u%-30s\n", categoria[i], numDownloadCategoria[i], CreaIstogramma((int)percentualiOccorrenze[i]));
				}
			}
			printf("\n\n");
			system("pause");

		}
		else
		{
			printf("Nome utente non esistente!\n\n");
			errore = true;
			system("pause");
		}


	} while (errore);
}

void Classifiche()
{
	bool ripeti;
	do
	{
		unsigned int sceltaMenu;
		ripeti = false;
		system("cls");

		puts("1. Classifica immagini\n2. Classifica creatori\n3. Classifica utilizzatori\n4. Indietro\n");
		scanf("%1u", &sceltaMenu);



		// Sottomenu Classifiche
		switch (sceltaMenu)
		{
			// Classifica immagini
			case 1:
			{
				system("cls");
				Immagine_t immagine[MAX_BUFFER] = { 0 };

				size_t numImmagini = CaricaArrayImmagini(file, immagine);

				printf("1. Per numero di download\n2. Per valutazione media\n3. Indietro\n\n");
				scanf("%1u", &sceltaMenu);

				switch (sceltaMenu)
				{
					case 1:
					{
						system("cls");
						//Ordiniamo per numero di download
						BubbleSortImmagine(immagine, numImmagini, true);
						printf("%-30s%-30s%-30s%-30s\n", "Titolo", "Autore", "Numero di download", "Categoria");

						for (size_t i = 0; i < numImmagini; i++)
						{
							printf("%-30s%-30s%-30u%-30s\n", immagine[i].titolo, immagine[i].nomeUtente, immagine[i].numDownload, immagine[i].categoria);
						}
						system("pause");
						break;
					}
					case 2:
					{
						system("cls");
						//Ordiniamo per valutazione media
						BubbleSortImmagine(immagine, numImmagini, false);
						printf("%-30s%-30s%-30s%-30s\n", "Titolo", "Autore", "Valutazione media", "Categoria");

						for (size_t i = 0; i < numImmagini; i++)
						{
							printf("%-30s%-30s%-30.1f%-30s\n", immagine[i].titolo, immagine[i].nomeUtente, immagine[i].valutazioneMedia, immagine[i].categoria);
						}
						system("pause");
						break;
					}
					case 3:
					{
						break;
					}
				}
				ripeti = true;
				break;
			}
			// Classifica creatori
			case 2:
			{
				system("cls");
				Creatore_t creatore[MAX_BUFFER] = { 0 };

				size_t numCreatori = CaricaArrayCreatori(file, creatore);

				printf("1. Per numero di download\n2. Per valutazione media\n3. Indietro\n\n");
				scanf("%1u", &sceltaMenu);

				switch (sceltaMenu)
				{
					case 1:
					{
						system("cls");
						//Ordiniamo per numero di download
						BubbleSortCreatore(creatore, numCreatori, true);
						printf("%-30s%-30s%-30s%-30s\n", "Nome utente", "Numero di immagini", "Numero di download", "Media valutazioni");

						for (size_t i = 0; i < numCreatori; i++)
						{
							printf("%-30s%-30u%-30u%-30.1f\n", creatore[i].nomeUtente, creatore[i].numImmagini, creatore[i].numDownloadTot, creatore[i].mediaValutazioni);
						}
						system("pause");
						break;
					}
					case 2:
					{
						system("cls");
						//Ordiniamo per valutazione media
						BubbleSortCreatore(creatore, numCreatori, false);
						printf("%-30s%-30s%-30s%-30s\n", "Nome utente", "Numero di immagini", "Numero di download", "Media valutazioni");

						for (size_t i = 0; i < numCreatori; i++)
						{
							printf("%-30s%-30u%-30u%-30.1f\n", creatore[i].nomeUtente, creatore[i].numImmagini, creatore[i].numDownloadTot, creatore[i].mediaValutazioni);
						}
						system("pause");
						break;
					}
					case 3:
					{
						break;
					}
				}

				ripeti = true;
				break;
			}
			// Classifica utilizzatori
			case 3:
			{
				system("cls");
				Utilizzatore_t utilizzatore[MAX_BUFFER] = { 0 };

				size_t numUtilizzatori = CaricaArrayUtilizzatori(file, utilizzatore);

				printf("1. Per numero di download\n2. Per numero di valutazioni\n3. Indietro\n\n");
				scanf("%1u", &sceltaMenu);

				switch (sceltaMenu)
				{
					case 1:
					{
						system("cls");
						//Ordiniamo per numero di download
						BubbleSortUtilizzatore(utilizzatore, numUtilizzatori, true);
						printf("%-30s%-30s%-30s\n", "Nome utente", "Numero di download", "Numero di valutazioni");

						for (size_t i = 0; i < numUtilizzatori; i++)
						{
							printf("%-30s%-30u%-30u\n", utilizzatore[i].nomeUtente, utilizzatore[i].numDownloadTot, utilizzatore[i].numValutazioni);
						}
						system("pause");
						break;
					}
					case 2:
					{
						system("cls");
						//Ordiniamo per numero di valutazioni
						BubbleSortUtilizzatore(utilizzatore, numUtilizzatori, true);
						printf("%-30s%-30s%-30s\n", "Nome utente", "Numero di download", "Numero di valutazioni");

						for (size_t i = 0; i < numUtilizzatori; i++)
						{
							printf("%-30s%-30u%-30u\n", utilizzatore[i].nomeUtente, utilizzatore[i].numDownloadTot, utilizzatore[i].numValutazioni);
						}
						system("pause");
						break;
					}
					case 3:
					{
						break;
					}
				}

				ripeti = true;
				break;
			}
			// Indietro
			case 4:
			{
				ripeti = false;
				break;
			}
			default:
				printf("Errore! Selezionare un'opzione valida!\n\n");
				ripeti = true;
				system("pause");
				break;
		}
	} while (ripeti);
}