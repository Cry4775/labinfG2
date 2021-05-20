#include "Immagini.h"

const char* formato[NUM_FORMATI] = { ".jpeg", ".jpg", ".png", ".bmp", ".gif", ".ico", ".svg", ".webp" };
const char* tipologia[NUM_FORMATI] = { "Immagine JPEG", "Immagine JPG", "Immagine PNG", "Bitmap", "GIF", "Icona", "Vettoriale", "Immagine compressa" };
const char* categoria[NUM_CATEGORIE] = { "Cibo", "Lavoro", "Moda e Design", "Natura e Animali", "Paesaggi", "Scienza e Spazio", "Sport e Fitness" };
const char* tags[NUM_TAGS] = { "Colazione", "Pranzo", "Cena", "Capo", "Collega", "Scrivania", "Arte", "Matrimonio", "Sfilata", "Cane", "Gatto",
                               "Mare", "Montagne", "Alpi", "Lago", "Luna", "Marte", "Razzo", "Calcio", "Palestra", "Olimpiadi" };

void InserisciDatiImmagine(Immagine_t* immagine, char nomeUtente[])
{
	// Inserimento TITOLO
	bool errore = false;

	do
	{
		SvuotaInputGetChar();
		errore = false;
		system("cls");
		printf("Inserire il titolo dell'immagine: ");

		char buffer[MAX_BUFFER] = { 0 };
		fgets(buffer, 100, stdin);
		SvuotaInputFGets(buffer);

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
		for (size_t i = 0; i < NUM_CATEGORIE; i++)
		{
			if (i % 2 == 0)
				printf("%d. %-30s", i + 1, categoria[i]);
			else
				printf("%d. %-30s\n", i + 1, categoria[i]);
		}
		printf("\n\nInserire il numero della categoria scelta: ");

		unsigned int categoriaScelta;
		scanf("%u", &categoriaScelta);

		if (categoriaScelta >= 1 && categoriaScelta <= NUM_CATEGORIE)
		{

			AssegnaStringa(immagine->categoria, categoria[categoriaScelta - 1], false);
		}
		else
		{
			errore = true;
			printf("Errore! Inserire un'opzione valida!");
			InvioPerContinuare();
		}

	} while (errore);

	// Inserimento TAGS
	do
	{
		printf("\n");
		errore = false;
		for (size_t i = 0; i < NUM_TAGS; i++)
		{
			if (i % 2 == 0)
				printf("%d. %-30s", i + 1, tags[i]);
			else
				printf("%d. %-30s\n", i + 1, tags[i]);
		}

		size_t j = 0;
		for (size_t i = 3; i > 0; i--)
		{
			do
			{
				// Bisogna aggiungere il controllo per la selezione di tags uguali
				errore = false;
				printf("\n\nInserire il numero del tag scelto (%d scelte rimanenti - Inserire 0 per terminare): ", i);

				unsigned int tagScelto;
				scanf("%u", &tagScelto);

				if (tagScelto >= 1 && tagScelto <= NUM_TAGS)
				{
					AssegnaStringa(immagine->tags[j], tags[tagScelto - 1], false);
					j++;
				}
				else if (tagScelto == 0)
				{
					if (i == MAX_TAGS)
					{
						errore = true;
						printf("\nErrore! Selezionare almeno un tag!\n");
					}
					else
						i = 1;
					// Esci dal ciclo
				}
				else
				{
					errore = true;
					printf("Errore! Inserire un'opzione valida!");
					InvioPerContinuare();
				}
			} while (errore);
		}

	} while (errore);

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

void SalvaDatiImmagine(FILE* file, Immagine_t* immagine)
{
	Immagine_t precImmagine = { 0 };																			//rendi l'essagnazione una funzione e aggiungi il controllo di id = 0 tra i record
	fseek(file, -(int)sizeof(Immagine_t), SEEK_END);
	fread(&precImmagine, sizeof(Immagine_t), 1, file);
	immagine->id = precImmagine.id + 1;
	fwrite(&*immagine, sizeof(Immagine_t), 1, file);
}

void ModificaImmagini(FILE* file, char nomeUtente[])
{
	
	while (!feof(file))
	{
		Immagine_t immagine = { 0 };
		int esito = fread(&immagine, sizeof(Immagine_t), 1, file);
		if (esito != 0)
		{
			if (strcmp(nomeUtente, immagine.nomeUtente) == 0)
			{
				printf("\nIMMAGINI CARICATE:");
				printf("\nTitolo: %s\nCategoria: %s", immagine.titolo, immagine.categoria);
			}
			else 
				puts("\nNon hai ancora caricato immagini!");
		}
	}
	rewind(file);
	bool errore;
	do
	{
		char buffer[MAX_BUFFER];
		SvuotaInputFGets(buffer);
		printf("\nInserisci il titolo dell'immagine da modificare: ");
		fgets(buffer, 100, stdin);
		SvuotaInputFGets(buffer);

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
						printf("\nSCEGLI IL CAMPO DA MODIFICARE:");
						printf("\n1. Titolo\n2. Categoria\n3. Tags\n");
						int scelta;
						scanf("%d", &scelta);

						switch (scelta)
						{
						case 1:
							printf("\nIl titolo attuale è: %s", immagine.titolo);
							printf("\nInserisci il nuovo titolo: ");
							fgets(buffer, 100, stdin);
							SvuotaInputFGets(buffer);
							AssegnaStringa(immagine.titolo, buffer, true);

							break;
						case 2:
							printf("\nLa categoria attuale è: %s", immagine.categoria);

							printf("\nLe categorie disponibili sono: ");
							for (size_t i = 0; i < NUM_CATEGORIE; i++)
							{
								if (i % 2 == 0)
									printf("%d. %-30s", i + 1, categoria[i]);
								else
									printf("%d. %-30s\n", i + 1, categoria[i]);
							}


							printf("\nInserisci la nuova categoria: ");
							bool errore = false;
							do
							{
								unsigned int categoriaScelta;
								scanf("%u", &categoriaScelta);

								if (categoriaScelta >= 1 && categoriaScelta <= NUM_CATEGORIE)
								{
									AssegnaStringa(immagine.categoria, categoria[categoriaScelta - 1], false);
								}
								else
								{
									errore = true;
									printf("Errore! Inserire un'opzione valida!");
									InvioPerContinuare();
								}
							} while (errore);
							break;
						case 3:
							printf("\nI tag attuali sono: ");
							for (size_t i = 0; i < MAX_TAGS; i++)
							{
								printf("%s ", immagine.tags[i]);
							}
							printf("\n");


							// Stampa i tags disponibili
							printf("I tags disponibili sono:\n");
							errore = false;
							for (size_t i = 0; i < NUM_TAGS; i++)
							{
								if (i % 2 == 0)
									printf("%d. %-30s", i + 1, tags[i]);
								else
									printf("%d. %-30s\n", i + 1, tags[i]);
							}

							// Selezione dei tags
							size_t j = 0;
							for (size_t i = 3; i > 0; i--)
							{
								do
								{
									// Bisogna aggiungere il controllo per la selezione di tags uguali
									errore = false;
									printf("\n\nInserire il numero del tag scelto (%d scelte rimanenti - Inserire 0 per terminare): ", i);

									unsigned int tagScelto;
									scanf("%u", &tagScelto);

									if (tagScelto >= 1 && tagScelto <= NUM_TAGS)
									{
										AssegnaStringa(immagine.tags[j], tags[tagScelto - 1], false);
										j++;
									}
									else if (tagScelto == 0)
									{
										if (i == MAX_TAGS)
										{
											errore = true;
											printf("\nErrore! Selezionare almeno un tag!\n");
										}
										else
											i = 1;
										// Esci dal ciclo
									}
									else
									{
										errore = true;
										printf("Errore! Inserire un'opzione valida!");
										InvioPerContinuare();
									}
								} while (errore);
							}
							break;
						default:
							printf("Errore! Selezionare un'opzione valida!");
							break;
						}

						fseek(file, -(int)sizeof(Immagine_t), 1, SEEK_CUR);
						fwrite(&immagine, sizeof(Immagine_t), 1, file);
					}
				}
				else
					puts("\nNon è stata trovata nessuna immagine corrispondente al titolo inserito");

			}
		}
	} while (errore);
	
}

void VisualizzaImmagine(FILE* file, Immagine_t immagine)
{
	printf("\nTitolo: %s\nCategoria: %s", immagine.titolo, immagine.categoria);
}