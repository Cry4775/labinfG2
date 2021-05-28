#include "Immagini.h"

const char* formato[NUM_FORMATI] = { ".jpeg", ".jpg", ".png", ".bmp", ".gif", ".ico", ".svg", ".webp" };
const char* tipologia[NUM_FORMATI] = { "Immagine JPEG", "Immagine JPG", "Immagine PNG", "Bitmap", "GIF", "Icona", "Vettoriale", "Immagine compressa" };
const char* categoria[NUM_CATEGORIE] = { "Cibo", "Lavoro", "Moda e Design", "Natura e Animali", "Paesaggi", "Scienza e Spazio", "Sport e Fitness" };
const char* tags[NUM_TAGS] = { "Colazione", "Pranzo", "Cena", "Capo", "Collega", "Scrivania", "Arte", "Matrimonio", "Sfilata", "Cane", "Gatto",
                               "Mare", "Montagne", "Alpi", "Lago", "Luna", "Marte", "Razzo", "Calcio", "Palestra", "Olimpiadi" };

void InserisciDatiImmagine(Immagine_t* immagine, const char nomeUtente[])
{
	bool errore = false;

	char scelta = { 0 };

	green();
	printf("\nVuoi che i dati vengano inseriti automaticamente? (Y/N): ");
	reset();

	if (scanf("%c", &scelta) == 1)
	{
		SvuotaInput();
		scelta = toupper(scelta);
		if (scelta == 'Y')
		{
			for (size_t i = 0; i < 8; i++)
			{
				immagine->titolo[i] = RNG('a', 'z');
			}
			immagine->titolo[0] = toupper(immagine->titolo[0]);

			strcpy(immagine->categoria, categoria[RNG(0, NUM_CATEGORIE)]);
			strcpy(immagine->tags[0], tags[RNG(0, NUM_TAGS)]);

		}

		else
		{
			// Inserimento TITOLO
			do
			{

				errore = false;
				system("cls");
				green();
				printf("Inserire il titolo dell'immagine: ");
				reset();

				char buffer[MAX_BUFFER] = { 0 };
				scanf("%[^\n]100", buffer);
				SvuotaInput();

				// Controlla che non contenga simboli
				errore = ContieneSimboli(buffer, true);

				// Altrimenti procedi
				if (!errore)
					AssegnaStringa(immagine->titolo, buffer, true);

			} while (errore);

			// Inserimento CATEGORIA
			do
			{
				errore = false;
				printf("\n");

				StampaCategorieDisponibili();

				green();
				printf("\n\nInserire il numero della categoria scelta: ");
				reset();

				InserisciCategoriaCaricamento(&immagine);

			} while (errore);

			// Inserimento TAGS
			do
			{
				printf("\n");
				errore = false;

				StampaTagsDisponibili();

				InserisciTagsCaricamento(&immagine);

			} while (errore);
		}
		// Assegnazione AUTORE
		AssegnaStringa(immagine->nomeUtente, nomeUtente, false);

		// Assegnazione FORMATO e TIPOLOGIA
		int indiceFormato = RNG(0, NUM_FORMATI);
		AssegnaStringa(immagine->formato, formato[indiceFormato], false);
		AssegnaStringa(immagine->tipologia, tipologia[indiceFormato], false);

		// Assegnazione NOME FILE
		char buffer[MAX_BUFFER] = { 0 };
		strcpy(buffer, immagine->titolo);
		strcat(buffer, immagine->formato);
		AssegnaStringa(immagine->nomeFile, buffer, false);

		// Assegnazione DATA DI CREAZIONE
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		immagine->dataCaricamento.giorno = tm.tm_mday;
		immagine->dataCaricamento.mese = tm.tm_mon + 1;
		immagine->dataCaricamento.anno = tm.tm_year + 1900;

		// Assegnazione RISOLUZIONE (supponiamo proporzioni 16:9)
		immagine->risoluzione.x = RNG(480, 3840);
		immagine->risoluzione.y = immagine->risoluzione.x / 1.7777;

		// Assegnazione DIMENSIONE (in MB) - Moltiplichiamo il numero totale dei pixel per 3 byte ovvero il peso di ogni pixel e dividiamo per ottenere i megabyte
		immagine->dimensione = (float)((immagine->risoluzione.x * immagine->risoluzione.y) * 3) / 1000000;
	}
	else
	{
		SvuotaInput();
		errore = true;
		StampaErrore("Errore! Sono ammessi solo caratteri!");
	}
}

void SalvaDatiImmagine(FILE* file, Immagine_t* immagine)
{
	Immagine_t precImmagine = { 0 };

	// Controllo innanzitutto che non ci sia un buco (un immagine rimossa)
	bool trovatoBuco = false;
	rewind(file);
	while (!feof(file) && !trovatoBuco)
	{
		Immagine_t tempImmagine = { 0 };
		int esito = fread(&tempImmagine, sizeof(Immagine_t), 1, file);

		if (esito != 0)
		{
			if (tempImmagine.id == 0)
			{
				// Mando il cursore a 2 struct prima (struct vuota -> struct precedente a quella vuota)
				fseek(file, -(int)sizeof(Immagine_t) * 2, SEEK_CUR);
				fread(&precImmagine, sizeof(Immagine_t), 1, file);

				// Mi salvo la posizione per flushare tra un'operazione e l'altra
				long posizioneAttuale = ftell(file);

				immagine->id = precImmagine.id + 1;
				fseek(file, posizioneAttuale, SEEK_SET);
				fwrite(&*immagine, sizeof(Immagine_t), 1, file);
				trovatoBuco = true;
			}
		}
	}

	if (!trovatoBuco)
	{
		fseek(file, -(int)sizeof(Immagine_t), SEEK_END);
		fread(&precImmagine, sizeof(Immagine_t), 1, file);
		immagine->id = precImmagine.id + 1;
		fwrite(&*immagine, sizeof(Immagine_t), 1, file);
	}
}

bool ModificaImmagini(FILE* file, const char nomeUtente[])
{
	bool errore = false;
	do
	{

		errore = false; 

		system("cls");
		rewind(file);

		bool trovato = StampaImmaginiCaricate(file, nomeUtente); // trovato = c'è almeno un'immagine caricata dall'utente?

		if (trovato)
		{

			rewind(file);

			// Inserimento titolo dell'immagine da modificare
			char buffer[MAX_BUFFER] = { 0 };
			green();
			printf("\n\nInserisci il titolo dell'immagine da modificare: ");
			reset();

			scanf("%[^\n]100", buffer);
			SvuotaInput();

			buffer[0] = toupper(buffer[0]);

			// Controlla che non contenga simboli
			errore = ContieneSimboli(buffer, true);

			if (!errore)
			{
				while (!feof(file))
				{
					Immagine_t immagine = { 0 };
					int esito = fread(&immagine, sizeof(Immagine_t), 1, file);

					if (esito != 0)
					{
						if (strcmp(nomeUtente, immagine.nomeUtente) == 0)
						{
							if (strcmp(buffer, immagine.titolo) == 0)
							{
								bool ripeti = true;
								bool indietro = false;
								do
								{
									indietro = false;
									errore = false;

									green();
									printf("\n\nScegli il campo da modificare: ");
									reset();
									printf("\n\n0. Indietro\n1. Titolo\n2. Categoria\n3. Tags\n");
									green();
									printf("->");
									reset();
									
									unsigned int scelta;
									if (scanf("%u", &scelta) == 1)
									{
										SvuotaInput();
										switch (scelta)
										{
										case 0:
											indietro = true;
											ripeti = false;
											break;
										case 1:
											do
											{
												system("cls");
												errore = false;

												printf("Il titolo attuale e': %s\n", immagine.titolo);
												green();
												printf("Inserisci il nuovo titolo: ");
												reset();

												scanf("%[^\n]100", buffer);
												SvuotaInput();

												// Controlla che non contenga simboli
												errore = ContieneSimboli(buffer, true);

												// Altrimenti procedi
												if (!errore)
												{
													AssegnaStringa(immagine.titolo, buffer, true);
													green();
													printf("Operazione effettuata!\n\n");
													reset();
													system("pause");
												}
											} while (errore);

											break;
										case 2:
											do
											{
												errore = false;
												system("cls");

												printf("La categoria attuale e': %s\n\n", immagine.categoria);
												printf("Le categorie disponibili sono: \n\n");
												StampaCategorieDisponibili();

												green();
												printf("\n\nInserisci la nuova categoria: ");
												reset();
												InserisciCategoriaModifica(&immagine);

												green();
												printf("Operazione effettuata!\n\n");
												reset();
												system("pause");
											} while (errore);

											break;
										case 3:
											errore = false;
											system("cls");

											printf("I tag attuali sono: ");
											StampaTagsImmagine(immagine);

											// Stampa i tags disponibili
											printf("I tags disponibili sono:\n\n");
											StampaTagsDisponibili();

											// Selezione dei tags
											InserisciTagsModifica(&immagine);

											green();
											printf("Operazione effettuata!\n\n");
											reset();
											system("pause");

											break;
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
								} while (ripeti);

								if (!indietro)
								{
									// Salva le modifiche sul file
									fseek(file, -(int)sizeof(Immagine_t), SEEK_CUR);
									fwrite(&immagine, sizeof(Immagine_t), 1, file);
									return true;
								}
								else
									return false;
							}
						}
					}
					else
					{
						red();
						puts("\nNon è stata trovata nessuna immagine corrispondente al titolo inserito!");
						reset();
						errore = true;
						system("pause");
					}
				}
			}
		}
	} while (errore);
	return false;
}

void StampaTagsImmagine(Immagine_t immagine)
{
	for (size_t i = 0; i < MAX_TAGS; i++)
	{
		printf("%s ", immagine.tags[i]);
	}
	printf("\n");
}

void StampaCategorieDisponibili()
{
	for (size_t i = 0; i < NUM_CATEGORIE; i++)
	{
		if (i % 2 == 0)
			printf("%d. %-30s", i + 1, categoria[i]);
		else
			printf("%d. %-30s\n", i + 1, categoria[i]);
	}
}

void StampaTagsDisponibili()
{
	for (size_t i = 0; i < NUM_TAGS; i++)
	{
		if (i % 2 == 0)
			printf("%d. %-30s", i + 1, tags[i]);
		else
			printf("%d. %-30s\n", i + 1, tags[i]);
	}
}

void InserisciTagsModifica(Immagine_t* immagine)
{
	bool errore = false;

	size_t j = 0;
	for (size_t i = 3; i > 0; i--)
	{
		do
		{
			errore = false;
			green();
			printf("\n\nInserire il numero del tag scelto (%d scelte rimanenti - Inserire 0 per terminare): ", i);
			reset();

			unsigned int tagScelto;
			if (scanf("%u", &tagScelto) == 1)
			{
				SvuotaInput();
				if (tagScelto >= 1 && tagScelto <= NUM_TAGS)
				{
					for (size_t l = 0; l < MAX_TAGS; l++)
					{
						if (strcmp(immagine->tags[l], tags[tagScelto - 1]) == 0)
						{
							StampaErrore("Errore! Non puoi scegliere un tag che hai gia' scelto!");
							errore = true;
						}
					}
					if (!errore)
					{
						AssegnaStringa(immagine->tags[j], tags[tagScelto - 1], false);
						j++;
					}
				}
				else if (tagScelto == 0)
				{
					if (i == MAX_TAGS)
					{
						errore = true;
						StampaErrore("Errore! Selezionare almeno un tag!");
					}
					else
						i = 1;
					// Esci dal ciclo
				}
				else
				{
					errore = true;
					StampaErrore("Errore! Inserire un'opzione valida!");
				}
			}
			else
			{
				SvuotaInput();
				errore = true;
				StampaErrore("Errore! Sono ammessi solo numeri!");
			}
		} while (errore);
	}
}

void InserisciCategoriaModifica(Immagine_t* immagine)
{
	bool errore = false;
	do
	{
		errore = false;
		unsigned int categoriaScelta;
		if (scanf("%u", &categoriaScelta) == 1)
		{
			SvuotaInput();
			if (categoriaScelta >= 1 && categoriaScelta <= NUM_CATEGORIE)
			{
				AssegnaStringa(immagine->categoria, categoria[categoriaScelta - 1], false);
			}
			else
			{
				errore = true;
				StampaErrore("Errore! Inserire un'opzione valida!");
			}
		}
		else
		{
			SvuotaInput();
			errore = true;
			StampaErrore("Errore! Sono ammessi solo numeri!");
		}
	} while (errore);
}

void InserisciTagsCaricamento(Immagine_t** immagine)
{
	bool errore = false;

	size_t j = 0;
	for (size_t i = 3; i > 0; i--)
	{
		do
		{
			errore = false;
			green();
			printf("\n\nInserire il numero del tag scelto (%d scelte rimanenti - Inserire 0 per terminare): ", i);
			reset();

			unsigned int tagScelto;
			if (scanf("%u", &tagScelto) == 1)
			{
				SvuotaInput();
				if (tagScelto >= 1 && tagScelto <= NUM_TAGS)
				{
					for (size_t l = 0; l < MAX_TAGS; l++)
					{
						if (strcmp((*immagine)->tags[l], tags[tagScelto - 1]) == 0)
						{
							StampaErrore("Errore! Non puoi scegliere un tag che hai gia' scelto!");
							errore = true;
						}
					}
					if (!errore)
					{
						AssegnaStringa((*immagine)->tags[j], tags[tagScelto - 1], false);
						j++;
					}
				}
				else if (tagScelto == 0)
				{
					if (i == MAX_TAGS)
					{
						errore = true;
						StampaErrore("Errore! Selezionare almeno un tag!");
					}
					else
						i = 1;
					// Esci dal ciclo
				}
				else
				{
					errore = true;
					StampaErrore("Errore! Inserire un'opzione valida!");
				}
			}
			else
			{
				SvuotaInput();
				errore = true;
				StampaErrore("Errore! Sono ammessi solo numeri!");
			}
		} while (errore);
	}
}

void InserisciCategoriaCaricamento(Immagine_t** immagine)
{
	bool errore = false;
	do
	{
		errore = false;
		unsigned int categoriaScelta;
		if (scanf("%u", &categoriaScelta) == 1)
		{
			SvuotaInput();
			if (categoriaScelta >= 1 && categoriaScelta <= NUM_CATEGORIE)
			{
				AssegnaStringa((*immagine)->categoria, categoria[categoriaScelta - 1], false);
			}
			else
			{
				errore = true;
				StampaErrore("Errore! Inserire un'opzione valida!");
			}
		}
		else
		{
			SvuotaInput();
			errore = true;
			StampaErrore("Errore! Sono ammessi solo numeri!");
		}
	} while (errore);
}

bool StampaImmaginiCaricate(FILE* file, const char nomeUtente[])	
{
	bool trovato = false;	 // trovato = c'è almeno un'immagine caricata dall'utente?								
	// Stampa le immagini caricate dall'utente
	
	StampaTitolo("****************\nI TUOI UPLOADS\n****************\n");
	while (!feof(file))
	{
		Immagine_t immagine = { 0 };
		int esito = fread(&immagine, sizeof(Immagine_t), 1, file);
		if (esito != 0)
		{
			if (strcmp(nomeUtente, immagine.nomeUtente) == 0)
			{
				printf("\n\nTitolo: %s\nCategoria: %s", immagine.titolo, immagine.categoria);
				trovato = true;
			}
		}
	}

	if (!trovato)
	{
		StampaErrore("Non hai ancora caricato immagini!");
	}

	return trovato;
}

bool RimuoviImmagine(FILE* file, const char nomeUtente[])
{
	bool errore = false;

	do
	{
		errore = false;

		system("cls");
		rewind(file);

		bool trovato = StampaImmaginiCaricate(file, nomeUtente); // trovato = c'è almeno un'immagine caricata dall'utente?

		if (trovato)
		{
			rewind(file);

			// Inserimento titolo dell'immagine da rimuovere
			char buffer[MAX_BUFFER] = { 0 };
			green();
			printf("\n\nInserisci il titolo dell'immagine da rimuovere: ");
			reset();

			scanf("%[^\n]100", buffer);
			SvuotaInput();

			buffer[0] = toupper(buffer[0]);

			// Controlla che non contenga simboli
			errore = ContieneSimboli(buffer, true);

			if (!errore)
			{
				while (!feof(file))
				{
					Immagine_t immagine = { 0 };
					Immagine_t immagineVuota = { 0 };
					int esito = fread(&immagine, sizeof(Immagine_t), 1, file);

					if (esito != 0)
					{
						if (strcmp(nomeUtente, immagine.nomeUtente) == 0)
						{
							if (strcmp(buffer, immagine.titolo) == 0)
							{
								fseek(file, -(int)sizeof(Immagine_t), SEEK_CUR);
								if (fwrite(&immagineVuota, sizeof(Immagine_t), 1, file) != 0)
									return true;
								else
									return false;
							}
						}
					}
					else
					{
						StampaErrore("Non e' stata trovata alcuna immagina corrispondente al titolo inserito!");
						errore = true;
					}
				}
			}
		}
	} while (errore);

	return false;
}

bool VisualizzaImmagineCreatore(FILE* file, const char nomeUtente[])
{
	bool errore = false;
	do
	{
		errore = false;

		system("cls");
		rewind(file);

		bool trovato = StampaImmaginiCaricate(file, nomeUtente); // trovato = c'è almeno un'immagine caricata dall'utente?

		if (trovato)
		{

			rewind(file);

			// Inserimento titolo dell'immagine da modificare
			char buffer[MAX_BUFFER] = { 0 };
			green();
			printf("\n\nInserisci il titolo dell'immagine da visualizzare: ");
			reset();

			scanf("%[^\n]100", buffer);
			SvuotaInput();

			buffer[0] = toupper(buffer[0]);

			// Controlla che non contenga simboli
			errore = ContieneSimboli(buffer, true);

			if (!errore)
			{
				while (!feof(file))
				{
					Immagine_t immagine = { 0 };
					int esito = fread(&immagine, sizeof(Immagine_t), 1, file);

					if (esito != 0)
					{
						if (strcmp(nomeUtente, immagine.nomeUtente) == 0)
						{
							if (strcmp(buffer, immagine.titolo) == 0)
							{
								system("cls");
								printf("Titolo: %s\nCategoria: %s\nTags: ", immagine.titolo, immagine.categoria);
								StampaTagsImmagine(immagine);
								printf("Nome del file: %s\nValutazione media: %.1f\nNumero di download: %u\nDimensione: %.1f MB\nRisoluzione: %u x %u\nData di caricamento: %u/%u/%u\n\n", immagine.nomeFile, immagine.valutazioneMedia, immagine.numDownload, immagine.dimensione, immagine.risoluzione.x, immagine.risoluzione.y, immagine.dataCaricamento.giorno, immagine.dataCaricamento.mese, immagine.dataCaricamento.anno);
								return true;
							}
						}
					}
					else
					{
						StampaErrore("Non e' stata trovata alcuna immagine corrispondente al titolo inserito!");
						errore = true;
					}
				}
			}
		}
	} while (errore);
	return false;
}

bool RicercaCategoria(FILE* file)
{
	bool errore = false;
	do
	{
		errore = false;

		system("cls");
		rewind(file);

		StampaCategorieDisponibili();

		green();
		printf("\n\nSeleziona la categoria che vuoi ricercare: ");
		reset();
		unsigned int categoriaScelta;
		if (scanf("%u", &categoriaScelta) == 1)
		{
			SvuotaInput();
			if (categoriaScelta >= 1 && categoriaScelta <= NUM_CATEGORIE)
			{
				printf("\n");

				bool trovato = false;

				while (!feof(file))
				{
					Immagine_t immagine = { 0 };
					int esito = fread(&immagine, sizeof(Immagine_t), 1, file);

					if (esito != 0)
					{
						// Stampa tutte le immagini con quella categoria
						if (strcmp(categoria[categoriaScelta - 1], immagine.categoria) == 0)
						{
							trovato = true;
							printf("Titolo: %s\nCategoria: %s\nAutore: %s\nNumero di downloads: %u\n\n", immagine.titolo, immagine.categoria, immagine.nomeUtente, immagine.numDownload);
						}
					}
				}

				if (!trovato)
				{
					StampaErrore("Non sono ancora state caricate immagini con la suddetta categoria!");
				}

				return trovato;
			}
			else
			{
				errore = true;
				StampaErrore("Errore! Inserire un'opzione valida!");
			}
		}
		else
		{
			SvuotaInput();
			errore = true;
			StampaErrore("Sono ammessi solo numeri!");
		}
	} while (errore);
	return false;
}

bool RicercaTags(FILE* file)
{
	bool errore = false;
	do
	{
		errore = false;

		system("cls");
		rewind(file);

		StampaTagsDisponibili();

		green();
		printf("\n\nSeleziona il tag che vuoi ricercare: ");
		reset();
		unsigned int tagScelto;
		if (scanf("%u", &tagScelto) != 0)
		{
			SvuotaInput();
			if (tagScelto >= 1 && tagScelto <= NUM_TAGS)
			{
				printf("\n");

				bool trovato = false;

				while (!feof(file))
				{
					Immagine_t immagine = { 0 };
					int esito = fread(&immagine, sizeof(Immagine_t), 1, file);

					if (esito != 0)
					{
						// Stampa tutte le immagini con quel tag
						for (size_t i = 0; i < MAX_TAGS; i++)
						{
							if (strcmp(tags[tagScelto - 1], immagine.tags[i]) == 0)
							{
								trovato = true;
								printf("Titolo: %s\nCategoria: %s\nAutore: %s\nNumero di downloads: %u\n\n", immagine.titolo, immagine.categoria, immagine.nomeUtente, immagine.numDownload);
							}
						}

					}
				}

				if (!trovato)
				{
					StampaErrore("Non sono ancora state caricate immagini con il suddetto tag!");
				}

				return trovato;
			}
			else
			{
				errore = true;
				StampaErrore("Errore! Inserire un'opzione valida!");
			}
		}
		else
		{
			SvuotaInput();
			errore = true;
			StampaErrore("Sono ammessi solo numeri!");
		}
	} while (errore);
	return false;
}

bool VisualizzaImmagine(FILE* file, char autoreImmagine[])
{
	bool errore = false;
	do
	{
		errore = false;
		
		rewind(file);

		// Inserimento titolo dell'immagine da visualizzare
		char buffer[MAX_BUFFER] = { 0 };
		green();
		printf("\n\nInserisci il titolo dell'immagine da visualizzare: ");
		reset();

		scanf("%[^\n]100", buffer);
		SvuotaInput();

		buffer[0] = toupper(buffer[0]);

		// Controlla che non contenga simboli
		errore = ContieneSimboli(buffer, true);

		if (!errore)
		{
			while (!feof(file))
			{
				Immagine_t immagine = { 0 };
				int esito = fread(&immagine, sizeof(Immagine_t), 1, file);

				if (esito != 0)
				{
					if (strcmp(buffer, immagine.titolo) == 0)
					{
						// Passo al menu l'autore dell'immagine
						strcpy(autoreImmagine, immagine.nomeUtente);
						system("cls");
						printf("Titolo: %s\nAutore: %s\nCategoria: %s\nTags: ", immagine.titolo, immagine.nomeUtente, immagine.categoria);
						StampaTagsImmagine(immagine);
						printf("Nome del file: %s\nNumero di valutazioni: %u\nValutazione media: %.1f\nNumero di download: %u\nDimensione: %.1f MB\nRisoluzione: %u x %u\nData di caricamento: %u/%u/%u\n\n", immagine.nomeFile, immagine.numValutazioni, immagine.valutazioneMedia, immagine.numDownload, immagine.dimensione, immagine.risoluzione.x, immagine.risoluzione.y, immagine.dataCaricamento.giorno, immagine.dataCaricamento.mese, immagine.dataCaricamento.anno);
						do
						{
							green();
							printf("Vuoi scaricarla? Digita Y o N: ");
							reset();

							char scelta = { 0 };
							
							if (scanf("%c", &scelta) == 1)
							{
								SvuotaInput();
								scelta = toupper(scelta);

								if (scelta != 'Y' && scelta != 'N')
								{
									errore = true;
									StampaErrore("Errore! Inserire Y o N!");
								}
								else if (scelta == 'Y')
									return true;
								else if (scelta == 'N')
									return false;
							}
							else
							{
								SvuotaInput();
								errore = true;
								StampaErrore("Errore! Sono ammessi solo caratteri!");
							}
						} while (errore);
					}
				}
				else
				{
					StampaErrore("Errore! Non e' stata trovata alcuna immagine corrispondente al titolo inserito!");
					errore = true;
				}
			}
		}
	} while (errore);
	return false;
}

unsigned int ValutaImmagine(FILE* file, const char nomeUtente[])
{
	bool errore = false;
	unsigned int valutazione;

	do
	{
		errore = false;

		Immagine_t immagine = { 0 };
		
		fseek(file, -(int)sizeof(Immagine_t), SEEK_CUR);
		fread(&immagine, sizeof(Immagine_t), 1, file);

		immagine.numDownload++;

		FILE* fileValutazioni = ApriFile(PERCORSO_FILE_VALUTAZIONI);

		bool giaValutata = false;

		// Controllo se l'immagine è stata già valutata
		while (!feof(fileValutazioni) && !giaValutata)
		{
			Valutazione_t valutazioneStruct;
			int esito = fread(&valutazioneStruct, sizeof(Valutazione_t), 1, fileValutazioni);

			if (esito != 0)
			{
				if (strcmp(valutazioneStruct.nomeUtenteValutatore, nomeUtente) == 0 && immagine.id == valutazioneStruct.idImmagineValutata)
				{
					fseek(file, -(int)sizeof(Immagine_t), SEEK_CUR);
					fwrite(&immagine, sizeof(Immagine_t), 1, file);
					giaValutata = true;
				}
			}
		}

		// Assegno 0 a valutazione per far sapere al programma che è stata già valutata
		valutazione = 0;
		fclose(fileValutazioni);



		if (!giaValutata)
		{
			green();
			printf("\n\nQuanto vuoi valutare quest'immagine? Inserire un numero da 1 a 5 (intero): ");
			reset();

			if (scanf("%u", &valutazione) == 1)
			{
				SvuotaInput();
				if (valutazione >= 1 && valutazione <= 5)
				{
					float sommaValutazioni = immagine.valutazioneMedia * immagine.numValutazioni; 
					immagine.numValutazioni++;
					sommaValutazioni += valutazione;
					immagine.valutazioneMedia = sommaValutazioni / immagine.numValutazioni;

					fseek(file, -(int)sizeof(Immagine_t), SEEK_CUR);
					fwrite(&immagine, sizeof(Immagine_t), 1, file);

				}
				else
				{
					errore = true;
					StampaErrore("Errore! Inserire un numero tra 1 e 5!");
				}
			}
			else
			{
				SvuotaInput();
				errore = true;
				StampaErrore("Errore! Inserire un numero tra 1 e 5!");
			}
		}
		else
		{
			StampaErrore("Errore! L'immagine e' gia' stata valutata! Non puoi valutarla due volte!");
		}
	} while (errore);

	return valutazione;
}

void SalvaValutazione(FILE* fileImmagine, const char nomeUtente[], unsigned int valutazione)
{
	Immagine_t immagine = { 0 };

	FILE* fileCreatore = ApriFile(PERCORSO_FILE_CREATORI);

	// Prelevo l'ID dell'immagine valutata
	fseek(fileImmagine, -(int)sizeof(Immagine_t), SEEK_CUR);
	fread(&immagine, sizeof(Immagine_t), 1, fileImmagine);


	Valutazione_t valutazioneStruct = { 0 };

	// Assegno i valori
	strcpy(valutazioneStruct.nomeUtenteValutatore, nomeUtente);
	valutazioneStruct.idImmagineValutata = immagine.id;
	valutazioneStruct.valutazione = valutazione;

	// Salvo sul file
	FILE* fileValutazioni = ApriFile(PERCORSO_FILE_VALUTAZIONI);

	fseek(fileValutazioni, 0, SEEK_END);
	fwrite(&valutazioneStruct, sizeof(Valutazione_t), 1, fileValutazioni);
	fclose(fileValutazioni);
}

size_t CaricaArrayImmagini(FILE* file, Immagine_t immagine[])
{
	file = ApriFile(PERCORSO_FILE_IMMAGINI);

	size_t i = 0;
	while (!feof(file) && i < MAX_BUFFER)
	{
		fread(&immagine[i], sizeof(Immagine_t), 1, file);
		if (immagine[i].id != 0)
			i++;
	}

	fclose(file);
	return i;
}

void ScambiaImmagine(Immagine_t *immagineA, Immagine_t *immagineB)
{
	Immagine_t temp = *immagineA;
	*immagineA = *immagineB;
	*immagineB = temp;
}

void BubbleSortImmagine(Immagine_t immagine[], size_t n, const bool criterio)
{
	bool scambiato = false;

	if (criterio)
	{
		do
		{
			scambiato = false;
			for (size_t i = 0; i < n - 1; i++)
			{
				if (immagine[i].numDownload < immagine[i + 1].numDownload)
				{
					ScambiaImmagine(&immagine[i], &immagine[i + 1]);
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
				if (immagine[i].valutazioneMedia < immagine[i + 1].valutazioneMedia)
				{
					ScambiaImmagine(&immagine[i], &immagine[i + 1]);
					scambiato = true;
				}
			}
		} while (scambiato);
	}
}