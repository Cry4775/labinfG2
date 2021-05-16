#include "Utenti.h"

bool ControllaNomeUtente(FILE* file, char buffer[])
{
    char buf[BUFSIZ];
    char* ptr = NULL;

    while (fgets(buf, sizeof(buf), file)) // Leggo ogni riga del file su buf
    {
        ptr = buf; // Assegno a ptr la stringa appena copiata dal file (buf)
        while ((ptr = strtok(ptr, ":")) != NULL) // Quando trova un : (delimitatore) dividi la stringa
        {
            if (strcmp(ptr, "nomeUtente") == 0)
            {
                ptr = strtok(NULL, " \n\0"); // Richiedi il token successivo (ciò che sta dopo user: )
                if (strcmp(ptr, buffer) == 0) // Compara la stringa contrassegnata da user con la stringa memorizzata nel buffer
                    return true;  // Se corrisponde, ritorna vero
            }
            ptr = NULL;
        }
    }
    return false;
}

bool ControllaPassword(FILE* file, char buffer[])
{
    char buf[BUFSIZ];
    char* ptr = NULL;

    while (fgets(buf, sizeof(buf), file)) // Leggo ogni riga del file su buf
    {
        ptr = buf; // Assegno a ptr la stringa appena copiata dal file (buf)
        while ((ptr = strtok(ptr, ":")) != NULL) // Quando trova un : (delimitatore) dividi la stringa
        {
            ptr = strtok(NULL, " \n\0"); // Richiedi il token successivo (ciò che sta dopo password: )
            if (strcmp(ptr, buffer) == 0)
                return true;
            else return false;
        }
    }
    return false;
}

void SalvaDatiCreatore(FILE* file, Creatore_t* creatore)
{
	fputs("nomeUtente:", file);
	fputs(creatore->nomeUtente, file);
	fputs("\n", file);
	free(creatore->nomeUtente);

	fputs("password:", file);
	fputs(creatore->password, file);
	fputs("\n", file);
	free(creatore->password);

	fputs("nome:", file);
	fputs(creatore->nome, file);
	fputs("\n", file);
	free(creatore->nome);

	fputs("cognome:", file);
	fputs(creatore->cognome, file);
	fputs("\n", file);
	free(creatore->cognome);

	fputs("sesso:", file);
	fputc(creatore->sesso, file);
	fputs("\n", file);

	fputs("professione:", file);
	fputs(creatore->professione, file);
	fputs("\n", file);
	free(creatore->professione);

	fputs("nazionalita:", file);
	fputs(creatore->nazionalita, file);
	fputs("\n", file);
	free(creatore->nazionalita);

	fputs("dataNascita:", file);
	fprintf(file, "%u/%u/%u\n", creatore->dataNascita.giorno, creatore->dataNascita.mese, creatore->dataNascita.anno);

	fputs("dataIscrizione:", file);
	fprintf(file, "%u/%u/%u\n", creatore->dataIscrizione.giorno, creatore->dataIscrizione.mese, creatore->dataIscrizione.anno);

	fputs("numImmagini:", file);
	fprintf(file, "%u\n", creatore->numImmagini);

	fputs("numDownloadTot:", file);
	fprintf(file, "%u\n", creatore->numDownloadTot);

	fputs("mediaValutazioni:", file);
	fprintf(file, "%f\n\n", creatore->mediaValutazioni);
}

void SalvaDatiUtilizzatore(FILE* file, Utilizzatore_t* utilizzatore)
{
	fputs("nomeUtente:", file);
	fputs(utilizzatore->nomeUtente, file);
	fputs("\n", file);
	free(utilizzatore->nomeUtente);

	fputs("password:", file);
	fputs(utilizzatore->password, file);
	fputs("\n", file);
	free(utilizzatore->password);

	fputs("nome:", file);
	fputs(utilizzatore->nome, file);
	fputs("\n", file);
	free(utilizzatore->nome);

	fputs("cognome:", file);
	fputs(utilizzatore->cognome, file);
	fputs("\n", file);
	free(utilizzatore->cognome);

	fputs("sesso:", file);
	fputc(utilizzatore->sesso, file);
	fputs("\n", file);

	fputs("professione:", file);
	fputs(utilizzatore->professione, file);
	fputs("\n", file);
	free(utilizzatore->professione);

	fputs("nazionalita:", file);
	fputs(utilizzatore->nazionalita, file);
	fputs("\n", file);
	free(utilizzatore->nazionalita);

	fputs("dataNascita:", file);
	fprintf(file, "%u/%u/%u\n", utilizzatore->dataNascita.giorno, utilizzatore->dataNascita.mese, utilizzatore->dataNascita.anno);

	fputs("dataIscrizione:", file);
	fprintf(file, "%u/%u/%u\n", utilizzatore->dataIscrizione.giorno, utilizzatore->dataIscrizione.mese, utilizzatore->dataIscrizione.anno);

	fputs("numValutazioni:", file);
	fprintf(file, "%u\n", utilizzatore->numValutazioni);

	fputs("numDownloadTot:", file);
	fprintf(file, "%u\n\n", utilizzatore->numDownloadTot);
}