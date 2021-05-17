#include "Immagini.h"

const char* formato[NUM_FORMATI] = { ".jpeg", ".jpg", ".png", ".bmp", ".gif", ".ico", ".svg", ".webp" };
const char* tipologia[NUM_FORMATI] = { "Immagine JPEG", "Immagine JPG", "Immagine PNG", "Bitmap", "GIF", "Icona", "Vettoriale", "Immagine compressa" };
const char* categoria[NUM_CATEGORIE] = { "Cibo", "Lavoro", "Moda e Design", "Natura e Animali", "Paesaggi", "Scienza e Spazio", "Sport e Fitness" };
const char* tags[NUM_TAGS] = { "Colazione", "Pranzo", "Cena", "Capo", "Collega", "Scrivania", "Arte", "Matrimonio", "Sfilata", "Cane", "Gatto",
                               "Mare", "Montagne", "Alpi", "Lago", "Luna", "Marte", "Razzo", "Calcio", "Palestra", "Olimpiadi" };

void SalvaDatiImmagine(FILE* file, Immagine_t* immagine)
{
	fputs("titolo:", file);
	fputs(immagine->titolo, file);
	fputs("\n", file);
	free(immagine->titolo);

	fputs("autore:", file);
	fputs(immagine->nomeUtente, file);
	fputs("\n", file);

	fputs("categoria:", file);
	fputs(immagine->categoria, file);
	fputs("\n", file);
	free(immagine->categoria);

	fputs("tags:", file);
	for (size_t i = 0; i < MAX_TAGS; i++)
	{
		fprintf(file, "%s ",immagine->tags[i]);
		free(immagine->tags[i]);
	}
	fputs("\n", file);

	fputs("nomeFile:", file);
	fputs(immagine->nomeFile, file);
	fputs("\n", file);
	free(immagine->nomeFile);

	fputs("formato:", file);
	fputs(immagine->formato, file);
	fputs("\n", file);
	free(immagine->formato);

	fputs("tipologia:", file);
	fputs(immagine->tipologia, file);
	fputs("\n", file);
	free(immagine->tipologia);

	fputs("dimensione:", file);
	fprintf(file, "%.1f\n", immagine->dimensione);

	fputs("risoluzione.x:", file);
	fprintf(file, "%u\n", immagine->risoluzione.x);

	fputs("risoluzione.y:", file);
	fprintf(file, "%u\n", immagine->risoluzione.y);

	fputs("dataCaricamento:", file);
	fprintf(file, "%u/%u/%u\n", immagine->dataCaricamento.giorno, immagine->dataCaricamento.mese, immagine->dataCaricamento.anno);

	fputs("valutazioneMedia:", file);
	fprintf(file, "%.2f\n\n", immagine->valutazioneMedia);
}